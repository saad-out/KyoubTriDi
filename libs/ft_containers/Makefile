CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_LIST_DIR = list
SRC_STACK_DIR = stack

SRCS_LIST = ft_lstadd_at_index.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_lstdel_at_index.c ft_lstdel_back.c ft_lstdel_front.c ft_lstiter.c \
			ft_lstmap.c ft_lstnew.c ft_lstsearch_item.c ft_lstsize.c

SRCS_STACK = ft_stack_clear.c ft_stack_create.c ft_stack_is_empty.c ft_stack_pop.c ft_stack_push.c ft_stack_size.c ft_stack_top.c

SRCS =    ${foreach file, $(SRCS_LIST), list/$(file)} \
            ${foreach file, $(SRCS_STACK), stack/$(file)}

OBJS = $(patsubst %.c, %.o, $(SRCS))

NAME = containersft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re