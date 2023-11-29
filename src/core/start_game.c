
#include "../incl/cub3d.h"

void	draw_background(cub3d_t *cub3d)
{
	unsigned int	row;
	unsigned int	column;

	row = -1;
	while (++row < cub3d->img->height)
	{
		column = -1;
		while (++column < cub3d->img->width)
		{
			if (row < cub3d->img->height / 2)
				mlx_put_pixel(cub3d->img, column, row, cub3d->ceiling_color);
			else
				mlx_put_pixel(cub3d->img, column, row, cub3d->floor_color);
		}
	}
}

//------------------------------------------------------------------------------

void	update_img_size(cub3d_t *cub3d)
{
	if ((int)cub3d->img->width != cub3d->mlx->width || (int)cub3d->img->height != cub3d->mlx->height)
	{
		mlx_delete_image(cub3d->mlx, cub3d->img);
		cub3d->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
		update_minimap(cub3d);
		mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0);
		if (!init_rays(cub3d))
		{
			err("Failed to malloc rays");
			mlx_close_window(cub3d->mlx);
		}
	}
}

//------------------------------------------------------------------------------

void	update(void *param)
{
	cub3d_t	*cub3d;

	cub3d = param;

	// update game
	if (cub3d->state == STATE_PAUSE)
	{
		update_pause_menu(cub3d, &cub3d->pause_menu);
		if (cub3d->settings.fisheye == OFF)
			cub3d->fov = FOV;
	}
	else if (cub3d->state == STATE_GAME)
	{
		update_img_size(cub3d);
		mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse.x, &cub3d->mouse.y);
		if (cub3d->keys.mouse_left && cub3d->on_minimap)
			move_minimap(cub3d);
		player_movement(cub3d);
		draw_background(cub3d);
		raycasting(cub3d);
		draw_world(cub3d);
		minimap(cub3d);
		enemy_vision(cub3d);
	}
	else if (cub3d->state == STATE_GAMEOVER)
	{
		// update_end_menu(cub3d, &cub3d->gameover_menu);
	}
}

void	start_game(cub3d_t *cub3d)
{
	cub3d->start_time = mlx_get_time();
	draw_start_menu(cub3d, &cub3d->start_menu);
	mlx_close_hook(cub3d->mlx, &handle_close_window, cub3d->mlx);
	mlx_key_hook(cub3d->mlx, &get_input, cub3d);
	mlx_scroll_hook(cub3d->mlx, &hook_mouse_scroll, cub3d);
	mlx_mouse_hook(cub3d->mlx, &hook_mouse_buttons, cub3d);
	mlx_loop_hook(cub3d->mlx, &update, cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
}
