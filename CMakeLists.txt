#CMake version
cmake_minimum_required(VERSION 2.8)
project(PlanetSimulation)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message( STATUS "Setting build type to 'Release as none was specified.")
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
	#set possible values of built type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug"
		"MinSizeRel" "RelWithDebInfo")
endif()

set(EXECUTABLE_NAME "PlanetSimulator")
set(VERSION_MAJOR 0)
set(VERSION MINOR 0)
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

#option to enable TGUI experimental
option (USE_TGUI
	"Use TGUI experimental implementation" ON)

#include all headers
set(HEADERS
	src/common/shader.hpp
	src/common/texture.hpp
	src/common/controls.hpp
	src/app.hpp
	src/planet.hpp
	src/planetmanager.hpp
)

#include all sources
set(SOURCES
	src/main.cpp
	src/app.cpp
	src/planetmanager.cpp
	src/common/shader.cpp
	src/common/texture.cpp
	src/common/controls.cpp
)

#these will be copied into the build directory
set(RUNTIME_DEPENDENCIES
	shaders/vertexshader.vert
	shaders/fragmentshader.frag
	textures/Planet.DDS
)

if(USE_TGUI)
	file(COPY ${PROJECT_SOURCE_DIR}/TGUI DESTINATION ${PROJECT_BINARY_DIR}/Release)
endif()

#include_directories("${PROJECT_BINARY_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}/shaders")
#include_directories("${PROJECT_SOURCE_DIR}/textures")
#include_directories("${PROJECT_SOURCE_DIR}/common")

add_executable(${EXECUTABLE_NAME} ${SOURCES} ${HEADERS} ${RUNTIME_DEPENDENCIES})

#copy shaders and textures into binary folder
add_custom_target(copy_runtime_dependencies ALL)
foreach(RUNTIME_DEPENDENCY ${RUNTIME_DEPENDENCIES})
    add_custom_command(TARGET copy_runtime_dependencies POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/${RUNTIME_DEPENDENCY}
                       $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/${RUNTIME_DEPENDENCY})
endforeach()

#OpenGL Libraries and definitions
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
add_definitions(${OPENGL_DEFINITIONS})

# move to own module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#SFML libraries
find_package(SFML 2 REQUIRED system window graphics)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

#GLEW libraries
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})
target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARY})
message( STATUS "Found GLEW in ${GLEW_INCLUDE_PATH}")

#GLM libraries
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
message(STATUS "GLM included at ${GLM_INCLUDE_DIRS}")

#OpenCL experimental
if(USE_OPENCL)
    find_package(OpenCL REQUIRED)
    include_directories(${OPENCL_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} ${OPENCL_LIBRARIES})
    #enable OpenCL in code
    add_definitions("-DUSE_OPENCL")
endif()

#TGUI experimental
if(USE_TGUI)
  find_package(TGUI REQUIRED)
  include_directories(${TGUI_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${TGUI_LIBRARY})
  message(STATUS "Found TGUI in ${TGUI_INCLUDE_DIR}")
  add_definitions("-DUSE_TGUI")
endif()

install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)

if(NOT MSVC)
    list(APPEND CMAKE_CXX_FLAGS "-std=c++0x")
endif()
