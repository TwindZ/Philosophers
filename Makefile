# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:27:08 by emlamoth          #+#    #+#              #
#    Updated: 2023/07/31 13:34:33 by emlamoth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c		\
		ft_atoi.c	\

HDRS = philo.h

OBJS_DIR = ./objs_philo/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

NAME = philo

CFLAGS = -Wall -Wextra -Werror

CC = gcc

GREEN = \033[1;32m
RED = \033[1;31m
NC = \033[0;0m

all:$(NAME)

$(OBJS_DIR)%.o:%.c $(HDRS)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${GREEN}PHILO COMPILED${NC}"

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --leak-check=full --show-leak-kinds=all -- ./$(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "${RED}PHILO OBJECTS DELETED${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}PHILO DELETED${NC}"

bonus: all

re: fclean all

.PHONY: all clean fclean bonus re leak