#pragma once

extern httpd_uri_t infop;

#define INFO_PAGE "<!DOCTYPE html>\
<html lang='en'>\
	<head>\
		<title>esp32_nat_router (Info)</title>\
		<link rel='stylesheet' type='text/css' href='css' />\
		<meta name='viewport' content='width=device-width, initial-scale=1'>\
	</head>\
	<body>\
		<nav class='nav-bar'>\
            <a class='nav-link' href='/'>CONFIG</a>\
            <a class='nav-link' href='/info'>INFO</a>\
            <a class='nav-link' href='/portmap'>PORTMAP</a>\
		</nav>\
		<div id='info-container'>\
				<div>\
					<h1>ESP32 NAT Router Info</h1>\
			  	</div>\
				    <h3>Network Info</h3>\
                    <div class='info-row'>\
						<span class='info-label'>AP SSIDs:</span> \
						<span id='apSSID' class='info-value'>%s</span>\
					</div>\
					<div class='info-row'>\
						<span class='info-label'>AP IP Address:</span> \
						<span id='apIpAddress' class='info-value'>%s</span>\
					</div>\
                    <div class='info-row'>\
						<span class='info-label'>STA SSID:</span> \
						<span id='staSSID' class='info-value'>%s</span>\
					</div>\
					<div class='info-row'>\
						<span class='info-label'>STA IP Address:</span> \
						<span id='staIpAddress' class='info-value'>%s</span>\
					</div>\
                    <div class='info-row'>\
						<span class='info-label'>Subnet Mask:</span> \
						<span id='subnetMask' class='info-value'>%s</span>\
					</div>\
					<div class='info-row'>\
						<span class='info-label'>Gateway:</span> \
						<span id='gateway' class='info-value'>%s</span>\
					</div>\
					<div class='info-row'>\
						<span class='info-label'>DNS Server:</span> \
						<span id='dnsServer' class='info-value'>%s</span>\
					</div>\
					<h3>Network Statistics</h3>\
					<div class='info-row'>\
					<span class='info-label'>Uptime:</span> \
					<span id='uptime' class='info-value'>%s</span>\
				</div>\
		</div>\
	</body>\
</html>"
