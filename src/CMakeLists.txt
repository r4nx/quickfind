add_executable(quickfind)

target_compile_features(quickfind PRIVATE cxx_std_20)

target_sources(quickfind PRIVATE
 "main.cpp"
 "trie.hpp"
 "trie.cpp")
