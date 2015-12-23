/* *** COPYRIGHT (C)2014-2016 Hull Softworks(Austin Hull). SteamPebble AND Planeboy Games ARE NOT AFFILIATED WITH Steam OR Valve Software IN ANY WAY OR CAPACITY.
THIS FREE SOFTWARE IS OPEN-SOURCE AND IS LICENSED UNDER THE GNU General Public License v2.
TERMS AND CONDITIONS OF THE GNU General Public License v2 MAY BE OBTAINED AT: https://gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1 
FULL PROGRAMMING CODE OF THIS SOFTWARE MAY BE OBTAINED AT Github: https://github.com/austinplaneboy/SteamPebble *** */

var combString;
var xhrRequest = function(url, type, callback)
{
  var xhr = new XMLHttpRequest();
  
  xhr.onload = function()
  {
    callback(this.responseText);
  };
  
  xhr.open(type, "http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002?key=A89AB1A31BB73310B4C13D3945B79954&" + "steamids=" + url , true);
  
  xhr.setRequestHeader('Content-Type:', 'application/x-www-form-urlencoded');
  
  xhr.send();
};

var ID;

function getSteamInfo()
{
  
  var ID2 = localStorage.getItem('ID');
  //ID2.trim();
  
  combString = JSON.parse(ID2);
  combString = combString.ID;
  
  console.log("http://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002?key=A89AB1A31BB73310B4C13D3945B79954&steamids=".concat(combString));
  
  xhrRequest(combString, 'GET', function(responseText){var json = JSON.parse(responseText); console.log(json.response.players[0]);  var currentName = json.response.players[0].personaname; console.log("name is: " + currentName); var realName = json.response.players[0].realname;
  console.log("real name is: " + realName); var state = json.response.players[0].locstatecode; console.log("state is: " + state); var country = json.response.players[0].loccountrycode; console.log("country is: " + country); var avatar = json.response.players[0].avatar; console.log("image data: " + avatar); var dictionary = {"KEY_CURRENTNAME": currentName, "KEY_REALNAME": realName, "KEY_STATE": state, "KEY_COUNTRY": country, "KEY_AVATAR": avatar};
  Pebble.sendAppMessage(dictionary);});
  
}

Pebble.addEventListener('showConfiguration', function(e){Pebble.openURL('http://steam.planeboygames.com/');});

Pebble.addEventListener('webviewclosed', function(e){console.log('Config returned: ' + e.response);});
Pebble.addEventListener('webviewclosed', function(e){ID = JSON.parse(decodeURIComponent(e.response)); console.log('Config says: ', JSON.stringify(ID)); localStorage.setItem('ID',JSON.stringify(ID)); getSteamInfo();});

//location.href = 'pebblejs://close#success';

//Pebble.addEventListener('ready', function(e){getSteamInfo();});

Pebble.addEventListener('appmessage', function(e){getSteamInfo();});