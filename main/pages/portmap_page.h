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

#define portmap_top "<html lang='en'><head>\
    <title>esp32_nat_router (Portmap)</title>\
    <meta name='viewport' content='width=device-width,initial-scale=1'>\
    <link rel='stylesheet' type='text/css' href='css'>\
    <script src='portmap/js' type='text/javascript'></script>\
</head>\
<body>\
    <nav class='nav-bar'>\
        <a class='nav-link' href='/'>CONFIG</a>\
        <a class='nav-link' href='/info'>INFO</a>\
        <a class='nav-link' href='/portmap'>PORTMAP</a>\
    </nav>\
    <div id='container'>\
        <div>\
            <h1>ESP32 NAT Router Portmap</h1>";

#define portmap_add_new "\
            <form id='naptForm'>\
                    <div>\
                        <label for='proto'>Protocol:</label>\
                        <select id='proto' name='proto'>\
                            <option value='TCP'>TCP</option>\
                            <option value='UDP'>UDP</option>\
                        </select>\
                    </div>\
                    <div>\
                        <label for='mport'>Local Port:</label>\
                        <input type='text' id='mport' name='mport' pattern='\\d*' maxlength='5'>\
                    </div>\
                    <div>\
                        <label for='dip'>Dest IP:</label>\
                        <input type='text' id='dip' name='dip' minlength='7' maxlength='15' pattern='^([0-9]{1,3}\\.){3}[0-9]{1,3}$'>\
                    </div>\
                    <div>\
                        <label for='dport'>Dest Port:</label>\
                        <input type='text' id='dport' name='dport' pattern='\\d*' maxlength='5'>\
                    </div>\
                <input type='button' value='Add Entry' onclick='addEntry()' class='ok-button'>\
                <input type='reset' value='Reset'>\
            </form>\
";

#define portmap_current_row "\
<tr>\
    <td>%s</td>\n\
    <td>%d.%d.%d.%d:%d</td>\n\
    <td>-></td>\n\
    <td>%d.%d.%d.%d:%d</td>\n\
    <td><input type='button' value='Delete' onclick=\"deleteEntry('%s',%d)\"; class='red-button'></td>\n\
</tr>";

#define portmap_bottom "\
        </div>\
    </div>\
</body></html>";
