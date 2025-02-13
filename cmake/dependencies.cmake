##! Dependancies
include(FetchContent)

set(DOCTEST_WITH_MAIN_IN_STATIC_LIB OFF CACHE BOOL "Override option" FORCE)
FetchContent_Declare(
        doctest
        URL https://github.com/onqtam/doctest/archive/2.3.3.tar.gz
)

FetchContent_Declare(
        entt
        URL https://github.com/skypjack/entt/archive/master.zip
)

set(BUILD_TESTING OFF CACHE BOOL "Override option" FORCE)
set(REPROC++ ON CACHE BOOL "" FORCE)

FetchContent_Declare(
        loguru
        URL https://github.com/emilk/loguru/archive/v2.1.0.zip
)

FetchContent_Declare(
        fmt
        URL https://github.com/fmtlib/fmt/releases/download/6.0.0/fmt-6.0.0.zip
)

FetchContent_Declare(
        doom_st
        URL https://github.com/doom/strong_type/archive/1.0.2.tar.gz
)

FetchContent_Declare(
        doom_meta
        URL https://github.com/doom/meta/archive/master.zip
)

SET(JSON_MultipleHeaders ON CACHE BOOL "Override option" FORCE)
SET(JSON_BuildTests OFF CACHE BOOL "Override option" FORCE)
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.7.0/include.zip
)

FetchContent_Declare(
        reproc
        URL https://github.com/DaanDeMeyer/reproc/archive/ebfcd6ca700e26845a3a27c21c6d704788ee77b7.zip
)

set(EXPECTED_ENABLE_TESTS OFF CACHE BOOL "Override option" FORCE)
FetchContent_Declare(
        expected
        URL https://github.com/Milerius/expected/archive/patch-1.zip
)

FetchContent_Declare(
        range-v3
        URL https://github.com/ericniebler/range-v3/archive/master.zip
)

FetchContent_Declare(
        refl-cpp
        URL https://github.com/veselink1/refl-cpp/archive/v0.6.3.zip
)

FetchContent_Declare(
        joboccara-pipes
        URL https://github.com/joboccara/pipes/archive/master.zip)

if (USE_BOX2D_ANTARA_WRAPPER)
    FetchContent_Declare(
            box2d
            URL https://github.com/erincatto/Box2D/archive/master.zip
    )
endif ()

if (USE_LUA_ANTARA_WRAPPER)
    FetchContent_Declare(
            lua
            URL https://github.com/lua/lua/archive/master.zip
    )

    FetchContent_Declare(
            sol2
            URL https://github.com/ThePhD/sol2/archive/21c030933f0c470ca328cdec51d847968370cd23.zip
    )
endif ()

if (USE_IMGUI_ANTARA_WRAPPER)
    FetchContent_Declare(imgui
            URL https://github.com/ocornut/imgui/archive/v1.73.zip)
    FetchContent_MakeAvailable(imgui)
endif()

if (USE_SFML_ANTARA_WRAPPER)
    if (APPLE)
        set(BUILD_SHARED_LIBS OFF CACHE BOOL "Override option" FORCE)
    endif ()
    FetchContent_Declare(
            SFML
            URL https://github.com/Milerius/SFML/archive/patch-1.zip
    )
endif ()


if (ENABLE_BLOCKCHAIN_MODULES)
    FetchContent_Declare(
            restclient-cpp
            URL https://github.com/mrtazz/restclient-cpp/archive/master.zip
    )
    if (APPLE)
        FetchContent_Declare(
                nspv
                URL https://github.com/SirSevenG/libnspv/releases/download/4/nspv-macos-691360cf0e110faa9f6e13a81df3a2bc000beadc.tar.gz
        )
    elseif (LINUX)
        FetchContent_Declare(
                nspv
                URL https://github.com/SirSevenG/libnspv/releases/download/4/nspv-linux-691360cf0e110faa9f6e13a81df3a2bc000beadc.tar.gz
        )
    elseif (WIN32)
        FetchContent_Declare(
                nspv
                URL https://github.com/SirSevenG/libnspv/releases/download/4/nspv-win-691360cf0e110faa9f6e13a81df3a2bc000beadc.zip
        )
    endif ()
    FetchContent_MakeAvailable(nspv restclient-cpp)
    find_package(CURL REQUIRED)

    add_library(restclient_obj STATIC)
    target_sources(restclient_obj PRIVATE
            ${restclient-cpp_SOURCE_DIR}/source/connection.cc
            ${restclient-cpp_SOURCE_DIR}/source/helpers.cc
            ${restclient-cpp_SOURCE_DIR}/source/restclient.cc)
    target_compile_features(restclient_obj PRIVATE cxx_std_11)
    target_include_directories(restclient_obj PUBLIC ${restclient-cpp_SOURCE_DIR}/include ${restclient-cpp_BINARY_DIR}/include)
    add_library(antara::http_client ALIAS restclient_obj)

    target_link_libraries(restclient_obj PUBLIC CURL::libcurl Threads::Threads)
    IF (UNIX)
        configure_file(${nspv_SOURCE_DIR}/nspv ${CMAKE_CURRENT_SOURCE_DIR}/modules/blockchain/assets/tools/nspv COPYONLY)
        configure_file(${nspv_SOURCE_DIR}/coins ${CMAKE_CURRENT_SOURCE_DIR}/modules/blockchain/assets/tools/coins COPYONLY)
    endif()
    IF (WIN32)
        configure_file(${nspv_SOURCE_DIR}/nspv.exe ${CMAKE_CURRENT_SOURCE_DIR}/modules/blockchain/assets/tools/nspv.exe COPYONLY)
        configure_file(${nspv_SOURCE_DIR}/libwinpthread-1.dll ${CMAKE_CURRENT_SOURCE_DIR}/modules/blockchain/assets/tools/libwinpthread-1.dll COPYONLY)
        configure_file(${nspv_SOURCE_DIR}/coins ${CMAKE_CURRENT_SOURCE_DIR}/modules/blockchain/assets/tools/coins COPYONLY)
    endif()
endif ()

FetchContent_MakeAvailable(doctest entt doom_st expected range-v3 refl-cpp doom_meta nlohmann_json joboccara-pipes loguru fmt reproc)

if (USE_SFML_ANTARA_WRAPPER)
    FetchContent_MakeAvailable(SFML)
    if (USE_IMGUI_ANTARA_WRAPPER)
        add_definitions(-DIMGUI_AND_SFML_ENABLED)
        set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "Override option" FORCE)
        set(IMGUI_DIR ${imgui_SOURCE_DIR})
        FetchContent_Declare(imgui-sfml URL https://github.com/eliasdaler/imgui-sfml/archive/master.zip)
        FetchContent_MakeAvailable(imgui-sfml)
    endif()
endif ()


add_library(antara_log INTERFACE)
target_sources(antara_log INTERFACE ${loguru_SOURCE_DIR}/loguru.cpp)
message(${loguru_SOURCE_DIR})
target_include_directories(antara_log INTERFACE ${loguru_SOURCE_DIR})
find_package(Threads)
if (EMSCRIPTEN)
    target_compile_definitions(antara_log INTERFACE -DLOGURU_USE_FMTLIB=1 -DLOGURU_STACKTRACES=0)
else ()
    target_compile_definitions(antara_log INTERFACE -DLOGURU_USE_FMTLIB=1)
endif ()
target_link_libraries(antara_log INTERFACE fmt::fmt-header-only Threads::Threads ${CMAKE_DL_LIBS})

add_library(antara::log ALIAS antara_log)

add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR})
add_library(nlohmann_json::nlohmann_json ALIAS nlohmann_json)

if (USE_BOX2D_ANTARA_WRAPPER)
    FetchContent_MakeAvailable(box2d)
    add_library(Box2D STATIC)
    file(GLOB_RECURSE BOX2D_SOURCES ${box2d_SOURCE_DIR}/Box2D/*.cpp)
    message(STATUS "box2d sources: -> ${BOX2D_SOURCES}")
    target_sources(Box2D PRIVATE ${BOX2D_SOURCES})
    target_include_directories(Box2D PUBLIC ${box2d_SOURCE_DIR})
    target_compile_features(Box2D PRIVATE cxx_std_11)
    add_library(antara::box2d_wrapper ALIAS Box2D)
endif ()

if (USE_LUA_ANTARA_WRAPPER)
    FetchContent_MakeAvailable(lua sol2)
    add_library(lua_lib STATIC)
    target_include_directories(lua_lib PUBLIC ${lua_SOURCE_DIR})
    file(GLOB SRC_FILES ${lua_SOURCE_DIR}/*.c)
    list(REMOVE_ITEM SRC_FILES "${lua_SOURCE_DIR}/onelua.c")
    list(REMOVE_ITEM SRC_FILES "${lua_SOURCE_DIR}/ltests.c")
    message(STATUS "lua_src -> ${SRC_FILES}")
    target_sources(lua_lib PRIVATE ${SRC_FILES})

    target_link_libraries(lua_lib PRIVATE ${CMAKE_DL_LIBS})
    if (UNIX)
        target_link_libraries(lua_lib PRIVATE m)
    endif ()
    add_library(antara::lua_lib ALIAS lua_lib)
endif ()

add_library(refl-cpp INTERFACE)
target_include_directories(refl-cpp INTERFACE ${refl-cpp_SOURCE_DIR})
add_library(antara::refl-cpp ALIAS refl-cpp)