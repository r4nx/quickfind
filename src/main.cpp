#include "trie.hpp"

#include <string>

int main()
{
    TrieNode trie_node;

    trie_node.insert(L"they");
    trie_node.insert(L"type");

    auto words = trie_node.extract_words();

    return 0;
}
