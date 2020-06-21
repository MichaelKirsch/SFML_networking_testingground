cmake_minimum_required(VERSION 3.12)
project(ParticlePlay)

set(CMAKE_CXX_STANDARD 17)

file (GLOB_RECURSE SOURCES "src/*.hpp" "src/*.cpp" "src/*.h")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_USE_STATIC_STD_LIBS TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)



add_executable(ParticlePlay ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${OPENGL_LIBRARIES})
