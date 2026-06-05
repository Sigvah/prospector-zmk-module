zephyr_include_directories(include)
zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)
zephyr_library()

if(CONFIG_SHIELD_PROSPECTOR_ADAPTER)

        add_subdirectory(${ZEPHYR_CURRENT_MODULE_DIR}/drivers/display)
        add_subdirectory(${ZEPHYR_CURRENT_MODULE_DIR}/modules/lvgl)

        if(CONFIG_DT_HAS_ZMK_BEHAVIOR_CAPS_WORD_ENABLED)
                zephyr_library_sources(src/events/caps_word_state_changed.c)
                set_source_files_properties(
                        ${APPLICATION_SOURCE_DIR}/src/behaviors/behavior_caps_word.c
                        TARGET_DIRECTORY app
                        PROPERTIES HEADER_FILE_ONLY ON)
                target_sources(app PRIVATE src/behaviors/behavior_caps_word.c)
        endif()

        # These sources pull in <zmk/ble.h> and BLE split-central APIs, which
        # only exist when Bluetooth is enabled. Building them without BLE leads
        # to errors such as 'CONFIG_BT_MAX_PAIRED' undeclared, so only compile
        # them when ZMK BLE support is present.
        if(CONFIG_ZMK_BLE)
                zephyr_library_sources(src/events/split_central_status_changed.c)
                zephyr_library_sources(src/split/bluetooth/central_status_changed_observer.c)
        endif()

endif()