output: main.o contact.o myvector.o contactbst.o
	g++ main.o contact.o myvector.o contactbst.o -o output
main.o: main.cpp
	g++ -c main.cpp
contact.o: contact.cpp contact.h
	g++ -c contact.cpp
myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp
contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp
clean:
	rm output main.o contact.o myvector.o contactbst.o
