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

    traversal.push({this});

    while (!traversal.empty())
    {
        auto [current_node, word] = traversal.top();
        traversal.pop();

        /*
        if (!char_queue.empty())
        {
            auto [c, is_word_end] = char_queue.front();
            char_queue.pop();

            if (new_word_required)
                words.push_back(prefix);

            words.back().push_back(c);

            new_word_required = is_word_end;
        }
        */

        for (auto &[key, val] : current_node->children)
        {
            QueueEntry child{&val, word};
            child.word.push_back(key);

            if (val.is_word_end)
                words.push_back(child.word);

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
        return current_node->extract_words();
    // Found nothing but the prefix itself
    else if (current_node->is_word_end)
        return {prefix};
    else
        return {};
}
