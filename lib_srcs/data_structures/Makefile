CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
EXE := test_graph.out

.PHONY: clean
clean: 
	rm $(EXE) *.o

$(EXE): %.out : %.c linked_list_graph.o graph.o doubly_linked_list.o linked_list_queue.o comp_funcs.o
	$(CC) $(CFLAGS) -o $@ $^ -I"includes" -I"../basic_data_manipulation/includes"

%.o: 
	$(CC) $(CFLAGS) -c $$(fdfind -g ${@:.o=.c} ../) -I"includes" -I"../basic_data_manipulation/includes"