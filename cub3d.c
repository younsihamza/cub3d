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

int check_pixel(t_vars *vars, char test)
{
	double i = -5;
	double j;
	while (i < 5)
	{
		j = -5;
		while (j < 5)
		{
			if (test == '+')
			{
				if (vars->store_map[(int)(vars->y_now + j + sin(vars->deriction) * 5) / 20][(int)((vars->x_now + i + cos(vars->deriction) * 5) / 20)] == '1')
					return (-1);
			}
			else if (test == '-')
			{
				if (vars->store_map[(int)(vars->y_now + j - sin(vars->deriction) * 5) / 20][(int)((vars->x_now + i - cos(vars->deriction) * 5) / 20)] == '1')
					return (-1);
			}
			j += 1;
		}
		i += 1;
	}
	return (0);
}


int key_hook(int key, t_vars *vars)
{
	if ((key == 13 || key == 126) && check_pixel(vars, '+') == 0)
	{
		vars->x_now += cos(vars->deriction) * 5;
		vars->y_now += sin(vars->deriction) * 5;
	}
	 if (key == 2 || key == 124)
		vars->deriction += 0.1;
	if (key == 0 || key == 123)
		vars->deriction -= 0.1;
	if ((key == 1 || key == 125) && check_pixel(vars, '-') == 0)
	{
		vars->x_now -= cos(vars->deriction) * 5;
		vars->y_now -= sin(vars->deriction) * 5;
	}
	printf("%d\n",key);
	return (0);
}

int key(int key)
{
	// vars->deriction /= key;
	printf("%d\n",key);
	return (0);
}

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void ber(t_vars *vars, int xi, int yi, int xf, int yf)
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
	printf("%f   %f \n",Xinc,Yinc);
	mlx_pixel_put(vars->mlx, vars->mlx_win, x, y, create_trgb(0, 200, 50, 100));
	while (i <= s)
	{
		mlx_pixel_put(vars->mlx, vars->mlx_win, x, y, create_trgb(0, 200, 50, 100));
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
	yn = (int)(vars->y_now / 20) * 20 + 20;
	if (sin(angle) < 0)
		yn = (int)(vars->y_now / 20) * 20;
	xn = -(vars->y_now - yn) / tan(angle) + vars->x_now;
	v.xa = xn;
	v.ya = yn;
	ystep = +20;
	if (sin(angle) < 0)
	{
		ystep = -20;
		offset = -1;
	}
	xstep = ystep / tan(angle);
	while (v.ya / 20 >= 0 && v.ya / 20 <= 13 && v.xa / 20 >= 0 && 33 >= v.xa / 20 && vars->store_map[(int)(v.ya + offset) / 20][(int)(v.xa) / 20] != '1')
	{
		v.xa += xstep;
		v.ya += ystep;
	}
	v.des = (v.ya - vars->y_now) / sin(angle);
	return (v);
}

t_v check_vertical(t_vars *vars, double angle)
{
	t_v v;
	double yn;
	double xn;
	double xstep = 0;
	double ystep = 0;
	int offset = 0;
	xn = (int)(vars->x_now / 20) * 20;
	if (cos(angle) > 0)
		xn = (int)(vars->x_now / 20) * 20 + 20;

	yn = vars->y_now - tan(angle) * (vars->x_now - xn);

	v.xa = xn;
	v.ya = yn;
	xstep = 20;
	if (cos(angle) < 0)
	{
		xstep = -20;
		offset = -1;
	}
	ystep = tan(angle) * xstep;
	while (v.ya / 20 >= 0 && v.ya / 20 <= 13 && v.xa / 20 >= 0 && 33 >= v.xa / 20 && vars->store_map[(int)(v.ya) / 20][(int)(v.xa + offset) / 20] != '1')
	{
		v.xa += xstep;
		v.ya += ystep;
	}
	v.des = (v.ya - vars->y_now) / sin(angle);
	return v;
}

int ft_draw(t_vars *vars)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	double PI = 3.141592653589793238462643383279502884197;
	mlx_clear_window(vars->mlx, vars->mlx_win);
	while (vars->store_map[i] != NULL)
	{
		j = 0;
		while (vars->store_map[i][j])
		{
			if (vars->store_map[i][j] == '1')
			{
				x = 0;
				while (x <= 20)
				{
					y = 0;
					while (y <= 20)
					{

						mlx_pixel_put(vars->mlx, vars->mlx_win, j * 20 + x, i * 20 + y, create_trgb(0, 100, 100, 100));
						y++;
					}
					x++;
				}
				
			}
			if (j == (int)vars->x_now / 20 && i == (int)vars->y_now / 20)
			{
				double on = 0;
				x = 0;
				y = 0;
				t_v v;
				// printf()
				on = -30 * (PI / 180);
				while (on <= 30 * (PI / 180))
				{

					v = check_hor(vars, vars->deriction + on);
					t_v g = check_vertical(vars, vars->deriction + on);
					if (v.des > g.des)
						ber(vars, vars->x_now, vars->y_now, g.xa, g.ya);
					else
						ber(vars, vars->x_now, vars->y_now, v.xa, v.ya);

					on += (PI / 1000);
				}
				x = -5;
				int f = 0;
				while (x <= 5)
				{
					y = -5;
					while (y <= 5)
					{
						mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now + x, vars->y_now + y, create_trgb(0, 20, 20, 100));
						y++;
					}
					while (f < 10)
					{
						mlx_pixel_put(vars->mlx, vars->mlx_win, vars->x_now + cos(vars->deriction) * f, vars->y_now + sin(vars->deriction) * f, create_trgb(0, 20, 20, 100));
						f++;
					}
					x++;
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	double PI = 3.141592653589793238462643383279502884197;
	t_vars vars;
	vars.store_map = NULL;
	vars.texture = NULL;
	vars.mlx = NULL;
	vars.mlx_win = NULL;
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
	vars.mlx_win = mlx_new_window(vars.mlx, 33 * 20, 14 * 20, "unrecorded");
	//   ft_draw(&vars);
	int i = 0;
	int j = 0;
	while (vars.store_map[i])
	{
		j = 0;
		while (vars.store_map[i][j])
		{
			if (vars.store_map[i][j] == 'N')
			{
				vars.x_now = (j * 20 + 10);
				vars.y_now = (i * 20 + 10);
				vars.deriction = (3*PI)/2;
			}
			j++;
		}
		i++;
	}
	mlx_loop_hook(vars.mlx, ft_draw, &vars);
	mlx_hook(vars.mlx_win, 2, 1L << 0, key_hook, &vars);
	//mlx_hook(vars.mlx_win, 6, 1L << 0, key, &vars);
	//mlx_mouse_hook(vars.mlx_win,mouse,&vars);
	mlx_loop(vars.mlx);
}