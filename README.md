### Quick guide

To download glew from conan, add remote repository

``` bash
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
