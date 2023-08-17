# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:27:08 by emlamoth          #+#    #+#              #
#    Updated: 2023/08/17 15:36:05 by emlamoth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	init.c			\
		main.c			\
		routine.c		\
		util.c			\
		util2.c			\
		monitoring.c	\

HDRS = ./include/philo.h

SRCS_DIR = ./srcs/
OBJS_DIR = ./srcs/objs_philo/
OBJS = $(SRCS:$(SCRS_DIR)%.c=$(OBJS_DIR)%.o)

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

CC = gcc

GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0;0m

all:$(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJS) $(HDRS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${GREEN}PHILO COMPILED${NC}"

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --leak-check=full --show-leak-kinds=all -- ./$(NAME) 2 200 200 200

clean:
	@rm -rf $(OBJS_DIR)
	@echo "${RED}PHILO OBJECTS DELETED${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}PHILO DELETED${NC}"

bonus: all

re: fclean all

.PHONY: all clean fclean bonus re leak