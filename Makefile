CC = gcc -I./include/ -fPIC
C_FLAGS = -W -Wall -Wextra -Werror -shared
RM = rm -f

SRC		=		src/malloc.c    \
				src/heap.c		\
				src/lists.c		\
				src/calloc.c	\
				src/free.c		\
				src/realloc.c	\
				src/utilities.c

TESTS	=		src/malloc.c    	\
				src/heap.c			\
				src/lists.c			\
				src/calloc.c		\
				src/free.c			\
				src/realloc.c		\
				tests/unit_tests.c	\

OBJ = $(SRC:.c=.o)

NAME    =   libmy_malloc.so

all:    $(NAME)

debug:	$(SRC)
	$(CC) $(SRC) -D DEBUG $(C_FLAGS) -o $(NAME)

$(NAME):    $(OBJ) $(TESTS)
	$(CC) $(OBJ) $(C_FLAGS) -o $(NAME)
	$(CC) $(TESTS) -o unit_tests -lcriterion --coverage -D DEBUG
	./unit_tests | gcovr

tests_run:	$(TESTS)
	gcc $(TESTS) -o unit_tests -D DEBUG -lcriterion --coverage
	./unit_tests | gcovr

clean:
	$(RM) $(shell find $(SOURCEDIR) -name '*.o')
	$(RM) $(shell find $(SOURCEDIR) -name '*.gc*')
	$(RM) unit_tests

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean