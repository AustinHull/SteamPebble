/* *** COPYRIGHT (C)2014-2016 Hull Softworks(Austin Hull). Wrist Steam AND Hull Softworks ARE NOT AFFILIATED WITH Steam OR Valve Software IN ANY WAY OR CAPACITY.
THIS FREE SOFTWARE IS OPEN-SOURCE AND IS LICENSED UNDER THE GNU General Public License v2.
TERMS AND CONDITIONS OF THE GNU General Public License v2 MAY BE OBTAINED AT: https://gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1 
FULL PROGRAMMING CODE OF THIS SOFTWARE MAY BE OBTAINED AT Github: https://github.com/AustinHull/SteamPebble *** */

#ifndef FUNCTIONDECLARATIONS_H
#define FUNCTIONDECLARATIONS_H

#include <pebble.h>
#include <pebble_fonts.h>
#include <stdlib.h>
#include <string.h>
#include "dataDeclarations.h"

// **Layer-related declarations**

// Used for the initial splash-screen.
static Window *window;
static TextLayer *textLayer;
static TextLayer *textLayer2;

// Window objects for the first menu screen.
static Window *mainMenuWindow;
//Layer *mainMenuWinLayer;
MenuLayer *menuLayerMain;

// Window objects for secondary menu screens.
static Window *secondaryWindow;
//Layer *secondaryLayer;
MenuLayer *secondaryMenuLayer;

// Window objects for guide menu screen.
static Window *secondaryWindow2;
//Layer *secondaryLayer2;
MenuLayer *secondaryMenuLayer2;

//Window objects for selected guide screens.
static Window *secondaryWindow2_1;
MenuLayer *secondaryMenuLayer2_1;
static TextLayer *guideTextLayer;
ScrollLayer *guideScrollLayer;

// Window objects for About screen.
static Window *secondaryWindow3;
static TextLayer *secondTextLayer;
ScrollLayer *scrollLayer;

static Window *friendsListWindow;
MenuLayer *friendsListMenuLayer;

// Defined functions for window-related services and methods.

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
    window_set_background_color(window, GColorWhite);
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
   
  // Friends list should be parsed before further processing...
  switch(cell_index->row)
  {
    case 0:
    menu_cell_basic_draw(ctx, cell_layer, name1, NULL, NULL);
    break;
    case 1:
    menu_cell_basic_draw(ctx, cell_layer, name2, NULL, NULL);
    break;
    case 2:
    menu_cell_basic_draw(ctx, cell_layer, name3, NULL, NULL);
    break;
    case 3:
    menu_cell_basic_draw(ctx, cell_layer, name4, NULL, NULL);
    break;
    case 4:
    menu_cell_basic_draw(ctx, cell_layer, name5, NULL, NULL);
    break;
  }
  
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

// Handlers for menu-related features and functionality. These are attached to specified Windows.
void down_single_click_handler(ClickRecognizerRef recognizer, void *context);
void config_provider(Window *window);
static void select_click_callback(MenuLayer *menuLayer, MenuIndex *cell_Index, void *callbackContext);
static void select_click_callbackGuide(MenuLayer *menuLayer, MenuIndex *cell_Index, void *callbackContext);
static void splashScreenClickProvider(void *context);

uint16_t num_rows_callback(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext);
void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context);

uint16_t num_rows_callback2(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext);
void draw_row_callback2(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context);

uint16_t num_rows_callback2_1(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext);
void draw_row_callback2_1(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context);

uint16_t num_rows_callback_FriendsList(MenuLayer *menuLayer, uint16_t sectionIndex, void *callbackContext);
void draw_row_callback_FriendsList(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context);

// Communication/Timer handlers used between the phone and watchapp.
static void inbox_received_callback(DictionaryIterator *iterator, void *context);
static void outbox_sent_callback(DictionaryIterator *iterator, void *context);
void bluetooth_Connection_Callback(bool connected);
static void tick_handler(struct tm *tick_time, TimeUnits unitsChanged);

// Prototypes for frequently-used Pebble services, which update throughout the runtime-loop.
void bluetooth_Connection_Callback(bool connected);
static void tick_handler(struct tm *tick_time, TimeUnits unitsChanged);


#endif