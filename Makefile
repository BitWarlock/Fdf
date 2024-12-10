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

UNAME			:= $(shell uname)
# C_FLAGS			= -O3 -g -DOS -Wall -Wextra -Werror
LIBFT			= libft/libft.a
HEADER			= $(shell find ./include -name '*.h')
LIBFT_SRCS		= $(shell find ./libft -name '*.c')
LIBFT_OBJS		= $(LIBFT_SRCS: .c=.o)
SRCS			= $(shell find ./src -name '*.c')
OBJS			= $(SRCS:.c=.o)
EXE				= fdf
RM				= rm -rf

# TODO Install mlx and it's dependencies if it's not installed

ifeq ($(UNAME), Darwin)
	MLX 	= -lmlx -framework OpenGL -framework AppKit
	OS		= MACOS
	C_FLAGS += -DMACOS
else ifeq ($(UNAME), Linux)
	MLX		= -Lmlx -lmlx -L/usr/local/lib -lXext -lX11 -lm
	CC		= gcc
	C_FLAGS	+= -DLINUX
	OS		= LINUX
endif

all: $(EXE)

$(EXE): $(OBJS) $(LIBFT)
	$(CC) $(C_FLAGS) $^ $(MLX) -o $@
	@echo ""
	@echo "\033[1;36m'fdf' is now ready."
	@echo "Usage: ./fdf maps/<map>"

%.o: %.c $(HEADER)
	@echo "\033[32m"
	$(CC) $(C_FLAGS) -c -o $@ $<

$(LIBFT):
	@echo "\033[32mCompiling libft"
	@echo ""
	$(MAKE) -C ./libft

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
