all: pipin.c
	gcc -o hw13 pipin.c
clean:
	rm *~
	rm a.out
run: all
	./hw13
