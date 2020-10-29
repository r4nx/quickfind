#ifndef DIRECTORY_INDEX_HPP_
#define DIRECTORY_INDEX_HPP_

#include "trie.hpp"

#include <filesystem>
#include <vector>

class DirectoryIndex {
public:
    DirectoryIndex(const std::filesystem::path &path_);

// private:
    std::filesystem::path       path;
    TrieNode                    dir_items;
    std::vector<DirectoryIndex> children;
};

#endif /* !DIRECTORY_INDEX_HPP_ */
