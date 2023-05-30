#include "cub3d.h"

void check_file_name(char *map_name)
{
    int len;
    char *extension;
    int i;

    extension =".cub";
    i = 3;
    len = ft_strlen(map_name);
    while (0 <= len-- && i >=0)
    {
        if(extension[i] != map_name[len])
        {
            write(2, "ERROR : your file exstension not valide\n", 41);
            exit(0);
        }
        i--;
    }
}

char  **read_map(int fd)
{
    char *line;
    char **map;
    char **tmp;

    map = NULL;
    tmp = NULL;
    line = get_next_line(fd);
    while(line != NULL)
    {
        tmp = map;
        map = ft_join2d(map,line);
        if(tmp != NULL)
            free(tmp);
        line = get_next_line(fd);
    }
    return(map);
}
void check_table(int *table,int len)
{
    int i = 0;
    while(i < len)
    {
         if(table[i] == 3)
            {
                printf("%d   table[%d] = %d\n",len,i,table[i]);
                write(2,"error in map\n",13);
                exit(0);
            }
        i++;
    }
}

void iterate_width(int *table ,char **map,int i, int len)
{
    int j;

    j = 0;
    while(map[i][j])
        {
                if(map[i][j] == '1')
                    table[j] = 1;
                else if(search("0NSEW",map[i][j]) == 1 && table[j] == 0)
                    table[j] = 3;
                else if(map[i][j] == ' ')
                    table[j] = 0;
            j++;
        }
    while(j < len)
    {
        table[j] = 0;
        j++;
    }
}
void iterate_height(int *table ,char **map,int i)
{
    int j;

    j = 0;
    while(map[j])
    {
            if((int)ft_strlen(map[j]) > i)
            {
                if(map[j][i] == '1')
                    table[j] = 1;
                else if(search("0NSEW",map[j][i]) == 1 && table[j] == 0)
                        table[j] = 3;
                else if(map[j][i] == ' ')
                    table[j] = 0;
            }
            else 
                table[j] = 0;
        j++;
    }
}

int max_len2d(char **map)
{
    int i;
    int len;
    
    len = 0;
    i = 0;
    while(map[i])
    {
        if((int)ft_strlen(map[i]) > len)
            len = ft_strlen(map[i]);
        i++;
    }
    return(len);
}

void check_map(char **map)
{
    int width;
    int height;
    int *table_top;
    int *table_left;
    int i;

    height = ft_strlen2d(map);
    width = max_len2d(map);
    table_top = ft_calloc(sizeof(int),width+1);
    table_left = ft_calloc(sizeof(int),height+1);
    i = 0;
    while(map[i])
    {
        iterate_width(table_top,map,i,width);
        check_table(table_top,width);
        i++;
    }
    i = height -1;
    ft_bzero(table_top,width);
    while(i>=0)
    {
        iterate_width(table_top,map,i,width);
        check_table(table_top,width);
        i--;
    }
    i = 0;
    while(i < width)
    {
        iterate_height(table_left,map,i);
        check_table(table_left,height);
        i++;
    }
    ft_bzero(table_left,height);
    i = width -1;
    while(i >= 0)
    {
        iterate_height(table_left,map,i);
        check_table(table_left,height);
        i--;
    }
    free(table_left);
    free(table_top);
}

void free2d(char **table)
{
    int i;

    i = 0;
    while(table[i])
    {
            
    }
}
void character_map(char **map)
{
    int i;
    int j;
    int start;

    i = 0;
    start = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(search("01NEWS ",map[i][j]) == 1)
            {
                if(search("NEWS",map[i][j]) == 1)
                      start++;
            }
            else
            {
                write(2,"ERROR : your map should have only this (0,1,N,E,W,S)\n",54);
                exit(0);
            }
            j++;
        }
        i++;
    }
    if(start != 1)
        write(2,"ERROR : your map should have  1 of (N,E,W,S)\n",45);
}
int main(int argc,char **argv)
{
    int fd;
    char **map;
    if(argc != 2)
        return(write(2,"ERROR :you must enter one argument\n",35));
    check_file_name(argv[1]);
    fd = open(argv[1],O_RDONLY);
    if(fd == -1)
        return(write(2,"ERROR : file did not open \n",28));
    map = read_map(fd);
    character_map(map);
    check_map(map);
}