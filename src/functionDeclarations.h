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

//Prototypes for window-related services and methods.
static void firstWindowLoad(Window *window);
static void firstWindowUnload(Window *window);
static void mainMenuLoad(Window *window);
static void mainMenuUnload(Window *window);
static void secondaryWindowLoad(Window *window);
static void secondaryWindowUnload(Window *window);
static void secondaryWindow2Load(Window *window);
static void secondaryWindow2Unload(Window *window);
static void secondaryWindow2_1Load(Window *window);
static void secondaryWindow2_1Unload(Window *window);
static void secondaryWindow3Load(Window *window);
static void secondaryWindow3Unload(Window *window);
static void friendsListWindowLoad(Window *window);
static void friendsListWindowUnload(Window *window);

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
  
// Prototypes for primary procedures used during the life of the application.
static void initBT(void);
static void init(void);
static void deinit(void);

// Prototypes for frequently-used Pebble services, which update throughout the runtime-loop.
void bluetooth_Connection_Callback(bool connected);
static void tick_handler(struct tm *tick_time, TimeUnits unitsChanged);

// Char buffers, used to contain parsed-through JSON variables, to then be passed to the user.
static char cName[33];
static char rName[33];
static char state[3];
static char country[3];
static char id[19];
static char friendsList[129];
static int32_t listSize;

// Use of unsigned short integer variable should be the most space-effective implementation for a micro-scale timer.
unsigned short int timer = 0;

// Used for tick_handler procedure - determines bluetooth connectivity, and API call-status, respectively.
bool currentState = false;
bool firstAPICall = false;

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


#endif