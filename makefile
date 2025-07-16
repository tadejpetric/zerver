CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Wconversion -pedantic -Wunused-result

.PHONY: server client

server: server.cpp
	$(CXX) $(CXXFLAGS) -o $@.out $^

client: client.cpp
	$(CXX) $(CXXFLAGS) -o $@.out $^