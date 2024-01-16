# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 21:05:43 by meserghi          #+#    #+#              #
#    Updated: 2024/01/16 13:57:06 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = pipex.c parsing_arg.c utils/exe_cmd.c utils/ft_split.c utils/ft_strjoin.c \
	utils/ft_strlen.c utils/ft_strnstr.c utils/my_free.c utils/checker_path.c\
	utils/ft_strdup.c
FILE_BONUS = pipex_bonus.c utils/exe_cmd.c parsing_arg.c utils/ft_split.c utils/ft_strjoin.c \
	utils/ft_strlen.c utils/ft_strnstr.c utils/my_free.c utils/checker_path.c\
	utils/ft_strdup.c

OBJ = ${FILE:.c=.o}
OBJ_BONUS = ${FILE_BONUS:.c=.o}

FLAGS = -Wall -Wextra -Werror

NAME = pipex

EXE_BONUS = pipex_bonus

all : ${NAME}

bonus : ${EXE_BONUS}

${NAME} : ${OBJ}
	cc ${FLAGS} ${OBJ} -o ${NAME}

${EXE_BONUS} : ${OBJ_BONUS}
	cc ${FLAGS} ${OBJ_BONUS} -o ${EXE_BONUS}

%.o : %.c pipex.h
	cc ${FLAGS} -c $< -o $@

clean :
	rm -f ${OBJ} ${OBJ_BONUS}

fclean : clean
	rm -f ${NAME} ${EXE_BONUS}

re : fclean all