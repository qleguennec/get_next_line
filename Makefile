# Directories
BINDIR		?=	.
BUILDDIR	?=	build
NAME		=	$(BINDIR)/libgnl.a

# Compiler options
CC			=	clang
CFLAGS		=	$(addprefix -I,$(INCLUDE)) -Wall -Wextra -Werror -g

# Color output
BLACK		=	"\033[0;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[0;34m"
MAGENTA		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[0;37m"
END			=	"\033[0m"

SRC += get_next_line.c
SRC += list_add.c
SRC += list_concat.c
SRC += list_del.c
SRC += list_del_one.c
SRC += list_new.c

OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))

all: $(NAME)

$(BUILDDIR)/%.o: %.c
	@[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR)
	@printf $(YELLOW)$(NAME)$(END)'\t'
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@ar rc $(@) $(OBJECTS)

.PHONY: clean fclean re

clean:
	@rm -rf build/

fclean: clean
	@rm -rf $(TARGET)

re: fclean all
