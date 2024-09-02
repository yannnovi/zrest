find_package(spdlog REQUIRED)
add_library (zrestutils log.cpp)
target_include_directories (zrestutils PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR} "/usr/local/include" "C:\\src\\spdlog\\include" "/opt/homebrew/include" )

