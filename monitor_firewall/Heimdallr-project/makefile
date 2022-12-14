CC = clang

PRG_DIR = prg
SRC_DIR = src
INC_DIR = inc

XDP_NAME = bpf_program
LDR_NAME = launcher
MAP_NAME = map_util

# I_PATH = -I/usr/include/bpf -Iinc -I/usr/include/x86_64-linux-gnu
I_PATH = -Iinc -I../../external/libbpf-0.8.0/src
L_PATH = -L../../external/libbpf-0.8.0/src -L/usr/lib64
U_LIBS = -lbpf -lelf -lz

XDP = $(PRG_DIR)/$(XDP_NAME).o
LDR = $(PRG_DIR)/$(LDR_NAME)
MAP = $(PRG_DIR)/$(MAP_NAME)

LDR_SRC = $(SRC_DIR)/$(LDR_NAME).c
XDP_SRC = $(SRC_DIR)/$(XDP_NAME).c
MAP_SRC = $(SRC_DIR)/$(MAP_NAME).c $(SRC_DIR)/map_driver.c

MAP_INC = $(INC_DIR)/common.h $(INC_DIR)/map_driver.h

XDP_TOOLS = $(XDP) $(LDR) $(MAP)

ifeq ($(CASH),TRUE)
  cash = -DHEIMDALLR_CASH
else
  cash = ""
endif

ifeq ($(DEBUG),TRUE)
  debug = -DHEIMDALLR_DEBUG
else
  debug = ""
endif

DEFINES = $(debug) $(cash)

all: $(PRG_DIR) $(XDP_TOOLS)

$(PRG_DIR):
		mkdir -p $(PRG_DIR)

$(MAP): $(MAP_SRC) $(INC_DIR)
		$(CC) $(MAP_SRC) $(I_PATH) $(U_LIBS) $(DEFINES) -o $@

$(XDP): $(XDP_SRC)
		$(CC) -O2 -target bpf $(I_PATH) $(DEFINES) -c $^ -o $@

$(LDR): $(LDR_SRC)
		$(CC) $(CFLAGS) $^ $(I_PATH) $(U_LIBS) $(L_PATH) $(DEFINES) -o $@

.PHONY: clean

clean:
		rm $(XDP_TOOLS)
