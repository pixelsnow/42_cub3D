/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:00 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 09:53:32 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	pos_is_goal(cub3d_t *cub3d)
{
	return (cub3d->level->map[(int)cub3d->player.pos.y][(int)cub3d->player.pos.x] == 'G');
}

void	collision_checker(cub3d_t *cub3d)
{
	dvector_t	delta;
	int			wall;

	delta.x = cub3d->player.new_pos.x - cub3d->player.pos.x;
	delta.y = cub3d->player.new_pos.y - cub3d->player.pos.y;
	wall = find_end_point(cub3d, &cub3d->player,
			cub3d->player.movement_angle, cub3d->player.new_pos);
	if (wall != NO_WALL)
	{
		if (wall == WE || wall == EA)
		{
			if (cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.pos.x] != WALL && !is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.pos.x))
				cub3d->player.pos.y = cub3d->player.new_pos.y;
		}
		else if (wall == NO || wall == SO)
		{
			if (cub3d->level->map[(int)cub3d->player.pos.y][(int)cub3d->player.new_pos.x] != WALL && !is_locked_door(cub3d, (int)cub3d->player.pos.y, (int)cub3d->player.new_pos.x))
				cub3d->player.pos.x = cub3d->player.new_pos.x;
		}
	}
	else
		cub3d->player.pos = cub3d->player.new_pos;
	item_collected_checker(cub3d);
	if (pos_is_goal(cub3d))
	{
		if (cub3d->player.thrown)
			cub3d->level->distractions[cub3d->level->num_distractions].img_distraction->instances[0].enabled = FALSE;
		level_finished(cub3d);
	}
}
