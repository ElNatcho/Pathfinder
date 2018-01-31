# >> Vars erstellen

# Allgemeine Projekteigenschaften
NAME := Pathfinder
P_ROOT := ~/Projekte/C-CPP/Pathfinder
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
SRC := $(SRC_DIR)/*.cpp $(SRC_DIR)/Graph/*.cpp $(SRC_DIR)/Graph/FileMgr/*.cpp
HED := $(SRC_DIR)/*.hpp $(SRC_DIR)/Graph/*.hpp $(SRC_DIR)/Graph/FileMgr/*.hpp
OBJ := main.o cGraph.o cNode.o cFileMgr.o

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
	$(CXX) $(C_F) $(HED)
else
	$(CXX) $(C_F) $(D_F) $(SRC)
	$(CXX) $(C_F) $(D_F) $(HED)
endif

.PHONY: clean
clean:
	-rm -f $(OBJ)
	-rm -f $(SRC_DIR)/*.hpp.gch $(SRC_DIR)/Graph/*.hpp.gch $(SRC_DIR)/Graph/FileMgr/*.hpp.gch
ifeq ($(C_MODE), R)
	mv $(NAME) $(REL_DIR)
else
	mv $(NAME) $(DBG_DIR)
endif
