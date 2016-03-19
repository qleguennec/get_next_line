# Directories
BINDIR		=	.
SRCDIR		=	.
BUILDDIR	=	.
LIBDIR		=	.
INCLUDE		=	libft/includes
NAME		=	gnl-test
TARGET		=	$(BINDIR)/$(NAME)

# Compiler options
CC			=	clang
LIBFLAGS	=	-L$(BUILDDIR) $(subst lib,-l,$(LIBSRC))
CFLAGS		=	-I$(INCLUDE) -Wall -Wextra -Werror -g

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

$(BUILDDIR)/%.a: $(LIBDIR)/% $(BUILDDIR) $(LIBDIR)/$(LIBSRC)
	@make -s -C $< > /dev/null
	@cp $</$(@F) $@
	@echo $(GREEN)+++ lib: $(CYAN)$(@F)$(END)

$(TARGET): $(LIBS) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)
	@echo $(GREEN)+++ bin: $(BLUE)$(NAME)$(END)

$(BUILDDIR):
	@mkdir $(BUILDDIR)

$(LIBDIR)/$(LIBSRC):
	@git clone http://github.com/qleguennec/$(@F).git $@
	@cp $@/$(shell make -C $@ include)/$(@F).h $(INCLUDE) > /dev/null 2>&1 || true

.PHONY: clean
clean:
	@rm -f $(LIBS)
	@echo $(RED)--- lib: $(CYAN)$(LIBS:$(BUILDDIR)/%=%)$(END)
	@rm -f $(OBJECTS)
	@echo $(RED)--- obj: $(YELLOW)$(OBJECTS:$(BUILDDIR)/%=%)$(END)
	@rm -rf $(BUILDDIR) > /dev/null 2>&1 || true

.PHONY:	fclean
fclean: clean
	@rm -f $(TARGET)
	@echo $(RED)--- bin: $(BLUE)$(NAME)$(END)

.PHONY: re
re: fclean all


.PHONY: test
test:
	@test/test.sh $(ARGS)
