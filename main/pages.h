#define CSS "\
:root{\
--primary:#0078e7;\
--success:#00b050;\
--danger:#e74c3c;\
--warning:#ffa500;\
--content:#808080;\
--nav-bg:#34495e;\
--nav-hover:#4a6785;\
--nav-active:#1f2d3d;\
}\
body{\
margin:0;\
}\
html{\
font-family:system-ui,  sans-serif;\
}\
nav{\
flex-wrap:wrap;\
display:flex;\
justify-content:space-around;\
background-color:var(--nav-bg);\
list-style:none;\
& *{\
display:flex;\
align-items:center;\
justify-content:center;\
margin:0;\
padding:0;\
flex-wrap:wrap;\
color:white;\
}\
> .heading{\
letter-spacing:5px;\
}\
> .nav-links{\
& a{\
display:block;\
color:white;\
text-decoration:none;\
letter-spacing:3px;\
font-weight:bold;\
font-size:14px;\
padding:14px 16px;\
&.active{\
background-color:var(--nav-active);\
}\
&:hover:not(.active),\
&:focus{\
background-color:var(--nav-hover);\
}\
}\
}\
}\
.container{\
display:flex;\
flex-wrap:wrap;\
flex-direction:column;\
align-content:center;\
font-weight:100;\
line-height:2em;\
margin:5px;\
& form{\
display:flex;\
flex-wrap:wrap;\
flex-direction:column;\
    align-items:flex-end;\
padding:0 10px;\
gap:10px;\
& label{\
align-items:center;\
justify-content:flex-end;\
}\
& input{\
width:210px;\
height:35px;\
border:1px solid #C4C4C4;\
border-radius:3px;\
padding:0px 14px;\
&:focus{\
border:1px solid #719ECE;\
outline:none;\
box-shadow:0 0 10px #719ECE;\
}\
&[type=submit]{\
width:240px;\
color:#fff;\
}\
}\
}\
& h2{\
font-size:1.2em;\
font-weight:200;\
}\
}\
.ok-button{\
background-color:var(--primary);\
}\
.red-button{\
background-color:var(--danger);\
}"

#define CONFIG_PAGE "<!DOCTYPE html>\
<html lang='en'>\
<head>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width, initial-scale=1'>\
<link rel='icon' href='data:,'>\
<link rel='stylesheet' href='style.css'>\
<title>ESP32 NAT Router</title>\
</head>\
<body>\
<nav>\
<div class='heading'>\
<h3>ESP32 NAT Router Config</h3>\
</div> \
<ul class='nav-links'>\
<li><a href='/'>Config</a></li>\
<li><a href='/status'>Status</a></li>\
<li><a href='/about'>About</a></li>\
</ul>\
</nav>\
<div class='container'>\
<h2>AP Settings (the new network)</h2>\
<form action method='GET'>\
<label>SSID <input type='text' name='ap_ssid' value='%s' placeholder='SSID of the new network'></label>\
<label>Password <input type='text' name='ap_password' value='%s' placeholder='Password of the new network'></label>\
<input type='submit' value='Set' class='ok-button'>\
<small><i>Password less than 8 chars = open</i></small>\
</form>\
<h2>STA Settings (uplink WiFi network)</h2>\
<form action method='GET'>\
<label>SSID <input type='text' name='ssid' value='%s' placeholder='SSID of existing network'></label>\
<label>Password <input type='text' name='password' value='%s' placeholder='Password of existing network'></label>\
<i>WPA2 Enterprise settings. Leave blank for regular</i>\
<label>Enterprise username <input type='text' name='ent_username' value='%s'></label>\
<label>Enterprise identity <input type='text' name='ent_identity' value='%s'></label>\
<input type='submit' value='Connect' class='ok-button'>\
</form>\
<h2>STA Static IP Settings</h2>\
<form action method='GET'>\
<label>Static IP <input type='text' name='staticip' value='%s'/></label>\
<label>Subnet Mask <input type='text' name='ssid' value='%s'></label>\
<label>Gateway <input type='text' name='ssid' value='%s'></label>\
<input type='submit' value='Connect' class='ok-button'/>\
<small><i>Leave it in blank if you want your ESP32 to get an IP using DHCP</i></small>\
</form>\
<h2>Device Management</h2>\
<form action method='GET'>\
<label>Device <input type='submit' name='reset' value='Reboot' class='red-button'/></label>\
</form>\
<script>\
document.querySelector('a[href=\"' + location.pathname + '\"]')?.classList.add('active');\
\
if (location.search.substr(1) != '')\
{\
document.querySelector('nav').style.display = 'none';\
document.querySelector('.container').innerHTML ='<h1>ESP32 NAT Router Config </h1>The new settings have been sent to the device.<br/>The page will refresh soon automatically...';\
setTimeout(\"location.href = '/'\",10000);\
}\
</script>\
</div>\
</body>\
</html>"

#define LOCK_PAGE "<html>\
<head></head>\
<meta name='viewport' content='width=device-width, initial-scale=1'>\
<style>\
body {\
font-family: apercu-pro, -apple-system, system-ui, BlinkMacSystemFont, 'Helvetica Neue', sans-serif;\
padding: 1em;\
line-height: 2em;\
font-weight: 100;\
}\
\
td {\
font-weight: 100;\
min-height: 24px;\
}\
\
td:first-child { \
text-align: right;\
min-width: 100px;\
padding-right: 10px;\
}\
\
h1 {\
font-size: 1.5em;\
font-weight: 200;\
}\
\
h2 {\
font-size: 1.2em;\
font-weight: 200;\
margin-left: 5px;\
}\
\
input {\
border: 1px solid rgb(196, 196, 196);\
color: rgb(76, 76, 76);\
width: 240px;\
border-radius: 3px;\
height: 40px;\
margin: 3px 0px;\
padding: 0px 14px;\
}\
\
input:focus {\
border:1px solid black;\
outline: none !important;\
box-shadow: 0 0 10px #719ECE;\
}\
\
#config {\
width:400px; \
margin:0 auto;\
}\
\
.ok-button {\
background-color: #0078e7;\
color: #fff;\
}\
\
.red-button {\
background-color: #e72e00;\
color: #fff;\
}\
</style>\
<body>\
<div id='config'>\
<h1>ESP32 NAT Router Config</h1>\
<script>\
if (window.location.search.substr(1) != '')\
{\
document.getElementById('config').display = 'none';\
document.body.innerHTML ='<h1>ESP32 NAT Router Config</h1>The new settings have been sent to the device.<br/>The page will refresh soon automatically...';\
setTimeout(\"location.href = '/'\",1000);\
}\
</script>\
<h2>Config Locked</h2>\
<form autocomplete='off' action='' method='GET'>\
<table>\
<tr>\
<td>Password:</td>\
<td><input type='password' name='unlock_password'/></td>\
</tr>\
<tr>\
<td></td>\
<td><input type='submit' value='Unlock' class='red-button'/></td>\
</tr>\
\
</table>\
<small>\
<i>Default: STA password to unlock<br />\
</small>\
</form>\
</div>\
</body>\
</html>\
"
