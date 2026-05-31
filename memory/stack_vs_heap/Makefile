compile: src/stack_vs_heap.c
	gcc -Wall -Wextra -g src/stack_vs_heap.c -o bin/stack_vs_heap.out

compile_functional: src/stack_vs_heap_functional.c
	gcc -Wall -Wextra -g src/stack_vs_heap_functional.c -o bin/stack_vs_heap_functional.out

valgrind: bin/stack_vs_heap.out
	valgrind --leak-check=full bin/stack_vs_heap.out