##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

NAME = my_hunter

SRCS = 	src/func_hunter.c	\
		src/my_cat.c		\
		src/my_strcmp.c 	\
		src/animation.c 	\
		src/base_list.c 	\
		src/destroy.c 		\
		src/handle_h_s.c 	\
		src/main_file.c 	\
		src/menu.c 			\
		src/my_get_round.c 	\
		src/my_get_score.c 	\
		src/my_getnbr.c 	\
		src/my_nbrlen.c 	\
		src/my_strdup.c 	\
		src/struct_init.c 	\

CFLAGS = -Wall -Wextra -I ./include/

CSFMLFLAGS = -l csfml-window -l csfml-graphics -l csfml-system -l csfml-audio

all :
	gcc -o $(NAME) $(SRCS) $(CFLAGS) $(CSFMLFLAGS)
clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)
	rm -rRf ./*~

debug: CFLAGS += -g
debug: fclean all

re : fclean all
