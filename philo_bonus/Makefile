# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zlaarous <zlaarous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 15:42:30 by zlaarous          #+#    #+#              #
#    Updated: 2023/07/21 04:41:40 by zlaarous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	philo_bonus
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
HEADER	=	./include/philo_bonus.h

SRC		=	./main_bonus.c \
			./ft_atoi_bonus.c \
			./execution_part_bonus.c \
			./routine_philos_bonus.c \
			./routine_activity_bonus.c \
			./setup_timing_bonus.c \
			./ft_itoa.c \
			./ft_strjoin.c \
			
OBJS	=	$(SRC:.c=.o)

%.o: 		%.c $(HEADER)
			@${CC} ${FLAGS}  -c $< -o $@

$(NAME) :	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME)

all		:	$(NAME)

clean	:	
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONE	:	all clean fclean re
