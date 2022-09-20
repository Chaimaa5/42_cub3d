#include "cub3d.h"

void    raycasting(t_cub *data)
{
    int i = 0;
    int j;
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
}

void    wall_projection(t_cub *data)
{
    raycasting(data);
}