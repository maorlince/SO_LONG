NAME = so_long

INCDIR = INCLUDES
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -I$(INCDIR) -I /minilibx-linux
SRCS =	SOURCES/flood_fill.c \
		SOURCES/init.c \
		SOURCES/input.c \
		SOURCES/maelstrom.c \
		SOURCES/main.c \
		SOURCES/map_checker.c \
		SOURCES/map_loader.c \
		SOURCES/bonus.c \
		SOURCES/moves.c \
		SOURCES/render.c \
		SOURCES/utils.c

OBJS = $(SRCS:.c=.o)

# Librairies
LIBFT_DIR = libft
PRINTF_DIR = ft_printf
GNL_DIR = get_next_line
MLX_DIR = minilibx-linux

LIBFT_A = $(LIBFT_DIR)/libft.a
PRINTF_A = $(PRINTF_DIR)/ft_printf.a
GNL_A = $(GNL_DIR)/get_next_line.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(PRINTF_DIR)
	make -C $(GNL_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(PRINTF_A) $(GNL_A) $(MLX_FLAGS) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	make clean -C $(GNL_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	make fclean -C $(GNL_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
