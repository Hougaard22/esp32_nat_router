#pragma once

extern httpd_uri_t cssp;

#define CSS_PAGE "html * {\
font-weight: 100;}\
body {\
font-family: system-ui, sans-serif;\
padding: 0em;\
margin: 0;\
line-height: 2em;\
}\
td {\
min-height: 24px;\
}\
td:first-child {\
text-align: right;\
min-width: 130px;\
padding-right: 10px;\
}\
h1 {\
font-size: 1.5em;\
}\
h2 {\
font-size: 1.2em;\
padding-top: 5px;\
}\
input {\
border: 1px solid rgb(196, 196, 196);\
color: rgb(76, 76, 76);\
width: 240px;\
border-radius: 3px;\
height: 40px;\
margin: 3px 0px;\
padding: 0px 14px;\
}\
input:focus {\
border:1px solid black;\
outline: none !important;\
box-shadow: 0 0 10px #719ECE;\
}\
#config {\
max-width:400px;\
margin:0 auto;\
width:100%;\
}\
.ok-button {\
background-color: #0078e7;\
color: #fff;\
}\
.red-button {\
background-color: #e72e00;\
color: #fff;\
}\
*:disabled {\
background-color: lightgray;\
}\
.nav-bar {\
padding: 0 20 0 20;\
background-color: #0078e7;\
text-align: center;\
padding: 5px;\
}\
.nav-link {\
display: inline-block;\
width: 100px;\
color: White;\
text-decoration: none;\
}\
"
