var http = require("http");
var fs = require("fs");
var express = require("express");
var app = express();
var session = require("express-session");
var firebase = require("connect-firebase")(session);
var firebaseOptions = {};
var passport = require('passport'), OpenIDStrategy = require('passport-steam').Strategy;
// Portions of code borrowed and retooled from the "Steam Strategy for Passport" project, available at https://www.github.com/liamcurry/passport-steam. Note that said project falls under the MIT License.
passport.use(new OpenIDStrategy({
    returnURL: 'http://steam.planeboygames.com:26648/auth/steam/return',
    realm: 'http://steam.planeboygames.com:26648/',
    apiKey: 'A89AB1A31BB73310B4C13D3945B79954'
  },
    function(identifier, profile, done) {
        // The done() function is provided by passport.  It's how we return
        // execution control back to passport.
        // Your database probably has its own asynchronous callback, so we're
        // faking that with nextTick() for demonstration.
        process.nextTick(function () {
            var user = identifier.match(/\d+$/)[0];
            return done(null, user);
        });
    }
  ));
  
passport.serializeUser(function(user, done) {
    done(null, user);
    });
passport.deserializeUser(function(identifier, done) {
    // For this demo, we'll just return an object literal since our user
    // objects are this trivial.  In the real world, you'd probably fetch
    // your user object from your database here.
    done(null, {
        identifier: identifier,
        steamId: identifier.match(/\d+$/)[0]
    });
});

var steamID;

app.use(passport.initialize());
app.use(passport.session());
app.get('/auth/steam',
  passport.authenticate('steam'),
  function(req, res) {
    // The request will be redirected to Steam for authentication, so
    // this function will not be called.
    //res.redirect('/auth/steam/return');
  });

app.get('/auth/steam/return',
  passport.authenticate('steam', { failureRedirect: '/login' }),
  function(req, res) {
    // Successful authentication, redirect home.
    res.redirect('/?steamid='+req.user);
    steamID = encodeURIComponent(JSON.stringify(req.user));
  });
  
app.get('/post',passport.authenticate('steam'),
    function(req, res, next){
    var location = req.encodeURIComponent(JSON.stringify(steamID));
    res.location = 'pebblejs://close#'+location;
    console.log("Hello!!!");
    next(res.location);
});
  
  
app.get('/', function(request, response) {
    response.write('<!DOCTYPE html>');
    response.write('<head><title>Wrist Steam, from Hull Softworks(Austin Hull) | Configuration Page</title></head>');
    response.write('<script src="https://code.jquery.com/jquery-1.9.1.min.js"></script>');
    response.write('<body bgcolor="black"><script type="text/javascript">');
    response.write('function returnID(){ var incomingID = decodeURIComponent(window.location.search.substring(1)); var splitID = incomingID.split("="); var finalID = splitID[1]; document.location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(finalID));}</script>');
    response.write('<script type="text/javascript">function cancel(){document.location = "pebblejs://close#";}</script>');
    if (request.user) {
        response.write(request.session.passport &&
            JSON.stringify(request.user) || 'None');
        //response.write('<form name="c" action="'+'http://pebblejs://close#'+encodeURIComponent(JSON.stringify(steamID))+'" method="get"><input name="b-save" value="Save SteamID to SteamPebble" type="button"/></form>');
    } else {
        if (!request.query.steamid) {
            response.write('<center><font color="white">Sign into Steam to link a new profile to Wrist Steam. Please note that OpenID is used for authentication, and that all account credentials are handled by the Steam login systems. After signing in through Steam, click the "Save SteamID to Wrist Steam" button.</font></center>');
        }
        response.write('<center><form name="a" action="/auth/steam" method="get">');
        response.write(
            '<input name="submit" type="image" src="http://steamcommunity-a.' +
            'akamaihd.net/public/images/signinthroughsteam/sits_large_border.png" ' +
            'alt="Sign in through Steam"/></form>');
        response.write('<form name="b" method="get">');
        response.write('<input name="b-save" value="Save SteamID to Wrist Steam" type="button" onClick="returnID()" /><br/>');
        response.write('<input name="b-cancel" value="Cancel" type="button" onClick="cancel()" /></form>');
        response.write('<font color="white">Copyright(C) 2015-2016 Hull Softworks (Austin Hull). Wrist Steam and Hull Softworks are not affiliated with Steam or Valve Software in any way. This is a free, open-source project, and can be audited at: https://www.github.com/AustinHull/SteamPebble.</font></center></body></html>')
    }
    response.send();
});

var port = 26648;
var server = app.listen(port);