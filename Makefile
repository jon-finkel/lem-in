# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 20:54:44 by nfinkel           #+#    #+#              #
#    Updated: 2018/02/25 17:12:13 by nfinkel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

#	Environment
OS :=						$(shell uname)

#	Output
NAME :=						lem-in

#	Compiler
CC :=						gcc
VERSION :=					-std=c11

#	Flags:
ifneq ($(OS), Linux)
	FLAGS +=				-Wall -Wextra -Werror 
endif

HEADERS :=					-I ./includes/
O_FLAG :=					-O2

#	Directories
LIBFTDIR =					./libft/
OBJDIR :=					./build/

SRCS_DIR :=					./srcs/

#	Sources
SRC +=						main.c bfs.c edkarp.c move.c parser.c parser2.c
SRC +=						debug.c errhdl.c misc.c

OBJECTS =					$(patsubst %.c,$(OBJDIR)%.o,$(SRCS))

SRCS +=						$(SRC)

vpath %.c $(SRCS_DIR)

#################
##    RULES    ##
#################

all: libft $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(DEBUG) $(FLAGS) $(O_FLAG) $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(SRCS))) -L $(LIBFTDIR) -lft -o $@
	@printf  "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-14s\033[32m[✔]\033[0m\n"

$(OBJECTS): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)%.o: %.c
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-29s\033[32m[$<]\033[0m\n" ""
	@$(CC) $(VERSION) $(DEBUG)$(FLAGS)$(O_FLAG) $(HEADERS) -c $< -o $@
	@printf "\033[A\033[2K"

clean:
	@/bin/rm -rf $(OBJDIR)
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-14s\033[32m[✔]\033[0m\n"

debug: CC := clang
debug: DEBUG := -g3 -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined 
debug: FLAGS :=
debug: re

fclean: clean
	@/bin/rm -f $(NAME)
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-14s\033[32m[✔]\033[0m\n"

libft:
	@$(MAKE) -C $(LIBFTDIR)

noflags: FLAGS :=
noflags: re

purge: fclean
	@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

valgrind: DEBUG := -ggdb3 
valgrind: FLAGS :=
valgrind: re

.PHONY: all cat clean debug fclean libft noflags purge re valgrind

#################
##  WITH LOVE  ##
#################

cat:
	@clear;
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@#\`.\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@:\`\`\`,.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@.\`:\`\`.,,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@,.;,\`\`\`,,.\`,\`#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`:;\`\`  \`\`,::::.\`\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@#;;\`;\`   \`\`\`\`::::,\`+@@@@@;\`\`\`..,,,:,,,,.\`\`:#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;:\`\`;\`\`   \`\`\`\`\`,:::.\`,,::::::::::::::::::::,,..#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;,\`\`\`;\`\`    \`\`\`\`\`,::::::::::,,,,,,,,,,::::::::::,\`;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:,##+\`:,\`\`   \` \`\`\`\`,.:,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.,::::::,\`\`@@@@@@@@@@@@@@@@@@@@@@@@\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.;#@;+\`;;\`\`   \`\`\`\`\`\` \`\`\`\`\`\`   \`\`\`\`\`\`   \`\`\`\`\`\`\`\`.::::::,\`@@@@@@@@@@@@@@@@@@@@@. @@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,\`#@##+:+;\`\`   \`\`\`\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  \`\`\`:::::::,.@@@@@@@@@@@@@@@@@\`,,\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`\`\`@#\`@@@#;\`\`  \`\`\`\`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`::::::::,\`#@@@@@@@@@@@@#\`::.\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`,:\`;@@@@@\`\`\`  \`\`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`:::::::::,.@@@@@@+;:..::::\`\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:,#:@@@@@@@\`\`\`  \`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`,:::::::::,::\`.:::::::::\`\`\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.;##@@@@@@@@:\`       \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`.::::::::::.::::::::,\`\` \`.@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.;##@@@@@@@@#.\`  \`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,:::::::::,:.\`\`\`\`\`\`\` \`:,@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;\`,\`@@@@@@@@@#\`\`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`::::::::::\`\` \`\`\`   \`\`\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#;.\`\`@@@@@@@@#;\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`.:::::::::\`\` \`\`  \`;:@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,:.\`;#@@@##,\`\`\`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  \`\`\`.::::::::\`\`    \`:.@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:+.:+#\`+#:\`\`\`\`\`\`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.:::::::\`\`\` \`+;\`@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`;\`::#\`.\`\`\`\`\` \`\`   \`\`\`  \`\`\`\`\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.:::::,\` \`:\`+\`@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@.+\` \`\`\`\`\`\`\` \`\`\`\`\`\`\`\`\`   \`\`\`\`\`\`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`\`,:::,\`\`#+:;@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`.\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`###+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`\`.:\`#+\`\`@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`+##@@@@#+.\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`.:+#;\`@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`+#@@@@@@@@#:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`,,:;;@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@@@@@@@#;\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`:,\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@,:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`@@@@@@@@@@@@@#,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@@@@@@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,.@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`;#@@@@@@@@@@@@@@@+\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`;##\`\`\`\`,#@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@+;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@##+\`+##@@@@#.\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@+\`\`\`,\`@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@,:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@#,:...:+#@@@@+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@\`\`\`\`,@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@,,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:#@@@#,.,,,,,,\`#@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:#@@@#\`\`\`,:@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`@@@#\`,,,,,,,,:+@@@#;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`+@@@@#;\`\`\`.@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@#:,,,,,,,,,:#@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@#\`\`\`,@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@;\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@#,,,,,,,,,,,#@@@#\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`####@@#\`\`\`.\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`;\` \`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@:,,,,,,,,,,,,#@@@.\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+:;+@@#:\`\`\`.@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@;;\` \`   \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,,.,,,,,;#@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:,,:#@@+\`\`\`.@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@.;\`\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#;,,,,\` \`,,,,,#@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:,,,+@@#\`\`\`\`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`\` \`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,\`  ,,,,.+@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.,,,,#@#\`\`\`\`#@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`\`\`\`  \`\`\`\`\`\`\`\`\`\`\`\` \`#@@#:,,,,   .,,,,;@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,,,,;#@#\`\` \`;@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`  \`  \`\`\`\`\`\`\`\`\`\`\`\` \`#@@#:,,,,   \`,,,,:#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,,,,:#@#.\`\`\`.@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`  \`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,    ,,,,:#@@#\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,\`.,,+@#:\`  \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`     \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,    ,,,,:#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.. \`,,+@#;\`   @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`:\`     \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,    ,,,,:#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.  ,.\`@@;\`   @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@\`;\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,\`   ,,,,:#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  ,.;@#;\` \` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@.;\`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@#:,,,,.  \`,,,;;#@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  ,.;@#:\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@:\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`@@@:,,,,,  .,,#@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  ,.;##:\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@+\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;#@@#.,,,,\`\`,,,#@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`  ,.;##,\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,,,,,,,.+@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`,:#@#\`\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@#:,,,,,,,,,,,#@@@+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`. .,@@@#\`\`\`  @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@,,\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@+,,,,,,,,,,;#@@@;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`,\`,,#@@#\`\`\`  @@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@.;\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:#@@#,,,,,,,,,,;@@@#.\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`,,,,:@@#\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@;,\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@#:,,,,,,,:#@@@#\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`.,,,+@@+\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@+\`:\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@##:,,,,,:#@@@@+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`:,,:#@#;\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@,:.\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.#@@@@#\`:::;#@@@@#\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`;::\`#@#.\` \` \`@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@+;\` \`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@@@@####@@@@@+\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`:#\`#@@#\`\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`;\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`.#@@@@@@@@@@@@@#.\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@\`\`\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;.  \`\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@@@@@@@@#+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@#.\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;;\` \`:,\`\`  \`\`\`\`\`\`\`\` \`\`+#@@@@@@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+@@@#\`\`\`\` \`@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.;\` \`;;,\` \`  \`\`\`\`\`\`\`\`\`+@@@@@@@@##\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`,#@#.\`\`\`\` @@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.:  \`\`\`\`;\`\`\`\`\`\`\`\`\`\`\`\`\`\`#@@@@##+\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`+#,\`\`    @@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@#@@@@@@@@@@@@@@,\`  .\`\`\`\`;.\`\`\`  \`\`\`\`\`\`\`;+++,\`\`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`\`\`  \`\` #@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@;.@@@@@@@@@@@@@@.\`  ,\`\`\`\`\`;:\`\`       \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`  \`   @@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@\`;\`\`@@@@@@@@@@@@.\` \`:\`\`\`\`\`#+\`,\`\`\`\` \` \`\` \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`    @@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@\`+;:\`;@@@@@@@@@@.\` \`:\`\`\`\`@@@@#+;\`\`\`\`\`\`\`  \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\` \`\`   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@\`+\`\`\`;;;;;;;;;;;:,\` \`:\`\`\`+@@@@@@@##\`.\`\`\`\`\`\`    \`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`   \`\`\`\`.\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@.+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;.  ,\`\`\`#@@@@@@@@@@##\`,\`\`\`\`\`\`    \`\` \`  \`\`\`\`\`\`\`\`\`\`\`   \`     \`\`.\`#:@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@:+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;\`  .;\`\`@@@@@@@@@@@@@@@##\`:.\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`.\`#@@\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@#\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;.  \`;\`\`@@@@@@@@@@@@@@@@@@@@####+;,..\`\`\`\`\`\`\`\`\`\`\`\`\`.:\`###@@@@\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@\`+\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`\`;:\` \`;\`+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########@@@@@@@@@@@;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@:+\`\`\`\`\`\`\`::::,:::::,\` \`.;\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@.+\`\`\`\`\`\`:::,.,,,,.,,,\`\`\`:\`#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@.+\`\`\`\`\`;:::,,,..,,,,..\`\`\`\`#@@@@@@@@@@@@@@@@@@#@@@@@@@@@@#@@@@@@@@+@@#+,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@,+\`\`\`\`\`\`;::::,,,,,,,,,.\`\`,\`@@@@@@@@@@@@@@@@@##@@@@@@@@#.#@@@@@#+@@#.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@\`+\`\`\`\`\`\`\`;;::,,,,,,,,,,..\`.+#@@@@@@@@@@@@@@@#;#@@@##,##;+##;\`#@#,\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@#:+\`\`\`\`\`\`;;;;::,,,,,,,,..,.\`;#@@@@@@@@@@@@@@@#+::+#@@@@@##@##.;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,\`\`\`\`\`;;;:,,,:;;:,,,.,.\`.\`,,.\`##@@@@@@@@@@@@@@@@@@@@@@@#\`.+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`\`;;;;;;;;;;;;::,,. \`.  .,,,\`\`.\`###@@@@@@@@@@@@@@##;\`;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#..,;;,:;;;;;;:,,,....      ,,,,,,\`\`\`\`.,:\`\`+++++\`:,.:#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@:,;;;;\`\`\`;;;,,....,,,,,,.\`      ,,::::,,\`\`      \`...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@,+\`\`\`\`\`\`\`\`;;:,,,,,,,,\`         ,,:::::::,,.\`\`\`\`\`...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#:+\`\`\`\`\`\`\`\`;;::,,,,,.          ::::::::::::::,,,,.+:\`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+:+\`\`\`\`\`\`\`\`;;;:,.\`.:\`         :;::::::::::::::,\`  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`:\`\`\`\`\`\`\`\`;;:\`+@#\`\`          ,;;::::::::::::,.     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,:\`\`\`;;,.#@@@\`\`            .;\`\`:::::::::,;,   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#;:@@@@@@\`\`              \`;\`\`\`;::::::\`\`:     #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:.                 \`;\`\`\`\`\`\`\`\`\`\`;       .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+,                   \`,;\`\`\`\`\`\`\`\`;     .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:\`                      .;\`\`\`\`\`\`;\`     \`@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`\`          .\`             \`:;\`\`\`;\`     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+:          .:\`               \`.;\`;\`      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,\`          @.,                  \`.        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;,          ;@\`:                             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,\`          @@,;                              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
