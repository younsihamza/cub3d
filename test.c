#include <mlx.h>
#include <stdio.h>

typedef struct v{
    void *mlx;
    void *mlx_win;
}t_vars;
int draw(t_vars *vars)
{
    int i = 300/2;
    int j = 0;
    while(i < 300/2 +10)
    {
        j = 200/2 - 30;
        while(j < 200/2 +30)
        {
            mlx_pixel_put(vars->mlx,vars->mlx_win,i,j,214);
            j++;
        }
        i++;
    }
    return(0);
}
int main()
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.mlx_win = mlx_new_window(vars.mlx,300,200,"test");

    mlx_loop_hook(vars.mlx,draw,&vars);
    mlx_loop(vars.mlx);
}