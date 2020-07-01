# Peyman Language

A programming language to make fun of our friend, Peyman.

## Installation from source

we use cmake as build system

### Building on a Unix-like system
1. Make sure you have installed all the dependencies:

    * `g++` 4.3 or later or `clang++` 3.3 or later
    * GNU `make`
    * `cmake` 3.15 or later
    * `git`
    * `flex`

On an ubuntu machine You can install them like this (but make sure the required version is installing):
```sh
$ sudo apt-get -y install git-all build-essential cmake flex
```

2. Clone the [source](https://github.com/amiremohamadi/peylang.git) with `git`:
```sh
$ git clone https://github.com/amiremohamadi/peylang.git
$ cd peylang
```

3. Build:
```sh
$ mkdir build
$ cd build
$ cmake .. && cmake --build .
```

You can run tests using `ctest` or 'make test'

