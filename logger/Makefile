NAME = Logger
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./includes

SRCS = \
	src/hash_map.c \
	src/main.c \
	src/stats_writer.c \

OBJ_DIR = obj
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = ./libraries/libft/get_next_line
GNL = $(GNL_DIR)/get_next_line


RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RED     = \033[31m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL) 
	@echo "$(YELLOW)compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL)
	@echo "$(GREEN)$(NAME) ready!$(RESET)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "$(BLUE)making objs directorys!$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)compiling LIBFT ...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(GNL):
	@echo "$(YELLOW)compiling GNL ...$(RESET)"
	@$(MAKE) -C $(GNL_DIR) --no-print-directory


v: re
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) clean --no-print-directory
	@echo "$(RED)objs cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) clean --no-print-directory
	@echo "$(RED)$(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re

