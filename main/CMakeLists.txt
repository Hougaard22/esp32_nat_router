idf_component_register(SRCS "esp32_nat_router.c"
                            "http_server.c"
                            "portmap_table.c"
                            "pages/css_page.c"
                    INCLUDE_DIRS "."
                            "pages"
                        )

set_source_files_properties(http_server.c
    PROPERTIES COMPILE_FLAGS
    -Wno-unused-function
)
