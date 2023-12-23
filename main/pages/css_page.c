#include "esp_err.h"
#include "esp_http_server.h"

#include "css_page.h"
#include "router_globals.h"

static esp_err_t css_get_handler(httpd_req_t *req)
{
    const char* css_page_template = CSS_PAGE;

    int page_len =
        strlen(css_page_template) +
        256;
    char* css_page = malloc(sizeof(char) * page_len);

    snprintf(css_page, page_len, css_page_template);

    httpd_resp_set_hdr(req, "Cache-Control", "max-age=3600");
    httpd_resp_send(req, css_page, strlen(css_page));

    free(css_page);
    return ESP_OK;
}

httpd_uri_t cssp = {
    .uri       = "/css",
    .method    = HTTP_GET,
    .handler   = css_get_handler,
};
