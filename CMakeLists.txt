cmake_minimum_required(VERSION 3.10)
project(SeaShepherdRules VERSION 1.0 LANGUAGES C CXX)


# CMake setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin/debug")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})

#set SDL2 and SDL2_image paths
set(CMAKE_PREFIX_PATH "C:/ProgLangs/cpp_libs/SDL2-2.28.5/x86_64-w64-mingw32;C:/ProgLangs/cpp_libs/SDL2_image-2.6.3/x86_64-w64-mingw32;C:/ProgLangs/cpp_libs/SDL2_ttf-2.20.0/x86_64-w64-mingw32")

message(STATUS "")
message(STATUS "Search for packages:")
# SDL2 setup
find_package(SDL2 REQUIRED)
message(STATUS "Found package: ${SDL2_DIR}")
# DLS2_image setup
find_package(SDL2_Image REQUIRED)
message(STATUS "Found package: ${SDL2_Image_DIR}")
# SDL2_ttf setup
find_package(SDL2_ttf REQUIRED)
message(STATUS "Found package: ${SDL2_ttf_DIR}")
message(STATUS "")

# set include directories
include_directories(
    ${CMAKE_INCLUDE_PATH}
    "C:/ProgLangs/cpp_libs/SDL2-2.28.5/x86_64-w64-mingw32/include"
    "C:/ProgLangs/cpp_libs/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2"
    "C:/ProgLangs/cpp_libs/SDL2_image-2.6.3/x86_64-w64-mingw32/include"
    "C:/ProgLangs/cpp_libs/SDL2_ttf-2.20.0/x86_64-w64-mingw32/include"
)
# set link directories
link_directories(
    "C:/ProgLangs/cpp_libs/SDL2-2.28.5/x86_64-w64-mingw32/lib"
    "C:/ProgLangs/cpp_libs/SDL2_image-2.6.3/x86_64-w64-mingw32/lib"
    "C:/ProgLangs/cpp_libs/SDL2_ttf-2.20.0/x86_64-w64-mingw32/lib"
)

# Files that should be compiled
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.h")

message(STATUS "Add source files:")
foreach(SRC_FILE IN LISTS SRC)
    message(STATUS "${SRC_FILE}")
    endforeach()
    message(STATUS "")

# Add project executable
add_executable(${PROJECT_NAME} ${SRC})
# Save it to:
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

# LINK PROGRAMS
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
)

#COPY ALL FILES TO OUTPUT DIRECTORY

# Copy over static .dll files
message(STATUS "Copying all dependencies to ${OUTPUT_DIR}")
file(GLOB PROJECT_DEPENDENCIES ${CMAKE_PREFIX_PATH})

foreach(Dependency IN LISTS PROJECT_DEPENDENCIES)
    file(GLOB DLL_FILES "${Dependency}/bin/*.dll")

    foreach(DLL_FILE IN LISTS DLL_FILES)
        file(
            COPY "${DLL_FILE}"
            DESTINATION ${OUTPUT_DIR}
        )
    endforeach()
endforeach()


#! ALSO NEEDED: 
#  ctrl+shift+p -> C/C++: Edit Configurations (UI)
#  go to 'Include Path' and add:
#  C:/ProgLangs/cpp_libs/SDL2_image-2.6.3/x86_64-w64-mingw32/**
#  C:/ProgLangs/cpp_libs/SDL2-2.28.5/x86_64-w64-mingw32/**
