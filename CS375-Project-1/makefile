file1= Card
file2= Program1
target= program1
OBJECTS= $(file1).o $(file2).o
CFLAGS= -std=c++14 -g

all: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o $(target)


$(file1).o: $(file1).h $(file1).cpp
	g++ -c $(CFLAGS) $(file1).cpp

$(file2).o: $(file2).cpp
	g++ -c $(CFLAGS) $(file2).cpp


clean:
	rm -rf output.txt
	rm -rf *.o
	rm $(target)

run: all
	./$(target)
memcheck: all
	valgrind ./$(target) -v --leak-check=full

winclean:
	del *.o
	del $(target).exe
