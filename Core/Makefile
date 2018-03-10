# >> Vars erstellen

# Allgemeine Projekteigenschaften
P_ROOT := $(shell pwd)
C_MODE := R
USR_INCS := /usr/local/include

# Kompiler und dessen Flags
CXX := g++
C_F := -c -std=c++14 -Wall -I $(USR_INCS) -I $(USR_INCS)/imgui -I $(USR_INCS)/imgui-sfml
D_F := -g

# Source Dateien
SRC := $(shell find -name *.cpp)
HED := $(shell find -name *.hpp)
OBJ := cGraph.o cNode.o cFileMgr.o imgui_demo.o imgui_draw.o imgui-SFML.o imgui.o

all: $(SRC_DIR)
	# Die alten Objekt-Dateien löschen
	-rm $(P_ROOT)/obj/*
	# Dateien kompilieren
ifeq ($(C_MODE), R)
	$(CXX) $(C_F) $(SRC)
	$(CXX) $(C_F) $(HED)
else
	$(CXX) $(C_F) $(D_F) $(SRC)
	$(CXX) $(C_F) $(D_F) $(HED)
endif
	# Die kompilierten Dateien in den obj-Ordner verschieben
	-mv *.o $(P_ROOT)/obj
	# Kompilierte(??) Headerdateien löschen
	-rm $(shell find -name *.hpp.gch)

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f $(shell find -name *.hpp.gch)
