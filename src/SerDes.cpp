#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(SerDes, SerializeDeserialize) {
  // 1. Serialize
  // 順序は保証されない
  // Ser/Des は UTF-8 エンコードのみに対応
  json j1 = {
      {"pi", 3.141},       {"happy", true},
      {"name", "Niels"},   {"nothing", {{"everything", 42}}},
      {"list", {1, 0, 2}},
  };
  const std::string str = j1.dump();
  std::cout << str << std::endl;
  EXPECT_EQ(
      str,
      R"({"happy":true,"list":[1,0,2],"name":"Niels","nothing":{"everything":42},"pi":3.141})");

  // 2. Deserialize
  try {
    json j2 = json::parse(str);
    EXPECT_EQ(j1, j2);
  } catch (json::parse_error &e) {
    FAIL() << e.what();
  }
}

TEST(SerDes, DeserializeError) {
  // 1. Deserialize
  const std::string str =
      R"({"happy":true,"list":[1,0,2],"name":"Niels","nothing":{"everything":42},"pi":3.141)";
  try {
    json j2 = json::parse(str);
    FAIL() << "Expected an exception";
  } catch (json::parse_error &e) {
    std::cout << e.what() << std::endl;
    // Exception message example:
    // [json.exception.parse_error.101] parse error at line 1, column 83: syntax
    // error while parsing object - unexpected end of input; expected '}'
  }
  SUCCEED();
}