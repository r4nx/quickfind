#include "trie.hpp"

#include <iterator>
#include <queue>
#include <string>
#include <vector>

void TrieNode::insert(const std::wstring &key)
{
    TrieNode *current_node = this;

    for (const auto c : key)
        current_node =
            &current_node->children.try_emplace(c, TrieNode{}).first->second;

    current_node->is_word_end = true;
}

std::vector<std::wstring> TrieNode::extract_words(const std::wstring &prefix)
{
    std::vector<std::wstring> words{prefix};
    std::queue<TrieNode *>    traversal;
    traversal.push(this);

    while (!traversal.empty())
    {
        TrieNode *current_node = traversal.front();
        traversal.pop();

        for (auto &[key, val] : current_node->children)
        {
            words.back().push_back(key);

            if (val.is_word_end)
                words.push_back(prefix);

            traversal.push(&val);
        }
    }

    return words;
}

std::vector<std::wstring> TrieNode::search_by_prefix(const std::wstring &prefix)
{
    TrieNode *current_node = this;

    // Traverse the tree by prefix
    for (const auto c : prefix)
    {
        const auto it = current_node->children.find(c);

        if (it == current_node->children.cend())
            return {};

        current_node = &it->second;
    }

    if (!current_node->children.empty())
        return current_node->extract_words();
    // Found nothing but the prefix itself
    else if (current_node->is_word_end)
        return {prefix};
    else
        return {};
}
