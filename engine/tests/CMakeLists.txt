include(CTest)
include(Catch)

add_executable(engine-tests-world
  world/delme.cpp
  world/ApplyGlobalPosition.test.cpp helpers/helpers.hpp)

target_link_libraries(engine-tests-world PRIVATE
  Catch2::Catch2WithMain
  engine::engine)

catch_discover_tests(engine-tests-world)