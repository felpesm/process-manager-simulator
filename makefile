compile:
	gcc source/process.c source/queue.c source/manager.c source/main.c -o main
	make clean

clean:
	rm -rf *.o