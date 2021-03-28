# all: a3q1

# a3q1: a3q1.c
# 	clang a3q1.c -Wall -Wpedantic -Wextra -Werror -pthread -o a3q1

# queue: queue.c
# 	clang queue.c -Wall -Wpedantic -Wextra -Werror -pthread -o queue

# clean:
# 	rm queue

CC=clang
CFLAGS=-c -Wall -Wpedantic -Wextra -Werror -pthread
# DEBUG=1

all: a3q1

a3q1: main.o queue.o 
	$(CC) main.o queue.o -o a3q1

main.o: main.c task.h queue.h
	$(CC) $(CFLAGS)  main.c task.h queue.h

queue.o: queue.c task.h queue.h
	$(CC) $(CFLAGS)  queue.c task.h queue.h

clean:
	rm a3q1 main.o queue.o queue.h.gch task.h.gch