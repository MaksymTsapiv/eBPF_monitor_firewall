# monitor-firewall

## Prerequisites

- glibc
- virtualenv (install it via pip)

## Compilation

Run the following commands in the `monitor_firewall` directory:

1. Pull submodules:
```bash
$ git submodule update --init --recursive
```

2. Compile libbpf (version 0.8.0)
```bash
$ cd ../external/libbpf-0.8.0/src
$ BUILD_STATIC_ONLY=y make
$ cd ../../../monitor_firewall
```

3. Compile monitorBX:
```bash
$ cd monitorBX
$ sudo make
$ cd ..
```

4. Setup virtual environment:
```
$ cd Heimdallr-project
$ sudo make
$ virtualenv .venv
$ source .venv/bin/activate
$ pip install -r requirements.txt
$ cd ..
```


## Usage

Run the following in the `monitor_firewall` directory:
```
$ python3 listener.py
```
