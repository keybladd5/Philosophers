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
FLAGS = -Wall -Wextra -Werror -pthread -g -MMD -fsanitize=thread
OBJS = $(addprefix .temporal_files/,$(SRCS:.c=.o))  # Modificado para que los objetos se guarden en .temporal_files/
DEPS = $(addprefix .temporal_files/,$(SRCS:.c=.d))  # Modificado para que los archivos de dependencias se guarden en .temporal_files/

all: $(NAME)

CC = gcc

.temporal_files/%.o: %.c Makefile | .temporal_files  # Modificado para crear .temporal_files/
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
