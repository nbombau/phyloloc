OBJS_COMMON = main.o Parser/newick.o Parser/tree.o
OBJS_TEST1  = $(OBJS_COMMON)

CC = g++
FLAGS = -g
# -Winit-self -Wswitch-enum -Wextra -Wfloat-equal -Wundef -Wno-invalid-offsetof -pthread -I/usr/local/include -g -O2

test1 : $(OBJS_TEST1)
	$(CC) $(FLAGS) -o test1  $(OBJS_TEST1)

clean:
	rm -f test1
	rm -f *.o

.NOEXPORT: