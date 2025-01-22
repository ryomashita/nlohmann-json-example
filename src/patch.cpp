#include <gtest/gtest.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


TEST(Patch, JsonPatch) {
    // patch: jdonへのパッチ操作を行う
    json document = {
        {"name", "John"},
        {"age", 30},
        {"hobbies", {"reading", "music"}}
    };
    
    // パッチの作成
    json patch = json::array({
        {{"op", "replace"}, {"path", "/name"}, {"value", "Jane"}},
        {{"op", "remove"}, {"path", "/age"}},
        {{"op", "add"}, {"path", "/email"}, {"value", "jane@example.com"}}
    });
    
    // パッチの適用
    json patched = document.patch(patch);
    
    // 結果の検証
    EXPECT_EQ(patched["name"], "Jane");
    EXPECT_FALSE(patched.contains("age"));
    EXPECT_EQ(patched["email"], "jane@example.com");
    EXPECT_EQ(patched["hobbies"], json({"reading", "music"}));
}

TEST(Patch, JsonMergePatch) {
    // merge_patch: jsonオブジェクトをマージする
    json original = {
        {"title", "Original"},
        {"author", {
            {"name", "John"},
            {"email", "john@example.com"}
        }},
        {"price", 100}
    };
    
    // マージパッチの作成と適用
    json patch = {
        {"title", "Updated"},
        {"author", {
            {"name", "Jane"}
        }},
        {"tags", {"x", "y"}}
    };
    
    original.merge_patch(patch);
    
    // 結果の検証
    EXPECT_EQ(original["title"], "Updated"); // プロパティが更新される
    EXPECT_EQ(original["author"]["name"], "Jane");
    EXPECT_EQ(original["author"]["email"], "john@example.com");  // 未変更
    EXPECT_EQ(original["tags"], json({"x", "y"})); // 新しいプロパティが追加される
    EXPECT_EQ(original["price"], 100); // 既存のプロパティは更新されない
}