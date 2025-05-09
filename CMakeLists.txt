cmake_minimum_required(VERSION 3.19.0)
# set the project name
project(zrest)
if(NOT WIN32)
FIND_PACKAGE(PkgConfig REQUIRED)
endif()
if(WIN32)
#set(Intl_INCLUDE_DIR "C:\\src\\gettext-0.21\\gettext-runtime\\intl") 
#set(Intl_LIBRARY  "C:\\src\\gettext-0.21\\gettext-runtime\\intl\\.libs")
set(fmt_DIR "C:\\src\\fmt")
set(CURL_LIBRARY "C:\\src\\curl-7.76.1")
set(CURL_INCLUDE_DIR "C:\\src\\curl-7.76.1")
set(spdlog_DIR "C:\\src\\spdlog")
set(WIN32_EXECUTABLE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ")
set(ENABLE_UNICODE on)
endif()
if(APPLE)
   set (spdlog_DIR "/opt/homebrew/include/spdlog")
endif()
if(NOT WIN32)
FIND_PACKAGE(Intl REQUIRED)
FIND_PACKAGE(Gettext 0.19.8.1 REQUIRED)
endif()
find_package(CURL REQUIRED)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
#set(MOD_DEP "fmt spdlog")
if(UNIX AND NOT APPLE)
set(LINUX TRUE)
endif()
if (LINUX) 
    PKG_CHECK_MODULES(GTKMM REQUIRED gtkmm-3.0 gtk+-3.0 )
    INCLUDE_DIRECTORIES(${GTKMM_INCLUDE_DIRS})
    LINK_DIRECTORIES(${GTKMM_LIBRARY_DIRS})
    
    # Add other flags to the compiler
    ADD_DEFINITIONS(${GTKMM_CFLAGS_OTHER})
endif ()
    

# add the executable

if (UNIX)
    add_executable( zrest  src/main.cpp)
endif()

if (LINUX)

    add_subdirectory("src/linux")
    add_subdirectory("src/linux/utils")
endif()

if(APPLE)
    add_subdirectory("src/darwin")
endif()
if(WIN32)

    add_executable(zrest WIN32 src/main.cpp)
    add_subdirectory("src/win32")

endif()

add_subdirectory("src/lang")
add_subdirectory("src/utils")
add_subdirectory("src/db")
add_subdirectory("src/model")
if (NOT WIN32)
set(languages en fr)
foreach(lang ${languages})
GETTEXT_PROCESS_PO_FILES(${lang} ALL DOMAIN "zrestlang" INSTALL_DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/locale/" PO_FILES "po/${lang}/zrestlang-${lang}.po")
#install(FILES "zrestlang-${lang}.gmo" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/locale/${lang}/LC_MESSAGES/" RENAME "zrestlang.mo")
endforeach()
#GETTEXT_CREATE_TRANSLATIONS ( zrestlang.gmo ALL po/en/zrestlang-en.po po/fr/zrestlang-fr.po)
endif()
if(APPLE)
set(DLINK stdc++ "-framework Foundation" "-framework Cocoa" objc zrestdarwin /opt/homebrew/lib/libfmt.a)
set(DINCL  src/darwin /opt/homebrew/include)
LINK_DIRECTORIES(/opt/homebrew/lib /usr/local/lib /System/DriverKit/usr/lib /)   
endif()

if(LINUX)
set(DINCL src/linux) 
   
set(DLINK zrestlinux zrestlinuxutils )
endif()
if(LINUX)
set(LTSLINK /usr/local/lib/static/liblitesql.a  /usr/local/lib/static/liblitesql_sqlite.a /usr/local/lib/static/liblitesql-util.a /usr/local/lib/static/libmodel.a)
endif()
if(WIN32)
set(DINCL src/win32 "c:\\src\\lite-sql\\include") 
set(LTSLINK  "C:\\src\\lite-sql\\src\\library\\Release\\litesql.lib" "C:\\src\\lite-sql\\src\\library\\Release\\litesql-util.lib" "C:\\src\\lite-sql\\src\\generator\\Release\\model.lib" "C:\\src\\sqlite3\\sqlite3.lib")   
set(DLINK zrestwin32 )
#SET(zrest_LINKFLAGS zrestres.res )

endif()

target_include_directories(zrest PUBLIC 
                           "src/lang" "src/utils" "src/db" 
                           ${DINCL}
                           linux 
                           ${GTKMM_INCLUDE_DIRS}
                           ${Intl_INCLUDE_DIRS})
target_link_libraries (zrest LINK_PUBLIC zrestlanguages  zrestutils zrestdb  ${LTSLINK}     ${DLINK} ${GTKMM_LIBRARIES} ${Intl_LIBRARIES} Threads::Threads ${CMAKE_DL_LIBS} zrestmodel )

