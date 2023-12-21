
#include "../incl/cub3d.h"

void	cause_distraction(cub3d_t *cub3d)
{
	ray_t	*ray;

	ray = cast_ray(cub3d);
	cub3d->level->distraction = ray->end;
	cub3d->level->distraction_amount = 10;
	cub3d->player.mushroom_count--;
	printf("caused distraction at pos %f,%f\n",ray->end.x,ray->end.y);
	free(ray);
}


static int	check_angles(cub3d_t *cub3d, int i, double dir_to_distraction)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->enemy[i].angle * 180 / M_PI - 30);
	angle_max = within_360(cub3d->enemy[i].angle * 180 / M_PI + 30);
	if (angle_max < angle_min)
	{
		if (dir_to_distraction > angle_max
			&& dir_to_distraction < angle_min)
			return (1);
	}
	else
	{
		if (dir_to_distraction < angle_min
			|| dir_to_distraction > angle_max)
			return (1);
	}
	return (0);
}

int	distraction(cub3d_t *cub3d, int i)
{
	dvector_t	distraction;
	double		dir_to_distraction;
	double		angle_min;
	double		angle_max;
	double		at_target;

	if (cub3d->level->distraction_amount <= 0)
		return (0);
	distraction = cub3d->level->distraction;
	dir_to_distraction = within_360(atan2(distraction.y
				- cub3d->enemy[i].pos.y, distraction.x
				- cub3d->enemy[i].pos.x) * 180 / M_PI);
	angle_min = within_360(cub3d->enemy[i].angle * 180 / M_PI - 30);
	angle_max = within_360(cub3d->enemy[i].angle * 180 / M_PI + 30);
	at_target = ENEMY_SPEED * (1 + cub3d->settings.e_speed) * 2;
	if (check_angles(cub3d, i, dir_to_distraction))
		return (0);
	else if (enemy_ray_to_distraction(cub3d, distraction, dir_to_distraction, i)
		&& (dist_between_d_vectors(distraction, cub3d->enemy[i].pos)
			> at_target))
		return (1);
	else
		return (0);
}