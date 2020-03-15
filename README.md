### Quick guide

To download glew from conan, add remote repository

``` bash
$ sudo apt-get update
$ sudo apt-get install python3 python3-distutils
$ curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
$ python get-pip.py
$ python -m pip install conan
$ conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"
```

then, let conan package manager install all the dependencies

``` bash
$ mkdir build
$ cd build
$ conan install .. --build=missing
```
run cmake, make

``` bash
$ cmake ..
$ make
$ ./bin/bootstrap
```

when to use Windows Visual Studio

``` bash
$ cmake .. -G "Visual Studio 16"
```

### clang-format

``` bash
$ sudo bash clang-format-all src/
```

### ctest

list all the test cases

```bash
$ cd build
$ ctest -N
```

run specific test case

```bash
$ cd build
$ ctest -R "test case 1"
```

### static analyzers

- cppcheck

```bash
cmake .. -DENABLE_CPPEHCK
```

- clang-tidy

```bash
cmake .. -DENABLE_CLANGTIDY
```

- iwyu

```bash
cmake .. -DENABLE_IWYU
```

### ccache

ccache built-in support

``` bash
ccache -s
```

### MSVC without Visual Studio

in order to use nmake in Visual c++, check the env variables to set cl.exe, vcvarsall.bat.  
cl.exe is core msvc c++ compiler program, vcvarsall.bat is batch script that helps cl.exe can set every vc variables like include (-I), link path.
nmake is helper program to build make files in Windows, unlike make command, it is not compatible with standard Makefiles.

``` bash
set PATH=%PATH%;path-to-cl;path-to-vcvarsall
mkdir build
cd build
conan install .. --build=missing
cmake -G "NMake Makefiles" ..
nmake
```
