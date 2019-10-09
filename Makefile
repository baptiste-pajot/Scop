# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/09 10:49:27 by bpajot       #+#   ##    ##    #+#        #
#    Updated: 2019/10/09 12:17:46 by bpajot      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = scop
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
LMLX_FLAGS = -L minilibx_macos/ -lmlx -framework OpenGl -framework Appkit
PATH_SRCS = ./srcs/
PATH_OBJS = ./objs/
PATH_INCS = ./includes/
FILES = scop.c
FILES_INC = scop.h
SRCS = $(addprefix $(PATH_SRCS), $(FILES))
OBJS = $(addprefix $(PATH_OBJS), $(FILES:.c=.o))
INCS = $(addprefix $(PATH_INCS), $(FILES_INC))

all: $(NAME)

$(NAME): $(OBJS)
	make -C minilibx_macos
	@echo "CREATION DE L'EXECUTABLE"
	$(CC) $(CC_FLAGS) -o $@ $^  $(LMLX_FLAGS)
	@echo "👍  COMPILATION REUSSIE 👍\ "

$(OBJS): $(SRCS) $(INCS)
	@echo "CREATION $@ "
	$(CC) $(CC_FLAGS) -o $@ -c $<
	@echo "👍  COMPILATION REUSSIE 👍\ "

clean:
	make -C minilibx_macos clean
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
