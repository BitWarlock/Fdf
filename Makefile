# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrezki <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 21:22:04 by mrezki            #+#    #+#              #
#    Updated: 2024/05/11 21:22:06 by mrezki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# C_FLAGS		= -fsanitize=address -O2 -g
LIB_DIR		= ./libft
HEADER		= srcs/fdf.h
LIBFT		= $(LIB_DIR)/libft.a
SRCS		= srcs/fdf.c srcs/Bresenham.c srcs/hooks.c \
		  srcs/parse.c srcs/coordinates.c srcs/rotation.c \
		  srcs/math.c srcs/draw.c srcs/free.c srcs/translation.c \
		  srcs/color.c
OBJS		= $(SRCS:.c=.o)
MLX		=  -lmlx -framework OpenGL -framework AppKit
EXE		= fdf
RM		= rm -rf

all: $(EXE)

$(EXE): $(LIBFT) $(OBJS)
	$(CC) $(C_FLAGS) -g $(MLX) $^ -o $@
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
