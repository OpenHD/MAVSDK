target_sources(mavsdk
    PRIVATE
    mavlink_passthrough.cpp
    mavlink_passthrough_impl.cpp
)

target_include_directories(mavsdk PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../../../mavsdk/core/>
    $<INSTALL_INTERFACE:include>
    )

install(FILES
    include/plugins/mavlink_passthrough/mavlink_passthrough.h
    ${CMAKE_CURRENT_BINARY_DIR}/../../../mavsdk/core/mavlink_include.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mavsdk/plugins/mavlink_passthrough
)

install(DIRECTORY
    ${MAVLINK_HEADERS}#Consti10 I had to add a "/mavlink" here, otherwise MAVSDK builds but the installed library cannot be used
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mavsdk/plugins/mavlink_passthrough
)
