# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwinthei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 13:26:35 by jwinthei          #+#    #+#              #
#    Updated: 2019/02/13 17:57:36 by jwinthei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libftprintf.a

SRC	=	ft_printf.c	itoa_base.c				output.c		\
		printstr.c	numeric_processing.c	types_analis.c	\
		patoi.c

OBJ = $(SRC:.c=.o)

INCL= ../includes/

FLG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc -c $(SRC) -I $(INCL) $(FLG)

clean:
	rm -f *.o

fclean: clean

re: fclean all
