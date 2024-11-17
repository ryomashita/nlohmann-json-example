include(FetchContent)

# v3.11.3 Release 2023-11-28
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

function(link_nlohmann_json target)
    target_link_libraries(${target} PRIVATE nlohmann_json::nlohmann_json)
endfunction()