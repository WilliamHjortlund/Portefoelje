CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET  = monster_spil
SRCS    = main.cpp character.cpp monsters.cpp combat.cpp menu.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean