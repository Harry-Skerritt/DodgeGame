cmake_minimum_required(VERSION 3.16)
project(SFMLProject)

set(CMAKE_CXX_STANDARD 20)

# Output directories for Debug and Release
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/)

# Add static flags - Windows Only?
if(WIN32)
    set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# Disable shared libs so we link statically
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML 2.6.1
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b
)
FetchContent_MakeAvailable(SFML)

# Source files
set(SOURCE_FILES
    src/main.cpp
    src/Game.cpp 
    src/Game.h src/GameObjects/GlowSprite.h src/GameObjects/GlowSprite.cpp
)

# Windows: add icon resource if available
if(WIN32)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/resources/resources.rc)
endif()

# Copy the resources folder into the build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/resources)

# Executable target
add_executable(SFMLProject ${SOURCE_FILES})

target_link_libraries(SFMLProject PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_compile_features(SFMLProject PRIVATE cxx_std_20)

# Data files copied to bin output
file(COPY ${CMAKE_SOURCE_DIR}/Data DESTINATION ${CMAKE_BINARY_DIR})

# macOS: App bundle + frameworks
if(APPLE)
    set(MACOSX_BUNDLE TRUE)
    set_target_properties(SFMLProject PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "SFMLProject"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/mac/Info.plist"
    )

    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation REQUIRED)

    target_link_libraries(SFMLProject PRIVATE
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
        ${COREFOUNDATION_LIBRARY}
    )

    # Install bundle and resources
    include(BundleUtilities)
    install(TARGETS SFMLProject BUNDLE DESTINATION .)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/Data DESTINATION SFMLProject.app/Contents/Resources)

    set_target_properties(SFMLProject PROPERTIES
        INSTALL_RPATH "@executable_path/../Frameworks"
    )

    install(CODE "
        include(BundleUtilities)
        fixup_bundle(
            \"\${CMAKE_INSTALL_PREFIX}/SFMLProject.app\"
            \"\"
            \"${SFML_SOURCE_DIR}/lib\"
        )
    ")
endif()

# Windows: Hide console window in Release builds
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(SFMLProject PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Windows: Copy SFML DLLs
if(WIN32)
    add_custom_command(
            TARGET SFMLProject
            COMMENT "Copy OpenAL DLL to build directory so app can have sound"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SFMLProject>
            VERBATIM)
endif()
