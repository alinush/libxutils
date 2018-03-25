libxutils
=========

A utility library with various useful functions.

`libxutils` is easily importable into CMake projects using either `add_subdirectory` (when not installed on the system but present locally in the code repository that's importing it) or using `find_package` (when installed on the system).

## Build

To build, create a `build/` directory (will be .gitignore'd by default) as follows:

    cd libxutils/   # assuming you are in the repo
    mkdir build/
    cd build/
    cmake ..
    cmake --build .
    cmake --build . --target install    

## Test

To run some tests:

    cd libxutils/   # assuming you are in the repo
    cd build/       # and you have built everything successfully
    ctest

## Git submodules

For historical purposes, when first I set up the submodules, I did:
    
    cd depends/
    git submodule add https://github.com/alinush/xassert 

To update your submodules with changes from their upstream github repos, do:

    git submodule foreach git pull origin master

