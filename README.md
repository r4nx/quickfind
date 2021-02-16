# quickfind

Tiny cross-platform utility for indexing a directory and searching files there recursively by typing first few letters of file name.

### Usage
Run the executable, specify the directory to index. As indexing finishes, type the beginning of the file name, press Enter and get the suggestions.

### Building
```
cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE="Release"
cmake --build build
```

### Algorithms behind the scene
Application uses [trie](https://en.wikipedia.org/wiki/Trie) for storing file names; folder hierarchy is represented by simple trees.
