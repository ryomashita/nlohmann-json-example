#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(Iterations, ArrayOperations) {
    // 配列の作成と操作のテスト
    json array;
    
    // 要素の追加
    array.push_back("first");
    array.push_back(42);
    array.emplace_back(true);
    
    // インデックスによるアクセス
    EXPECT_EQ(array[0], "first");
    EXPECT_EQ(array.at(1), 42);
    EXPECT_EQ(array[2], true);
    
    // サイズと空チェック
    EXPECT_EQ(array.size(), 3);
    EXPECT_FALSE(array.empty());
    
    // 要素の削除
    array.erase(array.begin());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], 42);
        
    // 配列のイテレーション
    json arr = {1, 2, 3, 4, 5};
    int sum = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        sum += it.value().get<int>();
    }
    EXPECT_EQ(sum, 15);
}

TEST(Iterations, IteratorUsage) {
    // イテレータの使用テスト
    json obj = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };
    
    // オブジェクトのイテレーション
    int sum = 0;
    std::vector<std::string> keys;
    for (auto& el : obj.items()) {
        keys.push_back(el.key());
        sum += el.value().get<int>();
    }
    EXPECT_EQ(sum, 6);
    EXPECT_EQ(keys, std::vector<std::string>({"a", "b", "c"}));
}