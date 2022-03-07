# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.old                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 13:04:56 by ahammoud          #+#    #+#              #
#    Updated: 2022/03/07 16:22:05 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	 ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

SRCSB	=	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS	=	${SRCS:.c=.o}

OBJSBN	=	${SRCSB:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

NAME	=	 libft.a

CFLAGS	=	-Wall -Werror -Wextra -g

CC	=	gcc

AR	=	ar rc

${NAME}	:	${OBJS} 
		${AR}  ${NAME} ${OBJS}

bonus	:	${OBJS} ${OBJSBN}
		${AR}  ${NAME} ${OBJS} ${OBJSBN}

all	:	${NAME}

RM	=	rm -f

clean	:
		${RM} ${OBJS} ${OBJSBN}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
