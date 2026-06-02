SRCS =  ft_putstr_help.c ft_putchar_help.c ft_putnbr_help.c ft_printf.c ft_ptr_help.c

NAME = libftprintf.a

COMPRESS = ar rcs

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

CC = cc

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 

$(NAME): $(OBJS) 
	@$(COMPRESS) $(NAME) $(OBJS)
	@echo "$(NAME) ready!"

clean:
	@$(RM) $(OBJS) 

fclean: clean
	@$(RM) $(NAME)

re: fclean all