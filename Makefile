CC = gcc
NAME = wolf3d
FLAGS = -Wall -Wextra -Werror
SRC =	srcs/main.c\
		srcs/load_map.c\
		srcs/env.c\
		srcs/map2d_funct.c\
		srcs/map3d_funct.c\
		srcs/map3d_funct_2.c\
		srcs/wall.c\
		srcs/texture_loader.c\
		srcs/texturer_sol_plafond.c\
		srcs/texture_tools.c\
		srcs/expose.c\
		srcs/hook.c\
		srcs/hook_tools.c\
		srcs/check_pos.c\
		srcs/tools.c\
		srcs/free.c\

OBJ = $(SRC:.c=.o)
INCLUDES = -I ./includes
LIBS = -L ./libft -lft -lmlx -framework OpenGL -framework AppKit 
#INCLUDES = -I ./includes -I /usr/X11/include
#LIBS = -L ./libft -lft -L /usr/X11/lib -lmlx -lXext -lX11

all : $(NAME)

$(NAME) : ./libft/libft.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(INCLUDES) $(LIBS) $(FLAGS)

./libft/libft.a : 
	make -C libft


%.o : %.c
	$(CC) -o $@ -c $< $(INCLUDES) $(FLAGS)

clean :
	rm -f $(OBJ)
	make -C libft/ fclean

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
