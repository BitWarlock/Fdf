# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghostface <ghostface@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 21:22:04 by mrezki            #+#    #+#              #
#    Updated: 2024/06/20 19:46:10 by ghostface        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FLAGS		= -O3 -g -Wall -Wextra -Werror
LIB_DIR		= ./libft
HEADER		= srcs/fdf.h bonus/fdf_bonus.h
LIBFT		= $(LIB_DIR)/libft.a
SRCS		= $(shell find ./srcs -name '*.c')
SRCS_B		= $(shell find ./bonus -name '*.c')
MLX		= -lmlx -framework OpenGL -framework AppKit
LIBFT_SRCS	= $(shell find $(LIB_DIR) -name '*.c')
LIBFT_OBJS	= $(LIBFT_SRCS:.c=.o)
OBJS		= $(SRCS:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)
EXE		= fdf
EXE_B		= fdf_bonus
RM		= rm -rf

all: $(EXE)

$(EXE): $(OBJS) $(LIBFT)
	$(CC) $(C_FLAGS) $^ $(MLX) -o $@
	@echo ""
	@echo "\033[1;36m'fdf' is now ready."
	@echo "Usage: ./fdf maps/<map>"

%.o: %.c $(HEADER)
	@echo "\033[32m"
	$(CC) $(C_FLAGS) -c -o $@ $<

$(LIBFT): $(LIBFT_OBJS)
	@echo "\033[32mCompiling libft"
	@echo ""
	$(MAKE) -C $(LIB_DIR)

bonus: $(OBJS_B) $(LIBFT)
	$(CC) $(C_FLAGS) $^ $(MLX) -o $(EXE_B)
	@echo ""
	@echo "\033[1;36m'fdf_bonus' is now ready."
	@echo "Usage: ./fdf_bonus maps/<map>"

clean:
	@echo "\033[38;2;188;31;54m"
	@$(RM) $(OBJS) $(OBJS_B)
	@$(MAKE) -C libft/ clean
	@echo ""
	@echo "\033[38;2;188;31;54mCleanup Complete."
	@echo ""

fclean: clean
	@$(RM) $(LIBFT) $(EXE) fdf.dSYM .DS_Store $(EXE_B)
	@$(MAKE) -C libft/ fclean
	@echo ""
	@echo "\033[38;2;188;31;54mFull Cleanup Complete."
	@echo ""

re: fclean all

.PHONY: clean fclean
