#pragma once

void register_portmap_uri_handlers(httpd_handle_t server);

#define portmap_script "\
function deleteEntry(proto,mport) { \n\
    var XHR = new XMLHttpRequest(); \n\
    XHR.open( 'DELETE', `?mport=${mport}&proto=${proto}`, true ); \n\
      XHR.onloadend = function(){ \n\
        alert( XHR.responseText ); \n\
        location.reload(); \n\
      } \n\
    XHR.send( null ); \n\
} \n\
function addEntry() { \n\
    var proto = document.getElementById('proto').value; \n\
    var mport = document.getElementById('mport').value; \n\
    var dip = document.getElementById('dip').value; \n\
    var dport = document.getElementById('dport').value; \n\
    var XHR = new XMLHttpRequest(); \n\
    XHR.open( 'PUT', `?proto=${proto}&mport=${mport.trim()}&dip=${dip.trim()}&dport=${dport.trim()}`, true ); \n\
      XHR.onloadend = function(){ \n\
        alert( XHR.responseText ); \n\
        location.reload(); \n\
      } \n\
    XHR.send( null ); \n\
}";

#define portmap_top "\
<!DOCTYPE html> \n\
<html lang='en'> \n\
<head> \n\
<title>esp32_nat_router (Portmap)</title> \n\
<meta name='viewport' content='width=device-width,initial-scale=1'> \n\
<link rel='stylesheet' type='text/css' href='css'/> \n\
<script src='portmap/js' type='text/javascript'></script> \n\
</head> \n\
<body> \n\
<nav class='nav-bar'>\
<a class='nav-link' href='/'>CONFIG</a> \
<a class='nav-link' href='/info'>INFO</a> \
<a class='nav-link' href='/portmap'>PORTMAP</a> \
</nav> \n\
<div id='config'> \n\
<h1>ESP32 NAT Router Portmap</h1>";

#define portmap_add_new "\
Add a new Portmap Rule \n\
    <form id='naptForm'> \n\
        <div class='form-row'> \n\
            <div class='form-column'> \n\
                <label for='proto'>Protocol:</label> \n\
                <select id='proto' name='proto'> \n\
                    <option value='TCP'>TCP</option> \n\
                    <option value='UDP'>UDP</option> \n\
                </select> \n\
            </div> \n\
            <div class='form-column'> \n\
                <label for='mport'>Local Port:</label> \n\
                <input type='text' id='mport' name='mport' pattern='\\d*' maxlength='5'> \n\
            </div> \n\
            <div class='form-column'> \n\
                <label for='dip'>Dest IP:</label> \n\
                <input type='text' id='dip' name='dip' minlength='7' maxlength='15' pattern='^([0-9]{1,3}\\.){3}[0-9]{1,3}$'> \n\
            </div> \n\
            <div class='form-column'> \n\
                <label for='dport'>Dest Port:</label> \n\
                <input type='text' id='dport' name='dport'  pattern='\\d*' maxlength='5'> \n\
            </div> \n\
        </div> \n\
        <input type='button' value='Add Entry' onclick='addEntry()' class='ok-button'> \n\
        <input type='reset' value='Reset'> \n\
    </form> \n\
<br/>";

#define portmap_current_row "\
<tr>\
<td><span>%s</span>\t %d.%d.%d.%d:%d -> %d.%d.%d.%d:%d</td>\n\
<td><input type='button' value='Delete' onclick=\"deleteEntry('%s',%d)\"; class='red-button'></td>\n\
</tr>";

#define portmap_bottom "\
</div>\n\
</body>\n\
</html>\
";
