#include "esp_err.h"
#include "esp_http_server.h"

#include "info_page.h"
#include "router_globals.h"

static esp_err_t info_get_handler(httpd_req_t *req)
{
    const char* info_page_template = INFO_PAGE;

    char* safe_ap_ip = html_escape(ap_ip);
    char* safe_netmask = html_escape(subnet_mask);
    char* safe_gateway_addr = html_escape(gateway_addr);
    char* safe_ap_dns = html_escape("routerinfo.ap_dns");

    int page_len =
        strlen(info_page_template) +
        strlen(safe_netmask) +
        strlen(safe_ap_ip) +
        strlen(safe_gateway_addr) +
        strlen(safe_ap_dns) +
        256;
    char* info_page = malloc(sizeof(char) * page_len);

    snprintf(
        info_page, page_len, info_page_template,
        safe_ap_ip, safe_netmask, safe_gateway_addr, safe_ap_dns);

    free(safe_ap_ip);
    free(safe_netmask);
    free(safe_gateway_addr);
    free(safe_ap_dns);

    httpd_resp_send(req, info_page, strlen(info_page));

    return ESP_OK;
}

static httpd_uri_t infop = {
    .uri       = "/info",
    .method    = HTTP_GET,
    .handler   = info_get_handler,
};