# Definições
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS =
OBJ = main.o Graph.o Node.o Edge.o
EXEC = main.exe

# Regra para compilar o executável
$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(EXEC) $(OBJ)

# Regras para compilar arquivos objeto
main.o: main.cpp Graph.hpp Node.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Graph.o: Graph.cpp Graph.hpp Node.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Graph.cpp

Node.o: Node.cpp Node.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Node.cpp

Edge.o: Edge.cpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Edge.cpp

# Regra para limpar arquivos objeto e executável
clean:
	rm -f $(OBJ) $(EXEC)
