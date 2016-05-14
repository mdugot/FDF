# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2016/01/13 14:47:34 by mdugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= fdf
CC= gcc
CFLAGS= -Wall -Werror -Wextra
MLX= -Lminilibx_macos -I/minilibx_macos \
	 -lmlx -framework OpenGL -framework AppKit
SRC_NAME= main.c draw.c rotation.c perspective.c event.c utils.c color.c \
		  line.c geometry.c memory.c read.c paint.c utils2.c utils3.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libft.a
LIB_ID= ft
LIB_PATH= ./libft/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) -L$(LIB_PATH) -I$(INC_PATH) -o $(NAME) -l$(LIB_ID) $(MLX) $(OBJ)

$(LIB):
	make re -C $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) -I$(INC_PATH) -I$(LIB_PATH) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)
	make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	rm -fv $(NAME)
	make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
