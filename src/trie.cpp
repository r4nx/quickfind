#include "trie.hpp"

#include <stack>
#include <string>
#include <utility>
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
    struct QueueEntry {
        TrieNode *   node = nullptr;
        std::wstring word;
    };

    std::stack<QueueEntry>    traversal;
    std::vector<std::wstring> words;

    traversal.push({this, prefix});

    while (!traversal.empty())
    {
        auto [current_node, word] = traversal.top();
        traversal.pop();

        for (auto &[key, val] : current_node->children)
        {
            QueueEntry child{&val, word};
            child.word.push_back(key);

            if (val.is_word_end)
                words.push_back(child.word);

            if (!val.children.empty())
                traversal.push(std::move(child));
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
        return current_node->extract_words(prefix);
    // Found nothing but the prefix itself
    else if (current_node->is_word_end)
        return {prefix};
    else
        return {};
}
