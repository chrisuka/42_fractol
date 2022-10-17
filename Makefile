# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 19:18:05 by ikarjala          #+#    #+#              #
#    Updated: 2022/10/17 16:39:56 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT	:= ./
NAME	:= fractol
BIN		= $(ROOT)$(NAME)

CFUNC	=\
main app_control draw_util

SRC_DIR		= $(ROOT)src/
OBJ_DIR		= $(ROOT)obj/
INC_DIR		= $(ROOT) include/ libft/

SRC			= $(CFUNC:%=$(SRC_DIR)%.c)
OBJ			= $(CFUNC:%=$(OBJ_DIR)%.o)
INCLUDE		= $(addprefix -I , $(INC_DIR))
RM			:= rm -f

EXT_LIBS	= libft/libft.a
LIBS		= $(LIBFT) $(MLX)
LIBFT		= -L libft -lft
MLX			= -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

CFLAGS		= -Wall -Wextra -Werror
DBFLAGS		= -g -fsanitize=address
CC			:= clang

.PHONY: all clean fclean re db debug so
all: $(NAME)
$(NAME): $(EXT_LIBS) $(OBJ) Makefile
	@$(ECHO) $(BMSG_AR)
	@$(CC) -o $(BIN) $(CFLAGS) $(OBJ) $(INCLUDE) $(LIBS)
	@$(ECHO) $(BMSG_FIN)

$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c Makefile
	@printf	"$<    \t\t... "
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	@$(ECHO)	"DONE"

$(EXT_LIBS):
	@make -C $(dir $@) all

clean:
	@$(ECHO)	"Cleaning objects..."
	@$(RM) $(OBJ)
fclean: clean
	@$(ECHO)	"Removing binaries..."
	@$(RM) $(BIN) $(BIN:.a=.so)
re: fclean all

db: debug
debug: CFLAGS += $(DBFLAGS)
debug: BMSG_FORM := =DEBUG=
debug: $(NAME)

##	UTILS ====
ECHO	:= echo
$(PRE_BUILD_MESSAGE):
	@$(ECHO)	$(BMSG_BIN)
	@$(ECHO)	$(BMSG_CC)
	@$(ECHO)	$(BMSG_RELINK)

BMSG_BIN	= "$(COL_HL)$(NAME) :: Starting $(BMSG_FORM) build... $(COL_NUL)"
BMSG_FORM	:= deploy

BMSG_CC		= "$(COL_HL)$(NAME) :: Using $(CC) with $(CFLAGS) $(COL_NUL)"
BMSG_RELINK	= "$(COL_HL)$(NAME) :: Compiling C objects:"
BMSG_AR		= "$(COL_HL)$(NAME) :: Linking... { $(AR) }"
BMSG_FIN	= "$(COL_CS)$(NAME) :: Build success! $(COL_NUL)"

COL_HL		:=\033[0;33m
COL_CS		:=\033[0;32m
COL_NUL		:=\033[0;0m

CMD_NORME	= norminette -R CheckForbiddenSourceHeader
norme:
	$(CMD_NORME) $(INC_DIR)*.h $(SRC_DIR)*.c
