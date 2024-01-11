/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:59 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 13:30:01 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	delete_textures_additional(cub3d_t *cub3d)
{
	mlx_delete_texture(cub3d->start_menu.title.texture);
	mlx_delete_texture(cub3d->start_menu.exit.texture);
	mlx_delete_texture(cub3d->start_menu.start.texture);
	mlx_delete_texture(cub3d->start_menu.level.texture);
	mlx_delete_texture(cub3d->start_menu.exit_hover.texture);
	mlx_delete_texture(cub3d->start_menu.start_hover.texture);
	mlx_delete_texture(cub3d->start_menu.level_hover.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_exit.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_start.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_level.texture);
	mlx_delete_texture(cub3d->level_menu.title.texture);
	mlx_delete_texture(cub3d->level_menu.back.texture);
	mlx_delete_texture(cub3d->level_menu.leaderboard.texture);
	mlx_delete_texture(cub3d->level_menu.back_hover.texture);
	mlx_delete_texture(cub3d->level_menu.leaderboard_hover.texture);
	mlx_delete_texture(cub3d->distraction_texture);
	mlx_delete_texture(cub3d->distraction_thrown_texture);
}

static void	delete_textures(cub3d_t *cub3d)
{
	int	i;

	delete_textures_additional(cub3d);
	i = 0;
	while (i < LEVELS)
	{
		mlx_delete_texture(cub3d->level_menu.minilevels[i++].number.texture);
	}
	i = 0;
	while (i < HEARTS)
	{
		mlx_delete_texture(cub3d->hearts[i].full.texture);
		mlx_delete_texture(cub3d->hearts[i++].empty.texture);
	}
	i = 0;
	while (i < NUM_FRAMES_ENEMY_IDLE)
	{
		mlx_delete_texture(cub3d->frames_idle[i++]);
	}
	i = 0;
	while (i < NUM_FRAMES_ENEMY_WALKING)
		mlx_delete_texture(cub3d->frames_walking[i++]);
	i = 0;
	while (i < 5)
		mlx_delete_texture(cub3d->door[i++].texture);
}

void	free_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < LEVELS + 1)
	{
		free_list(cub3d->levels[i].map_list);
		i++;
	}
	free(cub3d->rays);
	i = 0;
	while (i < LEVELS + 1)
	{
		free_backup(cub3d->levels[i]);
		i++;
	}
	delete_textures(cub3d);
	free(cub3d->levels);
}

void	free_delete_textures(level_t *level)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (level->texture[i].path)
			free(level->texture[i].path);
		if (level->texture[i].texture)
			mlx_delete_texture(level->texture[i].texture);
		i++;
	}
}
