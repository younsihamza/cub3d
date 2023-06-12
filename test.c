#include <mlx.h>
#include <stdio.h>
#include  <unistd.h>

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
    void *image;
    int x;
    int y;
    int bit;
    int size_line;
    int endian;


    vars.mlx = mlx_init();
    char *a="images.xpm";
    
    vars.mlx_win = mlx_new_window(vars.mlx,1000 ,1000,"yy");
    image = mlx_xpm_file_to_image(vars.mlx,"images.xpm",&x,&y);
    write(2,"hamza\n",6);
     char *mlx_data_addr = mlx_get_data_addr(image,&bit,&size_line,&endian);
     int i = 0;
    //  printf("x = %d y =%d\n",x,y);
     printf("bit = %d size = %d  endian = %d\n",bit, size_line,endian);
     int j = 0;

     while(i < 162)
     {
        //if(i%300 == 0)
            printf("%u\n",*(uint32_t *)(mlx_data_addr+j));
        j += 300;
        i++;
     }
     printf("i = %d\n",i);
    mlx_put_image_to_window(vars.mlx,vars.mlx_win,image,200,200);
    // mlx_loop_hook(vars.mlx,draw,&vars);
    mlx_loop(vars.mlx);
}