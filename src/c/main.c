/* *** COPYRIGHT (C)2014-2016 Hull Softworks(Austin Hull). Wrist Steam AND Hull Softworks ARE NOT AFFILIATED WITH Steam OR Valve Software IN ANY WAY OR CAPACITY.
THIS FREE SOFTWARE IS OPEN-SOURCE AND IS LICENSED UNDER THE GNU General Public License v2.
TERMS AND CONDITIONS OF THE GNU General Public License v2 MAY BE OBTAINED AT: https://gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1 
FULL PROGRAMMING CODE OF THIS SOFTWARE MAY BE OBTAINED AT Github: https://github.com/AustinHull/SteamPebble *** */

// Core system/font libraries
#include <pebble.h>
#include <pebble_fonts.h>
#include <stdlib.h>
#include <string.h>
#include "dataDeclarations.h"
#include "functionDeclarations.h"

//static GBitmap *avatarVar; Use of Profile Avatars currently not in development...

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
  
  /* 
  ** Provided Pebble is connected to 
  ** phone via Bluetooth, wait for data to be pulled from Steam's API servers, then proceed upon success.
  */
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
  else // Otherwise, give an error message, stating to user that Pebble is not connected to phone's Bluetooth..
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