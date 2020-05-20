NAME = libft.a
CC = gcc
FLAGS = -c -Wall -Wextra -Werror -MMD
HEAD_DIR = include
SRC_DIR = src
OBJ_DIR = obj
HEAD_FILES = libft.h
SRC_FILES = memalloc.c memdel.c strequ.c strnequ.c strjoin.c strnnum.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

-include $(OBJ:.o=.d)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) -I$(HEAD_DIR) -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
