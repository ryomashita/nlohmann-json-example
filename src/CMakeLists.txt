include(${CMAKE_SCRIPTS_DIR}/install_gtest.cmake)

add_executable(AddTest add.cpp add_test.cpp)
target_include_directories(AddTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
enable_gtest(AddTest)
enable_memcheck(AddTest)

add_executable(Literal literals.cpp)
link_nlohmann_json(Literal)
enable_gtest(Literal)
