#include <stdlib.h>
#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_netif_ip_addr.h"

#include "portmap_page.h"
#include "portmap_table.h"
#include "router_globals.h"

static esp_err_t portmap_get_handler(httpd_req_t *req)
{
    // send top part of page
    const char* portmap_page_template = portmap_top;
    httpd_resp_send_chunk(req, portmap_page_template, strlen(portmap_page_template));

    // buffer for the page
    char* buf = malloc(sizeof(char) * 2048);
    // buffer pointer
    int page_ptr = 0;

    if (portmap_count >= IP_PORTMAP_MAX) { // max rules set
        page_ptr += sprintf(buf + page_ptr,"Max of %d rules set, delete an existing rule to add a new rule<br/><br/>", IP_PORTMAP_MAX);
    } else {
        const char* add_new = portmap_add_new;
        page_ptr += sprintf(buf + page_ptr, add_new);
    }

    page_ptr += sprintf(buf + page_ptr, "Current Portmap Rules<br/>");

    if (portmap_count > 0) 
    {
        page_ptr += sprintf(buf + page_ptr, "<table>");
        const char* row = portmap_current_row; // row size with data = 162
        ip4_addr_t saddr;
        ip4_addr_t daddr;

        for (int i = 0; i<IP_PORTMAP_MAX; i++) {
            if (portmap_tab[i].valid) {
                saddr.addr = my_ip;
                daddr.addr = portmap_tab[i].daddr;

                page_ptr += sprintf(buf + page_ptr, row, 
                        portmap_tab[i].proto == PROTO_TCP ? "TCP ":"UDP ", 
                        IP2STR(&saddr), portmap_tab[i].mport,
                        IP2STR(&daddr), portmap_tab[i].dport,
                        portmap_tab[i].proto == PROTO_TCP ? "TCP":"UDP", 
                        portmap_tab[i].mport);
            }

            if ((i % 6) == 0){ // Send chunk and reset buffer (162 * 6) = 972
                httpd_resp_send_chunk(req, buf, page_ptr);
                page_ptr = 0;
            }
        }
        page_ptr += sprintf(buf + page_ptr, "</table>");
    }
    else 
    {
        page_ptr += sprintf(buf + page_ptr,"<table><tr><td>No rules set at this time</td></tr></table>");
    }
    
    httpd_resp_send_chunk(req, buf, strlen(buf));
    free(buf);

    // send bottom part of page
    portmap_page_template = portmap_bottom;
    httpd_resp_send_chunk(req, portmap_page_template, strlen(portmap_page_template));

    // send last chunk
    httpd_resp_send_chunk(req, NULL, 0);

    return ESP_OK;
}

httpd_uri_t portmapp = {
    .uri       = "/portmap",
    .method    = HTTP_GET,
    .handler   = portmap_get_handler,
};

static esp_err_t portmap_add_handler(httpd_req_t *req)
{
    size_t buf_len;
    char* buf;

    buf_len = httpd_req_get_url_query_len(req) + 1;
    buf = malloc(buf_len);

    char param_proto[4];
    char param_mport[10];
    char param_dip[20];
    char param_dport[10];

    ESP_ERROR_CHECK(httpd_req_get_url_query_str(req, buf, buf_len));

    httpd_query_key_value(buf, "proto", param_proto, sizeof(param_proto));
    httpd_query_key_value(buf, "mport", param_mport, sizeof(param_mport));
    httpd_query_key_value(buf, "dip", param_dip, sizeof(param_dip));
    httpd_query_key_value(buf, "dport", param_dport, sizeof(param_dport));

    uint8_t tcp_udp = strcmp(param_proto,"TCP") == 0 ? PROTO_TCP : PROTO_UDP;

    if (add_portmap(tcp_udp, (uint16_t) atoi(param_mport), ipaddr_addr(param_dip), (uint16_t) atoi(param_dport)) == ESP_OK) {
        httpd_resp_send(req, "Portmap rule added", strlen("Portmap rule added"));
    } else {
        httpd_resp_send(req, "Error could not add rule", strlen("Error could not add rule"));
    }
    
    free(buf);

    return ESP_OK;
}

httpd_uri_t portmapp_add = {
    .uri       = "/portmap",
    .method    = HTTP_PUT,
    .handler   = portmap_add_handler,
};

static esp_err_t portmap_del_handler(httpd_req_t *req)
{
    size_t buf_len;
    char* buf;

    buf_len = httpd_req_get_url_query_len(req) + 1;
    buf = malloc(buf_len);

    ESP_ERROR_CHECK(httpd_req_get_url_query_str(req, buf, buf_len));

    char param_proto[4];
    char param_mport[10];

    httpd_query_key_value(buf, "proto", param_proto, sizeof(param_proto));
    httpd_query_key_value(buf, "mport", param_mport, sizeof(param_mport));

    uint8_t tcp_udp = strcmp(param_proto,"TCP") == 0 ? PROTO_TCP : PROTO_UDP;

    if (del_portmap(tcp_udp, (uint16_t)atoi(param_mport)) == ESP_OK) {
        httpd_resp_send(req, "Portmap rule deleted", strlen("Portmap rule deleted"));
    } else {
        httpd_resp_send(req, "Error could not delete rule", strlen("Error could not delete rule"));
    }
    
    free(buf);

    return ESP_OK;
}

httpd_uri_t portmapp_del = {
    .uri       = "/portmap",
    .method    = HTTP_DELETE,
    .handler   = portmap_del_handler,
};

static esp_err_t portmap_js_get_handler(httpd_req_t *req)
{
    const char* portmap_js = portmap_script;

    httpd_resp_set_hdr(req, "Cache-Control", "max-age=3600");
    httpd_resp_set_type(req, "text/javascript");

    httpd_resp_send(req, portmap_js, strlen(portmap_js));

    return ESP_OK;
}

httpd_uri_t portmapp_js = {
    .uri       = "/portmap/js",
    .method    = HTTP_GET,
    .handler   = portmap_js_get_handler,
};

void register_portmap_uri_handlers(httpd_handle_t server) {
    httpd_register_uri_handler(server, &portmapp);
    httpd_register_uri_handler(server, &portmapp_js);
    httpd_register_uri_handler(server, &portmapp_del);
    httpd_register_uri_handler(server, &portmapp_add);  
}
