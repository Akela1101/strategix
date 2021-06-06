# Strategix — RTS game engine (draft)
The main aim of this project — to provide a template for common Real-Time Strategy games. 

## Contents
* **core** — strategix core library
* **server** — server based on this library
* **map_editor** — qt application for map editing
* **sample1** — sample of client, based on map_editor

![screenshot1](docs/screenshots/screenshot1.png)

## Features
* Configuring games with json.
* Simple client-server protocol.
* Entities now able to collect resources and attack enemy units.

## Dependencies
* cmake >=3.16
* boost >=1.67 (filesystem, property_tree, asio, serialization, ...)
* qt >=5.11 (widgets for map editor)
---
An Instruction **[For Windows](docs/windows.md)**

## Build
Checked on the following compilers:

* **mingw64 gcc** from [msys2](http://www.msys2.org/).
* **msvc 19** (VS 2019)

```sh
cd <your projects dir>
git clone git@github.com:Akela1101/strategix.git
cd strategix
mkdir build && cd build
cmake ..
make
```
