NAME = cub3d

CC = cc


header = ./cub3d.h
FLAG = -Wall -Wextra  -Werror 


files = main.c get_next_line.c get_next_line_utils.c tools.c


OPJECT = $(files:.c=.o)


all: $(NAME)

$(NAME): $(OPJECT)
	$(CC) $(FLAG)  $^ -o $@ 

%.o : %.c $(header)
	$(CC) $(FLAG)  -c -o $@  $< 

clean: 
	rm $(OPJECT)

fclean : clean 
	rm $(NAME)

re : fclean all