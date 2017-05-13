/* *** COPYRIGHT (C)2014-2016 Hull Softworks(Austin Hull). Wrist Steam AND Hull Softworks ARE NOT AFFILIATED WITH Steam OR Valve Software IN ANY WAY OR CAPACITY.
THIS FREE SOFTWARE IS OPEN-SOURCE AND IS LICENSED UNDER THE GNU General Public License v2.
TERMS AND CONDITIONS OF THE GNU General Public License v2 MAY BE OBTAINED AT: https://gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1 
FULL PROGRAMMING CODE OF THIS SOFTWARE MAY BE OBTAINED AT Github: https://github.com/AustinHull/SteamPebble *** */

#ifndef DATADECLARATIONS_H
#define DATADECLARATIONS_H

#include <pebble.h>
#include <pebble_fonts.h>
#include <stdlib.h>
#include <string.h>

// Used for moving data between JavaScript (apiCode.js) and C (main.c)
#define KEY_CURRENTNAME 0
#define KEY_REALNAME 1
#define KEY_STATE 2
#define KEY_COUNTRY 3
#define KEY_AVATAR 4
#define KEY_FRIENDNAME 5
#define KEY_LISTSIZE 6

// Prototypes for primary procedures used during the life of the application.
static void initBT(void);
static void init(void);
static void deinit(void);

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

#endif