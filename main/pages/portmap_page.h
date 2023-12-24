extern httpd_uri_t portmapp;

#define portmap_top "<html>\
<head>\
<title>Port Forwarding</title>\
<meta charset=\"utf-8\">\
<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\
<link rel='stylesheet' type='text/css' href='css'/>\n\
<script> \n\
function do_delete(proto,mport) { \n\
    var XHR = new XMLHttpRequest(); \n\
    XHR.open( \"GET\", `?delete=${mport}&proto=${proto}`, true ); \n\
      XHR.onloadend = function(){ \n\
        alert( XHR.responseText ); \n\
        location.reload(); \n\
      } \n\
    XHR.send( null ); \n\
} \n\
function do_add() { \n\
  var b = document.getElementById(\"nproto\").value; \n\
  var c = document.getElementById(\"port\").value; \n\
  var d = document.getElementById(\"dip\").value; \n\
  var e = document.getElementById(\"dport\").value; \n\
  if ((b == null || b.trim() == \"\") || (c == null || c.trim() == \"\") || (d == null || d.trim() == \"\") || (e == null || e.trim() == \"\")) { \n\
    alert( \"All fields must have valid values\" ); \n\
  } else { \n\
    var XHR = new XMLHttpRequest(); \n\
    XHR.open( \"GET\", `?add=${c.trim()}&nproto=${b}&dip=${d.trim()}&dport=${e.trim()}`, true ); \n\
      XHR.onloadend = function(){ \n\
        alert( XHR.responseText ); \n\
        location.reload(); \n\
      } \n\
    XHR.send( null ); \n\
  } \n\
} \n\
</script>\
</head>\
<body>\
<nav id='topnav'>\
<a class='nav-link' href='/'>CONFIG</a>\
<a class='nav-link' href='/info'>INFO</a>\
<a class='nav-link' href='/portmapping'>PORTMAP</a>\
</nav>\
<div>\
<center>\
<h1>Port Forwarding</h1>\n\
";

#define portmap_bottom "</center>\
</div>\
</body>\
</html>\
";
