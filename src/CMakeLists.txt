include(${CMAKE_SCRIPTS_DIR}/install_gtest.cmake)

add_executable(Literal literals.cpp)
link_nlohmann_json(Literal)
enable_gtest(Literal)

add_executable(Basic basic.cpp)
link_nlohmann_json(Basic)
enable_gtest(Basic)

add_executable(SerDes SerDes.cpp)
link_nlohmann_json(SerDes)
enable_gtest(SerDes)