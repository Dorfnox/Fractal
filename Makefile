# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpierce <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 10:27:14 by bpierce           #+#    #+#              #
#    Updated: 2017/08/22 13:57:45 by bpierce          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FILES = main images colors color_bars helperfuncs \
		hooks hooks_key_press hooks_mouse_press hooks_mouse_move \
		julia mandelbrot circle julia_tree forest doom_guy exploding_star \
		heaven random

C_LOC = src/
C_NAM = $(addsuffix .c, $(FILES))
C_SRC = $(addprefix $(C_LOC), $(C_NAM))

O_LOC = obj/
O_NAM = $(addsuffix .o, $(FILES))
O_SRC = $(addprefix $(O_LOC), $(O_NAM))

LIB_LOC = libft/
LIB_NAM = libft.a
LIB_SRC = $(addprefix $(LIB_LOC), $(LIB_NAM))

HEADERS = inc/fractol.h inc/fractol_macros.h

H_LOCS = -I inc -I libft/inc -I minilibx

C_FLAGS = -Wall -Wextra -Werror

MLBX = minilibx/libmlx.a

MLBX_FLAGS = -L minilibx -lmlx -framework OpenGL -framework Appkit -g

TEST_MAIN = main_for_testing.c

C_G = [32m
C_LG = \033[
C_Y = \033[33m
C_YL = \033[93m
C_R = \033[0;31m
C_O = \033[0;33m
C_OO = \033[1;33m
C_BLINK = [5m
C_NO = \033[0m

all: $(NAME)

$(NAME): $(O_SRC) $(LIB_SRC) $(MLBX)
	@echo "$(C_OO)Compiling executable... $@$(C_NO)"
	@gcc $(C_FLAGS) $(MLBX_FLAGS) -lpthread $^ -o $@
	@echo
	@echo "$(C_G)--------xxXXXXXXXXxx--------$(C_NO)"
	@echo "$(C_G)-----xXX------------XXx-----$(C_NO)"
	@echo "$(C_G)---xXX--- COMPLETE ---XXx---$(C_NO)"
	@echo "$(C_G)---xXX---- YIPPEE ----XXx---$(C_NO)"
	@echo "$(C_G)-----xXX------------XXx-----$(C_NO)"
	@echo "$(C_G)--------XXxxxxxxxxXX--------$(C_NO)"
	@echo

$(O_LOC)%.o: $(C_LOC)%.c $(HEADERS)
	@echo "$(C_Y)Re-compiling src file...$(C_NO) $(C_G)$<$(C_NO)"
	@gcc $(C_FLAGS) $(H_LOCS) -o $@ -c $<

$(LIB_SRC): force
	@echo
	@echo "$(C_Y)----------- Checking Libft Library -----------$(C_NO)"
	@printf "$(C_YL)$(LIB_NAM) re-compile status: $(C_NO)"
	@make -C $(LIB_LOC)
	@echo "$(C_Y)----------- Library Check Complete -----------$(C_NO)"
	@echo

$(MLBX): force
	@echo
	@echo "$(C_Y)----------- Checking $@ Library -----------$(C_NO)"
	@make -C minilibx
	@echo "$(C_Y)----------- $@ Check Complete -----------$(C_NO)"
	@echo

force:
	@true

clean:
	@/bin/rm -rf $(O_SRC)
	@make clean -C $(LIB_LOC)
	@make clean -C minilibx
	@echo "$(C_G)clean complete!$(C_NO)"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIB_LOC)
	@echo "$(C_G)fclean complete!$(C_NO)"

re: fclean all

test: $(NAME)
	@./$(NAME) 1 2 3 4 5 6 7 8 9

.PHONY: all test force clean fclean re
