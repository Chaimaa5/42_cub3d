#include "cub3d.h"

int direction(t_cub *data)
{
    int dir;

    if(data->map[(((int)data->pixelY + 1) / data->i_2D)][((int)data->pixelX / data->i_2D)] == '0')
        dir = 1;
    if(data->map[((int)data->pixelY / data->i_2D)][(((int)data->pixelX + 1) / data->i_2D)] == '0')
        dir = 2;
    if(data->map[(((int)data->pixelY - 1) / data->i_2D)][((int)data->pixelX / data->i_2D)] == '0')
        dir = 3;
    if(data->map[((int)data->pixelY / data->i_2D)][(((int)data->pixelX - 1) / data->i_2D)] == '0')
        dir = 4;
    return(dir);
}

void    wall_projection(t_cub *data, int i, int j)
{
    if (direction(data) == 1)
        pixel_put(&data->img_3D, i, j, 0xE0AC69);
    if (direction(data) == 2)
        pixel_put(&data->img_3D, i, j, 0xE0AC69);
    if (direction(data) == 3)
        pixel_put(&data->img_3D, i, j, 0xF1C27D);
    if (direction(data) == 4)
        pixel_put(&data->img_3D, i, j, 0xFFDBAC);
}

void    raycasting(t_cub *data)
{
    int i;
    int j;
    double x ;
    
    i = 0;
    x = -32;
    while (i < WINDOW_WIDTH )
    {
        j = 0;
        if ( x < 32 )
            render_line(data, (data->xpos + cos(data->rotation_angle + x) * 1000) - data->xpos, (data->ypos + sin(data->rotation_angle + x) * 1000) - data->ypos, data->rotation_angle + x);
        while(j < WINDOW_HEIGHT )
        {
            if (j < (WINDOW_HEIGHT - data->wall)  / 2)
                pixel_put(&data->img_3D, i, j, 0xFFFFFF);
            else if (j < ((WINDOW_HEIGHT - data->wall) / 2) + data->wall)
                wall_projection(data, i, j);
            else
                pixel_put(&data->img_3D, i, j, 0x8D5524);
            j++;
        }
        i++;
        x+= 1 / (WINDOW_WIDTH / 50);
    }
}
