NAME = pipex
LIBFT_DIR = ./utils/libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = gcc -g
FLAGS = -Wall -Werror -Wextra
INCLUDE = -I ./include
OBJ_FILES = $(SRC:%.c=%.o)
OBJ_FILES_BONUS = $(SRC_BONUS:%.c=%.o)
SRC =	./mandatory/pipex.c \
		./mandatory/pipex_path.c \
		./mandatory/pipex_error.c 
all : $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	gcc $(OBJ_FILES) $(LIBFT) -o $(NAME) 

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "Cleaning up .o files"
	$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(OBJ_FILES)

fclean: clean
	@echo "We are cleaning now"
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
