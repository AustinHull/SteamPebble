/* *** COPYRIGHT (C)2014-2016 Hull Softworks(Austin Hull). Wrist Steam AND Hull Softworks ARE NOT AFFILIATED WITH Steam OR Valve Software IN ANY WAY OR CAPACITY.
THIS FREE SOFTWARE IS OPEN-SOURCE AND IS LICENSED UNDER THE GNU General Public License v2.
TERMS AND CONDITIONS OF THE GNU General Public License v2 MAY BE OBTAINED AT: https://gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1 
FULL PROGRAMMING CODE OF THIS SOFTWARE MAY BE OBTAINED AT Github: https://github.com/AustinHull/SteamPebble *** */

// Core system/font libraries
#include<pebble.h>
#include<pebble_fonts.h>
#include <stdlib.h>
#include <string.h>
#include "functionDeclarations.h"

// Used for moving data between JavaScript (apiCode.js) and C (main.c)
#define KEY_CURRENTNAME 0
#define KEY_REALNAME 1
#define KEY_STATE 2
#define KEY_COUNTRY 3
#define KEY_AVATAR 4
#define KEY_FRIENDNAME 5
#define KEY_LISTSIZE 6

//static GBitmap *avatarVar; Use of Profile Avatars currently not in development...

// .load function for splash screen WindowHandler. WORK IN PROGRESS!!!
static void firstWindowLoad(Window *window)
{
    // Layer for primary window.
    Layer *window_Layer = window_get_root_layer(window);
    window_set_background_color(window, GColorBlack);
    
    // Initialize splash screen text. Sets the fonts and colors to be used for said text.
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
    
    text_layer_set_text(textLayer, "Wrist Steam  LOADING...");
    text_layer_set_font(textLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_background_color(textLayer, GColorBlack);
    text_layer_set_text_color(textLayer, GColorWhite);
    text_layer_set_text_alignment(textLayer, GTextAlignmentCenter);
  
    text_layer_set_font(textLayer2, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_background_color(textLayer2, GColorBlack);
    text_layer_set_text_color(textLayer2, GColorWhite);
    text_layer_set_text_alignment(textLayer2, GTextAlignmentCenter);
  
    text_layer_set_text(textLayer2, "CHECKING DEVICE CONNECTION...");
}
// .unload function for splash screen WindowHandler. WORK IN PROGRESS!!!
static void firstWindowUnload(Window *window)
{
  // Experimental method for deinitializing and destroying splash screen's child resources upon exit.
    text_layer_destroy(textLayer);
    text_layer_destroy(textLayer2);
    textLayer = NULL;
    textLayer2 = NULL;
}
// .load function for Main Menu WindowHandler. WORK IN PROGRESS!!!
static void mainMenuLoad(Window *window)
{
    //Layer *mainMenuWinLayer = window_get_root_layer(window);
    window_set_background_color(window, GColorWhite);

    //menu_layer_set_click_config_onto_window(menuLayerMain, window);
    //layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menuLayerMain));
}
// .unload function for Main Menu WindowHandler. WORK IN PROGRESS!!!
static void mainMenuUnload(Window *window)
{
    menu_layer_destroy(menuLayerMain);
    menuLayerMain = NULL;
}

// .load function for Profile Page WindowHandler. WORK IN PROGRESS!!!
static void secondaryWindowLoad(Window *window)
{
    window_set_background_color(window, GColorWhite);
  
    menu_layer_set_click_config_onto_window(secondaryMenuLayer, window);
    layer_add_child(window_get_root_layer(window), menu_layer_get_layer(secondaryMenuLayer));
}
// .unload function for Profile Page WindowHandler. WORK IN PROGRESS!!!
static void secondaryWindowUnload(Window *window)
{
    //menu_layer_destroy(secondaryMenuLayer);
    //secondaryMenuLayer = NULL;
}

// .load function for User Guide WindowHandler. WORK IN PROGRESS!!!
static void secondaryWindow2Load(Window *window)
{
    window_set_background_color(window, GColorWhite);
  
    //menu_layer_set_click_config_onto_window(secondaryMenuLayer2, window);
    //layer_add_child(window_get_root_layer(window), menu_layer_get_layer(secondaryMenuLayer2));
}
// .unload function for User Guide WindowHandler. WORK IN PROGRESS!!!
static void secondaryWindow2Unload(Window *window)
{
    //menu_layer_destroy(secondaryMenuLayer2);
    //secondaryMenuLayer2 = NULL;
}

static void secondaryWindow2_1Load(Window *window)
{
    window_set_background_color(window, GColorBlack);
  
    Layer *secondaryLayer3 = window_get_root_layer(window);
    GRect bounds = layer_get_frame(secondaryLayer3);
    GRect rect;
    rect.origin = (GPoint){0,0};
    rect.size.w = bounds.size.w;
    rect.size.h = bounds.size.h;
    guideTextLayer = text_layer_create(rect);
    guideScrollLayer = scroll_layer_create(bounds);// Work In Progress!
  
    text_layer_set_text(guideTextLayer, "Guides coming soon!"); // TODO: Finish setting up this Guide Page text!
    text_layer_set_font(guideTextLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_size(guideTextLayer, GSize(rect.size.w, 2000));
    GSize sTextLayerSize = text_layer_get_content_size(guideTextLayer);// Work In Progress!
    scroll_layer_set_content_size(guideScrollLayer, GSize(rect.size.w, sTextLayerSize.h));// Work In Progress! GET SCROLLING TO WORK!
    scroll_layer_add_child(guideScrollLayer, text_layer_get_layer(guideTextLayer));// Work In Progress!
    layer_add_child(window_get_root_layer(window), scroll_layer_get_layer(guideScrollLayer));// Work In Progress!
    text_layer_set_background_color(guideTextLayer, GColorBlack);
    text_layer_set_text_color(guideTextLayer, GColorWhite);
    scroll_layer_set_click_config_onto_window(guideScrollLayer, window);// Work In Progress!  
}
static void secondaryWindow2_1Unload(Window *window)
{
    scroll_layer_destroy(guideScrollLayer);
    text_layer_destroy(guideTextLayer);
}

// .load function for About Page WindowHandler. WORK IN PROGRESS!!!
static void secondaryWindow3Load(Window *window)
{
    Layer *secondaryLayer3 = window_get_root_layer(window);
    GRect bounds = layer_get_frame(secondaryLayer3);
    GRect rect;
    rect.origin = (GPoint){0,0};
    rect.size.w = bounds.size.w;
    rect.size.h = bounds.size.h;
    secondTextLayer = text_layer_create(rect);
    scrollLayer = scroll_layer_create(bounds);// Work In Progress!
  
    text_layer_set_text(secondTextLayer, "Copyright(C)2014-2016 Hull Softworks(Austin Hull). This software is open-source and not-for-profit. Hull Softworks(Austin Hull) is not affiliated with Steam or Valve Software in any way. This software is currently under development, and may contain bugs and/or incomplete features. By downloading this software, you understand that Hull Softworks(Austin Hull) is not liable for any issues that you or your Pebble hardware may experience by using this software."); // TODO: Finish setting up this About Page text!
    text_layer_set_font(secondTextLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_size(secondTextLayer, GSize(rect.size.w, 2000));
    GSize sTextLayerSize = text_layer_get_content_size(secondTextLayer);// Work In Progress!
    scroll_layer_set_content_size(scrollLayer, GSize(rect.size.w, sTextLayerSize.h));// Work In Progress! GET SCROLLING TO WORK!
    scroll_layer_add_child(scrollLayer, text_layer_get_layer(secondTextLayer));// Work In Progress!
    layer_add_child(window_get_root_layer(window), scroll_layer_get_layer(scrollLayer));// Work In Progress!
    text_layer_set_background_color(secondTextLayer, GColorBlack);
    text_layer_set_text_color(secondTextLayer, GColorWhite);
    scroll_layer_set_click_config_onto_window(scrollLayer, window);// Work In Progress!
}
// .unload function for About Page WindowHandler. WORK IN PROGRESS!!!
static void secondaryWindow3Unload(Window *window)
{
    scroll_layer_destroy(scrollLayer);
    text_layer_destroy(secondTextLayer);
}

static void friendsListWindowLoad(Window *window)
{
    window_set_background_color(window, GColorWhite);
  
    menu_layer_set_click_config_onto_window(friendsListMenuLayer, window);
    layer_add_child(window_get_root_layer(window), menu_layer_get_layer(friendsListMenuLayer));
}
static void friendsListWindowUnload(Window *window)
{
  
}

// During initial data retrieval (while splash screen is active), if the user is unable to successfully fetch their profile data, they may click the SELECT button to make another retrieval attempt.
void down_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
  if(window_stack_contains_window(window) && timer > 30)
  {
    firstAPICall = false;
    
    timer = 0;
    
    text_layer_set_text(textLayer2, "Re-fetching Data...");
  }
}

// Provides data and things for button click events.
void config_provider(Window *window)
{
  window_single_click_subscribe(BUTTON_ID_SELECT, down_single_click_handler);
}

// Callbacks for first(Main Menu) window.
uint16_t num_rows_callback(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext)
{
  return 4;
}

void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row)
  {
    case 0:
    menu_cell_basic_draw(ctx, cell_layer, "Profile Info", NULL, NULL);
    break;
    
    case 1:
    menu_cell_basic_draw(ctx, cell_layer, "Friends List", NULL, NULL);
    break;
    
    case 2:
    menu_cell_basic_draw(ctx, cell_layer, "User Guide", NULL, NULL);
    break;
    
    case 3:
    menu_cell_basic_draw(ctx, cell_layer, "About", NULL, NULL);
    break;
  }
}

// Callbacks for a secondary(Profile) window.
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

// Callbacks for a secondary(User Guide) window.
uint16_t num_rows_callback2_1(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext)
{
  return 2;
}

void draw_row_callback2_1(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row)
  {
    case 0:
    menu_cell_basic_draw(ctx, cell_layer, "Profile Setup", NULL, NULL);
    break;
    case 1:
    menu_cell_basic_draw(ctx, cell_layer, "Accessing Info", NULL, NULL);
    break;
  }
}

uint16_t num_rows_callback_FriendsList(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext)
{
  return (KEY_LISTSIZE - 1);  
}

// Very basic friends list display protocol. Only displays a static list of 5 friends at this time.
void draw_row_callback_FriendsList(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  
  char* textParse = malloc(sizeof(friendsList));
  char* splitString = malloc(200);
  
  char* name1 = malloc(33);
  char* name2 = malloc(33);
  char* name3 = malloc(33);
  char* name4 = malloc(33);
  char* name5 = malloc(33);
  
  strcpy(textParse, friendsList);
  
  splitString = strtok(textParse, "|");
  
  name1 = splitString;
  splitString = strtok(NULL, "|");
  name2 = splitString;
  splitString = strtok(NULL, "|");
  name3 = splitString;
  splitString = strtok(NULL, "|");
  name4 = splitString;
  splitString = strtok(NULL, "|");
  name5 = splitString;
  //splitString = strtok(NULL, "|");
  
  //cell_index->row = 0;
   
  // Friends list should be parsed before further processing...
  switch(cell_index->row)
  {
    case 0:
    menu_cell_basic_draw(ctx, cell_layer, name1, NULL, NULL);
    //splitString = strtok(NULL, "|");
    break;
    case 1:
    menu_cell_basic_draw(ctx, cell_layer, name2, NULL, NULL);
    //splitString = strtok(NULL, "|");
    break;
    case 2:
    menu_cell_basic_draw(ctx, cell_layer, name3, NULL, NULL);
    //splitString = strtok(NULL, "|");
    break;
    case 3:
    menu_cell_basic_draw(ctx, cell_layer, name4, NULL, NULL);
    //splitString = strtok(NULL, "|");
    break;
    case 4:
    menu_cell_basic_draw(ctx, cell_layer, name5, NULL, NULL);
    //splitString = strtok(NULL, "|");
    break;

    //cell_index->row++;
  }
  
  //menu_layer_reload_data(friendsListMenuLayer);
  
  free(textParse);
}

//Used to transition selections from main menu to secondary menu.
static void select_click_callback(MenuLayer *menuLayer, MenuIndex *cell_Index, void *callbackContext)
{
  switch(cell_Index->row)
  {
    // Each case's output corresponds to a single menu selection, depending on which menu row is selected at the time of button-press.
    case 0:
    // Case 0 is used to display profile data on the secondaryWindow.
    window_stack_push(secondaryWindow, true);
    break;
    case 1:
    // Case 1 is used to display the user's friends list.
    window_stack_push(friendsListWindow, true);
    break;
    case 2:
    // Case 2 is used to display Guides and other instructions to the user.
    window_stack_push(secondaryWindow2, true);
    
    menu_layer_set_click_config_onto_window(secondaryMenuLayer2, secondaryWindow2);
    layer_add_child(window_get_root_layer(secondaryWindow2), menu_layer_get_layer(secondaryMenuLayer2));
    break;
    case 3:
    // Case 3 is used to display About information to the user.
    window_stack_push(secondaryWindow3, true);    
    break;
  }
}

//Used to transition selections from guideWindow(secondaryWindow) to secondaryWindow2_1.
static void select_click_callbackGuide(MenuLayer *menuLayer, MenuIndex *cell_Index, void *callbackContext)
{
  switch(cell_Index->row)
  {
    // Each case's output corresponds to a single menu selection, depending on which menu row is selected at the time of button-press.
    case 0:
    // Case 0 is used to display profile data on the secondaryWindow.
    window_stack_push(secondaryWindow2_1, true);
    break;
    case 1:
    // Case 1 is used to display Guides and other instructions to the user.
    window_stack_push(secondaryWindow2_1, true);
    break;
  }
}

// Set up some initialization-related variables and objects.
bool dataSuccess = false;

// Receives messages from apiCode.js, takes JSON data and applies it to C variables.
static void inbox_received_callback(DictionaryIterator *iterator, void *context)
{
  
  Tuple *t = dict_read_first(iterator); // Set the Tuple pointer towards the address of the iterator's beginning point.
  
  while(t != NULL) // Keep interpreting data within the Tuple pointer so long as it's not empty.
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
      case KEY_AVATAR:
      snprintf(id, sizeof(id), "%s", t->value->cstring);
      break;
      case KEY_FRIENDNAME:
      snprintf(friendsList, sizeof(friendsList), "%s", t->value->cstring);
      break;
      case KEY_LISTSIZE:
      listSize = (t->value->int32);
      break;
      default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }
    
    t = dict_read_next(iterator); // Increment the iterator.
  }
  
  // Loads next windows, only if data is received from Steam.
  if(country != NULL)
  {
    dataSuccess = true;
    layer_set_hidden(text_layer_get_layer(textLayer2), true);
    timer = 0;
    
    
    //Creates and pushes new window for main menu to stack, and removes splash-screen from stack for performance management.
    mainMenuWindow = window_create();
    
    window_set_window_handlers(mainMenuWindow, (WindowHandlers)
    {
        .load = mainMenuLoad,
        .unload = mainMenuUnload
    });
    window_stack_push(mainMenuWindow, true);
    //Sets configurations for button click provider.
    window_set_click_config_provider(mainMenuWindow, (ClickConfigProvider)config_provider);
    //Creates and initializes main menu to be attached to new main menu window.
    menuLayerMain = menu_layer_create(GRect(0, 0, 144, 168));
    MenuLayerCallbacks callbacks = {.draw_row = (MenuLayerDrawRowCallback)draw_row_callback, .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback, .select_click = (MenuLayerSelectCallback)select_click_callback};
    menu_layer_set_callbacks(menuLayerMain, NULL, callbacks);
    menu_layer_set_click_config_onto_window(menuLayerMain, mainMenuWindow);
    layer_add_child(window_get_root_layer(mainMenuWindow), menu_layer_get_layer(menuLayerMain));
    
    window_stack_remove(window, false);
    
    /*
      Secondary windows and their parameters. These do not get pushed to screen until transition. 
      Also, creates and attaches secondary menu layer to secondary window. IN PROGRESS!!!
    */
    secondaryWindow = window_create();
    
    window_set_window_handlers(secondaryWindow, (WindowHandlers)
    {
        .load = secondaryWindowLoad,
        .unload = secondaryWindowUnload
    });
    
    secondaryMenuLayer = menu_layer_create(GRect(0, 0, 144, 168));
    MenuLayerCallbacks callbacks2 = {.draw_row = (MenuLayerDrawRowCallback)draw_row_callback2, .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback2, NULL};
    menu_layer_set_callbacks(secondaryMenuLayer, NULL, callbacks2);
    
    // Used to display Friends List.
    friendsListWindow = window_create();
    
    window_set_window_handlers(friendsListWindow, (WindowHandlers)
    {
         .load = friendsListWindowLoad,
         .unload = friendsListWindowUnload
    });
    
    friendsListMenuLayer = menu_layer_create(GRect(0, 0, 144, 168));
    MenuLayerCallbacks callbacksFriendsList = {.draw_row = (MenuLayerDrawRowCallback)draw_row_callback_FriendsList, .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback_FriendsList, NULL};
    menu_layer_set_callbacks(friendsListMenuLayer, NULL, callbacksFriendsList);
    
    // Used to display Guide Menu.
    secondaryWindow2 = window_create();
    
    window_set_window_handlers(secondaryWindow2, (WindowHandlers)
    {
         .load = secondaryWindow2Load,
         .unload = secondaryWindow2Unload
    });
    
    //secondaryLayer2 = window_get_root_layer(secondaryWindow2);
    secondaryMenuLayer2 = menu_layer_create(GRect(0, 0, 144, 168));
    MenuLayerCallbacks callbacks2_1 = {.draw_row = (MenuLayerDrawRowCallback)draw_row_callback2_1, .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)num_rows_callback2_1, .select_click = (MenuLayerSelectCallback)select_click_callbackGuide};
    menu_layer_set_callbacks(secondaryMenuLayer2, NULL, callbacks2_1);
    menu_layer_set_click_config_onto_window(secondaryMenuLayer2, secondaryWindow2);
    layer_add_child(window_get_root_layer(secondaryWindow2), menu_layer_get_layer(secondaryMenuLayer2));
    
    //Place stuff for secondaryWindow2_1 somewhere over here...
    secondaryWindow2_1 = window_create();
    
    window_set_window_handlers(secondaryWindow2_1, (WindowHandlers)
    {
        .load = secondaryWindow2_1Load,
        .unload = secondaryWindow2_1Unload
    });
    
    // Used to display About screen.
    secondaryWindow3 = window_create();
    
    window_set_window_handlers(secondaryWindow3, (WindowHandlers)
    {
         .load = secondaryWindow3Load,
         .unload = secondaryWindow3Unload
    });
  }
  else
  {
    //Will be displayed if Steam's API fails to provide non-NULL user data. //DEV NOTE: HAVE YET TO GET THIS MESSAGE TO SHOW...///
    if(timer < 31)
      timer++;
    if(timer >= 30)
      text_layer_set_text(textLayer2, "Steam API Unavailable!");
  }
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context)
{

}

// Used to register user's refresh attempts, if data was not retrieved during splashscreen's initialization.
static void splashScreenClickProvider(void *context)
{
  window_single_click_subscribe(BUTTON_ID_SELECT, down_single_click_handler);
}

// Layer for primary window.
//Layer *winLayer;

// First initialization point - Primary window and AppMessage-related registrations will be set up here.
static void init()
{
  window = window_create();
  
  window_set_click_config_provider(window, splashScreenClickProvider);
  
  window_set_window_handlers(window, (WindowHandlers)
  {
         .load = firstWindowLoad,
         .unload = firstWindowUnload
  });
  
  //window_set_background_color(window, GColorBlack);
  window_stack_push(window, true);
  //Layer *window_Layer = window_get_root_layer(window);
  
  //winLayer = window_Layer;
  initBT(); // I may or may not be planning on depreciating this specific function...

  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  app_message_open((uint32_t)1024, (uint32_t)1024);
}

// Now that the first window has been set up, use window data to set up the two TextLayer strings that will be displayed on the "splash screen" of the app, dependant on conditions.
static void initBT()
{
  
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
    }    
  }
}
  
// Releases the resources and is the exit point for the app. FREE THE SPACE!!!
void deinit()
{
  bluetooth_connection_service_unsubscribe();
  tick_timer_service_unsubscribe();
  //text_layer_destroy(textLayer);
  //text_layer_destroy(textLayer2);
  //text_layer_destroy(secondTextLayer);
  window_destroy(window);
  window_destroy(mainMenuWindow);
  window_destroy(secondaryWindow);
  window_destroy(secondaryWindow2);
  window_destroy(secondaryWindow2_1);
  window_destroy(secondaryWindow3);
  window_destroy(friendsListWindow);
  window = NULL;
  mainMenuWindow = NULL;
  secondaryWindow = NULL;
  secondaryWindow2 = NULL;
  secondaryWindow2_1 = NULL;
  secondaryWindow3 = NULL;
  friendsListWindow = NULL;
  
  menu_layer_destroy(secondaryMenuLayer);
  menu_layer_destroy(secondaryMenuLayer2);
  menu_layer_destroy(friendsListMenuLayer);
  secondaryMenuLayer = NULL;
  secondaryMenuLayer2 = NULL;
  friendsListMenuLayer = NULL;
  
  app_message_deregister_callbacks();
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