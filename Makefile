# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 16:06:03 by klakbuic          #+#    #+#              #
#    Updated: 2024/08/04 15:27:59 by soutchak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target executable name
NAME         = cub3D

# Directories
SRCSDIR      := srcs
OBJSDIR      := obj
PARSEDIR     := parsing
UTILSDIR     := utils
RENDERDIR    := render
DRAWDIR      := draw

# Compiler and flags
CC           := cc
DEBUG        := -g3 -fsanitize=address
CFLAGS       = -Wall -Wextra -Werror -I$(HOME)/local/include
LDFLAGS      = -L$(HOME)/local/lib -lmpg123 -lao

# Libraries
MLX          := libs/mlx/libmlx_Linux.a -lXext -lX11 -lm
LIBFT        := libs/libft/libft.a
CONTAINERS   := libs/ft_containers/containersft.a
LIBS         := $(MLX) $(LIBFT) $(CONTAINERS)

# Header file
HEADER       := includes/cub3d.h

# Source files
PARSE        := get_next_line.c \
				get_next_line_utils.c \
				parse_bools.c \
				parse.c \
				parse_elements.c \
				parse_elements_utils.c \
				parse_map.c \
				parse_map_utils.c \
				parse_utils.c

UTILS        := exit.c \
				hooks.c \
				init.c \
				load.c \
				mem.c \
				sound.c \
				sound_utils.c \
				load_utils.c

RENDER       := doors.c \
				player.c \
				raycasting.c \
				raycasting_utils.c \
				render_wall.c \
				textures.c \
				utils.c

DRAW         := DDA_2.c \
				DDA.c \
				draw.c \
				draw_line.c \
				draw_map.c

# All source files
SRCS         := $(foreach F,$(PARSE), $(SRCSDIR)/$(PARSEDIR)/$(F))  \
				$(foreach F,$(UTILS), $(SRCSDIR)/$(UTILSDIR)/$(F))   \
				$(foreach F,$(RENDER), $(SRCSDIR)/$(RENDERDIR)/$(F)) \
				$(foreach F,$(DRAW), $(SRCSDIR)/$(DRAWDIR)/$(F)) \
				$(SRCSDIR)/main.c

# All object files
OBJS         := $(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))

# Default target
all: $(NAME)

# Build target
$(NAME): $(OBJSDIR) $(OBJS) $(HEADER) $(LIBS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -I $(HEADER) -o $(NAME)

# Compile source files
$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Create object directories
$(OBJSDIR):
	@mkdir -p $(OBJSDIR)
	@mkdir -p $(OBJSDIR)/$(PARSEDIR)
	@mkdir -p $(OBJSDIR)/$(UTILSDIR)
	@mkdir -p $(OBJSDIR)/$(RENDERDIR)
	@mkdir -p $(OBJSDIR)/$(DRAWDIR)

$(LIBS):
	@make -C libs/libft
	@make -C libs/ft_containers
	@cd libs/mlx && ./configure && make

# Clean object files
clean:
	@make -C libs/libft clean
	@make -C libs/ft_containers clean
	@make -C libs/mlx clean
	@$(RM) -rf $(OBJSDIR)

# Clean object files and executable
fclean: clean
	@make -C libs/libft fclean
	@make -C libs/ft_containers fclean
	@$(RM) $(NAME)

# Clean and rebuild
re: fclean all

.PHONY: all clean fclean re