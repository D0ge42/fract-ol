NAME = libft.a

LIBFT_SRC = $(wildcard libft/*.c)
SRC = $(wildcard *.c)

LIBFT_OBJS = $(LIBFT_SRC:.c=.o) 
OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
AR = ar crs

$(NAME): $(OBJS) $(LIBFT_OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS) $(LIBFT_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: all clean fclean re bonus

