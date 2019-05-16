#PLIK MAKEFILE

CC = g++
CFLAGS = -std=c++11
TARGET = menu

$(TARGET): main.o button.o shell.o saveXML.o
	$(CC) main.o button.o shell.o saveXML.o -g -o $(TARGET)

main.o: main.cpp button.h
	$(CC) $(CFLAGS) -c -g main.cpp

button.o: button.cpp button.h shell.h saveXML.h
	$(CC) $(CFLAGS) -c -g button.cpp shell.cpp saveXML.cpp

shell.o: shell.cpp shell.h
	$(CC) $(CFLAGS) -c -g shell.cpp

saveXML.o: saveXML.cpp saveXML.h
	$(CC) $(CFLAGS) -c -g saveXML.cpp

clean:
	rm -f *.o $(TARGET)
