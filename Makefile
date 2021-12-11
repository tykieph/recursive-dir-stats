SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

CXX = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -fpermissive
LDLIBS = -lstdc++fs -lpthread
RM = rm -f

SRCS = 	$(SRC_DIR)/main.cpp $(SRC_DIR)/DirStats.cpp \
		$(SRC_DIR)/FileStats.cpp $(SRC_DIR)/ThreadPool.cpp \
		$(SRC_DIR)/SafeQueue.cpp
OBJS = 	$(OBJ_DIR)/main.o $(OBJ_DIR)/DirStats.o \
		$(OBJ_DIR)/FileStats.o  $(OBJ_DIR)/ThreadPool.o \
		$(OBJ_DIR)/SafeQueue.o
VPATH = $(SRC_DIR)

EXAMPLE_PATH = /home/tykieph
EXAMPLE_PROGOPTS = -p $(EXAMPLE_PATH) -r -m

all: main 

main: $(OBJS)
	$(CXX) -o $(BIN_DIR)/$@ $(OBJS) $(LDLIBS) 

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@  

run-example:
	$(BIN_DIR)/main $(EXAMPLE_PROGOPTS)

run-debug:
	gdb --args $(BIN_DIR)/main $(EXAMPLE_PROGOPTS)

clean:
	$(RM) $(BIN_DIR)/* $(OBJ_DIR)/*.o