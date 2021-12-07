SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

CXX = g++
CPPFLAGS = -std=c++17 -Og -Wall 
LDLIBS = -lstdc++fs
RM = rm -f

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/DirStats.cpp
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/DirStats.o
VPATH = $(SRC_DIR)

EXAMPLE_PATH = /home/tykieph/Programming/Cpp/BCF-Software/recursive-dir-stats
EXAMPLE_PROGOPTS = -p $(EXAMPLE_PATH) -r 0

all: main 

main: $(OBJS)
	$(CXX) -o $(BIN_DIR)/$@ $(OBJS) $(LDLIBS) 

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $< 


run-example:
	$(BIN_DIR)/main $(EXAMPLE_PROGOPTS)

clean:
	$(RM) $(BIN_DIR)/* $(OBJ_DIR)/*.o