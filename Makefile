build:
	g++ -Wall main.cpp network.cpp node.cpp -o main
clean:
	rm -f *.o *.gch main
