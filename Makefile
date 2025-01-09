NAME = libft.a

LIBFT_SRC = $(wildcard libft/*.c)
SRC = $(wildcard *.c)

LIBFT_OBJS = $(LIBFT_SRC:.c=.o)
OBJS = $(filter-out libft/%.o, $(SRC:.c=.o)) # Esclude i file oggetto di libft

CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -Imlx -Lmlx -lmlx -lX11 -lXext -lm
RM = rm -rf
AR = ar crs
EXEC = a.out

# Regola per creare l'eseguibile
$(EXEC): $(OBJS) $(NAME) mlx/libmlx_Linux.a
	$(CC) -o $(EXEC) $(OBJS) $(NAME) $(MLX_FLAGS) -g

# Regola per creare libft.a
$(NAME): $(LIBFT_OBJS)
	$(AR) $@ $^

# Regola per creare i file .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compila MinilibX
mlx/libmlx_Linux.a:
	$(MAKE) -C mlx

# Regola all
all: $(NAME) $(EXEC)

# Pulizia degli oggetti
clean:
	$(RM) $(OBJS) $(LIBFT_OBJS)
	$(MAKE) -C mlx clean

# Pulizia completa
fclean: clean
	$(RM) $(EXEC) $(NAME)
	$(MAKE) -C mlx clean

# Ricostruzione completa
re: fclean all

.PHONY: all clean fclean re
