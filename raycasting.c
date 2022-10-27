#include "cub3d.h"

int direction(t_cub *data)
{
    if(data->map[(((int)data->pixelY + 1) / data->i_2D)][((int)data->pixelX / data->i_2D)] == '0')
        data->tex.texPos = 1;
    if(data->map[((int)data->pixelY / data->i_2D)][(((int)data->pixelX + 1) / data->i_2D)] == '0')
        data->tex.texPos = 2;    
    if(data->map[(((int)data->pixelY - 1) / data->i_2D)][((int)data->pixelX / data->i_2D)] == '0')
        data->tex.texPos = 3;
    if(data->map[((int)data->pixelY / data->i_2D)][(((int)data->pixelX - 1) / data->i_2D)] == '0')
        data->tex.texPos = 4;
    return(data->tex.texPos);
}

void    raycasting(t_cub *data)
{
    int i = 0;
    int j;
    double x  = -32;
    double r = data->rotation_angle;

    while (i < WINDOW_WIDTH )
    {
        if(x <= 32)
            render_line(data, (data->xpos + cos(r + x) * 1000) - data->xpos,
                (data->ypos +  sin(r + x) * 1000) - data->ypos, 0xF96dFF, 0, r+x);
        j = 0;
        while(j < WINDOW_HEIGHT)
        {
            if (direction(data) == 1 || direction(data) == 3)
                data->tex.texX = fmod(data->pixelX / 50, 1) * 50;
            if (direction(data) == 2 || direction(data) == 4)
                data->tex.texX = fmod(data->pixelY / 50, 1) * 50;
            data->tex.texY = ((j - ((WINDOW_HEIGHT - data->wall) / 2)) * 50) / data->wall;
            if (j < (WINDOW_HEIGHT - data->wall) / 2)
                pixel_put(&data->img_3D, i, j, 0xFFFFFF);
            else if (j < ((WINDOW_HEIGHT - data->wall) / 2) + data->wall)
                pixel_put(&data->img_3D, i, j, get_pixel_color(&data->tex));
            else
                pixel_put(&data->img_3D, i, j, 0x8D5524);
            j++;
        }
        i++;
        x+= (64 * (PI / 180)) / WINDOW_WIDTH;
    }
}
