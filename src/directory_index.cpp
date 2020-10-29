#include "directory_index.hpp"

#include <filesystem>
#include <queue>
#include <stdexcept>
#include <utility>

namespace fs = std::filesystem;

DirectoryIndex::DirectoryIndex(const fs::path &path_) : path{path_}
{
    for (auto &dir_item : fs::directory_iterator(path))
    {
        dir_items.insert(dir_item.path().filename().wstring());

        if (dir_item.is_directory())
            children.emplace_back(dir_item.path());
    }
}
