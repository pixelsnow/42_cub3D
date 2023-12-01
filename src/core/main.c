/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:09:19 by vvagapov          #+#    #+#             */
/*   Updated: 2023/12/01 15:07:44 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int free_three_strings(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
	return (0);
}

int	read_all_levels(cub3d_t *cub3d)
{
	int		fd;
	int		i;
	char	*level_i;
	char	*path;
	char	*full_path;


	i = 1;
	while (i <= 9)
	{
		level_i = ft_itoa(i);
		path = ft_strjoin("assets/levels/level", level_i);
		full_path = ft_strjoin(path, ".cub");
		fd = open(full_path, O_RDONLY);
		if (fd < 0)
			return (free_three_strings(level_i, path, full_path), err("Failed to open level file"));
		if (!read_cub_file(&cub3d->levels[i], full_path))
			return (free_three_strings(level_i, path, full_path), err("Failed to read level file"));
		close(fd);
		free_three_strings(level_i, path, full_path);
		i++;
	}
	return (1);
}

int	check_ext(char *str)
{
	int		len;
	int		i;
	char	*ext;

	i = 0;
	len = ft_strlen(str) - 1;
	ext = "buc.";
	while (ext[i])
	{
		if (str[len] != ext[i])
			return (0);
		len--;
		i++;
	}
	return (1);
}

// Store av[1] in cub3d->levels[0]
// Read levels in level folder into cub3d->levels[1-9]

int	main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	printf("1\n");
	if (!check_ext(av[1]))
		return (err("Invalid extension"));
	if (!read_cub_file(&cub3d, av[1]) || !init_cub3d(&cub3d))
		return (1);
	print_info(&cub3d); // DEBUG
	start_game(&cub3d);
	free_cub3d(&cub3d);
	return (0);
}
