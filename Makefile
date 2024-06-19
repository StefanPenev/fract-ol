NAME = fractol

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes -I minilibx_opengl_20191021
LDFLAGS_MAC = -L minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -lm
LDFLAGS_LINUX = -L minilibx-linux -lmlx -lX11 -lXext -lXrender -lm

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
MLX = minilibx_opengl_20191021/libmlx.a

# Detect the operating system
UNAME_S := $(shell uname -s)

# Set the appropriate LDFLAGS based on the OS
ifeq ($(UNAME_S), Darwin)
    LDFLAGS = $(LDFLAGS_MAC)
else
    LDFLAGS = $(LDFLAGS_LINUX)
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C libft/

$(MLX):
	make -C minilibx_opengl_20191021/

clean:
	rm -f $(OBJS)
	make -C libft/ clean
	make -C minilibx_opengl_20191021/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx_opengl_20191021/ clean

re: fclean all
