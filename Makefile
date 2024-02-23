# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 16:01:18 by tde-la-r          #+#    #+#              #
#    Updated: 2024/02/23 18:05:30 by tde-la-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = main.c \
	   create_list.c \
	   exec.c \
	   list_utils.c \
	   error_utils.c
SRCS_DIR = sources/
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))

OBJS = $(SRCS:.c=.o)
OBJS_DIR = objects/
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))

NAME_B = pipex_bonus

SRCS_B = main_bonus.c \
	   create_list_bonus.c \
	   exec_bonus.c \
	   list_utils_bonus.c \
	   error_utils_bonus.c

OBJS_B = $(SRCS_B:.c=.o)
OBJS_B_PATH = $(addprefix $(OBJS_DIR), $(OBJS_B))

INCLUDES = -I$(LIBFT_INCLUDE) -I$(INCLUDE_DIR)
INCLUDE_DIR = includes/

CC = clang
FLAGS = -Wall -Wextra -Werror -g

LIBDIR = libft/
LIBFT = libft.a
LIBFT_INCLUDE = $(LIBDIR)include/

DEFAULT_PARAMS = infile "cat" "wc -w" outfile
BONUS_PARAMS = here_doc limit cat cat cat "wc -w" outfile
V_FLAGS = --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes

RM = rm -rf

all : libft $(NAME)

libft :
	make -C $(LIBDIR)

$(NAME) : $(OBJS_PATH)
	$(CC) $(OBJS_PATH) -o $(NAME) $(LIBDIR)$(LIBFT)

run : all
	./$(NAME) $(DEFAULT_PARAMS)

gdb : all
	gdb --tui $(NAME) -ex 'start $(DEFAULT_PARAMS)'

valgrind : all
	valgrind $(V_FLAGS) ./$(NAME) $(DEFAULT_PARAMS)

bonus : libft $(NAME_B)

$(NAME_B) : $(OBJS_B_PATH)
	$(CC) $(OBJS_B_PATH) -o $(NAME_B) $(LIBDIR)$(LIBFT)

bonus_run : bonus
	./$(NAME_B) $(BONUS_PARAMS)

bonus_gdb : bonus
	gdb --tui $(NAME_B) -ex 'start $(BONUS_PARAMS)'

bonus_valgrind : bonus
	valgrind $(V_FLAGS) ./$(NAME_B) $(BONUS_PARAMS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean :
	make clean -C $(LIBDIR)
	$(RM) $(OBJS_PATH) $(OBJS_B_PATH)

fclean : clean
	$(RM) $(LIBDIR)$(LIBFT)
	$(RM) $(NAME) $(NAME_B)

re : fclean all

.PHONY : all libft run gdb valgrind bonus bonus_run bonus_gdb bonus_valgrind clean fclean re
