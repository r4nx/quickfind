# Separated target for the tested part of application
# to make it possible to link with test runner
add_library(quickfind_tested STATIC
 "trie.hpp"
 "trie.cpp"
 "directory_index.hpp"
 "directory_index.cpp")

add_executable(quickfind
 "main.cpp")

target_compile_features(quickfind_tested PRIVATE cxx_std_20)
target_compile_features(quickfind PRIVATE cxx_std_20)
target_include_directories(quickfind_tested PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(quickfind PRIVATE quickfind_tested)
