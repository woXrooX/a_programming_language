# Out
OUT = -o ./out/APLC

# Flags
# -Wall = Warn ALl
FLAGS = -Wall

# C++ standard version
CPPSTDV = -std=c++2a

# File(s)
FILES = ./source/main.cpp

# Default / Main
build_and_run_main: clear build_main run_main

build_main:
	g++ $(FILES) $(OUT) $(CPPSTDV) $(FLAGS)

run_main: clear
	./out/APLC

# Clears The Terminal
clear:
	clear

# Cleans Outs
clean:
	rm ./out/*
