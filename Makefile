TARGET = main.cpp network.cpp node.cpp
BandR:
	g++ -Wall ${TARGET} -o main
	./main
build:
	g++ -Wall ${TARGET} -o main
clean:
	rm -f *.o *.gch main
