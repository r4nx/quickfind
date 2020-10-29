#include "directory_index.hpp"
#include "trie.hpp"

#include <clocale>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

int main()
{
    std::setlocale(LC_ALL, "");

    std::wstring folder_to_index;
    std::cout << "Path to the folder to index >";
    std::wcin >> folder_to_index;

    try
    {
        fs::path index_path(folder_to_index);

        if (!fs::exists(index_path))
        {
            std::cerr << "Cannot find the specified directory ;(" << std::endl;
            return EXIT_FAILURE;
        }
        else if (!fs::is_directory(index_path))
        {
            std::cerr << "Specified path doesn't appear to be a directory."
                      << std::endl;
            return EXIT_FAILURE;
        }

        std::cout << "Indexing, please wait.." << std::endl;
        DirectoryIndex index{index_path};

        while (true) {
            std::wstring query;

            std::cout << "Query >";
            std::wcin >> query;

            for (const auto &suggestion : index.get_suggestions(query))
                std::wcout << suggestion << std::endl;
        }
    }
    catch (const std::runtime_error &ex)
    {
        std::cerr << "== Oops, runtime error ==\n" << ex.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
