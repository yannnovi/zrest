if(WIN32)
execute_process(COMMAND "C:\\src\\litesql\\xlitesql-src-0.3.18\\src\\generator\\Debug\\litesql-gen.exe" -t c++ zrestdb.xml WORKING_DIRECTORY src/db)
set(LTSINC "C:\\src\\litesql\\litesql-src-0.3.18\\include")
INCLUDE_DIRECTORIES(${LTSINC})
endif()
if(APPLE)
execute_process(COMMAND /Users/yannbourdeau/src/litesql/src/generator/litesql-gen -t c++ zrestdb.xml WORKING_DIRECTORY src/db)
set(LTSINC "/Users/yannbourdeau/src/litesql/include")
endif()
add_library (zrestdb db.cpp zrestdb.cpp)

target_include_directories (zrestdb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${LTSINC})

