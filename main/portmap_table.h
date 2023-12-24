#pragma once

#include "lwip/ip4_addr.h"
#if !IP_NAPT
#error "IP_NAPT must be defined"
#endif
#include "lwip/lwip_napt.h"

typedef struct portmap_table_entry {
  u32_t daddr;
  u16_t mport;
  u16_t dport;
  u8_t proto;
  u8_t valid;
} portmap_table_entry_t;

extern portmap_table_entry_t portmap_tab[IP_PORTMAP_MAX];
