#include "directory_index.hpp"

#include <filesystem>
#include <utility>

namespace fs = std::filesystem;

DirectoryIndex::DirectoryIndex(fs::path path_) : path{std::move(path_)}
{
    for (auto &dir_item : fs::directory_iterator(path))
    {
        dir_items.insert(dir_item.path().filename().wstring());

        if (dir_item.is_directory())
            children.emplace_back(dir_item.path());
    }
}
