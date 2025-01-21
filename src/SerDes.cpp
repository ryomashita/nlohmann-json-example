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

TEST(SerDes, Utf8String) {
  // UTF-8 文字列のテスト
  json j1 = {
    {"japanese", "こんにちは世界\u3042"},  // 日本語
    {"emoji", "🌏🌍🌎"},           // 絵文字
    {"mixed", "Hello世界😊"},      // 英数字、日本語、絵文字の混在
    {"special", "∑∏√∞"}          // 特殊文字
  };

  // シリアライズ
  const std::string str = j1.dump();
  std::cout << "Serialized: " << str << std::endl;

  // デシリアライズして元のデータと比較
  try {
    json j2 = json::parse(str);
    EXPECT_EQ(j1, j2);

    // 個別の値の検証
    EXPECT_EQ(j2["japanese"], "こんにちは世界\u3042");
    EXPECT_EQ(j2["emoji"], "🌏🌍🌎");
    EXPECT_EQ(j2["mixed"], "Hello世界😊");
    EXPECT_EQ(j2["special"], "∑∏√∞");
  } catch (json::parse_error& e) {
    FAIL() << "Parse error: " << e.what();
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

TEST(SerDes, GetOrDump) {
  // store a string in a JSON value
  json j_string = "this is a string";

  // retrieve the string value
  auto cpp_string = j_string.template get<std::string>();
  // retrieve the string value (alternative when a variable already exists)
  std::string cpp_string2;
  j_string.get_to(cpp_string2);

  // retrieve the serialized value (explicit JSON serialization)
  std::string serialized_string = j_string.dump();

  // get, get_to と異なり、dump はシリアライズデータを取得するので、 `"` を含む
  EXPECT_TRUE(cpp_string == cpp_string2);
  EXPECT_TRUE(cpp_string == "this is a string");
  EXPECT_TRUE(serialized_string == R"("this is a string")");
}