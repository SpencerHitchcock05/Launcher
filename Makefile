CXX ?= g++
CXXFLAGS ?= -O2
CXXFLAGS += -std=c++17 -Wall -Wextra -Iinclude -MMD -MP \
	$(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
LDLIBS += $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=build/%.o)
DEP = $(OBJS:.o=.d)

all: build/Launcher

build/Launcher: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDLIBS)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

-include $(DEP)
.PHONY: all clean