# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 21:22:04 by mrezki            #+#    #+#              #
#    Updated: 2024/06/15 01:47:28 by mrezki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:= $(shell uname)
C_FLAGS		= -O3 -g -DOS
LIB_DIR		= ./libft
HEADER		= srcs/fdf.h
LIBFT		= $(LIB_DIR)/libft.a
SRCS		= srcs/fdf.c srcs/Bresenham.c srcs/hooks.c \
		  srcs/parse.c srcs/coordinates.c srcs/rotation.c \
		  srcs/math.c srcs/draw.c srcs/free.c srcs/translation.c \
		  srcs/color.c srcs/projection.c srcs/conic.c
OBJS		= $(SRCS:.c=.o)
EXE		= fdf
RM		= rm -rf

# TODO Install mlx and it's dependencies if it's not installed

ifeq ($(UNAME), darwin)
	MLX = -lmlx -framework OpenGL -framework AppKit
	OS = MACOS
else ifeq ($(UNAME), Linux)
	# MLX = -I/usr/local/include -L/usr/local/lib -lmlx -lXext -lX11 -lm -lz -lbsd
	MLX = -Lmlx -lmlx -L/usr/local/lib -lXext -lX11 -lm
	CC = gcc
	OS = LINUX
endif

all: $(LIBFT) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) $(LIBFT) $(MLX) -o $@
	@echo ""
	@echo "\033[1;36m'fdf' is now ready."
	@echo "Usage: ./fdf maps/<map>"

%.o: %.c $(HEADER)
	@echo "\033[32m"
	$(CC) $(C_FLAGS) -c -o $@ $<

$(LIBFT):
	@echo "\033[32mCompiling libft"
	@echo ""
	$(MAKE) -C $(LIB_DIR)

clean:
	@echo "\033[38;2;188;31;54m"
	$(RM) $(OBJS) $(OBJS_B)
	$(MAKE) -C libft/ clean
	@echo ""
	@echo "\033[38;2;188;31;54mCleanup Complete."
	@echo ""

fclean: clean
	$(RM) $(LIBFT) $(EXE) a.out a.out.dSYM.DS_Store
	$(MAKE) -C libft/ fclean
	@echo ""
	@echo "\033[38;2;188;31;54mFull Cleanup Complete."
	@echo ""

re: fclean all

.PHONY: clean fclean
