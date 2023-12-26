#include "../../incl/cub3d.h"

void	free_backup(level_t level)
{
	int	i;

	i = 0;
	while (level.backup[i])
	{
		free(level.backup[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		free(level.texture[i].path);
		i++;
	}
	free(level.backup);
}

void	delete_heart(cub3d_t *cub3d)
{
	mlx_delete_texture(cub3d->level->heart.texture);
	mlx_delete_texture(cub3d->level->heart_half.texture);
	mlx_delete_texture(cub3d->level->heart_empty.texture);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_img);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_half_img);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_empty_img);
}

void	free_key_groups(cub3d_t *cub3d, int i)
{
	int			j;
	key_node_t	*tmp;

	free_doors(cub3d->level->door_groups[i].door_positions);
	if (cub3d->level->key_groups[i].num_keys_total)
	{
		tmp = cub3d->level->key_groups[i].keys;
		while (tmp)
		{
			mlx_delete_image(cub3d->mlx, tmp->img_curr_frame);
			//tmp->img_curr_frame->instances[0].enabled = FALSE;
			tmp = tmp->next;
		}
		mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_text_key_count);
		mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_key_icon);
		mlx_delete_texture(cub3d->level->key_groups[i].texture_key_icon);
		free_keys(cub3d->level->key_groups[i].keys);
		j = 0;
		while (j < NUM_FRAMES_KEY)
			mlx_delete_texture(cub3d->level->key_groups[i].textures_frames[j++]);
		free(cub3d->level->key_groups[i].textures_frames);
	}
}

void	free_level(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		free_key_groups(cub3d, i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if(cub3d->level->texture[i].texture)
			mlx_delete_texture(cub3d->level->texture[i].texture);
		i++;
	}
	free_info(cub3d->level->map);
	cub3d->halo.img->instances[0].enabled = FALSE;
	if (cub3d->num_enemies)
	{
		i = 0;
		while (i < cub3d->num_enemies)
			mlx_delete_image(cub3d->mlx, cub3d->enemy[i++].img_curr_frame);
			//cub3d->enemy[i++].img_curr_frame->instances[0].enabled = FALSE;
		free(cub3d->enemy);
	}
	disable_hearts(cub3d);
}
