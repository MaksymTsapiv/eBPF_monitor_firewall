# xdp_test

## Compilation

**Run the following in the project root dir**:

#### Compile libbpf

```bash
$ cd ../libbpf/src
$ BUILD_STATIC_ONLY=y make
$ cd ../../xdp_example
```

#### Compile the program
```bash
$ mkdir build
$ cmake -S . -B ./build
$ cmake --build ./build
```
