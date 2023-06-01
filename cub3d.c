#include "get_next_line.h"

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

int check_pixel(t_vars *vars , char test)
{
	int i = -2;
	int j ;
	while(i < 2)
	{
		j = -2;
		while(j < 2)
		{
			if(test == '+')
			{
				if(vars->store_map[(int)(vars->y_now+j + sin(vars->deriction) * 5) / 20][(int)((vars->x_now+i  + cos(vars->deriction) * 5 )/20)] == '1')
					return(1);
			}
			else if (test == '-')
			{
				if(vars->store_map[(int)(vars->y_now+j - sin(vars->deriction) * 5) / 20][(int)((vars->x_now+i  - cos(vars->deriction) * 5 )/20)] == '1')
					return(-1);
			}
				j++;
		}
		i++;
	}
	return(0);
}


int key_hook(int key , t_vars *vars)
{
	 // 13 || 126 >> key N
	 //125 || 1 >> key S
	 //123 || 0 >> key E
	 //124 || 2 >> key W
	if((key == 13 || key == 126) &&check_pixel(vars,'-') == 0 )
	{
		vars->x_now -= cos(vars->deriction) * 5;
		vars->y_now -= sin(vars->deriction) * 5;
	}
	else if(key == 2 || key == 124)
	{
		// mlx_clear_window(vars->mlx,vars->mlx_win);
		vars->deriction += 0.1;
	}
	else if(key == 0 || key == 123)
	{
		// mlx_clear_window(vars->mlx,vars->mlx_win);
		vars->deriction -= 0.1;
	}
	if((key == 1 || key == 125) && check_pixel(vars,'+') == 0)
	{
		vars->x_now += cos(vars->deriction) * 5;
		vars->y_now += sin(vars->deriction) * 5;
	}
	printf("%f\n",sin(vars->deriction) * 5);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int check_ridues(t_vars *vars,int y,double on)
{
	double i = -0.5;
	while(i <= 0.5)
	{
		if(vars->store_map[(int)(vars->y_now + i - sin(vars->deriction +on)*y)/20][(int)(vars->x_now - cos(vars->deriction + on )*y)/20] == '1')
			return (-1);
		if(vars->store_map[(int)(vars->y_now  - sin(vars->deriction +on)*y)/20][(int)(vars->x_now + i - cos(vars->deriction + on )*y)/20] == '1')
			return (-1);
		i+=0.5;
	}
	return (0);
}

int ft_draw(t_vars *vars)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	double PI = 3.14159;
	// int k = 20;
	// printf("%c", vars->store_map[i][j]);
	mlx_clear_window(vars->mlx,vars->mlx_win);
	while(vars->store_map[i] != NULL)
	{
		j = 0;
		while(vars->store_map[i][j])
		{
			if(vars->store_map[i][j] == '1')
			{
				x = 0;
				while(x < 20)
				{
					y = 0;
					while(y < 20)
					{
						
						mlx_pixel_put(vars->mlx, vars->mlx_win, j * 20 + x ,i * 20 + y  , create_trgb(0,100,100,100));
						y++;
					}
					x++;
				}
			}
			if(j == (int)vars->x_now / 20 && i == (int)vars->y_now / 20)
			{
				double on = 0;
				x = 0;
				y = 0;
				//printf()
			
				while(on < 30*(PI/180))
				{
					y = 0;
					while(check_ridues(vars,y, on)==0)
					{
						mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now - cos(vars->deriction + on)*y ,vars->y_now - sin(vars->deriction +on)*y , create_trgb(0,200,50,100));
						y++;
					}
					on+=(PI/180);
				}
				x = 0;
				y = 0;
					on = 0;
				while(on < 30*(PI/180))
				{
					y = 0;
					while(check_ridues(vars,y,-1*on)==0)
					{
						mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now - cos(vars->deriction - on)*y ,vars->y_now - sin(vars->deriction -on)*y , create_trgb(0,200,50,100));
						y++;
					}
					on+=(PI/180);
				}

				x = -5;
				int f = 0;
				while(x < 5)
				{
					y = -5;
					while(y < 5)
					{
						mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now - cos(vars->deriction)*f ,vars->y_now - sin(vars->deriction)*f , create_trgb(0,20,20,100));
						// mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now - cos(vars->deriction)*f ,vars->y_now - sin(vars->deriction)*f+y , create_trgb(0,20,20,100));
						mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now + x ,vars->y_now + y , create_trgb(0,20,20,100));
						y++;
					}
					x++;
					f+=2;
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc,char **argv)
{
	double PI = 3.14159265359;
	t_vars vars;
	vars.store_map = NULL;
	vars.texture = NULL;
	vars.mlx = NULL;
	vars.mlx_win = NULL;
	if(argc != 2)
        return(write(2,"ERROR :you must enter one argument\n",35));
	check_file_name(argv[1]);
	vars.map_fd = open(argv[1],O_RDONLY);
    if(vars.map_fd  == -1)
        return(write(2,"ERROR : file did not open \n",28));
if (parcer_map(&vars) == 0) 
{
	return 0;
}


	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 33 * 20 , 14 * 20, "unrecorded");
	//   ft_draw(&vars);
	int i = 0;
	int j = 0;
	while(vars.store_map[i])
	{
		j = 0;
		while(vars.store_map[i][j])
		{
			if(vars.store_map[i][j] == 'N')
			{
				vars.x_now = (j * 20 + 10);
				vars.y_now = (i * 20 + 10);
				vars.deriction = PI/2;
			}
			j++;
		}
		i++;
	}
	mlx_loop_hook(vars.mlx, ft_draw, &vars);
	mlx_hook(vars.mlx_win,2,1L<<0,key_hook, &vars);
	//mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_loop(vars.mlx);
    
}