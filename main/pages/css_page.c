#include "esp_err.h"
#include "esp_http_server.h"

#include "css_page.h"
#include "router_globals.h"

static esp_err_t css_get_handler(httpd_req_t *req)
{
    const char* css_page_template = CSS_PAGE;

    httpd_resp_set_hdr(req, "Cache-Control", "max-age=3600");
    httpd_resp_set_type(req, "text/css");

    httpd_resp_send(req, css_page_template, strlen(css_page_template));

    return ESP_OK;
}

httpd_uri_t cssp = {
    .uri       = "/css",
    .method    = HTTP_GET,
    .handler   = css_get_handler,
};
