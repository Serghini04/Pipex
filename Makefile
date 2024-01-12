# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 21:05:43 by meserghi          #+#    #+#              #
#    Updated: 2024/01/12 22:36:19 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = pipex.c parsing_arg.c utils/ft_split.c utils/ft_strjoin.c \
	utils/ft_strlen.c utils/ft_strnstr.c
OBJ = ${FILE:.c=.o}
FLAGS = -Wall -Wextra -Werror

NAME = pipex

all : ${NAME}

${NAME} : ${OBJ}
	cc ${FLAGS} ${OBJ} -o ${NAME}

# ${EXE_BONUS} : ${OBJ_BONUS}
# 	cc ${FLAGS} ${OBJ_BONUS} -o ${EXE_BONUS}

%.o : %.c pipex.h
	cc ${FLAGS} -c $< -o $@

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all