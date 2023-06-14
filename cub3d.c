#include "get_next_line.h"

void check_file_name(char *map_name)
{
	int len;
	char *extension;
	int i;

	extension = ".cub";
	i = 3;
	len = ft_strlen(map_name);
	while (0 <= len-- && i >= 0)
	{
		if (extension[i] != map_name[len])
		{
			write(2, "ERROR : your file exstension not valide\n", 41);
			exit(0);
		}
		i--;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int check_pixel(t_vars *vars, double sin_value ,double cos_value)
{
	double i = -5;
	double j;
	while (i < 5)
	{
		j = -5;
		while (j < 5)
		{
				if (vars->store_map[(int)(vars->y_now + i + sin_value ) / (vars->height_window/14)][(int)((vars->x_now + j + cos_value) / (vars->size ))] == '1')
					return (-1);
			j += 1;
		}
		i += 1;
	}
	return (0);
}


int key_hook(int key,double k, t_vars *vars)
{
		double PI = 3.141592653589793238462203383279502884197;
	k= 0;
	if ((key == 126) && check_pixel(vars,sin(vars->deriction) * 20,cos(vars->deriction) *20) == 0)
	{
		vars->x_now += cos(vars->deriction) *20;
		vars->y_now += sin(vars->deriction) * 20;
		ft_draw(vars);
	}
	 if ( key == 124)
	 {
		vars->deriction += 0.1;
		ft_draw(vars);
	 }
	if ( key == 123)
	{
		vars->deriction -= 0.1;
		ft_draw(vars);
	}
	if ((key == 125) && check_pixel(vars, -sin(vars->deriction) * 5,-cos(vars->deriction) * 5) == 0)
	{
		vars->x_now -= cos(vars->deriction) * 5;
		vars->y_now -= sin(vars->deriction) * 5;
		ft_draw(vars);
	}
	if(key == 46)
	{
		if(vars->map == 0)
			vars->map = 1;
		else
			vars->map = 0;
		ft_draw(vars);
	}

	if (((key == 13 ) || vars->up == 1) && check_pixel(vars, sin(vars->deriction) * 10,cos(vars->deriction) * 10) == 0 )
	{
		vars->up = 1;
		vars->x_now += cos(vars->deriction) * 10;
		vars->y_now += sin(vars->deriction) * 10;
		ft_draw(vars);
	}
	 if ((key == 2  || vars->right == 1) && check_pixel(vars, sin(vars->deriction+(PI/2)) * 10,cos(vars->deriction+(PI/2)) * 10) == 0)
	 {
		vars->right = 1;
		vars->x_now += cos(vars->deriction+(PI/2)) * 10;
		vars->y_now += sin(vars->deriction+(PI/2)) * 10;
		ft_draw(vars);
	 }
	if ((key == 0 ||vars->left == 1) && check_pixel(vars, sin(vars->deriction-(PI/2)) * 10,cos(vars->deriction-(PI/2)) * 10) == 0)
	{
		vars->left = 1;
		vars->x_now += cos(vars->deriction-(PI/2)) * 10;
		vars->y_now += sin(vars->deriction-(PI/2)) * 10;
		ft_draw(vars);
	}
	if (((key == 1 )|| vars->down == 1) && check_pixel(vars, -sin(vars->deriction) * 10,-cos(vars->deriction) * 10) == 0)
	{
		vars->down = 1;
		
		vars->x_now -= cos(vars->deriction) * 10;
		vars->y_now -= sin(vars->deriction) * 10;
		ft_draw(vars);
	}
	
	printf("%d   \n",key);
	return (0);
}


int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void ber_c(t_vars *vars, double xi, double yi, double xf, double yf)
{
	double dy;
	double dx;
	double x;
	double y;
	int i = 1;
	double s = 0;
	double Xinc;
	double Yinc;
	x = xi;
	y = yi;

	dy = yf - yi;
	dx = xf - xi;
	if (abs((int)dx) > abs((int)dy))
		s = abs((int)dx);
	else
		s = abs((int)dy);
	Xinc = dx / s;
	Yinc = dy / s;
	while (i <= s)
	{
		if(y< 0 || y > 14*64 )
			y = 0;
		my_mlx_pixel_put(&vars->main_image,x,y,create_trgb(0, 135, 206, 235));
		x += Xinc;
		y += Yinc;
		i++;
	}
}

void ber_floor(t_vars *vars, double xi, double yi, double xf, double yf)
{
	double dy;
	double dx;
	double x;
	double y;
	int i = 1;
	double s = 0;
	double Xinc;
	double Yinc;
	x = xi;
	y = yi;

	dy = yf - yi;
	dx = xf - xi;
	if (abs((int)dx) > abs((int)dy))
		s = abs((int)dx);
	else
		s = abs((int)dy);
	Xinc = dx / s;
	Yinc = dy / s;
	while (i <= s)
	{
		if(y< 0 || y > 14*64 )
			y = 0;
		my_mlx_pixel_put(&vars->main_image,x,y,create_trgb(0, 218, 160, 109));
		x += Xinc;
		y += Yinc;
		i++;
	}
}

void ber(t_vars *vars, int xi, int yi, int xf, int yf,int  offset_x)
{
	//(void)color;
	double dy;
	double dx;
	double x;
	double y;
	int i = 1;
	double s = 0;
	double Xinc;
	double Yinc;
	int color;
	x = xi;
	y = yi;

	dy = yf - yi;
	dx = xf - xi;
	if (abs((int)dx) > abs((int)dy))
		s = abs((int)dx);
	else
		s = abs((int)dy);
	Xinc = dx / s;
	Yinc = dy / s;
	while (i <= s)
	{
	char *d = NULL;
		if( y < 0 || y > vars->len_v * (vars->size-1))
		{
			y = 0;
			//yi = 0;
		}
		int offset_y = abs((int)(y -  yi)) * 512.0/(yf - yi);
		//printf("%f\n",64.0/(yf - yi));
			//printf("x =%d  y = %d  :: y -yi = %d  :: ya =%d  yi = %d\n",offset_y,offset_x,(int)(y -  yi),(int)y,(int)yi);
		d = (vars->n_image.addr + ((int)offset_y * vars->n_image.line_length) + (offset_x*(int)(vars->n_image.bits_per_pixel/8)));
		color = *(unsigned int*)d;
		my_mlx_pixel_put(&vars->main_image,(int)x,(int)y,color);
		x += Xinc;
		y += Yinc;
		i++;
	}
}

typedef struct v
{
	double des;
	double xa;
	double ya;

} t_v;

void check_hor(t_vars *vars, double angle)
{
	double yn;
	double xn;
	double xstep = 0;
	double ystep = 0;
	int offset = 0;
	yn = (int)(vars->y_now / (vars->size)) * (vars->size) + (vars->size);
	if (sin(angle) < 0)
		yn = (int)(vars->y_now / (vars->size)) * (vars->size);
	xn = -(vars->y_now - yn) / tan(angle) + vars->x_now;
	vars->plane_x_h = xn;
	vars->plane_y_h  = yn;
	ystep = vars->size;
	if (sin(angle) < 0)
	{
		ystep = -vars->size;
		offset = -1;
	}
	xstep = ystep / tan(angle);
	while ((vars->plane_y_h + offset) / vars->size > 0 && (vars->plane_y_h + offset) / vars->size  < vars->len_v  && vars->plane_x_h / vars->size > 0 && ft_strlen(vars->store_map[(int)(vars->plane_y_h  + offset) / vars->size]) > vars->plane_x_h / vars->size && vars->store_map[(int)(vars->plane_y_h  +offset) / vars->size][(int)(vars->plane_x_h) / vars->size] != '1')
	{
		vars->plane_x_h += xstep;
		vars->plane_y_h += ystep;
	}

	 vars->plane_des_h = (vars->plane_y_h - vars->y_now) / sin(angle);
}
int kk(int key ,t_vars *vars)
{
	if(key == 13)
		vars->up = 0;
	if(key == 2)
		vars->right = 0;
	if(key == 0)
		vars->left = 0;
	if(key == 1)
		vars->down = 0;
	return(0);
}
void check_vertical(t_vars *vars, double angle)
{
	double yn;
	double xn;
	double xstep = 0;
	double ystep = 0;
	int offset = 1;
	xn = (int)(vars->x_now / (vars->size)) * (vars->size);
	if (cos(angle) > 0)
		xn = (int)(vars->x_now / (vars->size )) * (vars->size) + (vars->size);
	yn = vars->y_now - tan(angle) * (vars->x_now - xn);
	vars->plane_x_v = xn;
	vars->plane_y_v = yn;
	xstep = (vars->size );
	if (cos(angle) < 0)
	{
		xstep = -(vars->size );
		offset = -1;
	}
	ystep = tan(angle) * xstep;
	while (vars->plane_y_v / vars->size >= 0 && (int)(vars->plane_y_v / vars->size) < vars->len_v && vars->plane_x_v / vars->size >= 0 && ft_strlen(vars->store_map[(int)vars->plane_y_v / vars->size]) >= vars->plane_x_v / vars->size && vars->store_map[(int)(vars->plane_y_v) / 64][(int)(vars->plane_x_v + offset) / vars->size] != '1')
	{
		vars->plane_x_v += xstep;
		vars->plane_y_v += ystep;
	}
	vars->plane_des_v = (vars->plane_y_v - vars->y_now) / sin(angle);
}

int ft_draw(t_vars *vars)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	double PI = 3.141592653589793238462203383279502884197;
	mlx_clear_window(vars->mlx, vars->mlx_win);
	vars->main_image.img = mlx_new_image(vars->mlx,vars->width_window,vars->height_window);
	vars->main_image.addr = mlx_get_data_addr(vars->main_image.img, &vars->main_image.bits_per_pixel, &vars->main_image.line_length,&vars->main_image.endian);
	
	while (vars->store_map[i] != NULL)
	{
		j = 0;
		while (vars->store_map[i][j])
		{
			if (vars->store_map[i][j] == '1' && vars->map == 1)
			{
				x = 0;
				while (x <= (vars->size))
				{
					y = 0;
					while (y <= (vars->height_window/14))
					{
						my_mlx_pixel_put(&vars->main_image,x,y,create_trgb(0, 218, 160, 109));
						y++;
					}
					x++;
				}
				
			}
			if (j == (int)vars->x_now / (vars->size) && i == (int)vars->y_now /  (vars->height_window/14) )
			{
				x = 0;
				y = 0;
				int offset;
				int r = 0;
				r = 0;
				 double p_d = ((vars->width_window)/2)/tan(30*(PI/180));
				 double angle = -30;
				double pas = 60.0/vars->width_window;
				
				while (r < (vars->width_window) )
				{
					check_hor(vars, vars->deriction + angle*(PI/180));
					check_vertical(vars, vars->deriction + angle*(PI/180));
					if (vars->plane_des_h >= vars->plane_des_v)
					{
						vars->plane_des_v = vars->plane_des_v*cos(angle*(PI/180));
						vars->plane_height = ((vars->height_window/14)/vars->plane_des_v)*p_d;
						if(cos(vars->deriction + angle*(PI/180)) < 0)
						{
							offset = (int)((1-(fmod(vars->plane_y_v,64) / 64)) * 512);
					  		ber(vars,r,((vars->height_window)/2 - (vars->plane_height)/2) ,r,(vars->height_window)/2 + (vars->plane_height)/2,offset);
						}
						else
						{
							offset = (int)((( fmod(vars->plane_y_v,64)) / 64) * 512);
							ber(vars,r,((vars->height_window)/2 - (vars->plane_height)/2) ,r,(vars->height_window)/2 + (vars->plane_height)/2, offset);
						}
					}
					else
					{
						vars->plane_des_h = vars->plane_des_h*cos(angle*(PI/180));
						vars->plane_height = ((vars->height_window/14)/vars->plane_des_h)*p_d;
						if(sin(vars->deriction + angle*(PI/180)) < 0)
						{
							offset = (int)((fmod(vars->plane_x_h,64)/64) * 512)    ;
					  		ber(vars,r,((vars->height_window)/2 - (vars->plane_height)/2) ,r,(vars->height_window)/2 + (vars->plane_height)/2, offset);
						}
						else
						{
							offset = (int)((1 - (fmod(vars->plane_x_h,64)/64))*512);
							ber(vars,r,((vars->height_window)/2 - (vars->plane_height)/2) ,r,(vars->height_window)/2 + (vars->plane_height)/2, offset);
						}
					}

					ber_c(vars,r,0 ,r,(vars->height_window)/2 - (vars->plane_height)/2);
					ber_floor(vars,r,(vars->height_window)/2 + (vars->plane_height)/2 ,r,vars->height_window);
					angle += pas;
					  r++;
				}
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx,vars->mlx_win,vars->main_image.img,0,0);
	mlx_destroy_image(vars->mlx,vars->main_image.img);
	
	return (0);
}

int main(int argc, char **argv)
{
	double PI = 3.141592653589793238462203383279502884197;
	t_vars vars;
	vars.map =0;
	vars.store_map = NULL;
	vars.texture = NULL;
	vars.mlx = NULL;
	vars.mlx_win = NULL;




	vars.left = 0;
	vars.right = 0;
	vars.down = 0;
	vars.up = 0;

	if (argc != 2)
		return (write(2, "ERROR :you must enter one argument\n", 35));
	check_file_name(argv[1]);
	vars.map_fd = open(argv[1], O_RDONLY);
	if (vars.map_fd == -1)
		return (write(2, "ERROR : file did not open \n", 28));
	if (parcer_map(&vars) == 0)
	{
		return 0;
	}

	vars.mlx = mlx_init();
	vars.size = 64;
	vars.len_h = 33;
	vars.len_v = 14;
	vars.width_window =33*64;
	vars.height_window = 14*64;
	vars.mlx_win = mlx_new_window(vars.mlx,vars.width_window ,vars.height_window, "dd");
	int i = 0;
	int j = 0;
	while (vars.store_map[i])
	{
		j = 0;
		while (vars.store_map[i][j])
		{
			if (vars.store_map[i][j] == 'N')
			{
				vars.x_now = (int)(j * 64 + vars.size/2);
				vars.y_now = (int)(i * 64 + vars.size/2);
				vars.deriction = (3*PI)/2;
			}
			j++;
		}
		i++;
	}
	vars.n_image.img = mlx_xpm_file_to_image(vars.mlx,"hamza.xpm",&vars.n_image.width,&vars.n_image.height);
	printf("%d  %d\n",vars.n_image.width,vars.n_image.height);
	vars.n_image.addr = mlx_get_data_addr(vars.n_image.img, &vars.n_image.bits_per_pixel, &vars.n_image.line_length,&vars.n_image.endian);
	mlx_loop_hook(vars.mlx, ft_draw, &vars);
	ft_draw(&vars);
	mlx_hook(vars.mlx_win, 2,0, key_hook, &vars);
	mlx_hook(vars.mlx_win, 3,0, kk, &vars);
	mlx_loop(vars.mlx);
}