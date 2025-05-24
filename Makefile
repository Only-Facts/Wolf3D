##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Compiles C files
##

CC			=	gcc

DIR_LIB		=	lib/

LIB_FILES	=	write.c		\
				get_len.c	\
				my_cmp.c	\
				my_cpy.c	\
				my_dup.c	\
				convert.c	\
				swap.c		\
				file_reader.c	\
				free.c	\
				cut.c	\
				str_to_word_array.c

DIR_SETT	=	menu/settings/

SETT_FILES	=	settings.c 			\
				settings_events.c 	\

DIR_MENU	=	menu/

MENU_FILES	=	menu.c				\
				create_button.c 	\
				button_animation.c	\

DIR_GAME	=	game/

GAME_FILES	=	ceiling.c	\
				draw.c	\
				enemy.c	\
				event.c	\
				call_to_event.c	\
				floor.c	\
				fps.c	\
				map.c	\
				player.c	\
				weapon.c	\
				raycaster.c	\

DIR_WOLF	=	wolf/

WOLF_FILES	=	init.c		\
				window.c	\
				loop.c		\
				scenes.c	\
				$(addprefix $(DIR_MENU), $(MENU_FILES))	\
				$(addprefix $(DIR_GAME), $(GAME_FILES))	\
				$(addprefix $(DIR_SETT), $(SETT_FILES))	\

DIR_SRC		=	src/

SRC_FILES	=	main.c	\
				$(addprefix $(DIR_LIB), $(LIB_FILES))	\
				$(addprefix $(DIR_WOLF), $(WOLF_FILES))

SRC			=	$(addprefix $(DIR_SRC), $(SRC_FILES))

DIR_TEST	=	tests/

TEST_FILES	=	test.c	\
				lib.c	\

TESTS		=	$(addprefix $(DIR_TEST), $(TEST_FILES))

BINARY_TEST	=	test

DIR_OBJ		=	.obj/

OBJ			=	$(SRC:%.c=$(DIR_OBJ)%.o)

TEST_OBJ	=	$(TESTS:%.c=$(DIR_OBJ)%.o)	\
				$(filter-out $(DIR_OBJ)/src/main.o, $(OBJ))

CFLAGS		=	-I./include -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

DFLAGS		=	-g -Wall -Wextra

TFLAGS		=	--coverage -lcriterion

BINARY		=	wolf3d

all: 	$(BINARY)

$(BINARY):	$(OBJ)
		@$(CC) $^ -o $@ $(CFLAGS) $(DFLAGS)
		@echo -e "\x1b[36mMakefile -> compile\x1b[0m"

$(DIR_OBJ)%.o:	%.c
		@mkdir -p $(dir $@)
		@$(CC) $^ -c -o $@ $(CFLAGS) $(DFLAGS)
		@echo -e "\x1b[36mMakefile -> $@\x1b[0m"

clean:
		@rm -rf $(DIR_OBJ)
		@rm -rf .ropeproject
		@rm -rf .cache
		@echo -e "\x1b[35mMakefile -> clean\x1b[0m"

fclean: clean
		@rm -f $(BINARY)
		@rm -f $(BINARY_TEST)
		@rm -f *.log
		@rm -f *.gcov
		@rm -f *.gcda
		@rm -f *.gcno
		@rm -rf .cache
		@rm -f vgcore.*
		@rm -rf $(DIR_OBJ)
		@echo -e "\x1b[35mMakefile -> fclean\x1b[34m"

re:		fclean all
		@rm -rf .ropeproject
		@rm -rf $(DIR_OBJ)
		@echo -e "\x1b[31mMakefile -> re\x1b[0m"

run:	fclean all
		@docker-compose up --remove-orphans

criterion: fclean $(TEST_OBJ)
		@$(CC) -o $(BINARY_TEST) $(TEST_OBJ) $(CFLAGS) $(DFLAGS) $(TFLAGS)
		@echo -e "\x1b[36mMakefile -> criterion\x1b[0m"

run_tests:	criterion
		@-./$(BINARY_TEST)
		@gcovr --exclude ./$(BINARY_TEST)
		@rm -f $(BINARY) $(BINARY_TEST)
		@rm -f *.gcov
		@rm -f *.gcda
		@rm -f *.gcno
		@echo -e "\x1b[34mMakefile -> run_tests\x1b[0m"

.PHONY: all clean fclean re criterion run_tests run
