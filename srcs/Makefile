# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 17:53:29 by klakbuic          #+#    #+#              #
#    Updated: 2024/07/04 12:35:47 by klakbuic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ANSI_RESET			:= \\033[0m
ANSI_BOLD			:= \\033[2m
ANSI_BOLD_RESET		:= \\033[22m
ANSI_ULINE			:= \\033[4m
ANSI_ULINE_RESET	:= \\033[24m
ANSI_ITALIC			:= \\033[3m
ANSI_ITALIC_RESET	:= \\033[23m
ANSI_RED		:= \\033[38;5;125m
ANSI_LRED		:= \\033[38;5;196m
ANSI_WHITE		:= \\033[38;5;15m
ANSI_YELLOW		:= \\033[38;5;3m
ANSI_GREEN		:= \\033[38;5;2m
ANSI_ORANGE		:= \\033[38;5;208m
ANSI_LORANGE	:= \\033[38;5;215m
ANSI_GOLD		:= \\033[38;5;214m
ANSI_BLUE		:= \\033[38;5;4m
ANSI_PURPLE		:= \\033[38;5;129m
ANSI_CYAN		:= \\033[38;5;44m

DEBUG		:= -fsanitize=address -g
CCWI		:= cc -Wall -Wextra -Werror 
RDLIB		:= -L /Users/$(USER)/readline/lib
NAME		:= minishell
# directories
SRCSDIR		:= src
OBJSDIR		:= obj
BUILTSDIR	:= builtins
ENVDIR 		:= environment
EXECDIR		:= executor
EXPANDERDIR	:= expander
LEXERDIR	:= lexer
LIBSDIR		:= libs
MEMDIR		:= memory
PARSERDIR	:= parser
UTILSDIR	:= utils

# sources
BUILTINS	:=	\
	builtins.c	\
	ft_cd.c		\
	ft_echo.c	\
	ft_env.c	\
	ft_exit.c	\
	ft_export.c	\
	ft_pwd.c	\
	ft_unset.c	\
	sort_env.c

ENV 		:=		\
	environement.c 	\
	env_utils2.c	\
	env_utils3.c	\
	env_utils.c
					
EXEC		:=			\
	exec.c				\
	execute_tree.c		\
	execute_utils2.c	\
	execute_utils.c		\
	executor.c			\
	pipe.c

EXPANDER	:=			\
	env_vars.c			\
	expander.c			\
	expander_utils.c	\
	expand_exec.c		\
	expand_heredoc.c	\
	expand_quotes.c		\
	expand_redir.c		\
	expand_utils2.c		\
	wildcards.c			\
	wildcards_utils.c	\

LEXER	:=				\
	heredoc.c			\
	lexer.c				\
	literals.c			\
	post_lexer.c		\
	redir_utils.c		\
	special_tokens.c	\
	string_iterator.c	\
	syntax_checker.c	\
	syntax_utils.c		\
	token.c				\
	whitespace.c		\
	word_token.c		\

LIBS	:= 			\
	ft_atoi.c		\
	ft_isalpha.c	\
	ft_isdigit.c	\
	ft_memcpy.c		\
	ft_putendl_fd.c	\
	ft_putstr_fd.c	\
	ft_split.c		\
	ft_strcmp.c		\
	ft_strjoin.c	\
	ft_strndup.c	\
	ft_tolower.c	\
	ft_isalnum.c	\
	ft_isascii.c	\
	ft_itoa.c		\
	ft_putchar_fd.c	\
	ft_putnbr_fd.c	\
	ft_realloc.c	\
	ft_strchr.c		\
	ft_strdup.c		\
	ft_strlen.c		\
	ft_substr.c

MEM		:=	\
	mem.c	\
	utils.c

PARSER  :=			\
	consturtor.c	\
	heredoc.c		\
	heredoc_utils.c	\
	parser.c		\
	parser_utils.c	\
	RDP_2.c			\
	RDP.c			\

UTILS	:=	\
	error.c						\
	get_next_line_bonus.c		\
	get_next_line_utils_bonus.c	\
	globals.c					\
	signals.c


SRCS	:= 	\
			$(foreach F,$(BUILTINS),$(SRCSDIR)/$(BUILTSDIR)/$(F))		\
			$(foreach F,$(ENV),$(SRCSDIR)/$(ENVDIR)/$(F))				\
			$(foreach F,$(EXEC),$(SRCSDIR)/$(EXECDIR)/$(F))				\
			$(foreach F,$(EXPANDER),$(SRCSDIR)/$(EXPANDERDIR)/$(F))		\
			$(foreach F,$(LEXER),$(SRCSDIR)/$(LEXERDIR)/$(F))			\
			$(foreach F,$(LIBS),$(SRCSDIR)/$(LIBSDIR)/$(F))				\
			$(foreach F,$(MEM),$(SRCSDIR)/$(MEMDIR)/$(F))				\
			$(foreach F,$(PARSER),$(SRCSDIR)/$(PARSERDIR)/$(F))			\
			$(foreach F,$(UTILS),$(SRCSDIR)/$(UTILSDIR)/$(F))			\
			$(SRCSDIR)/main.c											\
			$(SRCSDIR)/minishell.c
			
# objects
OBJS		:= $(patsubst src/%.c,obj/%.o,$(SRCS))

all : $(NAME)

bonus : all

debug : CCWI += $(DEBUG)
debug : all

$(NAME) : $(OBJSDIR) $(OBJS)
	@$(CCWI) $(OBJS) -lreadline $(RDLIB) -o $(NAME)
	@printf "$(ANSI_GREEN)"
	@printf "███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n"
	@printf "████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n"
	@printf "██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n"
	@printf "██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n"
	@printf "██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\n"
	@printf "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n"
	@printf "$(ANSI_RESET)\\033[38;5;10m"
	@printf "▀█▀ █▀▀ 　 ▒█▀▀█ █▀▀ █▀▀█ █▀▀▄ █░░█\n"
	@printf "▒█░ ▀▀█ 　 ▒█▄▄▀ █▀▀ █▄▄█ █░░█ █▄▄█\n"
	@printf "▄█▄ ▀▀▀ 　 ▒█░▒█ ▀▀▀ ▀░░▀ ▀▀▀░ ▄▄▄█\n"
	@printf "$(ANSI_RESET)"

$(OBJS) : $(OBJSDIR)/%.o : $(SRCSDIR)/%.c
	@$(CCWI) -c $< -o $@
	@printf "$(ANSI_PURPLE)$(ANSI_ITALIC)"
	@printf "$@ "
	@printf "$(ANSI_GREEN)"
	@printf "[DONE]\n"
	@printf "$(ANSI_RESET)"

$(OBJSDIR) :
	@mkdir -p $(OBJSDIR)
	@mkdir -p $(OBJSDIR)/$(BUILTSDIR)
	@mkdir -p $(OBJSDIR)/$(ENVDIR)
	@mkdir -p $(OBJSDIR)/$(EXECDIR)
	@mkdir -p $(OBJSDIR)/$(EXPANDERDIR)
	@mkdir -p $(OBJSDIR)/$(LEXERDIR)
	@mkdir -p $(OBJSDIR)/$(LIBSDIR)
	@mkdir -p $(OBJSDIR)/$(MEMDIR)
	@mkdir -p $(OBJSDIR)/$(PARSERDIR)
	@mkdir -p $(OBJSDIR)/$(UTILSDIR)

clean :
	@rm -rf $(OBJSDIR)
	@printf "$(ANSI_LRED)"
	@printf "|-------------------|\n"
	@printf "  Cleaning OBJS ...\n"
	@printf "       [DONE].\n"
	@printf "|-------------------|\n"
	@printf "$(ANSI_RESET)"

fclean : clean
	@rm -rf $(NAME)
	@printf "$(ANSI_RED)"
	@printf "|----------------------|\n"
	@printf "  REMOVE MINISHELL ...\n"
	@printf "         [DONE].\n"
	@printf "|----------------------|\n"
	@printf "$(ANSI_RESET)"
	
print:
	@echo $(USER)
	# @echo $(OBJS)
re : fclean all

.PHONY : clean