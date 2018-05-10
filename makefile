compile:
	gcc process.c queue.c manager.c main.c -o main
	make clean

clean:
	rm -rf *.o