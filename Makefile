all: project3.o item.o sales.o
	gcc -o project3 project3.o item.o sales.o

project3.o: project3.c project3.h item.c item.h sales.c sales.h
	gcc -c project3.c item.c sales.c

sales.o: sales.c sales.h item.c item.h
	gcc -c sales.c item.c

item.o: item.c item.h
	gcc -c item.c

clean:
	rm *.o