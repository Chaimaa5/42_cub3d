#include "cub3d.h"

void    raycasting(t_cub *data)
{
    int i = 0;
    int j;
    double x  = - PI / 6;
    double l = data->rotation_angle;

    while (i < WINDOW_WIDTH)
    {
        j = 0;
        if ( x < PI / 6 && x != 0)
            render_line(data,(data->xpos + cos(l + x) * 1000) - data->xpos,(data->ypos + sin(l + x) * 1000) - data->ypos,  0x40E0D0);
        while(j < WINDOW_HEIGHT)
        {
            if (j < (WINDOW_HEIGHT - data->wall)  / 2)
                pixel_put(&data->img_3D, i, j, 0xFFFFFF);
            else if (j < ((WINDOW_HEIGHT - data->wall)  / 2) + data->wall)
            {
                if(data->pixelX < 0  && data->pixelY > 0)
                    pixel_put(&data->img_3D, i, j, 0xFFBFFF);
                else if(data->pixelX < 0  && data->pixelY < 0)
                    pixel_put(&data->img_3D, i, j, 0xFFB0FF);
                else
                    pixel_put(&data->img_3D, i, j, 0xFFEEFF);
            }
            else
                pixel_put(&data->img_3D, i, j, 0xFFBF000);
            j++;
        }
        i++;
        x+= 0.001;
    }
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_3D.mlx_img, 0, 0);
}
