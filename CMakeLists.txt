cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(TestTask LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

include_directories(src)
include_directories(src/engine)
include_directories(src/test)
include_directories(src/timer)

set(
  SOURCES
  src/main.cpp
  src/engine/internal_combustion_engine.cpp
  src/test/test_engine_power.cpp
  src/test/test_engine_temperature.cpp
  src/timer/simulation_timer.cpp
)

set(
  HEADERS
  src/engine/engine.hpp
  src/engine/internal_combustion_engine.hpp
  src/test/test_engine.hpp
  src/test/test_engine_power.hpp
  src/test/test_engine_temperature.hpp
  src/timer/simulation_timer.hpp
)

add_executable(main ${HEADERS} ${SOURCES})

target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/example/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/example/)
