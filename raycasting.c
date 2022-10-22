#include "cub3d.h"

double	normalizeAngle(double rayAngle)
{
	rayAngle = remainder(rayAngle, 2 * PI);
	if (rayAngle < 0)
		rayAngle = rayAngle + (2 * PI);
	return (rayAngle);
}

int HitWall(t_cub *data, double HorzWallHitX, double HorzWallHitY)
{
    if (data->map[(int)floor(HorzWallHitY / data->i_2D)][(int)floor(HorzWallHitX / data->i_2D)] == '1')
		return(0);
	return(1);
}

void    HorizontalInter(t_cub *data, double rayAngle)
{
    rayAngle = normalizeAngle(rayAngle);
    int RayFacingDown = rayAngle > 0 && rayAngle < PI;
    int RayFacingUp = !RayFacingDown;
    int RayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int RayFacingLeft = !RayFacingRight;


    data->ray.yinter = floor(data->ypos / data->i_2D) * data->i_2D;
    data->ray.yinter += RayFacingDown ? data->i_2D  : 0;
	data->ray.xinter = data->xpos + (data->ray.yinter - data->xpos) / tan(rayAngle);

	data->ray.ystep = data->i_2D;
    data->ray.ystep *= RayFacingUp ? -1 : 1;
	data->ray.xstep = data->i_2D / tan(rayAngle);
    data->ray.xstep *= (RayFacingLeft && data->ray.xstep > 0) ? -1 : 1;
    data->ray.xstep *= (RayFacingRight && data->ray.xstep < 0) ? -1 : 1;

	double nextHorizxinter = data->ray.xinter;
	double nextHorizyinter = data->ray.yinter;

	while(nextHorizxinter >= 0 && nextHorizyinter >= 0 && nextHorizxinter <= WINDOW_WIDTH && nextHorizyinter <= WINDOW_HEIGHT)
	{
        double xCheck = nextHorizxinter;
        double yCheck = nextHorizyinter + (RayFacingUp ? -1 : 0);
		if (HitWall(data, xCheck, yCheck))
		{
			data->ray.HorizWallHitX = nextHorizxinter;
			data->ray.HorizWallHitY = nextHorizyinter;
            //horizcontent = map[(int)ytocheck / i2d][(int)xcheck / i2d];
            data->ray.HorizWallHit = 1;
			break;
		}
		else
        {
			nextHorizxinter += data->ray.xstep;
			nextHorizyinter += data->ray.ystep;
        }
    }
}

void    VerticalInter(t_cub *data, double rayAngle)
{
    rayAngle = normalizeAngle(rayAngle);
    int RayFacingDown = rayAngle > 0 && rayAngle < PI;
    int RayFacingUp = !RayFacingDown;
    int RayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int RayFacingLeft = !RayFacingRight;

	data->ray.xinter = floor(data->ypos / data->i_2D) * data->i_2D;
    data->ray.xinter += RayFacingRight ? data->i_2D  : 0;
	data->ray.yinter = data->ypos + (data->ray.xinter - data->ypos) * tan(rayAngle);

	data->ray.xstep = data->i_2D;
    data->ray.xstep *= RayFacingLeft ? -1 : 1;
	data->ray.ystep = data->i_2D * tan(rayAngle);
    data->ray.ystep *= (RayFacingLeft && data->ray.ystep > 0) ? -1 : 1;
    data->ray.ystep *= (RayFacingRight && data->ray.ystep < 0) ? -1 : 1;

	double nextVerXinter = data->ray.xinter;
	double nextVerYinter = data->ray.yinter;

	while(nextVerXinter >= 0 && nextVerYinter >= 0 && nextVerXinter <= WINDOW_WIDTH && nextVerYinter <= WINDOW_HEIGHT)
	{
        double yCheck = nextVerYinter;
        double xCheck = nextVerXinter + (RayFacingUp ? -1 : 0);
		if (HitWall(data, xCheck, yCheck))
		{
			data->ray.VerWallHitX = nextVerXinter;
			data->ray.VerWallHitY = nextVerYinter;
            //horizcontent = map[(int)ytocheck / i2d][(int)xcheck / i2d];
            data->ray.VerWallHit = 1;
			break;
		}
		else
        {
			nextVerXinter += data->ray.xstep;
			nextVerYinter += data->ray.ystep;
        }
	}
}

void    WallDistance(t_cub *data)
{
	if (data->ray.VerWallHit)
		data->ray.VerWalllDist =  (sqrt(pow(data->ray.VerWallHitX  - data->xpos , 2) + pow(data->ray.VerWallHitY  - data->ypos, 2)));
	else
		data->ray.HorizWalllDist = (sqrt(pow(data->ray.HorizWallHitX  - data->xpos , 2) + pow(data->ray.HorizWallHitY  - data->ypos, 2)));
	if (data->ray.HorizWalllDist < data->ray.VerWalllDist)
	{
		data->ray.WallHitX = data->ray.HorizWallHitX;
		data->ray.WallHitY  = data->ray.HorizWallHitY;
	}
	else 
    {
		data->ray.WallHitX  = data->ray.VerWallHitX;
		data->ray.WallHitY = data->ray.VerWallHitX;
    }
}


void    castRay(t_cub *data, double rayAngle)
{
        HorizontalInter(data, rayAngle);
        VerticalInter(data, rayAngle);
        WallDistance(data);
}

void    castAllRays(t_cub *data)
{
	int id = 0;
	double rayAngle = data->rotation_angle - (FOV /2);
	while (id < RAYS)
	{
		castRay(data, rayAngle);
		render_line(data, rayAngle);
		rayAngle += FOV / RAYS;
		id++;
	}

}