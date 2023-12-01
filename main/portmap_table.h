#ifdef __cplusplus
extern "C" {
#endif



//typedef struct portmap_table_entry portmap_table_entry_t;

//extern struct portmap_table_entry portmap_tab[IP_PORTMAP_MAX];

esp_err_t apply_portmap_tab();
esp_err_t delete_portmap_tab();
void print_portmap_tab();
esp_err_t get_portmap_tab();
esp_err_t add_portmap(uint8_t proto, uint16_t mport, uint32_t daddr, uint16_t dport);
esp_err_t del_portmap(uint8_t proto, uint16_t mport);

#ifdef __cplusplus
}
#endif
