NAME = Analyser
CC = c++
CFLAGS = -Wall -Wextra -Werror -g -std=c++20 -I./includes

SRCS = \
	src/alert_writer.cpp \
	src/attacker_profile.cpp \
	src/log_parser.cpp \
	src/main.cpp \
	src/detection_engine.cpp \
	src/sliding_window.cpp \

OBJ_DIR = obj
OBJS = $(SRCS:src/%.cpp=$(OBJ_DIR)/%.o)

RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RED     = \033[31m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) ready!$(RESET)"

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	@echo "$(BLUE)making objs directorys!$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@


v: re
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)objs cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re

