# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 16:06:03 by klakbuic          #+#    #+#              #
#    Updated: 2024/07/06 10:48:05 by klakbuic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME         = cub3D
HEADER       = includes/cub3d.h

CC           = cc
DEBUG        = -g3 -fsanitize=address
CFLAGS       = -Wall -Wextra $(DEBUG) #-Werror

# libs
MLX          = libs/minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm
LIBFT        = libs/libft/libft.a
CONTAINERS   = libs/ft_containers/containersft.a
LIBS         = $(MLX) $(LIBFT) $(CONTAINERS)

# directories
SRCSDIR      := srcs
OBJSDIR      := obj
PARSEDIR     := parsing
UTILSDIR     := utils
RENDERDIR    := render

# sources files
PARSE        := get_next_line.c  get_next_line_utils.c  parse.c  parse_elements.c  parse_map.c  parse_utils.c
UTILS        := mem.c
RENDER       := draw.c  init.c

# All sources files
SRCS         := $(foreach F,$(PARSE), $(SRCSDIR)/$(PARSEDIR)/$(F))  \
                $(foreach F,$(UTILS), $(SRCSDIR)/$(UTILSDIR)/$(F))   \
                $(foreach F,$(RENDER), $(SRCSDIR)/$(RENDERDIR)/$(F)) \
                $(SRCSDIR)/main.c

# All objects files
OBJS         := $(patsubst srcs/%.c, obj/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -I $(HEADER) -o $(NAME)

$(OBJS) : $(OBJSDIR)/%.o : $(SRCSDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)
	@mkdir -p $(OBJSDIR)/$(PARSEDIR)
	@mkdir -p $(OBJSDIR)/$(UTILSDIR)
	@mkdir -p $(OBJSDIR)/$(RENDERDIR)

print:
	@echo $(SRCS)
	@echo $(OBJS)

run: all
	./$(NAME)

clean:
	@$(RM) -rf $(OBJSDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re