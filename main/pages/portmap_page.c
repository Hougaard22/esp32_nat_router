#include <stdlib.h>
#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_netif_ip_addr.h"

#include "portmap_page.h"
#include "portmap_table.h"
#include "router_globals.h"

char * the_page = NULL;  // used to hold complete response page before its sent to browser

static esp_err_t portmap_get_handler(httpd_req_t *req)
{
    char*  buf;
    size_t buf_len;

    //const char* template = msg1;
    the_page = malloc(sizeof(char) * 5000);

    char param_delete[10]; // has mport
    char param_proto[12];
    char param_add[10];  // has mport
    char param_nproto[12];
    char param_dip[20];
    char param_dport[10];

    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1) {
        buf = malloc(buf_len);
        ESP_ERROR_CHECK(httpd_req_get_url_query_str(req, buf, buf_len));
        // process setting network if info is there
        if (httpd_query_key_value(buf, "delete", param_delete, sizeof(param_delete)) != ESP_OK) 
            strcpy(param_delete,"");
        if (httpd_query_key_value(buf, "proto", param_proto, sizeof(param_proto)) != ESP_OK) 
            strcpy(param_proto,"");
        if (httpd_query_key_value(buf, "add", param_add, sizeof(param_add)) != ESP_OK) 
            strcpy(param_add,"");
        if (httpd_query_key_value(buf, "nproto", param_nproto, sizeof(param_nproto)) != ESP_OK) 
            strcpy(param_nproto,"");
        if (httpd_query_key_value(buf, "dip", param_dip, sizeof(param_dip)) != ESP_OK) 
            strcpy(param_dip,"");
        if (httpd_query_key_value(buf, "dport", param_dport, sizeof(param_dport)) != ESP_OK) 
            strcpy(param_dport,"");


        // delete port forwarding rule
        if (strlen(param_delete) > 0 && strlen(param_proto) > 0) {
            uint8_t tcp_udp;
            if (strcmp(param_proto,"PROTO_TCP") == 0) {
                tcp_udp = PROTO_TCP;
            } else {
                tcp_udp = PROTO_UDP;
            }
            del_portmap(tcp_udp, (uint16_t) atoi(param_delete));

            char* restxt = "Portmapped rule deleted";
            httpd_resp_send(req, restxt, strlen(restxt));
            return ESP_OK;
        }

        // add port forwarding rule
        if (strlen(param_add) > 0 && strlen(param_nproto) > 0 && strlen(param_dip) > 0 && strlen(param_dport) > 0) {
            uint8_t tcp_udp;
            if (strcmp(param_nproto,"PROTO_TCP") == 0) {
                tcp_udp = PROTO_TCP;
            } else {
                tcp_udp = PROTO_UDP;
            }
            add_portmap(tcp_udp, (uint16_t) atoi(param_add), ipaddr_addr(param_dip), (uint16_t) atoi(param_dport));
            char* restxt = "Portmapped rule add";
            httpd_resp_send(req, restxt, strlen(restxt));
            return ESP_OK;
        }
        free(buf);
        strcpy(the_page, "Bad command");
        httpd_resp_send(req, the_page, strlen(the_page));
        return ESP_OK;
    }

    const char* portmap_page_template = portmap_top;

    // send first chunk
    httpd_resp_send_chunk(req, portmap_page_template, strlen(portmap_page_template));

    int rulecount = 0;
    for (int i = 0; i<IP_PORTMAP_MAX; i++) {
        if (portmap_tab[i].valid) { rulecount++; }
    }

    buf = malloc(200);
    if (rulecount >= IP_PORTMAP_MAX) { // max rules set
        sprintf (buf,"Max of %d rules set, delete an existing rule to add a new rule<br/><br/>\n", IP_PORTMAP_MAX);
        strcat(the_page,buf);
    } else {
        strcpy(the_page, "Add a new Portmap Rule<br/><table>"); 
        strcat(the_page, "<tr><td>&nbsp;Proto</td><td>&nbsp;Port</td><td>&nbsp;Dest IP</td><td>&nbsp;Dest Port</td><tr>"); 
        strcat(the_page, "<tr><td><select id=\"nproto\"><option value=\"PROTO_TCP\">TCP</option><option value=\"PROTO_UDP\">UDP</option></select></td><td><input type=\"text\" id=\"port\" maxlength=\"5\"></td><td><input type=\"text\" id=\"dip\" maxlength=\"15\"></td><td><input type=\"text\" id=\"dport\" maxlength=\"5\"></td><td><input type=\"button\" value=\"Add\" onclick=\"do_add();\" class='ok-button'></td><tr>\n"); 
        strcat(the_page,"</table><br/>\n");
    }  

    strcat(the_page, "Current Portmap Rules<br/><table>\n");

    if (rulecount > 0) {
        for (int i = 0; i<IP_PORTMAP_MAX; i++) {
            if (portmap_tab[i].valid) {
                sprintf (buf,"<tr><td>%s", portmap_tab[i].proto == PROTO_TCP?"TCP ":"UDP ");
                strcat(the_page,buf);
                ip4_addr_t addr;
                addr.addr = my_ip;
                sprintf (buf, IPSTR":%d -> ", IP2STR(&addr), portmap_tab[i].mport);
                strcat(the_page,buf);
                addr.addr = portmap_tab[i].daddr;
                sprintf (buf, IPSTR":%d</td>\n", IP2STR(&addr), portmap_tab[i].dport);
                strcat(the_page,buf);
                sprintf (buf, "<td><input type=\"button\" value=\"Delete\" onclick=\"do_delete('PROTO_%s',%d);\" class='ok-button'></td></tr>\n", portmap_tab[i].proto == PROTO_TCP?"TCP":"UDP",portmap_tab[i].mport);
                strcat(the_page,buf);
            }
        }
    }
      else {
        strcat(the_page,"<tr><td>No rules set at this time</td></tr>\n");
    }
    free(buf);
    strcat(the_page, "</table>\n");

    httpd_resp_send_chunk(req, the_page, strlen(the_page));

    // send second chunk
    portmap_page_template = portmap_bottom;
    httpd_resp_send_chunk(req, portmap_page_template, strlen(portmap_page_template));

    // send last chunk
    httpd_resp_send_chunk(req, NULL, 0);

    free(the_page);

    return ESP_OK;
}

httpd_uri_t portmapp = {
    .uri       = "/portmapping",
    .method    = HTTP_GET,
    .handler   = portmap_get_handler,
};
