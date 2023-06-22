#!/bin/sh
NAME = cub3d

CC = cc 

FLAGA = -Wall -Wextra  -Werror 

HEADER = cub3d.h




SRCS =   cub3d.c parcer_map.c ft_split.c  get_next_line.c get_next_line_utils.c ft_atoi.c tools.c ft_itoa.c  sprite.c  map_tools.c map_tools_1.c  help_parcer_1.c help_parcer_2.c help_parcer_3.c help_1.c help_2.c help_3.c help_4.c help_5.c tools_1.c minimap.c minimap_tools.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS) 
	$(CC)  $(FLAGA)  -lmlx -framework OpenGL -framework AppKit  $^ -o $@  
	
%.o : %.c  $(HEADER)
	$(CC) $(FLAGA)  -Imlx -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all 