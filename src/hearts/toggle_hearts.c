/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_hearts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:10 by slampine          #+#    #+#             */
/*   Updated: 2024/01/12 11:05:11 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	disable_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.img->instances[0].enabled = FALSE;
		cub3d->hearts[i].empty.img->instances[0].enabled = FALSE;
	}
}

void	enable_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.img->instances[0].enabled = TRUE;
		cub3d->hearts[i].empty.img->instances[0].enabled = FALSE;
	}
}

void	adjust_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < cub3d->player.health)
	{
		cub3d->hearts[i].full.img->instances[0].enabled = TRUE;
		cub3d->hearts[i].empty.img->instances[0].enabled = FALSE;
	}
	while (i < HEARTS)
	{
		cub3d->hearts[i].full.img->instances[0].enabled = FALSE;
		cub3d->hearts[i].empty.img->instances[0].enabled = TRUE;
		i++;
	}
}
