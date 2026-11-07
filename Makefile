CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=build/%.o)

build/Launcher: $(OBJS)
	$(CXX) $(OBJS) -o $@

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build