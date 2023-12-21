#include "../incl/cub3d.h"

static int	player_is_invulnerable(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->player.hit_timestamp < INVULNERABILITY_TIME);
}

void	draw_health(cub3d_t *cub3d)
{
	cub3d->level->heart_img->instances[0].enabled = FALSE;
	cub3d->level->heart_half_img->instances[0].enabled = FALSE;
	cub3d->level->heart_empty_img->instances[0].enabled = FALSE;
	if (cub3d->player.health == 2)
		cub3d->level->heart_half_img->instances[0].enabled = TRUE;
	if (cub3d->player.health == 1)
		cub3d->level->heart_empty_img->instances[0].enabled = TRUE;
}

void	player_is_hit(cub3d_t *cub3d)
{
	if (player_is_invulnerable(cub3d))
	{
		// printf("Player is invulnerable [%f]\n", mlx_get_time() - cub3d->player.hit_timestamp);
		return ;
	}
	cub3d->player.hit_timestamp = mlx_get_time();
	cub3d->player.health -= 1;
	activate_halo(&cub3d->halo, RED);
	if (cub3d->player.health > 0)
		draw_health(cub3d);
	printf("Player health: %i\n", cub3d->player.health);
}