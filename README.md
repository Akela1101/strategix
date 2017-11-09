# Strategix — RTS game engine (draft)
The main aim of this project is a base library for common Real-Time Strategy games. 

## Contents
* core — strategix core library
* map_editor — Qt application for map editing
* samples — samples of games \[ outdated ]

## Build
Probably any popular C++17 compiler can be used. 
But tested on **mingw64 gcc 7.2**.
```sh
mkdir build && cd build
cmake ..
make
```
cmake might ask for some options like the prefix to QT
, so the command would be:
```sh
cmake -DCMAKE_PREFIX_PATH=C:\msys\mingw64\qt5-static ..
```
Anyway it's better to use IDE for build purposes.
