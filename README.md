# Strategix — RTS game engine (draft)
The main aim of this project is a base library for common Real-Time Strategy games. 

## Contents
* core — strategix core library
* map_editor — qt application for map editing
* sample1 — sample of game based on map_editor \[ in progress... ]

## Dependencies
* boost
* qt5
* [easylogging++](https://github.com/muflihun/easyloggingpp)
* [nya](https://github.com/Akela1101/nya)

## Build
Probably any popular C++17 compiler can be used. 
But tested on **mingw64 gcc 7.2** from [msys2](http://www.msys2.org/).
```sh
cd <your projects dir>
git clone git@github.com:muflihun/easyloggingpp.git
git clone git@github.com:Akela1101/nya.git
git clone git@github.com:Akela1101/strategix.git
cd strategix
mkdir build && cd build
cmake .. # see below
make
```
cmake might ask for some options like the prefix to QT
, so the command would be:
```sh
cmake -DCMAKE_PREFIX_PATH=C:\msys\mingw64\qt5-static ..
```
Anyway it's better to use IDE for build purposes.
