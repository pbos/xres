all: xres.c
	gcc -lX11 -o xres xres.c
clean:
	rm -f xres
