#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.
include(CMakeFindDependencyMacro)
find_dependency(parson)
find_dependency(uamqp)
find_dependency(uhttp)
find_dependency(umqtt)
find_dependency(azure_c_shared_utility)

include("${CMAKE_CURRENT_LIST_DIR}/azure_iot_sdksTargets.cmake")

get_target_property(IOTHUB_CLIENT_INCLUDES iothub_client INTERFACE_INCLUDE_DIRECTORIES)

set(IOTHUB_CLIENT_INCLUDES ${IOTHUB_CLIENT_INCLUDES} CACHE INTERNAL "")

include("${CMAKE_CURRENT_LIST_DIR}/azure_iot_sdksFunctions.cmake")