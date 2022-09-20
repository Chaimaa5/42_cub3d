#include "cub3d.h"

void    raycasting(t_cub *data)
{
    int i = 0;
    int j;
    double x  = -30;
    while (x < PI / 6)
	{
    while (i < WINDOW_WIDTH)
    {
        j = 0;
        while(j < WINDOW_HEIGHT)
        {
            if (j < (WINDOW_HEIGHT - data->wall)  / 2)
                pixel_put(&data->img_3D, i, j, 0xFFFFFF);
            else
                pixel_put(&data->img_3D, i, j, 0xFFBFFF);
            j++;
        }
        i++;
    }
    x+= 0.05;
    }
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_3D.mlx_img, 0, 0);
}
