# Dependencies on Windows

* Check your cmake version.
* Select **[appropriate](https://stackoverflow.com/questions/42123509/cmake-finds-boost-but-the-imported-targets-not-available-for-boost-version)** boost version.
* Download **[binary package](https://boostorg.jfrog.io/artifactory/main/release/1.74.0/binaries/)** (change to your version).
* Install it.
---
* Install Qt with msys2 for MinGW.
    * `-D CMAKE_PREFIX_PATH=C:\msys\mingw64\qt5-static`
* OR
* Install Qt binaries with online installer (offline one does not have Qt5 binaries for VS2019 for the moment).
    * `-D CMAKE_PREFIX_PATH=C:\Qt\5.15.2\msvc2019_64`
  