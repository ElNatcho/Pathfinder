# >> Vars erstellen

# Allgemeine Projekteigenschaften
NAME := MapCreator
P_ROOT := $(shell pwd)
SRC_DIR := $(P_ROOT)/src
REL_DIR := $(P_ROOT)/bin/release
DBG_DIR := $(P_ROOT)/bin/debug
C_MODE := R

# Kompiler und dessen Flags
CXX := g++
C_F := -c -std=c++14 -Wall
L_F := -o $(NAME) -Wall
D_F := -g

# Source Dateien
SRC := $(SRC_DIR)/*.cpp
#HED := $(SRC_DIR)/*.hpp
OBJ := main.o

all: $(OBJ)
ifeq ($(C_MODE), R)
	$(CXX) $(L_F) $(OBJ)
else
	$(CXX) $(L_F) $(D_F) $(OBJ)
endif
	make clean

$(OBJ): $(SRC_DIR)
ifeq ($(C_MODE), R)
	$(CXX) $(C_F) $(SRC)
	#$(CXX) $(C_F) $(HED)
else
	$(CXX) $(C_F) $(D_F) $(SRC)
	#$(CXX) $(C_F) $(D_F) $(HED)
endif

.PHONY: clean
clean:
	-rm -f $(OBJ)
ifeq ($(C_MODE), R)
	mv $(NAME) $(REL_DIR)
else
	mv $(NAME) $(DBG_DIR)
endif