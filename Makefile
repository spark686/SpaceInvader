CXX=g++
CXXFLAGS=  -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
OBJS_MAIN = src/main.o
OBJS_SPACE = src/spaceInvader.o src/user.o src/enemies.o 
LIBS_PATH = -L/opt/homebrew/lib -lGL -lglut
INC_PATH = -I/opt/homebrew/include
MAIN= main space

.PHONY: all clean

all: main space

main: $(OBJS_MAIN)
	$(CXX) $(CXXFLAGS) $(OBJS_MAIN) -o $@ $(INC_PATH) $(LIBS_PATH)

space: $(OBJS_SPACE)
	$(CXX) $(CXXFLAGS) $(OBJS_SPACE) -o $@ $(INC_PATH) $(LIBS_PATH)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	$(RM) main space src/*.o src/lib/*.o

# g++ -o myprogram -I/opt/homebrew/include -L/opt/homebrew/lib -lGL -lglut main.cpp