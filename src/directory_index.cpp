#include "directory_index.hpp"

#include <filesystem>
#include <queue>
#include <string>
#include <utility>
#include <vector>

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

std::vector<std::wstring>
DirectoryIndex::get_suggestions(const std::wstring &query)
{
    std::vector<std::wstring>    suggestions;
    std::queue<DirectoryIndex *> traversal;

    traversal.push(this);

    while (!traversal.empty())
    {
        DirectoryIndex *dir_index = traversal.front();
        traversal.pop();

        for (const auto &file_name :
             dir_index->dir_items.search_by_prefix(query))
        {
            suggestions.push_back((dir_index->path / file_name).wstring());
        }

        for (auto &child_dir : dir_index->children)
        {
            // We can get a pointer to the vector elements as long as it doesn't
            // invalidate its iterators
            traversal.push(&child_dir);
        }
    }

    return suggestions;
}
