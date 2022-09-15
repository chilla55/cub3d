# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 03:58:29 by agrotzsc          #+#    #+#              #
#    Updated: 2022/09/14 12:50:46 by agrotzsc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---- Config ------------------------------------------------------------------#

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS 		=	-g -ggdb -Wall -Wextra -Werror
else
	CFLAGS		=	-Wall -Wextra -Werror
endif


NAME			=	cub3d
CC				=	gcc
DEF_COLOR		=	\033[0;39m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
RM				=	rm -rf

#---- Directories -------------------------------------------------------------#

SRC_DIR			=	src/
OBJ_DIR			=	obj/

#---- Files -------------------------------------------------------------------#

SOURCES = $(shell find $(SRC_DIR) -name '*.c')

#---- Prefix ------------------------------------------------------------------#

OBJS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#---- Libraries ---------------------------------------------------------------#

MLX_DIR			=	./lib/minilibx-linux/
MLX_FILES		=	libmlx_Linux.a
MLX				=	$(addprefix $(MLX_DIR),$(MLX_FILES))

LIBFT_DIR		=	./lib/libft/
LIBFT_FILES		=	libft.a
LIBFT			=	$(addprefix $(LIBFT_DIR),$(LIBFT_FILES))

all: mlx_all libft_all ${NAME}

$(NAME): $(OBJS)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $(NAME)$(DEF_COLOR)"
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) -lm -L/usr/include/X11/extensions -lX11 -lXext
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(GREEN)$(NAME) compiled.$(DEF_COLOR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@printf "%b" "\r\033[2K"
	@printf "%b" "\r$(YELLOW)Compiling: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

mlx_all:
	cd $(MLX_DIR) && ./configure

mlx_clean:
	cd $(MLX_DIR) && ./configure clean

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
