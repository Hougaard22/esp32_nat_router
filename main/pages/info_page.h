extern httpd_uri_t infop;

#define INFO_PAGE "\
<html>\
<head>\
<title>Info</title>\
<link rel='stylesheet' type='text/css' href='css' />\
<meta name='viewport' content='width=device-width, initial-scale=1'>\
</head>\
<body>\
<nav id='topnav'>\
<a class='nav-link' href='/'>CONFIG</a>\
<a class='nav-link' href='/info'>INFO</a>\
<a class='nav-link' href='/portmapping'>PORTMAP</a>\
</nav>\
<div id='config'>\
<h1>ESP32 NAT Router Info</h1>\
<h2>AP info</h2>\
<table>\
<tr>\
<td>IP</td>\
<td><input disabled type='text' name='ap_ip' value='%s'/></td>\
</tr>\
<tr>\
<td>Subnet Mask</td>\
<td><input disabled type='text' name='ap_netmask' value='%s'/></td>\
</tr>\
<tr>\
<td>Gateway</td>\
<td><input disabled type='text' name='ap_gw' value='%s'/></td>\
</tr>\
<tr>\
<td>DNS Server</td>\
<td><input disabled type='text' name='ap_dns' value='%s'/></td>\
</tr>\
</table>\
</div>\
</body>\
</html>\
"
