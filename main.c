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
int check_table(int *table,int len)
{
    int i = 0;
    int number_zero = 0;;
    while(i < len)
    {
        if(table[i] == 0)
            number_zero++;
        else if(table[i] == 3)
            {
                write(2,"error in map\n",13);
                exit(0);
            }
        i++;
    }
    return (number_zero);
}
void check_map(char **map)
{
    int width;
    int height;
    int i;

    width = 0;
    i = 0;
    height = ft_strlen2d(map);
    while(map[i])
    {
        if(ft_strlen(map[i]) > width)
            width = ft_strlen(map[i]);
        i++;
    }
    int *table_top = ft_calloc(sizeof(int),width);
    int *table_bottom = ft_calloc(sizeof(int),width);
    int *table_left = ft_calloc(sizeof(int),height);
    int *table_right = ft_calloc(sizeof(int),height);
    i = 0;
    int  j = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == '1')
                table_top[j] = 1;
            else if(map[i][j] != '1' && map[i][j] != ' ')
                table_top[j] = 3;
            else if(map[i][j] == ' ')
                table_top[j] = 0;
            j++;
        }
        printf("%s\n",map[i]);
        check_table(table_top,width);
        i++;
    }
    j = 0;
    while(j < width)
    {
        printf("%d\n",table_top[j++]);
    }
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
    check_map(map);
    



}