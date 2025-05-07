all: block blockchain main.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g  main.cpp block blockchain  -o main -lcrypto -lssl
block: block.h block.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g -c block.cpp -o block
blockchain: blockchain.h blockchain.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g -c blockchain.cpp -o blockchain