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


// while(column < width)
    //cast a ray
    //trace a ray until intersection
    //record intersection x,y and distance
    // increment angle +=60/windowwidth

void    castAllRays(t_cub *data)
{
	int id = 0;
	double rayAngle = data->rotation_angle - (FOV /2);
	double numray = WINDOW_WIDTH / data->i_2D;
	while (id < numray)
	{
		// render_line(data->xpos, data->ypos, data->xpos + cos(rayAngle) * 30,  data->ypos + sin(rayAngle) * 30)
		rayAngle += FOV / numray;
		id++;
	}
}

double	normalizeangle(t_cub *data)
{
	angle = angle % (2 * PI);
	if (angle < 0)
		anglw= angle + (2 * PI);
	}
	return (angle);
}

//raydow  rayangle > 0 && rayangle < PI
//rayright rayangle < 0.5 * PI || rayangle > 1.5 * PI
void raycasting(int id)
{
	double xinter, yinter, xstep,ystep;

	//y coordinate of the closet horizontal inter
	yinter = floor(data->ypos / data->i_2d) * data->i_2D;
	//x coordinate of the closet horizontal inter
	xinter = data->xpos + (yinter - data->xpos) / tan(ray_angle);

	//ystep
	ystep = data->i_2D;
	//if rayfacing up ystep * -1
	xstep = data->i_2D / tan(ray_angle);
	//if rayfacing left && xstep > 0  xstep * -1
	//if rayfacing right && xstep < 0  xstep * -1

	double nextHorizxinter = xinter;
	double nextHorizyinter = yinter;

	//looping until finding wall
	while(nextHorizxinter >= 0 && nextHorizyinter >= 0 && nextHorizxinter <= WINDOW_WIDTH && nextHorizyinter <= WINDOW_HEIGHT)
	{
		if (hitwall(nextHorizxinter, nextHorizyinter))
		{
			horwallhitx = nextHorizxinter;
			horwallhity = nextHorizyinter
			break;
		}
		else
			nextHorizxinter += xstep;
			nextHorizyinter += ystep;
	}

	//x coordinate of the closet vertical inter
	xinter = floor(data->ypos / data->i_2d) * data->i_2D;
	//if rayfacing right +=data->i_2D
	//y coordinate of the closet vertical inter
	yinter = data->ypos + (xinter - data->ypos) * tan(ray_angle);

	//ystep
	xstep = data->i_2D;
	//if rayfacing left ystep * -1
	ystep = data->i_2D * tan(ray_angle);
	//if rayfacing up && ystep > 0  xstep * -1
	//if rayfacing down && ystep < 0  xstep * -1

	double nextverxinter = xinter;
	double nextveryinter = yinter;

	//looping until finding wall
	while(nextverxinter >= 0 && nextveryinter >= 0 && nextverxinter <= WINDOW_WIDTH && nextveryinter <= WINDOW_HEIGHT)
	{
		if (hitwall(nextverxinter, nextveryinter))
		{
			vertical_hit = true;
			verwallhitx = nextverxinter;
			verwallhity = nextveryinter
			break;
		}
		else
			nextverxinter += xstep;
			nextveryinter += ystep;
	}

	//calculate hor and ver then choose the smallest
	if (vertical_hitt)
		verdist =  (sqrt(pow(verwallhitx  - data->xpos , 2) + pow(verwallhity  - data->ypos, 2)));
	else
		hordistance = (sqrt(pow(horwallhitx  - data->xpos , 2) + pow(horwallhity  - data->ypos, 2)));
	// store the smallest
	if (hordistance < verdist)
		{
			wallxhit = horwallhitx
			wallyhit = horwallhity
		}
	else 
		wallxhit = verwallhitx
			wallyhit = verwallhity

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
        if ( x <= 32 )
            render_line(data, (data->xpos + cos(data->rotation_angle + x) * 1000), (data->ypos + sin(data->rotation_angle + x) * 1000), data->rotation_angle + x);
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
        x+=  0.0005;
    }
}
