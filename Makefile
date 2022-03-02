NAME = pipex
CC = gcc
FLAGS = -Wall -Werror -Wextra
INCLUDE =
OBJ_FILES = $(SRC:%.c=%.o)
SRC =	pipex.c \
		./src/ft_split.c

all : $(NAME)

$(NAME): $(OBJ_FILES)
	gcc $(OBJ_FILES) -o $(NAME) 

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "Cleaning up .o files"
	@rm -f $(OBJ_FILES)

fclean: clean
	@echo "We are cleaning now"
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
