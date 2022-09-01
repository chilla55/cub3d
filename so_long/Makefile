# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/03 16:47:04 by skorte            #+#    #+#              #
#    Updated: 2022/04/07 13:00:59 by skorte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=so_long

CC=gcc
CFLAGS= -Wall -Wextra -Werror -g
CFLAGS_BONUS= -Wall -Wextra -Werror -D GUARD=1 -D USE_ARROW_KEYS=1
LIBFT=-Llibft/ -lft
MLX=-Lminilibx-linux/ -lmlx_Linux -lXext -lX11

SOURCES	=	so_long.c \
			ft_exit.c \
			ft_load_imgs.c \
			ft_mlx_init.c \
			ft_move.c \
			ft_put_draw.c \
			ft_redraw.c \
			ft_t_map_init.c \
			ft_t_map_print.c

all: $(NAME)

OBJECTS=$(SOURCES:.c=.o)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(MLX)

SOURCES_BONUS=$(SOURCES:.c=_bonus.c)

$(SOURCES_BONUS): %_bonus.c : %.c
	cp $< $@

OBJECTS_BONUS=$(SOURCES_BONUS:.c=.o)

$(OBJECTS_BONUS):$(SOURCES)
	$(CC) $(CFLAGS_BONUS) -I/usr/include -Iminilibx-linux -O3 -c $(SOURCES_BONUS)

bonus: $(SOURCES_BONUS) $(OBJECTS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS_BONUS) -o $(NAME) $(OBJECTS_BONUS) $(LIBFT) $(MLX)

$(OBJECTS):$(SOURCES)
	$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux -O3 -c $(SOURCES)

$(LIBFT):
	make -C ./libft/

$(MLX):
	make -C ./minilibx-linux/

clean:
	rm -rf *.o
	rm -f *_bonus.c
	make fclean -C ./libft/ 
	make clean -C ./minilibx-linux/

fclean: clean
	rm -rf $(NAME)

re: fclean all

no:
	norminette *.c *.h libft/*.c libft/*.h

.PHONY: clean fclean re no

#export DISPLAY=192.168.56.1:0.0 IP as shown in XMing log. USE XLaunch... deactivate access control

#GCC *.c -L libft -l ft -L minilibx-linux/ -lmlx_Linux -lXext -lX11 -D GUARD=1 -D USE_ARROW_KEYS=1 -o so_long