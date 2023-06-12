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
				if (vars->store_map[(int)(vars->y_now + i + sin_value ) / (vars->height_window/14)][(int)((vars->x_now + j + cos_value) / (vars->width_window/33 ))] == '1')
					return (-1);
			j += 1;
		}
		i += 1;
	}
	return (0);
}


int key_hook(int key,double k, t_vars *vars)
{
	//printf("%d\n",)
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
		// vars->deriction += 0.1;
		vars->x_now += cos(vars->deriction+(PI/2)) * 10;
		vars->y_now += sin(vars->deriction+(PI/2)) * 10;
		ft_draw(vars);
	 }
	if ((key == 0 ||vars->left == 1) && check_pixel(vars, sin(vars->deriction-(PI/2)) * 10,cos(vars->deriction-(PI/2)) * 10) == 0)
	{
		vars->left = 1;
		//vars->deriction -= 0.1;
		vars->x_now += cos(vars->deriction-(PI/2)) * 10;
		vars->y_now += sin(vars->deriction-(PI/2)) * 10;
		//vars->y_now -= cos(vars->deriction+(PI/2)) * 5;
		ft_draw(vars);
	}
	if (((key == 1 )||vars->down == 1) && check_pixel(vars, sin(vars->deriction) * 10,cos(vars->deriction) * 10) == 0)
	{
		vars->down = 1;
		vars->x_now -= cos(vars->deriction) * 10;
		vars->y_now -= sin(vars->deriction) * 10;
		ft_draw(vars);
	}
	
	//printf("%d  %f \n",key,k);
	return (0);
}

// int key(int key)
// {
// 	// vars->deriction /= key;
// 	//printf("%d\n",key);
// 	return (0);
// }

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
		mlx_pixel_put(vars->mlx, vars->mlx_win, x, y, create_trgb(0, 135, 206, 235));
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
		mlx_pixel_put(vars->mlx, vars->mlx_win, x, y, create_trgb(0, 218, 160, 109));
		x += Xinc;
		y += Yinc;
		i++;
	}
}

void ber(t_vars *vars, double xi, double yi, double xf, double yf, int color)
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
		// if(x < 0 || y < 0)
		// 	printf("hamza\n");
		//mlx_pixel_put(vars->mlx, vars->mlx_win, x, y, color);
		my_mlx_pixel_put(&vars->main_image,x,y,color);
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

t_v check_hor(t_vars *vars, double angle)
{
	t_v v;
	double yn;
	double xn;
	double xstep = 0;
	double ystep = 0;
	int offset = 0;
	yn = (int)(vars->y_now / (vars->height_window/14)) * (vars->height_window/14) + (vars->height_window/14);
	if (sin(angle) < 0)
		yn = (int)(vars->y_now / (vars->height_window/14)) * (vars->height_window/14);
	xn = -(vars->y_now - yn) / tan(angle) + vars->x_now;
	v.xa = xn;
	v.ya = yn;
	ystep = vars->width_window/33;
	if (sin(angle) < 0)
	{
		ystep = -vars->width_window/33;
		offset = -1;
	}
	xstep = ystep / tan(angle);
	while ((v.ya + offset) / 64 > 0 && (v.ya + offset) / 64 <= 13  && v.xa / 64 > 0 && ft_strlen(vars->store_map[(int)(v.ya + offset) / 64]) > v.xa / 64 && vars->store_map[(int)(v.ya +offset) / 64][(int)(v.xa) / 64] != '1')
	{
		
		v.xa += xstep;
		v.ya += ystep;
	}

	// v.des = (v.ya - vars->y_now) / sin(angle);
	v.des = sqrt(pow(((v.xa - vars->x_now)) ,2) + pow(((v.ya -vars->y_now)),2));
	//printf("h =%f\n",v.des);
	return (v);
}
int kk(int key ,t_vars *vars)
{
	//printf("hamza\n");
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
t_v check_vertical(t_vars *vars, double angle)
{
	t_v v;
	double yn;
	double xn;
	double xstep = 0;
	double ystep = 0;
	int offset = 1;
	xn = (int)(vars->x_now / (vars->width_window/33 )) * (vars->width_window/33 );
	if (cos(angle) > 0)
		xn = (int)(vars->x_now / (vars->width_window/33 )) * (vars->width_window/33 ) + (vars->width_window/33 );
	yn = vars->y_now - tan(angle) * (vars->x_now - xn);
	v.xa = xn;
	v.ya = yn;
	xstep = (vars->width_window/33 );
	if (cos(angle) < 0)
	{
		xstep = -(vars->width_window/33 );
		offset = -1;
	}
	ystep = tan(angle) * xstep;
	
	while (v.ya / 64 >= 0 && (int)(v.ya / 64) <= 13 && v.xa / 64 >= 0 && ft_strlen(vars->store_map[(int)v.ya / 64]) >= v.xa / 64 && vars->store_map[(int)(v.ya) / 64][(int)(v.xa + offset) / 64] != '1')
	{
		v.xa += xstep;
		v.ya += ystep;
	}
	v.des = sqrt(pow((v.xa - vars->x_now) ,2) + pow((v.ya -vars->y_now),2));
	//printf("v =%f\n",v.des);
	return v;
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
				while (x <= (vars->width_window/33))
				{
					y = 0;
					while (y <= (vars->height_window/14))
					{

						mlx_pixel_put(vars->mlx, vars->mlx_win, j * (vars->height_window/14) + x, i * (vars->width_window/33) + y, create_trgb(0, 150, 251, 20));
						y++;
					}
					x++;
				}
				
			}
			if (j == (int)vars->x_now / (vars->width_window/33) && i == (int)vars->y_now /  (vars->height_window/14) )
			{
				double on = 0;
				x = 0;
				y = 0;
				t_v v;
				t_v g;
				double  plane;
				int r = 0;
				r = 0;
				// printf()
				on = -30 ;
				 double p_d = ((vars->width_window)/2)/tan(30*(PI/180));
				 double angle = -30;
				//  double angle_of_each =(60/(vars->width_window));

				//  printf("%f\n",number_ray);
				// double pas = 60/number_ray;
				
				while (r < (vars->width_window) )
				{
					v = check_hor(vars, vars->deriction + angle*(PI/180));
					g = check_vertical(vars, vars->deriction + angle*(PI/180));
					if (v.des >= g.des)
					{
						if(vars->map == 1)
							{
								if(cos(vars->deriction + angle*(PI/180))< 0)
								ber(vars, vars->x_now, vars->y_now, g.xa, g.ya,create_trgb(0, 159, 226, 191));
							else
								ber(vars, vars->x_now, vars->y_now, g.xa, g.ya,create_trgb(0, 150, 50, 191));
							}
						g.des = g.des*cos(angle*(PI/180));
						plane = ((vars->height_window/14)/g.des)*p_d;
						if(plane > vars->height_window)
						 plane = vars->height_window;
					if(plane < -vars->height_window)
						plane = -vars->height_window;
						if(vars->map == 0)
					 {
						if(cos(vars->deriction + angle*(PI/180))< 0)
					  		ber(vars,r,(int)((vars->height_window)/2 - (plane)/2) ,r,(vars->height_window)/2 + (plane)/2,274795);
						else
							ber(vars,r,(int)((vars->height_window)/2 - (plane)/2) ,r,(vars->height_window)/2 + (plane)/2,create_trgb(0, 150, 50, 191));
					  }
					}
					else
					{
						if(vars->map == 1)
						{
							if(sin(vars->deriction + angle*(PI/180))< 0)
							{
								ber(vars, vars->x_now, vars->y_now, v.xa, v.ya,create_trgb(0, 255, 127, 80));
							}
							else
								ber(vars, vars->x_now, vars->y_now, v.xa, v.ya,create_trgb(0, 255, 50, 80));

						}
						v.des = v.des*cos(angle*(PI/180));
						// if(plane )
						//printf("angle = %f\n",angle);
						plane = ((vars->height_window/14)/v.des)*p_d;
						if(plane > vars->height_window)
						 plane = vars->height_window;
						if(plane < -vars->height_window)
						plane = -vars->height_window;
						if(vars->map == 0)
					 {
						if(sin(vars->deriction + angle*(PI/180)) < 0)
					  		ber(vars,r,(int)((vars->height_window)/2 - (plane)/2) ,r,(vars->height_window)/2 + (plane)/2,create_trgb(0, 255, 127, 80));
						else
							ber(vars,r,(int)((vars->height_window)/2 - (plane)/2) ,r,(vars->height_window)/2 + (plane)/2,create_trgb(0, 255, 50, 80));
					  }
					}
					//printf("color = %d\n",create_trgb(0, 150, 255, 6511));
					if(plane > vars->height_window)
						 plane = vars->height_window;
					if(plane < -vars->height_window)
						plane = -vars->height_window;
					// if(v.des< 1||g.des<1)
					// // //printf("%f  %f\n",(1080/2) - (plane / 2),plane);
					// if(vars->map == 0)
					//  {ber_c(vars,r,0 ,r+1,(vars->height_window)/2 - (plane)/2);
					//  // ber(vars,r,(int)((vars->height_window)/2 - (plane)/2) ,r,(vars->height_window)/2 + (plane)/2,create_trgb(0, 255, 50, 80));
					//   ber_floor(vars,r,(vars->height_window)/2 + (plane)/2 ,r,vars->height_window);
					//   }
					  //printf("==%f\n",(13*20)/2 - (plane)/2);
					  //printf("plane = %f\n",plane);
					//  printf("r =%d\n",r);
					angle += 0.0284;
					//printf("%f\n",angle_of_each);
					  r++;
				}
				// x = -5;
				// int f = 0;
				// while (x <= 5)
				// {
				// 	y = -5;
				// 	while (y <= 5)
				// 	{
				// 		//mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now + x, vars->y_now + y, create_trgb(0, 20, 20, 20));
				// 		y++;
				// 	}
				// 	while (f < 10)
				// 	{
				// 		mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now + cos(vars->deriction) * f, vars->y_now + sin(vars->deriction) * f, create_trgb(0, 20, 20, 20));
				// 		f++;
				// 	}
				// 	x++;
				// }
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
	vars.width_window =33*64;
	vars.height_window = 14*64;
	vars.mlx_win = mlx_new_window(vars.mlx,vars.width_window ,vars.height_window, "dd");
	//   ft_draw(&vars);
	int i = 0;
	int j = 0;
	//void *image;
	// while(vars.store_map[i])
	// {
	// 	printf("%s\n",vars.store_map[i++]);
	// }
	while (vars.store_map[i])
	{
		j = 0;
		while (vars.store_map[i][j])
		{
			if (vars.store_map[i][j] == 'N')
			{
				vars.x_now = (j * vars.width_window/33 );
				vars.y_now = (i * vars.height_window/14 );
				vars.deriction = (3*PI)/2;
			}
			j++;
		}
		i++;
	}
	mlx_loop_hook(vars.mlx, ft_draw, &vars);
	ft_draw(&vars);
	mlx_hook(vars.mlx_win, 2,0, key_hook, &vars);
	mlx_hook(vars.mlx_win, 3,0, kk, &vars);
	vars.n_image.img = mlx_xpm_file_to_image(vars.mlx,"hamza.xpm",&vars.n_image.width,&vars.n_image.height);

	//mlx_hook(vars.mlx_win, 6, 1L << 0, key, &vars);
	//mlx_mouse_hook(vars.mlx_win,mouse,&vars);
	mlx_loop(vars.mlx);
}