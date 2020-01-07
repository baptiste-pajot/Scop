# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/10/09 10:49:27 by bpajot       #+#   ##    ##    #+#        #
#    Updated: 2020/01/07 14:39:13 by bpajot      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = scop
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
LMLX_FLAGS = -L minilibx_macos/ -lmlx -framework OpenGl -framework Appkit
PATH_SRCS = ./srcs/
PATH_OBJS = .
PATH_INCS = ./includes/
FILES = center.c \
		event.c \
		free.c \
		indices.c \
		matrice_pipeline.c \
		matrice_rot.c \
		matrice_tr_proj.c \
		matrice_utils.c \
		parser.c \
		scop.c \
		shader1.c \
		shader2.c \
		textures.c \
		vbo.c \
		vertices.c
FILES_INC = scop.h
SRCS = $(addprefix $(PATH_SRCS), $(FILES))
OBJS = $(addprefix $(PATH_OBJS), $(FILES:.c=.o))
INCS = $(addprefix $(PATH_INCS), $(FILES_INC))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C minilibx_macos
	@echo "CREATION DE L'EXECUTABLE"
	@$(CC) $(CC_FLAGS) -o $@ $^  $(LMLX_FLAGS)
	@echo "COMPILATION EXECUTABLE REUSSIE 👍"

$(PATH_OBJS)%.o: $(PATH_SRCS)%.c $(INCS)
	@echo "creation $@ "
	@$(CC) $(CC_FLAGS) -o $@ -c $<
	@echo "compilation $@ ok 👍"

clean:
	@make -C minilibx_macos clean
	@/bin/rm -f $(OBJS)
	@echo "NETTOYAGE REUSSIE 👍"

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
