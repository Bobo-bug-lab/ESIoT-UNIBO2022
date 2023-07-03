#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "iothub_service_client" for configuration "Debug"
set_property(TARGET iothub_service_client APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(iothub_service_client PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/iothub_service_client.lib"
  )

list(APPEND _cmake_import_check_targets iothub_service_client )
list(APPEND _cmake_import_check_files_for_iothub_service_client "${_IMPORT_PREFIX}/debug/lib/iothub_service_client.lib" )

# Import target "hsm_security_client" for configuration "Debug"
set_property(TARGET hsm_security_client APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(hsm_security_client PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/hsm_security_client.lib"
  )

list(APPEND _cmake_import_check_targets hsm_security_client )
list(APPEND _cmake_import_check_files_for_hsm_security_client "${_IMPORT_PREFIX}/debug/lib/hsm_security_client.lib" )

# Import target "prov_auth_client" for configuration "Debug"
set_property(TARGET prov_auth_client APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(prov_auth_client PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/prov_auth_client.lib"
  )

list(APPEND _cmake_import_check_targets prov_auth_client )
list(APPEND _cmake_import_check_files_for_prov_auth_client "${_IMPORT_PREFIX}/debug/lib/prov_auth_client.lib" )

# Import target "iothub_client" for configuration "Debug"
set_property(TARGET iothub_client APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(iothub_client PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/iothub_client.lib"
  )

list(APPEND _cmake_import_check_targets iothub_client )
list(APPEND _cmake_import_check_files_for_iothub_client "${_IMPORT_PREFIX}/debug/lib/iothub_client.lib" )

# Import target "iothub_client_http_transport" for configuration "Debug"
set_property(TARGET iothub_client_http_transport APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(iothub_client_http_transport PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/iothub_client_http_transport.lib"
  )

list(APPEND _cmake_import_check_targets iothub_client_http_transport )
list(APPEND _cmake_import_check_files_for_iothub_client_http_transport "${_IMPORT_PREFIX}/debug/lib/iothub_client_http_transport.lib" )

# Import target "iothub_client_amqp_transport" for configuration "Debug"
set_property(TARGET iothub_client_amqp_transport APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(iothub_client_amqp_transport PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/iothub_client_amqp_transport.lib"
  )

list(APPEND _cmake_import_check_targets iothub_client_amqp_transport )
list(APPEND _cmake_import_check_files_for_iothub_client_amqp_transport "${_IMPORT_PREFIX}/debug/lib/iothub_client_amqp_transport.lib" )

# Import target "iothub_client_amqp_ws_transport" for configuration "Debug"
set_property(TARGET iothub_client_amqp_ws_transport APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(iothub_client_amqp_ws_transport PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/iothub_client_amqp_ws_transport.lib"
  )

list(APPEND _cmake_import_check_targets iothub_client_amqp_ws_transport )
list(APPEND _cmake_import_check_files_for_iothub_client_amqp_ws_transport "${_IMPORT_PREFIX}/debug/lib/iothub_client_amqp_ws_transport.lib" )

# Import target "iothub_client_mqtt_transport" for configuration "Debug"
set_property(TARGET iothub_client_mqtt_transport APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(iothub_client_mqtt_transport PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/iothub_client_mqtt_transport.lib"
  )

list(APPEND _cmake_import_check_targets iothub_client_mqtt_transport )
list(APPEND _cmake_import_check_files_for_iothub_client_mqtt_transport "${_IMPORT_PREFIX}/debug/lib/iothub_client_mqtt_transport.lib" )

# Import target "iothub_client_mqtt_ws_transport" for configuration "Debug"
set_property(TARGET iothub_client_mqtt_ws_transport APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(iothub_client_mqtt_ws_transport PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/iothub_client_mqtt_ws_transport.lib"
  )

list(APPEND _cmake_import_check_targets iothub_client_mqtt_ws_transport )
list(APPEND _cmake_import_check_files_for_iothub_client_mqtt_ws_transport "${_IMPORT_PREFIX}/debug/lib/iothub_client_mqtt_ws_transport.lib" )

# Import target "serializer" for configuration "Debug"
set_property(TARGET serializer APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(serializer PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/serializer.lib"
  )

list(APPEND _cmake_import_check_targets serializer )
list(APPEND _cmake_import_check_files_for_serializer "${_IMPORT_PREFIX}/debug/lib/serializer.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
