find_package(spdlog REQUIRED)
add_library (zrestutils log.cpp)
if(WIN32)
set(LTSINC "C:\\src\\litesql\\include" "C:\\src\\spdlog\\include")
INCLUDE_DIRECTORIES(${LTSINC})
endif()
if(LINUX)
set(LTSINC "/home/yannb/src/litesql/include")
endif()
if(APPLE)
set(LTSINC "/Users/yannbourdeau/src/litesql/include")
endif()

target_include_directories (zrestutils PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR} ${LTSINC} /opt/homebrew/include)


