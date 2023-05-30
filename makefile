NAME = cub3d

CC = cc 

files = main.c get_next_line.c get_next_line_utils.c tools.c

OPJECT = $(files:.c=.o)

all : $(NAME)

$(NAME) : $(OPJECT)
	 $(CC)    -o $@ $^ 

%.o:%.c
	$(CC) -c $< $@

clean : 
	rm $(OPJECT)