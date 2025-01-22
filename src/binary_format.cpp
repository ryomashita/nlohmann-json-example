#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <cstdint>

using json = nlohmann::json;

TEST(BinaryFormat, MessagePack) {
    // 基本的なデータ型のテスト
    json original = {
        {"null", nullptr},
        {"boolean", true},
        {"integer", 42},
        {"float", 3.14},
        {"string", "Hello, MessagePack!"},
        {"array", {1, 2, 3}},
        {"object", {{"key", "value"}}},
        {"binary", std::vector<std::uint8_t>{0x80, 0x90, 0xA0}},
        {"japanese", "こんにちは"}
    };

    // MessagePackへの変換
    std::vector<std::uint8_t> msgpack = json::to_msgpack(original);

    // MessagePackからJSONへの変換
    json decoded = json::from_msgpack(msgpack);

    // 元のデータと一致することを確認
    EXPECT_EQ(original, decoded);
    
    // 個別の値の検証
    EXPECT_EQ(decoded["null"], nullptr);
    EXPECT_EQ(decoded["boolean"], true);
    EXPECT_EQ(decoded["integer"], 42);
    EXPECT_EQ(decoded["float"], 3.14);
    EXPECT_EQ(decoded["string"], "Hello, MessagePack!");
    EXPECT_EQ(decoded["array"], json({1, 2, 3}));
    EXPECT_EQ(decoded["japanese"], "こんにちは");
}

TEST(BinaryFormat, CBOR) {
    // CBORの特殊機能のテスト
    json original = {
        {"datetime", "2024-03-20T12:00:00Z"},
        {"bignum", 9007199254740991ull},  // JavaScript の最大安全整数
        {"negative", -1234567},
        {"binary", std::vector<std::uint8_t>{0x01, 0x02, 0x03}},
        {"nested", {
            {"array", {1, 2, {{"deep", "value"}}}},
            {"map", {{"a", 1}, {"b", 2}}}
        }}
    };

    // CBORへの変換
    std::vector<std::uint8_t> cbor = json::to_cbor(original);

    // CBORからJSONへの変換
    json decoded = json::from_cbor(cbor);

    // 元のデータと一致することを確認
    EXPECT_EQ(original, decoded);
    
    // 個別の値の検証
    EXPECT_EQ(decoded["datetime"], "2024-03-20T12:00:00Z");
    EXPECT_EQ(decoded["bignum"], 9007199254740991ull);
    EXPECT_EQ(decoded["negative"], -1234567);
}

TEST(BinaryFormat, BSON) {
    // BSONの特徴的な機能のテスト
    json original = {
        {"_id", 12345},  // BSONでよく使用されるフィールド
        {"date", "2024-03-20"},
        {"document", {
            {"field1", "value1"},
            {"field2", 42},
            {"field3", true}
        }},
        {"array_of_docs", {
            {{"id", 1}, {"name", "doc1"}},
            {{"id", 2}, {"name", "doc2"}}
        }}
    };

    // BSONへの変換
    std::vector<std::uint8_t> bson = json::to_bson(original);

    // BSONからJSONへの変換
    json decoded = json::from_bson(bson);

    // 元のデータと一致することを確認
    EXPECT_EQ(original, decoded);
    
    // 個別の値の検証
    EXPECT_EQ(decoded["_id"], 12345);
    EXPECT_EQ(decoded["date"], "2024-03-20");
    EXPECT_EQ(decoded["document"]["field2"], 42);
}

TEST(BinaryFormat, ErrorHandling) {
    // 不正なバイナリデータの処理テスト
    std::vector<std::uint8_t> invalid_data = {0x80, 0x90, 0xA0};  // 不正なデータ

    // MessagePack
    EXPECT_THROW({
        [[maybe_unused]] std::string result = json::from_msgpack(invalid_data);
    }, json::parse_error);

    // CBOR
    EXPECT_THROW({
        [[maybe_unused]] std::string result = json::from_cbor(invalid_data);
    }, json::parse_error);

    // BSON
    EXPECT_THROW({
        [[maybe_unused]] std::string result = json::from_bson(invalid_data);
    }, json::parse_error);
}
