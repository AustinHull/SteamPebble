/* *** COPYRIGHT (C)2014-2016 Hull Softworks(Austin Hull). Wrist Steam AND Hull Softworks ARE NOT AFFILIATED WITH Steam OR Valve Software IN ANY WAY OR CAPACITY.
THIS FREE SOFTWARE IS OPEN-SOURCE AND IS LICENSED UNDER THE GNU General Public License v2.
TERMS AND CONDITIONS OF THE GNU General Public License v2 MAY BE OBTAINED AT: https://gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1 
FULL PROGRAMMING CODE OF THIS SOFTWARE MAY BE OBTAINED AT Github: https://github.com/AustinHull/SteamPebble *** */

var combString; // Is used to hold the fully-constructed URL request to be sent to Steam's API services.
var callIdentifier; // Will be used by xhrRequest to differentiate between API calls.

/* 
   This function is used to make an XMLHTTP Request to Steam's API services by combining the base request URL with data
   retrieved from the user. The function will return JSON data the profile of whichever user's steamid_64 was entered. 
*/
var xhrRequest = function(url, type, callback)
{
  var xhr = new XMLHttpRequest();
  
  xhr.onload = function()
  {
    callback(this.responseText);
  };
  
  if(callIdentifier === 0)
  {
    xhr.open(type, "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002?key=A89AB1A31BB73310B4C13D3945B79954&" + "steamids=" + url, false);
  }
  else if(callIdentifier === 1)
  {
    xhr.open(type, "http://api.steampowered.com/ISteamUser/GetFriendList/v0001/?key=A89AB1A31BB73310B4C13D3945B79954&" + "steamid=" + url + "&relationship=friend", false);
  }
  
  xhr.setRequestHeader('Content-Type:', 'application/x-www-form-urlencoded');
  
  xhr.send();
};

var ID; // Will hold user's steamid.
var SET_NUM_LIST = 5; // Will hold user's numList configuration for their friends list.

// Holds the dictionary to be sent to the watchapp. Should have all keys-values consolidated together before sending.
var dict1;

//var nameArray = []; // This array will hold the profile names of each friend's steamid located in listArray.
var dicString = "";

/* 
  This function retrieves a pre-existing user-supplied steamid64 (if available) and makes a request to Steam's API services
  with this information in order to retrieve relevant profile information of the user, including friends list metadata.
*/
function getSteamInfo()
{
  callIdentifier = 0; // Tell the xhrRequest function to use Steam's GetPlayerSummaries API service.
  
  var ID2 = localStorage.getItem('ID'); // Attempt to retrieve a saved instance of the user's steamid.
  //ID2.trim();
  
  combString = JSON.parse(ID2); // Prepare the steamid to be used in the xhrRequest function.
  //combString = combString.ID;
  
  console.log("http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002?key=A89AB1A31BB73310B4C13D3945B79954&steamids=".concat(combString));
  
  xhrRequest(combString, 'GET', function(responseText){var json = JSON.parse(responseText); console.log(json.response.players[0]);  var currentName = json.response.players[0].personaname; console.log("name is: " + currentName); var realName = json.response.players[0].realname;
  console.log("real name is: " + realName); var state = json.response.players[0].locstatecode; console.log("state is: " + state); var country = json.response.players[0].loccountrycode; console.log("country is: " + country); var avatar = json.response.players[0].avatar; console.log("image data: " + avatar); dict1 = {"KEY_CURRENTNAME": currentName, "KEY_REALNAME": realName, "KEY_STATE": state, "KEY_COUNTRY": country, "KEY_AVATAR": avatar};
  /*Pebble.sendAppMessage(dict1);*/ getFriendsInfo();}); // Send the retrieved profile data to the Pebble watch.
  
}

/*
  This function retrieves the steamids of the user's friends. It proceeds to call the convertFriendNames() function.
*/
function getFriendsInfo()
{
  callIdentifier = 1; // Tells the xhrRequest function to request info from Steam's GetFriendsList API service.
  
  var numList = 5; // This variable is expected to eventually be set by the user via the configuration page.
  var listArray = []; // Array which holds data for each friend of the user to be listed.
  
  console.log("http://api.steampowered.com/ISteamUser/GetFriendList/v0001/?key=A89AB1A31BB73310B4C13D3945B79954&steamid=".concat(combString + "&relationship=friend"));
  
  // Retrieve a preset number of friends' steamids, as prescribed by numList, and store said ids in listArray.
  xhrRequest(combString, 'GET', function(responseText){var json = JSON.parse(responseText); for(var i = 0; i < numList; i++){ listArray.push(json.friendslist.friends[i].steamid); console.log("Friend " + i + " is " + listArray[i]); } convertFriendNames(listArray);});
  
}

function convertFriendNames(listArray)
{
  callIdentifier = 0; // When called, tell the xhrRequest function that it will be calling the GetPlayerSummaries Steam API.
  
  //var nameArray = []; // This array will hold the profile names of each friend's steamid located in listArray.
  
  // For every friend's steamid in listArray, execute an xhrRequest to retrieve their profile name associated with said id.
  //xhrRequest(listArray[0], 'GET', function(responseText){var json = JSON.parse(responseText); /*nameArray.push(json.response.players[0].personaname);*/ var dicString = (json.response.players[0].personaname + "|"); console.log("Friend " + 0 + " Name: " + json.response.players[0].personaname); setKeysAndSubmit(dicString);});
  for(var i = 0; i < listArray.length; i++)
  {
    // Get proper values assigned to a string block and send all keys to watch app.
    xhrRequest(listArray[i], 'GET', function(responseText){var json = JSON.parse(responseText); var tempString = (json.response.players[0].personaname + "|"); console.log("Friend " + i + " Name: " + json.response.players[0].personaname); setKeysAndSubmit(tempString, i);});
    
    if(i == listArray.length - 1)
    {
      dict1.KEY_FRIENDNAME = dicString;
      dict1.KEY_LISTSIZE = 5;
      Pebble.sendAppMessage(dict1);  
    }
    //setTimeout(500);
  }
  
  // WORK IN PROGRESS!!! Create a functional way to send array of Friends' Names to Pebble app.
  //var dicString = "";
  for(var j = 0; j < 0; j++)
  {  
    //dicString.concat(nameArray[j] + "|");
  }
  
  //dict1.KEY_FRIENDNAME = dicString; // Adds a new key-value pair to the dictionary, to contain the names of user's friends.
  //dict1.KEY_LISTSIZE = SET_NUM_LIST; // Adds a new key-value pair to dictionary, to contain the number of friend elements.

  console.log(listArray.length);
  
  //while(dict1[5] === null){} // Ensure that the dictionary is propogated before submitting it.
  //Pebble.sendAppMessage(dict1);
}

function setKeysAndSubmit(string, count)
{
  dicString += string;
}

Pebble.addEventListener('showConfiguration', function(e){Pebble.openURL('http://steam.planeboygames.com:26648/');});

Pebble.addEventListener('webviewclosed', function(e){console.log('Config returned: ' + e.response);});
Pebble.addEventListener('webviewclosed', function(e){ID = JSON.parse(decodeURIComponent(e.response)); console.log('Config says: ', JSON.stringify(ID)); localStorage.setItem('ID',JSON.stringify(ID)); getSteamInfo();});


//Pebble.addEventListener('ready', function(e){getSteamInfo();});

Pebble.addEventListener('appmessage', function(e){getSteamInfo();});