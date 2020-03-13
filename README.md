### Add conan Remote

To download glew from conan,

``` bash
$ conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"
```

### before run cmake

``` bash
$ cd build
$ conan install .. --build=missing
```

### clang-format

``` bash
$ sudo bash clang-format-all src/
```