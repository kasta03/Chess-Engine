cmake_minimum_required(VERSION 3.10)
project(Project)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

add_definitions(-DPROJECTPATH="${PROJECT_SOURCE_DIR}")

set(CMAKE_BUILD_TYPE Debug) #Release
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

# Znajdź wszystkie pliki źródłowe w katalogu src
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Dodaj Project.cpp do listy plików źródłowych, jeśli nie jest już tam
list(FIND SOURCES "${PROJECT_SOURCE_DIR}/Project.cpp" PROJECT_CPP_INDEX)
if(${PROJECT_CPP_INDEX} EQUAL -1)
    list(APPEND SOURCES "${PROJECT_SOURCE_DIR}/Project.cpp")
endif()

add_compile_definitions(PROJECTPATH="${CMAKE_SOURCE_DIR}")

# Specify the SFML directory explicitly
set(SFML_DIR "C:/Users/kstar/Documents/SFML-2.6.2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)
if (SFML_FOUND)
    message(STATUS "SFML found")
    # Create executable target
    add_executable(Project ${SOURCES})
    # Link SFML libraries
    target_link_libraries(Project PRIVATE sfml-graphics sfml-window sfml-system)
    
    if(WIN32)
      # Copy SFML DLLs to the build directory 
      file(GLOB SFML_DLLS "${SFML_DIR}/../../../bin/*.dll")
        foreach(SFML_DLL ${SFML_DLLS})
        add_custom_command(TARGET Project POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SFML_DLL}" "$<TARGET_FILE_DIR:Project>")
    endforeach()
    endif()
else()
    message(SEND_ERROR "SFML not found")
endif()