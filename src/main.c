/* *** COPYRIGHT (C)2014-2015 Planeboy Games(Austin Hull). NetDownload and PNG-related portions of code provided with permission from: https://github.com/pebble-examples/pebble-faces. SteamPebble AND Planeboy Games ARE NOT AFFILIATED WITH Steam OR Valve Software IN ANY WAY OR CAPACITY.
THIS FREE SOFTWARE IS OPEN-SOURCE AND IS LICENSED UNDER THE GNU General Public License v2.
TERMS AND CONDITIONS OF THE GNU General Public License v2 MAY BE OBTAINED AT: https://gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1 
FULL PROGRAMMING CODE OF THIS SOFTWARE MAY BE OBTAINED AT Github: https://github.com/austinplaneboy/SteamPebble *** */

// Core system/font libraries
#include<pebble.h>
#include<pebble_fonts.h>

// Used for data moving between JavaScript (apiCode.js) and C (main.c)
#define KEY_CURRENTNAME 0
#define KEY_REALNAME 1
#define KEY_STATE 2
#define KEY_COUNTRY 3
#define KEY_AVATAR 4
#define ID 5
  
// Char buffers, used to contain parsed-through JSON variables, to be passed to the viewer.
static char cName[33];
static char rName[33];
static char state[3];
static char country[3];
static char id[19];

static GBitmap *avatarVar;

// Used for the initial splash-screen.
static Window *window;
static TextLayer *textLayer;
static TextLayer *textLayer2;

// Window variables for the first menu screen.
static Window *mainMenuWindow;
Layer *mainMenuWinLayer;
MenuLayer *menuLayerMain;

// Window variables for secondary menu screens.
static Window *secondaryWindow;
Layer *secondaryLayer;
MenuLayer *secondaryMenuLayer;
MenuLayer *secondaryMenuLayer2;
MenuLayer *secondaryMenuLayer3;

void down_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
  //Window *window = (Window *)context;
}

// Provides data and things for button click events.
void config_provider(Window *window)
{
  window_single_click_subscribe(BUTTON_ID_SELECT, down_single_click_handler);
}

uint16_t num_rows_callback(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext)
{
  return 3;
}

void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row)
  {
    case 0:
    menu_cell_basic_draw(ctx, cell_layer, "Profile Info", NULL, NULL);
    break;
    case 1:
    menu_cell_basic_draw(ctx, cell_layer, "User Guide", NULL, NULL);
    break;
    case 2:
    menu_cell_basic_draw(ctx, cell_layer, "About", NULL, NULL);
    break;
  }
}

uint16_t num_rows_callback2(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext)
{
  return 4;
}

void draw_row_callback2(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row)
  {
    case 0:
    menu_cell_basic_draw(ctx, cell_layer, cName, NULL, NULL);
    break;
    case 1:
    menu_cell_basic_draw(ctx, cell_layer, rName, NULL, NULL);
    break;
    case 2:
    menu_cell_basic_draw(ctx, cell_layer, state, NULL, NULL);
    break;
    case 3:
    menu_cell_basic_draw(ctx, cell_layer, country, NULL, NULL);
    break;
  }
}

//Used to transition selection from main menu to secondary menu.
static void select_click_callback(MenuLayer *menuLayer, MenuIndex *cell_Index, void *callbackContext)
{
  switch(cell_Index->row)
  {
    case 0:
    window_stack_push(secondaryWindow, true);
    
    menu_layer_set_click_config_onto_window(secondaryMenuLayer, secondaryWindow);
    layer_add_child(window_get_root_layer(secondaryWindow), menu_layer_get_layer(secondaryMenuLayer));
    break;
    case 1:
    window_stack_push(secondaryWindow, true);
    break;
    case 2:
    window_stack_push(secondaryWindow, true);    
    break;
  }
}

// Set up some initialization-related variables and objects.
bool dataSuccess = false;

static void initText(Layer *window_Layer);
static void init(void);
static void deinit(void);
void bluetooth_Connection_Callback(bool connected);
//BluetoothConnectionHandler bluetoothConnect;
static void tick_handler(struct tm *tick_time, TimeUnits unitsChanged);

unsigned short int timer = 0;

// Receives messages from apiCode.js, takes JSON data and applies it to C variables.
static void inbox_received_callback(DictionaryIterator *iterator, void *context)
{
  
  Tuple *t = dict_read_first(iterator);
  
  while(t != NULL)
  {
    switch(t->key)
    {
      case KEY_CURRENTNAME:
      snprintf(cName, sizeof(cName), "%s", t->value->cstring);
      break;
      case KEY_REALNAME:
      snprintf(rName, sizeof(rName), "%s", t->value->cstring);
      break;
      case KEY_STATE:
      snprintf(state, sizeof(state), "%s", t->value->cstring);
      break;
      case KEY_COUNTRY:
      snprintf(country, sizeof(country), "%s", t->value->cstring);
      break;
      case ID:
      snprintf(id, sizeof(id), "%s", t->value->cstring);
      break;
      default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }
    
    t = dict_read_next(iterator);
  }
  
  // Loads new window, only if data is received from Steam.
  if(country != NULL)
  {
    dataSuccess = true;
    layer_set_hidden(text_layer_get_layer(textLayer2), true);
    timer = 0;
    
    
    //Creates and pushes new window for main menu to stack, and removes splash-screen from stack for performance management.
    mainMenuWindow = window_create();
    mainMenuWinLayer = window_get_root_layer(mainMenuWindow);
    //window_set_fullscreen(mainMenuWindow, true);
    window_set_background_color(mainMenuWindow, GColorWhite);
    window_stack_push(mainMenuWindow, true);
    window_stack_remove(window, false);
    
    //Secondary window parameters. Does not get pushed to screen until transition. Also, creates and attaches secondary menu layer to secondary window. //IN PROGRESS!!!//
    secondaryWindow = window_create();
    secondaryLayer = window_get_root_layer(mainMenuWindow);
    //window_set_fullscreen(secondaryWindow, true);
    window_set_background_color(secondaryWindow, GColorWhite);
    
    secondaryMenuLayer2 = menu_layer_create(GRect(0, 0, 144, 168));
    //MenuLayerCallbacks callbacks2_1 = {.draw_row = , .get_num_rows = , NULL};
    
    secondaryMenuLayer = menu_layer_create(GRect(0, 0, 144, 168));
    MenuLayerCallbacks callbacks2 = {.draw_row = (MenuLayerDrawRowCallback)draw_row_callback2, .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback2, NULL};
    menu_layer_set_callbacks(secondaryMenuLayer, NULL, callbacks2);
    //menu_layer_set_click_config_onto_window(secondaryMenuLayer, secondaryWindow);
    
    //layer_add_child(window_get_root_layer(secondaryWindow), menu_layer_get_layer(secondaryMenuLayer));
    
    //Sets configurations for button click provider.
    window_set_click_config_provider(mainMenuWindow, (ClickConfigProvider)config_provider);
    
    //Creates and initializes main menu to be attached to new main menu window.
    menuLayerMain = menu_layer_create(GRect(0, 0, 144, 168));
    MenuLayerCallbacks callbacks = {.draw_row = (MenuLayerDrawRowCallback)draw_row_callback, .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback, .select_click = (MenuLayerSelectCallback)select_click_callback};
    menu_layer_set_callbacks(menuLayerMain, NULL, callbacks);
    menu_layer_set_click_config_onto_window(menuLayerMain, mainMenuWindow);
    
    layer_add_child(window_get_root_layer(mainMenuWindow), menu_layer_get_layer(menuLayerMain));
  }
  else
  {
    //Will be displayed if Steam's API fails to provide non-NULL user data. //DEV NOTE: HAVE YET TO GET THIS MESSAGE TO SHOW...///
    if(timer<31)
      timer++;
    if(timer>=30)
      text_layer_set_text(textLayer2, "Steam API Unavailable!");
  }
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context)
{
  
}

// Layer of primary window.
Layer *winLayer;
// First initialization point - Primary window and AppMessage-related registrations will be set up here.
static void init()
{
  window = window_create();
  
  //window_set_fullscreen(window, true);
  window_set_background_color(window, GColorBlack);
  window_stack_push(window, true);
  Layer *window_Layer = window_get_root_layer(window);
  
  winLayer = window_Layer;
  initText(window_Layer);

  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

bool currentState = false;
bool firstAPICall = false;

// Now that the window has been set up, use window data to set up the two TextLayer strings that will be displayed on the "splash screen" of the app, dependant on conditions.
static void initText(Layer *window_Layer)
{
  GRect bounds = layer_get_frame(window_Layer);
  GRect rect;
  rect.origin = (GPoint){0,10};
  rect.size.w = bounds.size.w;
  rect.size.h = (.5 * bounds.size.h);
  textLayer = text_layer_create(rect);
  rect.origin = (GPoint){0, rect.size.h};
  textLayer2 = text_layer_create(rect);
  
  layer_add_child(window_Layer, text_layer_get_layer(textLayer));
  layer_add_child(window_Layer, text_layer_get_layer(textLayer2));
  
  text_layer_set_text(textLayer, "SteamPebble  LOADING...");
  text_layer_set_font(textLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_background_color(textLayer, GColorBlack);
  text_layer_set_text_color(textLayer, GColorWhite);
  text_layer_set_text_alignment(textLayer, GTextAlignmentCenter);
  
  text_layer_set_font(textLayer2, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_background_color(textLayer2, GColorBlack);
  text_layer_set_text_color(textLayer2, GColorWhite);
  text_layer_set_text_alignment(textLayer2, GTextAlignmentCenter);
  
  text_layer_set_text(textLayer2, "CHECKING DEVICE CONNECTION...");
  
  // Subscribe to the "seconds" member of the Pebble's time handler. Allows us to programmatically update a timer every second.
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  bluetooth_connection_service_subscribe(bluetooth_Connection_Callback);
  
  if(bluetooth_connection_service_peek())
  {
    if(!dataSuccess)
    {
      text_layer_set_text(textLayer2, "Fetching Profile Data!");
    }
    
    currentState = true;
    
    if(dataSuccess)
      layer_set_hidden(text_layer_get_layer(textLayer2), true);
  }
  else
  {
    text_layer_set_text(textLayer2, "DEVICE NOT CONNECTED");
  }
}

// Used to determine whether or not the Pebble watch is connected to the Bluetooth device. DOES NOT check for internet connectivity.
void bluetooth_Connection_Callback(bool connected)
{
  if(connected && !currentState)
  {
    currentState = true;
    
    layer_set_hidden(text_layer_get_layer(textLayer2), true);
    timer = 0;
  }
  else if(!connected)
  {
    currentState = false;
  }
}

// Uses the Pebble watch's time updater function to increment a timer by 1 for every second that the Pebble is disconnected from the Bluetooth device. If the timer goes past 5 seconds, "LOST DEVICE CONNECTION" is displayed to the viewer.
static void tick_handler(struct tm *tick_time, TimeUnits unitsChanged)
{
  //Displayed if connection to device is lost for at least 5 seconds during program initialization.
  if(!currentState)
  {
      if(timer<6)
        timer++;
    
      if(timer>=5)
      {
        text_layer_set_text(textLayer2, "LOST DEVICE CONNECTION!");
        layer_set_hidden(text_layer_get_layer(textLayer2), false);
      }
  }
  else if(!firstAPICall)
  {
    // Send a request to apiCode.js to retrieve user data from the Steam API.
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_uint8(iter, 0, 0);
    app_message_outbox_send();
    
    firstAPICall = true;
  }
  
  if(currentState && !dataSuccess)
  {
    if(timer<31)
      timer++;
    
    if(timer>=30)
    {
       text_layer_set_text(textLayer2, "COULD NOT RETRIEVE DATA!");
       firstAPICall = false;
    }    
  }
}
  
// Release of resources and exit point for the app.
void deinit()
{
  bluetooth_connection_service_unsubscribe();
  tick_timer_service_unsubscribe();
  text_layer_destroy(textLayer);
  text_layer_destroy(textLayer2);
  window_destroy(window);
  window_destroy(mainMenuWindow);
  window_destroy(secondaryWindow);
  
  menu_layer_destroy(menuLayerMain);
  menu_layer_destroy(secondaryMenuLayer);
  
  //layer_destroy(secondaryLayer);
  //layer_destroy(mainMenuWinLayer);
  //layer_destroy(winLayer);
}

// Entry point of the program.
int main(void)
{
  // Start initialization of functions and variables.
  init();
  
  // Begin the program's runtime and update loop.
  app_event_loop();
  
  // Release all resources and exit the program
  deinit();
  return 0;
}