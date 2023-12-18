#include "../incl/cub3d.h"

void scale_curr_frame(cub3d_t *cub3d, key_node_t *key, mlx_texture_t *src, double factor)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;

	ft_memset(key->img_curr_frame->pixels, 0, key->img_curr_frame->width * key->img_curr_frame->height * 4);
	row_res = 0;
	while (row_res < src->height * factor)
	{
		col_res = 0;
		if (row_res < key->img_curr_frame->height)
		{
			while (col_res < src->width * factor)
			{
				// TODO: handle out of limits pixels
				if (col_res < key->img_curr_frame->width)
				{
					row_src = (uint32_t)round(row_res / factor);
					// make sure that source pixel is not out of limits
					if (row_src >= src->height)
						row_src--;
					col_src = (uint32_t)round(col_res / factor);
					if (col_src >= src->width)
						col_src--;
					if (cub3d->rays[(int)(key->pos_screen.x - src->width * factor * 0.5 + col_res)].length > key->dist_to_player)
						ft_memcpy(key->img_curr_frame->pixels + row_res * key->img_curr_frame->width * 4 + col_res * 4,
							src->pixels + row_src * src->width * 4 + col_src * 4,
							4);
				}
				col_res++;
				// Maybe optimise and skip column completely?
			}
		}
		row_res++;
	}
	//printf("pos_screen: x: %d, y: %d\n", pos_screen.x, pos_screen.y);
	key->img_curr_frame->instances[0].x = key->pos_screen.x - src->width * factor * 0.5;
	key->img_curr_frame->instances[0].y = key->pos_screen.y - src->height * factor * 1.5;
	//printf("instance pos: x: %d, y: %d\n", res->instances[0].x, res->instances[0].y);
}

void scale_curr_enemy_frame(cub3d_t *cub3d, t_enemy *enemy, mlx_texture_t *src, double factor)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;

	ft_memset(enemy->img_curr_frame->pixels, 0, enemy->img_curr_frame->width * enemy->img_curr_frame->height * 4);
	row_res = 0;
	while (row_res < src->height * factor)
	{
		col_res = 0;
		if (row_res < enemy->img_curr_frame->height)
		{
			while (col_res < src->width * factor)
			{
				// TODO: handle out of limits pixels
				if (col_res < enemy->img_curr_frame->width)
				{
					row_src = (uint32_t)round(row_res / factor);
					// make sure that source pixel is not out of limits
					if (row_src >= src->height)
						row_src--;
					col_src = (uint32_t)round(col_res / factor);
					if (col_src >= src->width)
						col_src--;
					if (cub3d->rays[(int)(enemy->pos_screen.x - src->width * factor * 0.5 + col_res)].length > enemy->dist_to_player)
						ft_memcpy(enemy->img_curr_frame->pixels + row_res * enemy->img_curr_frame->width * 4 + col_res * 4,
							src->pixels + row_src * src->width * 4 + col_src * 4,
							4);
				}
				col_res++;
				// Maybe optimise and skip column completely?
			}
		}
		row_res++;
	}
	//printf("pos_screen: x: %d, y: %d\n", pos_screen.x, pos_screen.y);
	enemy->img_curr_frame->instances[0].x = enemy->pos_screen.x - src->width * factor * 0.5;
	enemy->img_curr_frame->instances[0].y = enemy->pos_screen.y - src->height * factor;
}

double	calculate_scale_factor(double dist, double normal_dist)
{
	double	scale_factor;

	if (!dist)
		dist = 1;
	scale_factor = normal_dist / dist;
	return (scale_factor);
}

void	draw_keys(cub3d_t *cub3d, int group_index, int curr_frame_num)
{
	key_node_t  *tmp;
	double scale_factor;
	//mlx_image_t	*old_img;

	//TODO: handle drawing keys in order of distance
	//printf("draw_keys, curr_frame_num: %i\n", curr_frame_num);
	tmp = cub3d->level->key_groups[group_index].keys;
	while (tmp)
	{
		if (tmp->collected == FALSE && tmp->visible == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = TRUE;
			scale_factor = calculate_scale_factor(tmp->dist_to_player, KEY_NORMAL_SCALE_DISTANCE);
			scale_curr_frame(
				cub3d,
				tmp,
				cub3d->level->key_groups[group_index].textures_frames[curr_frame_num],
				scale_factor);
		}
		else if (tmp->visible == FALSE || tmp->collected == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = FALSE;
		}
		tmp = tmp->next;
	}
}

void	draw_enemies_frames(cub3d_t *cub3d, int index)
{
	double scale_factor;
	mlx_texture_t *frame;

	if (cub3d->enemy[index].visible == TRUE)
	{
		cub3d->enemy[index].img_curr_frame->instances[0].enabled = TRUE;
		scale_factor = calculate_scale_factor(cub3d->enemy[index].dist_to_player, ENEMY_NORMAL_SCALE_DISTANCE);
		if (cub3d->enemy[index].state == IDLE)
			frame = cub3d->frames_blue_idle[cub3d->curr_frame_index_idle];
		else if (cub3d->enemy[index].state == WALKING)
			frame = cub3d->frames_green_walking[cub3d->curr_frame_index_walking];
		else
			frame = cub3d->frames_blue_idle[cub3d->curr_frame_index_idle];
		scale_curr_enemy_frame(
				cub3d,
				&cub3d->enemy[index],
				frame,
				scale_factor);
	}
	else
	{
		cub3d->enemy[index].img_curr_frame->instances[0].enabled = FALSE;
	}
}

int	count_not_collected_visible_keys(key_node_t	*keys)
{
	int	count;

	count = 0;
	while (keys)
	{
		if (keys->collected == FALSE && keys->visible == TRUE)
			count++;
		keys = keys->next;
	}
	return (count);
}

int	count_all_not_collected_visible_keys(cub3d_t *cub3d)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		count += count_not_collected_visible_keys(cub3d->level->key_groups[i].keys);
		i++;
	}
	return (count);
}

void	sort_keys_by_dist_to_player(key_node_t **keys)
{
	int			i;
	int			j;
	key_node_t	*tmp;

	i = 0;
	while (keys[i])
	{
		j = i + 1;
		while (keys[j])
		{
			if (keys[i]->dist_to_player < keys[j]->dist_to_player)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void fill_keys_array(cub3d_t *cub3d, key_node_t **keys)
{
	int			i;
	int			j;
	key_node_t	*tmp;

	i = 0;
	j = 0;
	while (i < NUM_DOORS_MAX)
	{
		tmp = cub3d->level->key_groups[i].keys;
		while (tmp)
		{
			if (tmp->collected == FALSE && tmp->visible == TRUE)
			{
				keys[j] = tmp;
				j++;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

key_node_t	**create_list_of_pointers_to_all_keys_ordered_by_dist_to_player(cub3d_t *cub3d)
{
	key_node_t	**keys;
	int			count;

	count = count_all_not_collected_visible_keys(cub3d);
	keys = malloc(sizeof(key_node_t *) * (count + 1));
	keys[count] = NULL;
	// TODO: handle malloc errors
	fill_keys_array(cub3d, keys);
	sort_keys_by_dist_to_player(keys);
	return (keys);
}

void print_pos_and_dist_ordered_keys(key_node_t **keys)
{
	int	i;

	i = 0;
	while (keys[i])
	{
		printf("key %d, pos: x: %f, y: %f, dist: %f\n", i, keys[i]->pos.x, keys[i]->pos.y, keys[i]->dist_to_player);
		i++;
	}
}


int	count_visible_enemies(cub3d_t *cub3d)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < cub3d->num_enemies)
	{
		if (cub3d->enemy[i].visible == TRUE)
			count++;
		i++;
	}
	if (count > 0)
		printf("count_visible_enemies: %d\n", count);
	return (count);
}

void	fill_visible_enemies_array(cub3d_t *cub3d, t_enemy **enemies)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub3d->num_enemies)
	{
		if (cub3d->enemy[i].visible == TRUE)
		{
			enemies[j] = &cub3d->enemy[i];
			j++;
		}
		i++;
	}
}

void	sort_enemies_by_dist_to_player(t_enemy **enemies)
{
	int			i;
	int			j;
	t_enemy		*tmp;

	i = 0;
	while (enemies[i])
	{
		j = i + 1;
		while (enemies[j])
		{
			if (enemies[i]->dist_to_player < enemies[j]->dist_to_player)
			{
				tmp = enemies[i];
				enemies[i] = enemies[j];
				enemies[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_enemy **create_list_of_pointers_to_all_enemies_ordered_by_dist_to_player(cub3d_t *cub3d)
{
	t_enemy		**enemies;
	int			count;

	count = count_visible_enemies(cub3d);
	enemies = malloc(sizeof(t_enemy *) * (count + 1));
	enemies[count] = NULL;
	fill_visible_enemies_array(cub3d, enemies);
	sort_enemies_by_dist_to_player(enemies);
	return (enemies);
}

void print_dist_ordered_enemies(t_enemy **enemies)
{
	int	i;

	i = 0;
	while (enemies[i])
	{
		printf("enemy %d, dist: %f\n", i, enemies[i]->dist_to_player);
		i++;
	}
}

void	draw_animated_keys(cub3d_t *cub3d)
{
	int 		i;
	key_node_t	**ordered_keys;
	t_enemy		**ordered_enemies;

	
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->door_groups[i].num_keys_left > 0)
		{
			//printf("key group %d has %d keys left\n", i, cub3d->level->door_groups[i].num_keys_left);
			// set current frame based on time
			cub3d->level->key_groups[i].curr_frame_index = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_KEY;
			if (cub3d->level->key_groups[i].prev_frame_index
				!= cub3d->level->key_groups[i].curr_frame_index)
			{
				draw_keys(cub3d, i, cub3d->level->key_groups[i].curr_frame_index);
				cub3d->level->key_groups[i].prev_frame_index
					= cub3d->level->key_groups[i].curr_frame_index;
			}
		}
		i++;
	}
	printf("keys done\n");
	cub3d->curr_frame_index_idle = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_ENEMY_IDLE;
	cub3d->curr_frame_index_walking = (int)(cub3d->run_time / ANIMATION_INTERVAL_MS * 1000) % NUM_FRAMES_ENEMY_WALKING;
	printf("before enemies\n");
	if (cub3d->prev_frame_index_idle != cub3d->curr_frame_index_idle)
	{
		ordered_keys = create_list_of_pointers_to_all_keys_ordered_by_dist_to_player(cub3d);
		//print_pos_and_dist_ordered_keys(ordered_keys);
		ordered_enemies = create_list_of_pointers_to_all_enemies_ordered_by_dist_to_player(cub3d);
		print_dist_ordered_enemies(ordered_enemies);
		printf("printed\n");
		i = 0;
		while (i < cub3d->num_enemies)
		{
			draw_enemies_frames(cub3d, i);
			i++;
		}
		cub3d->prev_frame_index_idle = cub3d->curr_frame_index_idle;
		cub3d->prev_frame_index_walking = cub3d->curr_frame_index_walking;
	}
	printf("function done\n");
}
