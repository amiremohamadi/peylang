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

-- string
chaap 'salam donya!';

chiz esm = 'peyman';
chaap esm + ' khar ast';

-- logical and or
agar (folan > 10 va folan < 20) ya folan == 40 {
    chaap 200;
}
```

You can find more samples [here](https://github.com/amiremohamadi/peylang/tree/0.0.4/test/samples).


## Syntax Highlighter
- [vim](https://github.com/amiremohamadi/peylang/blob/master/.vim/syntax/pey.vim) highlighter
- [vscode](https://marketplace.visualstudio.com/items?itemName=peylang.peylang) highlighter

## Installing Peylang
### Windows
On Windows machines, you can use [PeySetup](https://github.com/amiremohamadi/peylang/releases/download/0.0.4/PeySetup.exe).
<br/>
Don't forget to restart your machine after installing. Then open cmd and type:
```
peyman your_file_name.pey
```

If it didn't recognize the command, add it manually to PATH variables and retry.

### Linux
On linux machines, download [this](https://github.com/amiremohamadi/peylang/releases/download/0.0.4/peyman).
<br/>
Don't forget ```chmod +x peyman```

### Docker
Also you can use docker to build and use Peylang!
```
git clone https://github.com/amiremohamadi/peylang.git
cd peylang
docker build -t peylang .
docker run -it peylang
```

### From source

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
