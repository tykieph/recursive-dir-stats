SRC_DIR = ./src
TESTS_DIR = ./tests
OBJ_DIR = ./obj
BIN_DIR = ./bin

CXX = g++
CPPFLAGS = -std=c++17 -Wall -Wextra 
LDLIBS = -lstdc++fs -lpthread -lgtest 
RM = rm -f

SRCS = 	main.cpp DirStats.cpp FileStats.cpp 
TESTS_SRCS = DirStats_test.cpp FileStats_test.cpp
OBJS = $(addprefix $(OBJ_DIR)/, $(patsubst %cpp, %o, $(SRCS)))
OBJS += $(addprefix $(OBJ_DIR)/, $(patsubst %cpp, %o, $(TESTS_SRCS)))
VPATH = $(SRC_DIR) $(TESTS_DIR)

CURRENT_DIR = $(shell pwd)
EXAMPLE_PATH = /home/tykieph
EXAMPLE_PROGOPTS = -p $(EXAMPLE_PATH) -r

all: main 

main: $(OBJS)
	$(CXX) -o $(BIN_DIR)/$@ $(OBJS) $(LDLIBS) 

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@  

tests: CPPFLAGS += -D RUN_TESTS
tests: all 

run-example:
	$(BIN_DIR)/main $(EXAMPLE_PROGOPTS)

clean:
	$(RM) $(BIN_DIR)/* $(OBJ_DIR)/*.o
