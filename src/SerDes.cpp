#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(SerDes, Serialize) {
  // 順序は保証されない
  // Ser/Des は UTF-8 エンコードのみに対応
  json j1 = {
      {"pi", 3.141},       {"happy", true},
      {"name", "Niels"},   {"nothing", {{"everything", 42}}},
      {"list", {1, 0, 2}},
  };
  auto str = j1.dump();
  std::cout << str << std::endl;
  EXPECT_EQ(
      str,
      R"({"happy":true,"list":[1,0,2],"name":"Niels","nothing":{"everything":42},"pi":3.141})");
}