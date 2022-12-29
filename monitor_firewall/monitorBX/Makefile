CLANG = clang

EXECABLE = monitorBX

BPFCODE = bpf_program

MACRO = -D BPF_TRACE_CUSTOM

LIBRARY_PATH = -L/usr/lib64
BPFSO = -lbpf

LOADINCLUDE += -I/usr/include/bpf

.PHONY: clean $(CLANG) bpfload build

clean:
	rm -f *.o *.so $(EXECABLE)

build: ${BPFCODE.c}
	$(CLANG) $(MACRO) -O2 -target bpf -c $(BPFCODE:=.c) $(CCINCLUDE) -o ${BPFCODE:=.o} -isystem /usr/include/x86_64-linux-gnu

bpfload: build
	g++ -std=c++11 loader.cpp $(CFLAGS) $(MACRO) -o $(EXECABLE) -lelf $(LOADINCLUDE) $(LIBRARY_PATH) $(BPFSO) \
        $(BPFLOADER) -lm 
$(EXECABLE): bpfload

.DEFAULT_GOAL := $(EXECABLE)
