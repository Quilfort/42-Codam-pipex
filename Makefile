NAME = pipex
CC = gcc -g
FLAGS = -Wall -Werror -Wextra
INCLUDE = -I ./include
OBJ_FILES = $(SRC:%.c=%.o)
SRC =	pipex.c \
		pipex_path.c \
		pipex_error.c \
		./utils/ft_split.c \
		./utils/ft_strjoin.c \
		./utils/ft_strnstr.c \
		./utils/ft_strlen.c \
		./utils/ft_substr.c \
		./utils/ft_strdup.c \
		./utils/ft_putstr_fd.c

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
