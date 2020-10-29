find_package(doctest REQUIRED)

add_executable(tests
 "doctest_main.cpp"
 "trie_tests.cpp")

target_compile_features(tests PRIVATE cxx_std_20)
target_link_libraries(tests PRIVATE quickfind_tested doctest::doctest)
target_include_directories(tests PRIVATE ${DOCTEST_INCLUDE_DIR})

include(doctest)
doctest_discover_tests(tests)
