# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 13:26:35 by jwinthei          #+#    #+#              #
#    Updated: 2019/02/28 12:28:13 by jwinthei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1= checker
NAME2= push_swap

SRC  = st_func.c	st_oper.c	str_func.c	arg_analis.c	pratoi.c	printer.c
SRCPS= st_sortmed.c	st_sortrotpaste.c

OBJ  = $(SRC:.c=.o)

INCL = libft/includes/

LIB  = libft/

FLG  = -Wall -Wextra -Werror

all: $(NAME1) $(NAME2)

mlib:
	@make -C libft/ fclean && make -C libft/

mobj:
	@gcc -c $(SRC) -I $(INCL) $(FLG)

$(NAME1):
	@make -C libft/ fclean && make -C libft/
	@gcc -c $(SRC) -I $(INCL) $(FLG)
	gcc -o $(NAME1) $(NAME1).c $(OBJ) -I $(INCL) -L $(LIB) -lft $(FLG)

$(NAME2):
	@make -C libft/ fclean && make -C libft/
	@gcc -c $(SRC) -I $(INCL) $(FLG)
	gcc -o $(NAME2) $(NAME2).c $(SRCPS) $(OBJ) -I $(INCL) -L $(LIB) -lft $(FLG)

clean:
	rm -f *.o
	make -C libft/ clean

fclean: clean
	rm -f $(NAME1)
	rm -f $(NAME2)
	make -C libft/ fclean

re: fclean all
