# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 03:58:29 by agrotzsc          #+#    #+#              #
#    Updated: 2022/10/08 02:54:16 by agrotzsc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---- Config ------------------------------------------------------------------#

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS 		=	-g -ggdb -Wall -Wextra -Werror
else
	CFLAGS		=	-Wall -Wextra -Werror
endif


NAME			=	cub3D
CC				=	gcc
DEF_COLOR		=	\033[0;39m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
RM				=	rm -rf

#---- Directories -------------------------------------------------------------#

SRC_DIR			=	src/
OBJ_DIR			=	obj/

#---- Files -------------------------------------------------------------------#

SRC_FILES	=	src/exit.c                	\
				src/load_cub_3.c          	\
				src/load_cub_1.c          	\
				src/angle_helpers.c       	\
				src/keyhooks.c            	\
				src/main.c                	\
				src/load_cub_2.c          	\
				src/mlx_init.c            	\
				src/mlx_fill_buffer.c     	\
				src/mlx_pixel_handler.c   	\
				src/load_images.c         	\
				src/raycasting.c          	\
				src/game_init.c           	\
				src/map_test.c            	\
				src/raycasting_find_wall.c	\
				src/game_loop.c           	\
				src/raycasting_init.c     	\
				src/map/encode_rgb.c      	\
				src/map/parse.c           	\
				src/map/get_texture.c     	\
				src/utils/free_split.c		\


ifeq ($(shell uname -s),Darwin)
	MLX	:= lib/mlx/libmlx.a
	LIBS	:= -Llib/mlx -framework OpenGL -framework AppKit
	SRC_FILES += src/exit_mac.c
else
	MLX	:= lib/mlx/libmlx_Linux.a
	LIBS	:= -lXext -lX11 -lm
	SRC_FILES += src/exit_linux.c
endif

#---- Prefix ------------------------------------------------------------------#

OBJS = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#---- Libraries ---------------------------------------------------------------#

LIBFT_DIR		=	./lib/libft/
LIBFT_FILES		=	libft.a
LIBFT			=	$(addprefix $(LIBFT_DIR),$(LIBFT_FILES))

all: libft_all ${NAME}

$(NAME): $(OBJS)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $(NAME)$(DEF_COLOR)"
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) $(LIBS)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(GREEN)$(NAME) compiled.$(DEF_COLOR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

libft_all:
	cd $(LIBFT_DIR) && make DEBUG=$(DEBUG)

libft_fclean:
	cd $(LIBFT_DIR) && make fclean


clean:
	@${RM} ${OBJ_DIR}
	@echo "$(GREEN)Clean.$(DEF_COLOR)"
fclean: clean
	@${RM} ${NAME}
	@echo "$(GREEN)FClean.$(DEF_COLOR)"

re: fclean all

#---- WSL2 set Xlaunch display command ---------------------------------------#
#export DISPLAY="$(grep nameserver /etc/resolv.conf | sed 's/nameserver //'):0"