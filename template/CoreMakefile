SRC_FILES := $(wildcard src/*.cpp)
LIB_FILES := $(patsubst src/%.cpp, lib/%.o, $(SRC_FILES))
CPP_FLAGS := -std=c++11
INC_FLAGS := -I ../../include/


all: $(LIB_FILES)
$(LIB_FILES): lib/%.o : src/%.cpp
	g++ $(CPP_FLAGS)	 -c -o $@ $^  $(INC_FLAGS)
clean:
	rm lib/*.o
binary:
	cd bin && $(MAKE)
