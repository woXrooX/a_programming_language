#### Out

OUT_DIR = ./out
OUT_BIN = $(OUT_DIR)/APLC
OUT = -o $(OUT_BIN)

#### Flags

# -Wall = Warn ALl
FLAGS = -Wall

# C++ standard version
CPPSTDV = -std=c++2a

# File(s)
FILES = ./source/main.cpp

# Default / Main
build_and_run_main: clear build_main run_main

build_main:
	mkdir -p $(OUT_DIR)
	g++ $(FILES) $(CPPSTDV) $(FLAGS) $(OUT)

run_main: clear
	$(OUT_BIN) ./out/my_app.a

# Clears The Terminal
clear:
	clear

clean:
	rm -f $(OUT_BIN)
