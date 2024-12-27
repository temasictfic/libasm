NAME = libasm.a
TEST = test_libasm
NASM = nasm
NASM_FLAGS = -f elf64
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJ = $(SRC:.s=.o)
TEST_SRC = main.c
INC = libasm.h

all: $(NAME)

%.o: %.s
	$(NASM) $(NASM_FLAGS) $<

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

test: $(NAME) $(TEST_SRC) $(INC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST) -L. -lasm
	./$(TEST)

clean:
	rm -f $(OBJ)
	rm -f $(TEST)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test