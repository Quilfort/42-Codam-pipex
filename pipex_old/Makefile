NAME = pipex
CC = gcc -g
FLAGS = -Wall -Werror -Wextra
INCLUDE = -I ./include
OBJ_FILES = $(SRC:%.c=%.o)
OBJ_FILES_BONUS = $(SRC_BONUS:%.c=%.o)
SRC =	./bonus/pipex_bonus.c \
		./mandatory/pipex_path.c \
		./mandatory/pipex_error.c \
		./utils/ft_split.c \
		./utils/ft_strjoin.c \
		./utils/ft_strnstr.c \
		./utils/ft_strlen.c \
		./utils/ft_substr.c \
		./utils/ft_strdup.c \
		./utils/ft_putstr_fd.c
SRC_BONUS = ./bonus/pipex_bonus.c

ifdef ADD_BONUS
COMP_ALL = $(OBJ_FILES) $(OBJ_FILES_BONUS)
else
COMP_ALL = $(OBJ_FILES)
endif

all : $(NAME)

$(NAME): $(COMP_ALL)
	gcc $(OBJ_FILES) -o $(NAME) 

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

bonus:
	@$(MAKE) ADD_BONUS=1 all

clean:
	@echo "Cleaning up .o files"
	@rm -f $(OBJ_FILES)

fclean: clean
	@echo "We are cleaning now"
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
