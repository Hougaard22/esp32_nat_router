#include "esp_err.h"
#include "esp_http_server.h"

#include "info_page.h"
#include "router_globals.h"

static esp_err_t info_get_handler(httpd_req_t *req)
{
    const char* info_page_template = INFO_PAGE;

    int page_len =
        strlen(info_page_template) +
        strlen(subnet_mask) +
        strlen(ap_ip) +
        strlen(gateway_addr) +
        strlen(ap_dns) +
        32;
    char* info_page = malloc(sizeof(char) * page_len);

    snprintf(
        info_page, page_len, info_page_template,
        ap_ip, subnet_mask, gateway_addr, ap_dns);

    httpd_resp_send(req, info_page, strlen(info_page));

    free(info_page);
    
    return ESP_OK;
}

httpd_uri_t infop = {
    .uri       = "/info",
    .method    = HTTP_GET,
    .handler   = info_get_handler,
};