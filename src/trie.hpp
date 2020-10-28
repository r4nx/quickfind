#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <map>
#include <string>
#include <vector>

class TrieNode {
public:
    void insert(const std::wstring &word);

    /*
     * @brief Extracts all the words found in the tree and optionally prepends
     * specified @p prefix to them.
     */
    std::vector<std::wstring> extract_words(const std::wstring &prefix = L"");

    /*
     * @brief Found all the words, that start with the specified @p prefix.
     */
    std::vector<std::wstring> search_by_prefix(const std::wstring &prefix);

private:
    std::map<wchar_t, TrieNode> children;
    bool                        is_word_end = false;
};

#endif /* !TRIE_HPP_ */
