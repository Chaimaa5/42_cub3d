#include "cub3d.h"

float	normalizeAngle(float rayAngle)
{
	rayAngle = remainder(rayAngle, 2 * PI);
	if (rayAngle < 0)
		rayAngle = rayAngle + (2 * PI);
	return (rayAngle);
}

int HitWall(t_cub *data, float X, float Y)
{
	if (X < 0 || Y < 0 || X > WINDOW_WIDTH || Y > WINDOW_HEIGHT)
		return (0);
	if (data->map[(int)floor(Y / data->i_2D)][(int)floor(X / data->i_2D)] == '1')
		return(0);
	return(1);
}

int	FacingUporDown(float Angle)
{
	if (Angle > 0 && Angle < PI)
	 	return(DOWN);
	return (UP);
}


int	FacingLeftorRight(float Angle)
{
	if (Angle < 0.5 * PI || Angle > 1.5 * PI)
	 	return(RIGHT);
	return (LEFT);
}

void    HorizontalInter(t_cub *data, float rayAngle)
{
    data->ray.yinter = floor(data->ypos / data->i_2D) * data->i_2D;
	if (FacingUporDown(rayAngle) == DOWN)
    	data->ray.yinter += data->i_2D;
	data->ray.xinter = data->xpos + (data->ray.yinter - data->ypos) / tan(rayAngle);

	data->ray.ystep = data->i_2D;
	if (FacingUporDown(rayAngle) == UP)
    	data->ray.ystep *= -1;
	data->ray.xstep = data->i_2D / tan(rayAngle);
	if (FacingLeftorRight(rayAngle) == LEFT && data->ray.xstep > 0)
    	data->ray.xstep *=  -1;
	else if (FacingLeftorRight(rayAngle) == RIGHT && data->ray.xstep < 0)
    data->ray.xstep *=  -1;

	float nextHorizxinter = data->ray.xinter;
	float nextHorizyinter = data->ray.yinter;

	while(nextHorizxinter >= 0 && nextHorizyinter >= 0 && nextHorizxinter <= WINDOW_WIDTH && nextHorizyinter <= WINDOW_HEIGHT)
	{
        float xCheck = nextHorizxinter;
        float yCheck = nextHorizyinter;
		if (FacingUporDown(rayAngle) == UP)
			yCheck = yCheck - 1;
		if (data->ray.HorizWallHit == 1 || yCheck > WINDOW_HEIGHT || xCheck > WINDOW_WIDTH)
			break;
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



void    VerticalInter(t_cub *data, float rayAngle)
{
	data->ray.xinter = floor(data->xpos / data->i_2D) * data->i_2D;
	if (FacingUporDown(rayAngle) == RIGHT)
    	data->ray.xinter += data->i_2D;
	data->ray.yinter = data->ypos + (data->ray.xinter - data->xpos) * tan(rayAngle);

	data->ray.xstep = data->i_2D;
	if (FacingLeftorRight(rayAngle) == LEFT)
    	data->ray.xstep *= -1;
	data->ray.ystep = data->i_2D * tan(rayAngle);
	if (FacingUporDown(rayAngle) == UP &&  data->ray.ystep > 0)
    	data->ray.ystep *= -1;
	else if(FacingUporDown(rayAngle) == DOWN &&  data->ray.ystep < 0)
    	data->ray.ystep *= -1;

	float nextVerXinter = data->ray.xinter;
	float nextVerYinter = data->ray.yinter;

	while(nextVerXinter >= 0 && nextVerYinter >= 0 && nextVerXinter <= WINDOW_WIDTH && nextVerYinter <= WINDOW_HEIGHT)
	{
        float yCheck = nextVerYinter;
        float xCheck = nextVerXinter;
		if (FacingLeftorRight(rayAngle) == LEFT)
			xCheck = xCheck - 1;
		if (data->ray.VerWallHit == 1 || yCheck > WINDOW_HEIGHT || xCheck > WINDOW_WIDTH)
			break;
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
	data->ray.VerWalllDist =  (sqrt(pow(data->ray.VerWallHitX  - data->xpos , 2) + pow(data->ray.VerWallHitY  - data->ypos, 2)));
	data->ray.HorizWalllDist = (sqrt(pow(data->ray.HorizWallHitX  - data->xpos , 2) + pow(data->ray.HorizWallHitY  - data->ypos, 2)));
	if (data->ray.HorizWalllDist < data->ray.VerWalllDist && data->ray.HorizWalllDist > 0)
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

void    castRay(t_cub *data, float rayAngle)
{
        HorizontalInter(data, rayAngle);
        VerticalInter(data, rayAngle);
        WallDistance(data);
}

void    castAllRays(t_cub *data)
{
	int id = 0;
	float rayAngle = data->rotation_angle - (FOV /2);
	while (id < RAYS)
	{
		castRay(data, normalizeAngle(rayAngle));
		render_line(data, normalizeAngle(rayAngle));
		rayAngle += FOV / RAYS;
		id++;
	}

}