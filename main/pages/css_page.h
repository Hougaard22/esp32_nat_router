#pragma once

extern httpd_uri_t cssp;

#define CSS_PAGE "body {\
    font-weight: 100;\
    font-family: system-ui, sans-serif;\
    margin: 0;\
    line-height: 2em;\
}\
select,\
input {\
    border: 1px solid rgb(196, 196, 196);\
    color: rgb(76, 76, 76);\
    width: 100%;\
    border-radius: 3px;\
    height: 40px;\
    margin: 3px 0px;\
    padding: 0px 10px;\
}\
    input:focus {\
    border:1px solid black;\
    outline: none !important;\
    box-shadow: 0 0 10px #719ECE;\
}\
#container {\
    display: flex;\
    flex-direction: column;\
    flex-wrap: nowrap;\
    align-items: center;\
    width: 100%;\
}\
#container div {\
    display: flex; \
    flex-direction: column;\
    min-width: 400px;\
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
table {\
    width: 100%;\
    border-collapse: collapse;\
    margin-top: 10px;\
}\
#info-container {\
    display: flex;\
    flex-direction: column;\
    flex-wrap: nowrap;\
    align-items: center;\
    width: 100%;\
}\
#info-container div {\
    min-width: 400px;\
}\
.info-row {\
    display: flex;\
    align-items: center;\
    padding: 8px;\
    background-color: #c0c0c0;\
}\
.info-row:nth-child(even) {\
    background-color: #e0e0e0;\
}\
.info-label {\
    font-weight: bold;\
    width: 30%;\
}\
.info-value {\
    margin-right: 10px;\
    flex-grow: 1;\
    text-align: right;\
}"
