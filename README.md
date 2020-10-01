# Peyman Language

A programming language to honor our beloved friend, Peyman.

## Sample
```
-- in yek commente :D

-- ba chiz moteghayer tarif mikonim
chiz folan = 12;

-- injoori print mishe
chaap folan;

-- injoori voroodi migire
begir folan;

-- while loop ham dare
ta folan < 20 {
   -- if else ham dare
   agar folan % 2 == 0 {
      chaap 1;
   } vagarna {
      chaap 0;
   }
   
   folan += 1;
}
```

## Installation from source

~~we use cmake as build system~~ not anymore!

### Building on a Unix-like system
1. Make sure you have installed all the dependencies:

    * `g++` 4.3 or later
    * GNU `make`
    * `git`
    * `flex`
    * `bison`

On an ubuntu machine You can install them like this (but make sure the required version is installing):
```sh
$ sudo apt-get -y install git-all build-essential cmake flex bison
```

2. Clone the [source](https://github.com/amiremohamadi/peylang.git) with `git`:
```sh
$ git clone https://github.com/amiremohamadi/peylang.git
$ cd peylang
```

3. Build & Run:
```sh 
$ make
$ ./peyman
```

You can run tests using `ctest` or 'make test'

