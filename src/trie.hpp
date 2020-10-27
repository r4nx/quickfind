#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <map>
#include <string>
#include <vector>

class TrieNode {
public:
    void                      insert(const std::wstring &key);
    std::vector<std::wstring> extract_words(const std::wstring &prefix = L"");
    std::vector<std::wstring> search_by_prefix(const std::wstring &prefix);

private:
    std::map<wchar_t, TrieNode> children;
    bool                        is_word_end = false;
};

#endif /* !TRIE_HPP_ */
