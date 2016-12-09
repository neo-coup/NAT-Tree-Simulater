TARGET = main.cpp option.cpp network.cpp node.cpp
BandR:
	g++ -Wall -std=c++11 ${TARGET} -o main
		./main
build:
	g++ -Wall -std=c++11 ${TARGET} -o main
clean:
	rm -f *.o *.gch main
