#include "../incl/cub3d.h"

void collision_checker(cub3d_t *cub3d)
{
	dvector_t delta;
	int wall;

	if (cub3d->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.new_pos.x] == WALL)
	{
		delta.x = cub3d->player.new_pos.x - cub3d->player.pos.x;
		delta.y = cub3d->player.new_pos.y - cub3d->player.pos.y;
		wall = find_end_point(cub3d, &cub3d->player, cub3d->player.angle, &cub3d->player.new_pos);
		if (wall == WE || wall == EA)
		{
			cub3d->player.new_pos.y = cub3d->player.pos.y + delta.y;
			if (cub3d->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.pos.x] != WALL)
				cub3d->player.pos.y = cub3d->player.new_pos.y;
		}
		else if (wall == NO || wall == SO)
		{
			cub3d->player.new_pos.x = cub3d->player.pos.x + delta.x;
			if (cub3d->map[(int)cub3d->player.pos.y][(int)cub3d->player.new_pos.x] != WALL)
				cub3d->player.pos.x = cub3d->player.new_pos.x;
		}
	}
	else
		cub3d->player.pos = cub3d->player.new_pos;
}