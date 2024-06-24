# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 16:06:03 by klakbuic          #+#    #+#              #
#    Updated: 2024/06/24 15:14:10 by klakbuic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME         = cub3D
HEADER       = /includes/cub3d.h

CC           = cc
DEBUG        = -g3 -fsanitize=address
CFLAGS       = -Wall -Wextra $(DEBUG) #-Werror
MLX          = libs/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
SRCSDIR      = srcs
SRCSFILES    = draw.c  init.c  main.c
SRCS	     = $(addprefix $(SRCSDIR)/, $(SRCSFILES))

OBJSDIR      = obj
OBJSFILES    = $(SRCSFILES:.c=.o)
OBJS	     = $(addprefix $(OBJSDIR)/, $(OBJSFILES))

all: $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIB) -I $(HEADER) -o $(NAME)

run: all
	./$(NAME)
	
clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus