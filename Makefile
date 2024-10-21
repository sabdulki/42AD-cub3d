NAME = cub3d

SRC_GNL =	./src/get_next_line/get_next_line.c \
			./src/get_next_line/get_next_line_utils.c

SRC_P = 	./src/parsing/parsing.c \
			./src/parsing/fill_sprites.c \
			./src/parsing/check_file.c \
			./src/parsing/list.c \
			./src/parsing/map.c \
			./src/parsing/map_edges.c \
			./src/parsing/nbrs_check.c
			

SRC_U = 	./src/utils/utils_message.c \
			./src/utils/utils.c \
			./src/utils/utils_color.c \
			./src/utils/utils_map.c

SRCS_S =	./main.c 

SRC_RAYCAST = ./src/raycast/raycast.c

SRC = $(SRCS_S) $(SRC_GNL) $(SRC_P) $(SRC_U) $(SRC_RAYCAST)
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = cub3d
MAKE_MLX = cd mlx && make
MAKE_LIBFT = cs ./src/Libft && make
LIBFT_A = ./src/Libft/libft.a
all : $(NAME)

$(NAME) : $(OBJ)
	$(MAKE_MLX) 
	${CC} ${CFLAGS} ${OBJ} ${LIBFT_A} -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
clean:
	rm -f $(OBJ)
	$(MAKE) clean -C mlx
fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re