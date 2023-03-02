# To get started on a new plugin, copy this entire folder (containing this file and C++ sources) to
# a convenient location, and then start making modifications.

# The first line of any CMake project should be a call to `cmake_minimum_required`, which checks
# that the installed CMake will be able to understand the following CMakeLists, and ensures that
# CMake's behaviour is compatible with the named version. This is a standard CMake command, so more
# information can be found in the CMake docs.

cmake_minimum_required(VERSION 3.15)


if (WIN32)
    #set (CMAKE_GENERATOR_TOOLSET ClangCL)
    #static linking in Windows
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# If we are compiling for Mac OS we want to target OS versions down to 10.9
option(UniversalBinary "Build universal binary for mac" ON)

if (APPLE)
    set (CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE INTERNAL "")
    if (UniversalBinary)
        set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE INTERNAL "")
        #set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)        
    endif()
endif()







# The top-level CMakeLists.txt file for a project must contain a literal, direct call to the
# `project()` command. `project()` sets up some helpful variables that describe source/binary
# directories, and the current project version. This is a standard CMake command.

project(aooserver VERSION 1.1.0)

set(BUILDVERSION 10)


# If you've installed JUCE somehow (via a package manager, or directly using the CMake install
# target), you'll need to tell this project that it depends on the installed copy of JUCE. If you've
# included JUCE directly in your source tree (perhaps as a submodule), you'll need to tell CMake to
# include that subdirectory as part of the build.

# find_package(JUCE CONFIG REQUIRED)        # If you've installed JUCE to your system
# or


# By default we don't want Xcode schemes to be made for modules, etc
set(CMAKE_XCODE_GENERATE_SCHEME OFF)

# No ZERO_CHECK target (it helps bust cache for cmake)
set(CMAKE_SUPPRESS_REGENERATION true) 

# prevent install all
#set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

# Adds all the module sources so they appear correctly in the IDE
# Must be set before JUCE is added as a sub-dir (or any targets are made)
# https://github.com/juce-framework/JUCE/commit/6b1b4cf7f6b1008db44411f2c8887d71a3348889
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

# This is a failed attempt to bury ALL_BUILD in Targets/
# This should be called before any target is made
# Bug in Xcode? https://gitlab.kitware.com/cmake/cmake/-/issues/21383
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "Targets")

# Create a /Modules directory in the IDE with the JUCE Module code
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Show all module sources in IDE projects" ON)


# include JUCE

add_subdirectory(deps/juce EXCLUDE_FROM_ALL )


set (FormatsToBuild Standalone)


juce_add_console_app(aooserver
    PRODUCT_NAME "aooserver")     # The name of the final executable, which can differ from the target name

juce_generate_juce_header(aooserver)


set (HEADER_INCLUDES
    deps/aoo
    deps/aoo/include
    deps/aoo/deps
)

set (LIB_PATHS  "")

set (PLAT_COMPILE_DEFS
    $<$<CONFIG:Debug>:AOO_LOGLEVEL=AOO_LOGLEVEL_VERBOSE>
    USE_CODEC_OPUS=0
    AOO_TIMEFILTER_CHECK=0
    AOO_HAVE_PTHREAD_RWLOCK=1
    AOO_STATIC)


# platform specific stuff
if (WIN32)

    message (STATUS "Win generator platform is: ${CMAKE_VS_PLATFORM_NAME}" )
    if ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        list (APPEND LIB_PATHS
            $<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/Debug32>
            $<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/Release32>
        )
    else()
        list (APPEND LIB_PATHS
            $<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/Debug>
            $<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/Release>
        )
    endif()

    list (APPEND PLAT_COMPILE_DEFS
        _USE_MATH_DEFINES
        WINVER=0x0601
        _WIN32_WINNT=0x0601)
else()
    # Linux
endif()


set(SourceFiles
    Source/Main.cpp
)

set(AOOSourceFiles

deps/aoo/aoo/src/aoo.cpp
deps/aoo/aoo/src/binmsg.hpp
deps/aoo/aoo/src/codec
deps/aoo/aoo/src/codec/pcm.cpp
deps/aoo/aoo/src/detail.hpp
deps/aoo/aoo/src/events.hpp
deps/aoo/aoo/src/memory.hpp
deps/aoo/aoo/src/net/client.cpp
deps/aoo/aoo/src/net/client.hpp
deps/aoo/aoo/src/net/client_endpoint.cpp
deps/aoo/aoo/src/net/client_endpoint.hpp
deps/aoo/aoo/src/net/client_events.hpp
deps/aoo/aoo/src/net/detail.cpp
deps/aoo/aoo/src/net/detail.hpp
deps/aoo/aoo/src/net/event.hpp
deps/aoo/aoo/src/net/message_buffer.cpp
deps/aoo/aoo/src/net/message_buffer.hpp
deps/aoo/aoo/src/net/osc_stream_receiver.hpp
deps/aoo/aoo/src/net/peer.cpp
deps/aoo/aoo/src/net/peer.hpp
deps/aoo/aoo/src/net/server.cpp
deps/aoo/aoo/src/net/server.hpp
deps/aoo/aoo/src/net/server_events.hpp
deps/aoo/aoo/src/packet_buffer.cpp
deps/aoo/aoo/src/packet_buffer.hpp
deps/aoo/aoo/src/resampler.cpp
deps/aoo/aoo/src/resampler.hpp
deps/aoo/aoo/src/rt_memory_pool.hpp
deps/aoo/aoo/src/sink.cpp
deps/aoo/aoo/src/sink.hpp
deps/aoo/aoo/src/source.cpp
deps/aoo/aoo/src/source.hpp
deps/aoo/aoo/src/time_dll.hpp
deps/aoo/aoo/src/timer.cpp
deps/aoo/aoo/src/timer.hpp

deps/aoo/common/lockfree.hpp
deps/aoo/common/net_utils.cpp
deps/aoo/common/net_utils.hpp
deps/aoo/common/priority_queue.hpp
deps/aoo/common/sync.cpp
deps/aoo/common/sync.hpp
deps/aoo/common/tcp_server.cpp
deps/aoo/common/tcp_server.hpp
deps/aoo/common/time.cpp
deps/aoo/common/time.hpp
deps/aoo/common/udp_server.cpp
deps/aoo/common/udp_server.hpp
deps/aoo/common/utils.hpp

deps/aoo/include/aoo/aoo.h
deps/aoo/include/aoo/aoo_client.h
deps/aoo/include/aoo/aoo_client.hpp
deps/aoo/include/aoo/aoo_codec.h
deps/aoo/include/aoo/aoo_controls.h
deps/aoo/include/aoo/aoo_defines.h
deps/aoo/include/aoo/aoo_events.h
deps/aoo/include/aoo/aoo_net.h
deps/aoo/include/aoo/aoo_server.h
deps/aoo/include/aoo/aoo_server.hpp
deps/aoo/include/aoo/aoo_sink.h
deps/aoo/include/aoo/aoo_sink.hpp
deps/aoo/include/aoo/aoo_source.h
deps/aoo/include/aoo/aoo_source.hpp
deps/aoo/include/aoo/codec/aoo_pcm.h

deps/aoo/deps/oscpack/osc/MessageMappingOscPacketListener.h
deps/aoo/deps/oscpack/osc/OscException.h
deps/aoo/deps/oscpack/osc/OscHostEndianness.h
deps/aoo/deps/oscpack/osc/OscOutboundPacketStream.cpp
deps/aoo/deps/oscpack/osc/OscOutboundPacketStream.h
deps/aoo/deps/oscpack/osc/OscPacketListener.h
deps/aoo/deps/oscpack/osc/OscPrintReceivedElements.cpp
deps/aoo/deps/oscpack/osc/OscPrintReceivedElements.h
deps/aoo/deps/oscpack/osc/OscReceivedElements.cpp
deps/aoo/deps/oscpack/osc/OscReceivedElements.h
deps/aoo/deps/oscpack/osc/OscTypes.cpp
deps/aoo/deps/oscpack/osc/OscTypes.h

deps/aoo/deps/md5/md5.c
deps/aoo/deps/md5/md5.h

)

target_sources(aooserver PRIVATE 
       ${SourceFiles} 
       ${AOOSourceFiles}
   )

# No, we don't want our source buried in extra nested folders
set_target_properties(aooserver PROPERTIES FOLDER "")

# The source tree should uhhh, still look like the source tree, yo
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Source PREFIX "" FILES ${SourceFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/deps/aoo PREFIX "aoo" FILES ${AOOSourceFiles})

# Move the INTERFACE auto-created JUCE library stuff into its own folder
source_group("JUCE Library Code" REGULAR_EXPRESSION "juce_")


target_include_directories(aooserver
    PUBLIC
    ${HEADER_INCLUDES}
)


# Require at least C++17 to build `my_target`
target_compile_features(aooserver PRIVATE cxx_std_17)
    



target_compile_definitions(aooserver
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_USE_MP3AUDIOFORMAT=1
    JUCE_LOAD_CURL_SYMBOLS_LAZILY=1
    JUCE_ASIO=1
    JUCE_WASAPI=1
    JUCE_DIRECTSOUND=0
    JUCE_JACK=1
    JUCE_ALSA=1
    JUCE_USE_ANDROID_OBOE=1
    JUCE_USE_OBOE_STABILIZED_CALLBACK=1
${PLAT_COMPILE_DEFS} )



if (UNIX AND NOT APPLE)
    
    if (JUCE_LINUX_TARGET_ARCHITECTURE MATCHES "arm" )
        message(STATUS "ARM platform, adding -march=native")
        target_compile_options(aooserver PUBLIC
            -march=native
        )
    endif()
     
endif()


target_link_directories(aooserver INTERFACE
    ${LIB_PATHS}
)

target_link_libraries(aooserver 
    PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_formats
    juce::juce_cryptography
    juce::juce_data_structures
    juce::juce_core
    juce::juce_events
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    #   juce::juce_recommended_warning_flags
)

