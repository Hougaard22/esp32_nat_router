#include "esp_err.h"
#include "esp_timer.h"
#include "esp_http_server.h"

#include "info_page.h"
#include "router_globals.h"

void format_time(char *buffer, size_t buffer_size) {
    int64_t time_us = esp_timer_get_time();
    int64_t time_s = time_us / 1000000; // convert microseconds to seconds

    int32_t days = time_s / 86400;
    time_s = time_s % 86400;

    int32_t hours = time_s / 3600;
    time_s = time_s % 3600;

    int32_t minutes = time_s / 60;
    int32_t seconds = time_s % 60;

    sprintf(buffer, "%ld days, %ld hours, %ld minutes, %ld seconds", days, hours, minutes, seconds);
}

static esp_err_t info_get_handler(httpd_req_t *req)
{
    const char* info_page_template = INFO_PAGE;
    
    char* uptime_str = malloc(sizeof(char) * 50);
    format_time(uptime_str, sizeof(uptime_str));

    

    int page_len =
        strlen(info_page_template) +
        strlen(ap_ssid) +
        strlen(ap_ip) +
        strlen(ssid) +
        strlen(sta_ip) +
        strlen(subnet_mask) +
        strlen(gateway_addr) +
        strlen(ap_dns) +
        strlen(uptime_str) +
        32;
    char* info_page = malloc(sizeof(char) * page_len);

    snprintf(
        info_page, page_len, info_page_template,
        ap_ssid, ap_ip, ssid, sta_ip, subnet_mask, gateway_addr, ap_dns, uptime_str);

    httpd_resp_send(req, info_page, strlen(info_page));

    free(uptime_str);
    free(info_page);
    
    return ESP_OK;
}

httpd_uri_t infop = {
    .uri       = "/info",
    .method    = HTTP_GET,
    .handler   = info_get_handler,
};
