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

  // operator[]: キーにアクセスする
  EXPECT_TRUE(j["pi"] == 3.141);

  // operator==: 2つのjsonオブジェクトが等しいかどうかを確認する
  EXPECT_TRUE(j == j2);

  // contains: キーが存在するか確認する
  EXPECT_TRUE(j.contains("pi"));
  EXPECT_FALSE(j.contains("address"));

  // emplace: キーと値を追加する
  j.emplace("age", 30);
  EXPECT_EQ(j["age"], 30);
  // get<T>: キーに対応する値を取得する
  EXPECT_EQ(j["age"].get<int>(), 30);
  
  // erase: キーを削除する
  j.erase("pi");
  EXPECT_FALSE(j.contains("pi"));
}
