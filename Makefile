CXX=g++
CXXFLAGS=  -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
OBJS_MAIN = src/main.o
OBJS_SPACE = src/spaceInvader.o src/user.o
LIBS_PATH = -L/opt/homebrew/lib -lGL -lglut
INC_PATH = -I/opt/homebrew/include
MAIN= main space

.PHONY: all clean

all: main space

main: $(OBJS_MAIN)
	$(CXX) $(CXXFLAGS) $(INC_PATH) $+ -o $@ $(LIBS_PATH)

space: $(OBJS_SPACE)
	$(CXX) $(CXXFLAGS) $(INC_PATH) $+ -o $@ $(LIBS_PATH)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $(INC_PATH) $< -o $@

clean: 
	$(RM) main space src/*.o src/lib/*.o

# g++ -o myprogram -I/opt/homebrew/include -L/opt/homebrew/lib -lGL -lglut main.cpp