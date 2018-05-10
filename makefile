compile:
	gcc src/process.c src/queue.c src/manager.c src/main.c -o bin/main
	make clean

clean:
	rm -rf *.o
