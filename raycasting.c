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
    if (data->map[(int)HorzWallHitY / data->i_2D][(int)HorzWallHitX / data->i_2D] == '1')
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


    // y coordinate of the closet horizontal inter
    data->ray.yinter = floor(data->ypos / data->i_2D) * data->i_2D;
    data->ray.yinter += RayFacingDown ? data->i_2D  : 0;
	//x coordinate of the closet horizontal inter
	data->ray.xinter = data->xpos + (data->ray.yinter - data->xpos) / tan(rayAngle);

	//increment ystep
	data->ray.ystep = data->i_2D;
	//if rayfacing up ystep * -1
    data->ray.ystep *= RayFacingUp ? -1 : 1;
	data->ray.xstep = data->i_2D / tan(rayAngle);
	//if rayfacing left && xstep > 0  xstep * -1
	//if rayfacing right && xstep < 0  xstep * -1
    data->ray.xstep *= (RayFacingLeft && data->ray.xstep > 0) ? -1 : 1;
    data->ray.xstep *= (RayFacingRight && data->ray.xstep < 0) ? -1 : 1;

	double nextHorizxinter = data->ray.xinter;
	double nextHorizyinter = data->ray.yinter;

	//looping until finding wall
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

	//x coordinate of the closet vertical inter
	data->ray.xinter = floor(data->ypos / data->i_2D) * data->i_2D;
	//if rayfacing right +=data->i_2D
    data->ray.xinter += RayFacingRight ? data->i_2D  : 0;
	//y coordinate of the closet vertical inter
	data->ray.yinter = data->ypos + (data->ray.xinter - data->ypos) * tan(rayAngle);

	//ystep
	data->ray.xstep = data->i_2D;
	//if rayfacing left xstep * -1
    data->ray.xstep *= RayFacingLeft ? -1 : 1;
	data->ray.ystep = data->i_2D * tan(rayAngle);
	//if rayfacing up && ystep > 0  xstep * -1
	//if rayfacing down && ystep < 0  xstep * -1
    data->ray.ystep *= (RayFacingLeft && data->ray.ystep > 0) ? -1 : 1;
    data->ray.ystep *= (RayFacingRight && data->ray.ystep < 0) ? -1 : 1;

	double nextVerXinter = data->ray.xinter;
	double nextVerYinter = data->ray.yinter;

	//looping until finding wall
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

	//calculate hor and ver then choose the smallest
	if (data->ray.VerWallHit)
		data->ray.VerWalllDist =  (sqrt(pow(data->ray.VerWallHitX  - data->xpos , 2) + pow(data->ray.VerWallHitY  - data->ypos, 2)));
	else
		data->ray.HorizWalllDist = (sqrt(pow(data->ray.HorizWallHitX  - data->xpos , 2) + pow(data->ray.HorizWallHitY  - data->ypos, 2)));
	// store the smallest
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
        VerticalInter(data, rayAngle);
        HorizontalInter(data, rayAngle);
        WallDistance(data);
		// render_line(data, rayAngle);

}

void    castAllRays(t_cub *data)
{
	int id = 0;
	double rayAngle = data->rotation_angle - (FOV /2);
	while (id < RAYS)
	{
		castRay(data, rayAngle);
		rayAngle += FOV / RAYS;
		id++;
	}
}