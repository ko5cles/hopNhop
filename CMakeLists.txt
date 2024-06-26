cmake_minimum_required(VERSION 3.10.0)
project(Assignment4Tex)

find_package(OpenGL REQUIRED)
#find_package(GLU REQUIRED)

# Suppress warnings of the deprecation of glut functions on macOS.
if(APPLE)
 add_definitions(-Wno-deprecated-declarations)
endif()


### Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

### Compilation flags: adapt to your needs ###
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj") ### Enable parallel compilation
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR} )
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR} )
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

### Add src to the include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

### Add OpenGL
set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
set(LIBRARIES ${OPENGL_LIBRARIES})

### Include Eigen for linear algebra
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/glm")

### Compile GLFW3 statically
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL " " FORCE)
set(GLFW_BUILD_INSTALL OFF CACHE BOOL " " FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw" "glfw")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/glfw/include")
set(LIBRARIES "glfw" ${GLFW_LIBRARIES})

### On windows, you also need glew
if((UNIX AND NOT APPLE) OR WIN32)
  set(GLEW_INSTALL OFF CACHE BOOL " " FORCE)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glew" "glew")
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/glew/include")
  list(APPEND LIBRARIES "glew")
endif()

if(APPLE)
list(APPEND LIBRARIES "-framework OpenGL")
endif()

### Compile all the cpp files in src
file(GLOB SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

### Collect all the h files in src
file(GLOB HEADERS
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

### Collect all the glsl files in src
file(GLOB GLSL
"${CMAKE_CURRENT_SOURCE_DIR}/shader/*.glsl"
)

add_executable(${PROJECT_NAME}_bin ${SOURCES} ${HEADERS} ${GLSL} src/Game.h src/Game.cpp src/Resources.h src/Resources.cpp src/Shader.h src/Shader.cpp src/Texture.h src/Texture.cpp src/stb_image.h src/BoxRenderer.h src/BoxRenderer.cpp src/GameObj.h src/GameObj.cpp src/GameLev.h src/GameLev.cpp src/HopObj.h src/HopObj.cpp src/Camera.h src/Camera.cpp src/EnvironmentRenderer.h src/EnvironmentRenderer.cpp src/ShadowRenderer.h src/ShadowRender.cpp src/QuadRenderer.h src/QuadRenderer.cpp src/BoxOutliner.h src/BoxOutliner.cpp)
target_link_libraries(${PROJECT_NAME}_bin ${LIBRARIES} ${OPENGL_LIBRARIES})
