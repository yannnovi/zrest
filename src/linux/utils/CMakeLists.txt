add_library (zrestlinuxutils widgetlocale.cpp)

target_include_directories(zrestlinuxutils PUBLIC "../../lang")
target_include_directories(zrestlinuxutils PUBLIC "../../3rd")
target_include_directories(zrestlinuxutils PUBLIC "../../utils")
target_include_directories (zrestlinuxutils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

