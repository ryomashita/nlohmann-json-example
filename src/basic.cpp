#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(Basic, object) {
  // create json object using operator[]
  json j;
  j["pi"] = 3.141;                                       // number (double)
  j["happy"] = true;                                     // boolean
  j["name"] = "Niels";                                   // string
  j["nothing"]["everything"] = 42;                       // nested
  j["list"] = {1, 0, 2};                                 // array
  j["object"] = {{"currency", "USD"}, {"value", 42.99}}; // object

  // create json object using initializer list
  json j2 = {
      {"pi", 3.141},       {"happy", true},
      {"name", "Niels"},   {"nothing", {{"everything", 42}}},
      {"list", {1, 0, 2}}, {"object", {{"currency", "USD"}, {"value", 42.99}}},
  };

  EXPECT_TRUE(j["pi"] == 3.141);
  EXPECT_TRUE(j == j2);
}