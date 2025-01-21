#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(Literals, String) {
  // Using `R` (C++ raw string literals) and json::parse
  json ex1 = json::parse(R"({
    "pi":3.141, 
    "happy":true
   }
   )");

  // Using `R` (C++ raw string literals) and `_json` (user-defined literal)
  using namespace nlohmann::literals;
  json ex2 = R"(
  {
    "pi": 3.141,
    "happy": true
  }
)"_json;

  // Using initializer lists
  json ex3 = {
      {"happy", true},
      {"pi", 3.141},
  };

  EXPECT_TRUE(ex1 == ex2);
  EXPECT_TRUE(ex2 == ex3);

  // using json::array
  json ex4 = json::array({1, 2, 3});
  EXPECT_EQ(ex4[0], 1);
  EXPECT_EQ(ex4[1], 2);
  EXPECT_EQ(ex4[2], 3);

  // using json::object
  json ex5 = json::object({{"a", 1}, {"b", 2}, {"c", 3}});
  EXPECT_EQ(ex5["a"], 1);
  EXPECT_EQ(ex5["b"], 2);
  EXPECT_EQ(ex5["c"], 3);
}
