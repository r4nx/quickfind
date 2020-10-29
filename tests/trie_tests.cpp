#include "trie.hpp"

#include <doctest/doctest.h>

#include <algorithm>
#include <vector>

TEST_SUITE("trie")
{
    TEST_CASE("words search and extraction")
    {
        TrieNode                  node;
        std::vector<std::wstring> testing_data{
            L"hello",
            L"testing",
            L"testable",
            L"world"};
        std::vector<std::wstring> prefixed_data{L"testing", L"testable"};

        for (const auto &word : testing_data)
            node.insert(word);

        std::vector<std::wstring> extracted = node.extract_words();
        std::vector<std::wstring> by_prefix = node.search_by_prefix(L"test");

        CHECK(extracted.size() == testing_data.size());
        CHECK(by_prefix.size() == prefixed_data.size());

        for (const auto &word : testing_data)
            CHECK(
                std::find(extracted.cbegin(), extracted.cend(), word)
                != extracted.cend());

        for (const auto &word : prefixed_data)
            CHECK(
                std::find(by_prefix.cbegin(), by_prefix.cend(), word)
                != by_prefix.cend());
    }
}
