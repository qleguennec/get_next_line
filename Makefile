# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/25 17:44:49 by qle-guen          #+#    #+#              #
#    Updated: 2016/02/21 21:03:18 by qle-guen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BINDIR		=	test
SRCDIR		=	src
BUILDDIR	=	build
LIBDIR		=	.
INCLUDE		=	.
NAME		=	gnl-test
TARGET		=	$(BINDIR)/$(NAME)

# Compiler options
CC			=	clang
LIBFLAGS	=	-L$(BUILDDIR) $(subst lib,-l,$(LIBSRC))
CFLAGS		=	-I$(INCLUDE) -Wall -Wextra -Werror -g

# Color output
BLACK		=	"\033[0;30;40m"
RED			=	"\033[0;31;40m"
GREEN		=	"\033[0;32;40m"
YELLOW		=	"\033[1;33;40m"
BLUE		=	"\033[0;34;40m"
MAGENTA		=	"\033[0;35;40m"
CYAN		=	"\033[0;36;40m"
WHITE		=	"\033[0;37;40m"
END			=	"\033[0m"

# Source files
SRC			+=	main.c
SRC			+=	get_next_line.c

# Libraries
LIBSRC		+=	libft

OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))
LIBS		=	$(addprefix $(BUILDDIR)/, $(addsuffix .a,$(LIBSRC)))

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)+++ obj: $(YELLOW)$(@F)$(END)

$(BUILDDIR)/%.a: $(LIBDIR)/% $(BUILDDIR)
	@make -s -C $<
	@cp $</$(@F) $@
	@echo $(GREEN)+++ lib: $(CYAN)$(@F)$(END)

$(TARGET): $(LIBS) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)
	@echo $(GREEN)+++ bin: $(BLUE)$(NAME)$(END)

$(BUILDDIR):
	@mkdir build/

.PHONY: clean
clean:
	@rm -f $(LIBS)
	@echo $(RED)--- lib: $(CYAN)$(LIBS:$(BUILDDIR)/%=%)$(END)
	@rm -f $(OBJECTS)
	@echo $(RED)--- obj: $(YELLOW)$(OBJECTS:$(BUILDDIR)/%=%)$(END)
	@rm -rf build/

.PHONY:	fclean
fclean: clean
	@rm -f $(TARGET)
	@echo $(RED)--- bin: $(BLUE)$(NAME)$(END)

.PHONY: re
re: fclean all

test: $(TARGET)
	@test/test.sh $(ARGS)
