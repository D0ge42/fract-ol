NAME = libft.a

LIBFT_SRC = libft/ft_atoi.c \
       libft/ft_bzero.c   \
       libft/ft_calloc.c  \
       libft/ft_isalnum.c \
       libft/ft_isalpha.c \
       libft/ft_isascii.c \
       libft/ft_isdigit.c \
       libft/ft_isprint.c \
       libft/ft_memchr.c  \
       libft/ft_memcmp.c  \
       libft/ft_memcpy.c  \
       libft/ft_memmove.c \
       libft/ft_memset.c  \
       libft/ft_putchar_fd.c \
       libft/ft_putendl_fd.c \
       libft/ft_putnbr_fd.c \
       libft/ft_putstr_fd.c \
       libft/ft_split.c  \
       libft/ft_strchr.c \
       libft/ft_strdup.c \
       libft/ft_striteri.c \
       libft/ft_strjoin.c \
       libft/ft_strlcat.c \
       libft/ft_strlcpy.c \
       libft/ft_strlen.c \
       libft/ft_strmapi.c \
       libft/ft_strncmp.c \
       libft/ft_strnstr.c \
       libft/ft_strrchr.c \
       libft/ft_strtrim.c \
       libft/ft_substr.c \
       libft/ft_tolower.c \
       libft/ft_toupper.c \
       libft/ft_itoa.c \
	   libft/ft_lstadd_back.c  \
	   libft/ft_lstadd_front.c \
	   libft/ft_lstclear.c     \
	   libft/ft_lstdelone.c    \
	   libft/ft_lstiter.c      \
	   libft/ft_lstlast.c      \
	   libft/ft_lstmap.c       \
	   libft/ft_lstnew.c       \
	   libft/ft_lstsize.c	\
	   libft/ft_utils.c \
	   libft/ft_utils2.c \
	   libft/ft_utils3.c \
	   libft/ft_utils4.c \
	   libft/get_next_line_bonus.c \
	   libft/get_next_line_utils_bonus.c \
	   libft/hexa_handler.c \
	   libft/info_gatherer.c \
	   libft/pointer_handler.c \
	   libft/string_handler.c \
	   libft/struct_handler.c \
	   libft/type_handler.c \
	   libft/type_handler.c \
	   libft/unsigned_handler.c\
	   libft/ft_printf.c\
	   libft/char_handler.c\
	   libft/integers_handler.c\
	   libft/ft_printnbr_count.c\
	   libft/ft_print_hexa.c\
	   libft/ft_print_pointer.c\
	   libft/ft_putstr_count.c




SRC = srcs/fractol.c  srcs/colors.c srcs/fractal_handler.c \
srcs/helpers.c srcs/helpers2.c srcs/initializer.c srcs/camera_handler.c

LIBFT_OBJS = $(LIBFT_SRC:.c=.o)
OBJS = $(SRC:.c=.o) # Esclude i file oggetto di libft

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -gdwarf-4
MLX_FLAGS = -Imlx -Lmlx -lmlx -lX11 -lXext -lm
RM = rm -rf
AR = ar crs
EXEC = fractol

# Regola per creare l'eseguibile
$(EXEC): $(OBJS) $(NAME) mlx/libmlx_Linux.a
	$(CC) -o $(EXEC) $(OBJS) $(NAME) $(MLX_FLAGS)

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

bonus: $(NAME) $(EXEC)

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

.PHONY: all clean fclean re bonus
