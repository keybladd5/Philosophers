# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 13:14:54 by polmarti          #+#    #+#              #
#    Updated: 2024/04/22 13:14:57 by polmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
SRCS = main.c utils.c routine.c check_and_errors.c monitoring.c
INCLUDES = philosophers.h colors.h
FLAGS = -Wall -Wextra -Werror -pthread -MMD -g #-fsanitize=thread
OBJS = $(addprefix .temporal_files/,$(SRCS:.c=.o)) 
DEPS = $(addprefix .temporal_files/,$(SRCS:.c=.d)) 

all: $(NAME)

CC = gcc

.temporal_files/%.o: %.c Makefile | .temporal_files
	$(CC) $(FLAGS) -I ./ -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

.temporal_files:
	mkdir -p .temporal_files

clean:
	rm -rf .temporal_files $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
