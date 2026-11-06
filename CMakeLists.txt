cmake_minimum_required(VERSION 3.20)
project(sd_battle_sumo LANGUAGES C CXX)

# Pattern-fetch trace diagnostic (disabled by default)
option(CYC_TRACE_PATTERN_FETCH "Enable pattern-fetch trace diagnostic" OFF)

# Host-side presentation overlay test mode (disabled by default)
option(CYC_HOST_EXTRAS_BUILD "Build with host-side overlay test mode" OFF)
set(_cyc_host_extras_args "")
if(CYC_HOST_EXTRAS_BUILD)
    set(_cyc_host_extras_args HOST_EXTRAS "${CMAKE_SOURCE_DIR}/sd_battle_overlay.c" "${CMAKE_SOURCE_DIR}/ne_detect.c")
endif()

set(NESRECOMP_ROOT "C:/DecompProjects/engine-test" CACHE PATH "NESRecomp engine root")
set(NESRECOMP_BACKEND "cycle" CACHE STRING "CPU backend: cycle or legacy")
set_property(CACHE NESRECOMP_BACKEND PROPERTY STRINGS cycle legacy)

if(CYC_TRACE_PATTERN_FETCH)
    add_compile_definitions(CYC_TRACE_PATTERN_FETCH=1)
    message(STATUS "Pattern-fetch trace ENABLED")
endif()

if(NESRECOMP_BACKEND STREQUAL "cycle")
    include("${NESRECOMP_ROOT}/runner/cyc/project.cmake")
    nesrecomp_add_cycle_game(SDBattleSumo
        ROM "${CMAKE_SOURCE_DIR}/SD Battle Oozumou - Heisei Hero Basho (Japan).nes"
        REGION NTSC
        ${_cyc_host_extras_args})
    return()
endif()
if(NOT NESRECOMP_BACKEND STREQUAL "legacy")
    message(FATAL_ERROR "Unknown NESRECOMP_BACKEND: ${NESRECOMP_BACKEND}")
endif()
