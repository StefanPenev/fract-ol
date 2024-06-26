NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes 
LDFLAGS_MAC = -L minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -lm
LDFLAGS_LINUX = -L minilibx-linux -lmlx -lX11 -lXext -lm

SRCS = src/color.c src/defaults.c src/draw.c src/events.c src/fractol.c src/main.c \
	   src/utils.c src/validations.c 

OBJS = $(SRCS:.c=.o)

LIBFT = Libft/libft.a

UNAME_S := $(shell uname -s)

COLOR_GREEN = '\033[32m'

ifeq ($(UNAME_S), Darwin)
    LDFLAGS = $(LDFLAGS_MAC)
    MLX_DIR = minilibx_opengl_20191021
	CFLAGS += -I $(MLX_DIR)
else
    LDFLAGS = $(LDFLAGS_LINUX)
    MLX_DIR = minilibx-linux
    CFLAGS += -I $(MLX_DIR)
endif

MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo ${COLOR_GREEN}"Fract'ol Compiled!\n\n\
Example of using: $$> ./fractol mandelbrot, julia, julia arg1 arg2, ship"

$(LIBFT):
	make -C Libft/

$(MLX):
	make -C $(MLX_DIR)/

clean:
	rm -f $(OBJS)
	make -C Libft/ clean
	make -C $(MLX_DIR)/ clean

fclean: clean
	rm -f $(NAME)
	make -C Libft/ fclean
	make -C $(MLX_DIR)/ clean

re: fclean all

.PHONY: all clean fclean re
