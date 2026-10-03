#!/bin/bash

RESET=$'\033[0m'
GREEN=$'\033[32m'
YELLOW=$'\033[33m'
BLUE=$'\033[34m'
RED=$'\033[31m'

echo "${BLUE}Generating Makefile!${RESET}"

read -p "${GREEN}Program name: ${RESET}" NAME

SRCS=$(find src -type f \( -name "*.c" -o -name "*.cpp" \) | sort)

C=0;
CPP=0;

for file in $SRCS
do
	case "$file" in
		*.c)
			C=1;
			;;
		*.cpp)
			CPP=1
			;;
		*)
			echo "${RED}Error: Unsuported file: ${YELLOW}$file${RESET}"
			exit 1
			;;
	esac
done

if [[ "$C" -eq 1 && "$CPP" -eq 1 ]]; then
	echo "${RED}Mixed files (.c && .cpp)${RESET}"
	exit 1

elif [ "$C" -eq 1 ]; then
	CC=cc
	EXT=.c

elif [ "$CPP" -eq 1 ]; then
	CC=c++
	EXT=.cpp
fi


MAKEFILE=Makefile
> "$MAKEFILE"

{
echo "NAME = $NAME"
echo "CC = $CC"
echo "CFLAGS = -Wall -Wextra -Werror -g -I./includes"
echo ""

echo "SRCS = \\"

for f in $SRCS;
do
	echo "	$f \\"
done

echo ""

echo "OBJ_DIR = obj"
echo "OBJS = \$(SRCS:src/%$EXT=\$(OBJ_DIR)/%.o)"
echo ""

echo "LIBFT_DIR = ./libraries/libft"
echo "LIBFT = \$(LIBFT_DIR)/libft.a"
echo ""

cat << EOF

RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RED     = \033[31m

all: \$(NAME)

\$(NAME): \$(OBJS) \$(LIBFT)
	@echo "\$(YELLOW)compiling \$(NAME)...\$(RESET)"
	@\$(CC) \$(CFLAGS) -o \$(NAME) \$(OBJS) \$(LIBFT)
	@echo "\$(GREEN)\$(NAME) ready!\$(RESET)"

\$(OBJ_DIR)/%.o: src/%$EXT
	@mkdir -p \$(@D)
	@echo "\$(BLUE)making objs directorys!\$(RESET)"
	@\$(CC) \$(CFLAGS) -c \$< -o \$@

\$(LIBFT):
	@echo "\$(YELLOW)compiling LIBFT ...\$(RESET)"
	@\$(MAKE) -C \$(LIBFT_DIR) --no-print-directory


v: re
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./\$(NAME)

clean:
	@rm -rf \$(OBJ_DIR)
	@\$(MAKE) -C \$(LIBFT_DIR) clean --no-print-directory
	@echo "\$(RED)objs cleaned\$(RESET)"

fclean: clean
	@rm -f \$(NAME)
	@\$(MAKE) -C \$(LIBFT_DIR) fclean --no-print-directory
	@echo "\$(RED)\$(NAME) removed!\$(RESET)"

re: fclean all

.PHONY: all clean fclean re

EOF

} >> "$MAKEFILE"

echo "${GREEN}Makefile generated successfully!${RESET}"
	
