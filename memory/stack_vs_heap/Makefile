compile: stack_vs_heap.c
	gcc -Wall -Wextra -g stack_vs_heap.c -o stack_vs_heap

compile_functional: stack_vs_heap_functional.c
	gcc -Wall -Wextra -g stack_vs_heap_functional.c -o stack_vs_heap_functional

valgrind: stack_vs_heap
	valgrind --leak-check=full ./stack_vs_heap