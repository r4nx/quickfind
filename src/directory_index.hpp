#ifndef DIRECTORY_INDEX_HPP_
#define DIRECTORY_INDEX_HPP_

#include "trie.hpp"

#include <filesystem>
#include <string>
#include <vector>

class DirectoryIndex {
public:
    DirectoryIndex(std::filesystem::path path_);

    std::vector<std::wstring> get_suggestions(const std::wstring &query);

private:
    std::filesystem::path       path;
    TrieNode                    dir_items;
    std::vector<DirectoryIndex> children;
};

#endif /* !DIRECTORY_INDEX_HPP_ */
