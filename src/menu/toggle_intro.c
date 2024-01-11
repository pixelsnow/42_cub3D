/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_intro.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:28 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 17:48:27 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	disable_intro(cub3d_t *cub3d)
{
	cub3d->intro.img[0].enabled = FALSE;
}

void	enable_intro(cub3d_t *cub3d)
{
	cub3d->intro.img[0].enabled = TRUE;
}
