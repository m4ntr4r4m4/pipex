# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 13:14:42 by ahammoud          #+#    #+#              #
#    Updated: 2022/11/15 16:10:52 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./source/fd.c ./source/parse.c ./source/pipex.c ./source/utils.c

OBJS	=	${SRCS:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/

NAME	=	 pipex

CFLAGS	=	-Wall -Werror -Wextra -g
#CFLAGS	=	-Wall -Werror -Wextra -g -fsanitize=address
#CFLAGS	=	 -g 


CC	=	gcc


${NAME}	:	${OBJS} 
			cd ./source/libft/ && make bonus
			${CC} ${CFLAGS} ${OBJS} ./source/libft/libft.a -o ${NAME}

all	:	${NAME}

RM	=	rm -f

clean	:
		${MAKE} clean -C ./source/libft
		${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
