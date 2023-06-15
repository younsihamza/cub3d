#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
#include     <mlx.h>
#include <stdio.h> 
 #include <fcntl.h>
//  #include <MLX42/MLX42.h>
 #include <math.h>



typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int height;
    int width;
}	t_data;

typedef struct vars{
    int size;
    void	*mlx;
    void  *mlx_win;
	char ***texture;
    char **store_map;
    int   map_fd;
    double x_now;
    double y_now;
    double deriction;
    int len_h;
    int len_v;
    void *wind2;
    int width_window;
    int height_window;
    int map;
    int key;
    int left;
    int up;
    int down;
    t_data n_image;
    t_data s_image;
    t_data e_image;
    t_data w_image;
    t_data main_image;
    int right;
    double plane_height;
    double plane_x_v;
    double plane_y_v;
    double plane_des_v;
    double plane_x_h;
    double plane_y_h;
    double plane_des_h;
    int speed;
    int pas;
} t_vars;
size_t	found_nl(const char *str, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t number, size_t size);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
int	    ft_atoi(const char *nptr);
int parcer_map(t_vars *vs);
size_t	ft_strlen(char const *p);
int search(char *str,char n);
int ft_strcmp(char *str1, char *str2);
int	ft_strncmp( const char *str1, const char *str2, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
int	ft_strlen2d(char **s1);
void	ft_bzero(void *s, size_t n);
char	**ft_join2d(char **env, char *var);
char	*ft_itoa(int n);
int ft_draw(t_vars *vars);
#endif