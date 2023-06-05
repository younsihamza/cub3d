#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
#include <stdio.h>
#include "get_next_line.h"

int ft_isalpha(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] < '0' || str[i] > '9')
            return -1;
        i++;
    }
    return 0;
}


int ft_lastindex(char *str, int find)
{
    int i = strlen(str);
    while(i != 0)
    {
        if(str[i] == find)
            return i;
        i--;
    }
    return -1;
}

void check_table(int *table,int len)
{
    int i = 0;
    while(i < len)
    {
         if(table[i] == 3)
            {
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

int parcer_map(t_vars *vs)
{
    char *tmp = NULL;
    //char **color = NULL;
    int i = 0;
    if(vs->map_fd < 0)
    {
        return -1;
    }
    tmp = get_next_line(vs->map_fd);
    while(tmp != NULL)
    {
        if(tmp[0] != '\n')
            i++;
        tmp = get_next_line(vs->map_fd);
        free(tmp);
        
    }
    vs->texture = calloc(sizeof(char *), 7);
    vs->store_map = calloc(sizeof(char *), (i - 5));
    close(vs->map_fd);
    vs->map_fd = open("./map/map.cub", O_RDONLY);
    i = 0;
    // stote data fo vs->texture in 2D array format
    while(i < 6)
    {
        tmp = get_next_line(vs->map_fd);
        if(tmp[0] != '\n')
        {
            vs->texture[i] = ft_split(tmp, ' ');
            i++;
        }
        free(tmp);
    }
    // store data of map items in 2D array  format
    tmp = get_next_line(vs->map_fd);
    i = 0;
    while(tmp != NULL)
    {
        if(tmp[0] != '\n')
        {
            vs->store_map[i] = strdup(tmp);
            i++;
        }
        free(tmp);
        tmp = get_next_line(vs->map_fd);
    }
    i = 0;
    int j = 0;
    while(vs->texture[i] != NULL)
    {
        if(strlen(vs->texture[i][0]) == 2)
        {
            if(strncmp(vs->texture[i][0], "NO", 2) == 0 || strncmp(vs->texture[i][0], "SO", 2) == 0
            || strncmp(vs->texture[i][0], "WE", 2) == 0 || strncmp(vs->texture[i][0], "EA", 2) == 0)
            {
                j++;
            }
            else
            {   
                printf("vs->texture not available");
                return(0);
            }
        }
        else if(strlen(vs->texture[i][0]) == 1)
        {
            if( strncmp(vs->texture[i][0], "F",1) == 0|| strncmp(vs->texture[i][0], "C",1) == 0)
                j++;
            else
            {
                    puts("heref");
                printf("vs->texture not available");
                return(0);
            }  
        }
        else
        {
            perror("vs->texture don't  respect the rules");
            return(0);
        }
       i++;
    }
    if(i != j)
    {
        // puts("here");
        perror("vs->texture don't  respect the rules");
        return(0);
    }
    // j = 0;
    i = 0;
    // while(i < j)
    // {
    //      int k = 0;
    //      while(vs->texture[k] != NULL)
    //      {
    //         if(k == i)
    //           k++;
    //         else if(strcmp(vs->texture[k][0], vs->texture[i][0]) == 0)
    //         {
    //             printf("vs->texture duplicated");
    //             return(0);
    //         }
    //         k++;

    //      }  
    //      i++; 
    // }
    // i = 0;
    // close(vs->map_fd);
    // while(vs->texture[i] != NULL)
    // {
    //     if(strncmp(vs->texture[i][0], "F", 1) == 0 || strncmp(vs->texture[i][0], "C", 1) == 0)
    //     {
    //         tmp = ft_substr(vs->texture[i][1], 0, strlen(vs->texture[i][1]) - 1);
    //         if(tmp == NULL)
    //             return(0);
    //         color = ft_split(tmp, ',');
    //         free(tmp);
    //         j = 0;
    //         while(color[j] != NULL)
    //         {
    //             if(ft_isalpha(color[j]) == -1 || ft_atoi(color[j]) < 0 || ft_atoi(color[j]) > 255)
    //             {
    //                 printf("color not acceptable");
    //                 return(0);
    //             }
    //             j++;
    //         }
    //         i++;
    //     }
    //     else
    //     {
    //         tmp = ft_substr(vs->texture[i][1], 0, strlen(vs->texture[i][1]) - 1);
    //         if(tmp == NULL)
    //             return(0);
    //         vs->map_fd = open(tmp, O_RDWR);
    //         if(vs->map_fd < 0)
    //             return(0);
    //         free(tmp);
    //         tmp = ft_substr(tmp, ft_lastindex(tmp, '.'), strlen(tmp));
    //         if(tmp == NULL)
    //             return(0);
    //         if(strncmp(tmp, ".xpm", strlen(tmp)) != 0)
    //                 return(0);
    //         free(tmp);
    //         i++;
    //     }
    // }
    check_map(vs->store_map);
    return(1);
}