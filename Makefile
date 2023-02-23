# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 12:39:59 by arafeeq           #+#    #+#              #
#    Updated: 2023/02/23 17:18:36 by arafeeq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo philo_utils philo_utils2 init_alloc routine

OBJDIR = objects

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

CC = cc

CFLAGS = -Wall -Wextra -Werror

$(OBJDIR)/%.o : %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean

	rm -f $(NAME)

re: fclean all