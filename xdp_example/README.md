# xdp_example

## Compilation

**Run the following in the project root dir**:

1. Pull submodules:
```bash
$ git submodule update --init --recursive
```

2. Compile libbpf:
```bash
$ cd ../external/libbpf/src
$ BUILD_STATIC_ONLY=y make
$ cd ../../../xdp_example
```

3. Compile the program:
```bash
$ mkdir build
$ cmake -S . -B ./build
$ cmake --build ./build
```

## Usage

```bash
$ sudo ./build/xdp_example
```
