SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

NAME = get_next_line

COMPRESS = ar rcs

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

CC = cc

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(COMPRESS) $(NAME) $(OBJS)
	@echo "$(NAME) ready!"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all