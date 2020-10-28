#include "trie.hpp"

#include <stack>
#include <string>
#include <utility>
#include <vector>

void TrieNode::insert(const std::wstring &word)
{
    TrieNode *current_node = this;

    for (const auto c : word)
        current_node =
            &current_node->children.try_emplace(c, TrieNode{}).first->second;

    current_node->is_word_end = true;
}

std::vector<std::wstring> TrieNode::extract_words(const std::wstring &prefix)
{
    using QueueEntry = std::pair<TrieNode *, std::wstring>;

    std::stack<QueueEntry>    traversal;
    std::vector<std::wstring> words;

    traversal.push({this, prefix});

    while (!traversal.empty())
    {
        auto [current_node, word] = std::move(traversal.top());
        traversal.pop();

        for (auto &[key, child_node] : current_node->children)
        {
            QueueEntry entry{&child_node, word};
            entry.second.push_back(key);

            if (child_node.is_word_end)
                words.push_back(entry.second);

            if (!child_node.children.empty())
                traversal.push(std::move(entry));
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
