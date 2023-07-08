# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 15:42:30 by zlaarous          #+#    #+#              #
#    Updated: 2023/07/08 19:24:35 by zlaarous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	philo
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
HEADER	=	./include/philo.h

SRC		=	./main.c \
			./ft_atoi.c \
			./execution_part.c \
			./routine_yawmi.c \
			./routine_activity.c \
			./setup_timing.c \
			
OBJS	=	$(SRC:.c=.o)

%.o: 		%.c $(HEADER)
			@${CC} ${FLAGS} -c $< -o $@

$(NAME) :	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME)

all		:	$(NAME)

clean	:	
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONE	:	all clean fclean re
