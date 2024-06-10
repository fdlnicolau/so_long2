/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:49:29 by lnicolau          #+#    #+#             */
/*   Updated: 2024/06/07 22:49:29 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void game_control(t_game *game)
{
	game->mlx = mlx_init(game->wth * 64, game->hgt * 64, "so_long", true);
	if(game->mlx == NULL)
			ft_error("mlx_init failed");
	load_image(game);
	mlx_key_hook(game->mlx, &init_key_hook, game);
	mlx_loop(game->mlx);
}

void load_image(t_game *game)
{
	  load_png(game);
    texture_to_img(game);
    img_to_window(game);
    load_player(game);
}
void load_player(t_game *game)
{
		int i;
		int j;
		mlx_image_t *image;

		i = 0;
		while(i < game->hgt)
		{
				j = 0;
				while(j < game->wth)
				{
						if(game->map[i][j] == 'P')
						{
								game->player_y = i;
								game->player_x = j;
								image = convert_texture_to_image(game->mlx, game->player_tex);
								mlx_image_to_window(game->mlx, image, j * 64, i * 64);
						}
						j++;
				}
				i++;
		}
}
mlx_image_t *convert_texture_to_image(void *mlx, mlx_texture_t *texture)
{
    mlx_image_t *image = mlx_texture_to_image(mlx, texture);
    if (!image)
        ft_error("Error converting texture to image");
    return image;
}

void img_to_window(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->hgt)
    {
        j = 0;
        while (j < game->wth)
        {
            if (game->map[i][j] == '1')
                mlx_image_to_window(game->mlx, game->wall_img, j * 64, i * 64);
            else if (game->map[i][j] == '0')
                mlx_image_to_window(game->mlx, game->floor_img, j * 64, i * 64);
            else if (game->map[i][j] == 'C')
                mlx_image_to_window(game->mlx, game->collect_img, j * 64, i * 64);
            else if (game->map[i][j] == 'E')
                mlx_image_to_window(game->mlx, game->exit_img, j * 64, i * 64);
            j++;
        }
        i++;
    }
}

void load_png(t_game *game)
{
	game->floor_tex = mlx_load_png("./sprites/floor.png");
	game->exit_tex = mlx_load_png("./sprites/exit.png");
	game->player_tex = mlx_load_png("./sprites/player.png");
	game->wall_tex = mlx_load_png("./sprites/wall.png");
	game->collect_tex = mlx_load_png("./sprites/collect.png");
    if(!game->floor_tex || !game->exit_tex || !game->player_tex || !game->wall_tex || !game->collect_tex)
        ft_error("Error loading texture");
}

void texture_to_img(t_game *game)
{
    game->floor_tex = mlx_load_png("./sprites/floor.png");
    game->exit_tex = mlx_load_png("./sprites/exit.png");
    game->player_tex = mlx_load_png("./sprites/player.png");
    game->wall_tex = mlx_load_png("./sprites/wall.png");
    game->collect_tex = mlx_load_png("./sprites/collect.png");

    if (!game->floor_tex || !game->exit_tex || !game->player_tex || !game->wall_tex || !game->collect_tex)
        ft_error("Error loading texture");

    game->floor_img = mlx_texture_to_image(game->mlx, game->floor_tex);
    game->exit_img = mlx_texture_to_image(game->mlx, game->exit_tex);
    game->player_img = mlx_texture_to_image(game->mlx, game->player_tex);
    game->wall_img = mlx_texture_to_image(game->mlx, game->wall_tex);
    game->collect_img = mlx_texture_to_image(game->mlx, game->collect_tex);
}

void game_init(t_game *game)
{
    game->map = NULL;
    game->rows = 0;
    game->cols = 0;
    game->players = 0;
    game->exit = 0;
    game->collectibles = 0;
    game->hgt = 0;
    game->wth = 0;
    game->map_to_free = NULL;
    game->player_y = 0;
    game->player_x = 0;
    game->floor_tex = NULL;
    game->exit_tex = NULL;
    game->player_tex = NULL;
    game->wall_tex = NULL;
    game->collect_tex = NULL;
    game->floor_img = NULL;
    game->exit_img = NULL;
    game->player_img = NULL;
    game->wall_img = NULL;
    game->collect_img = NULL;
    game->floor_height = 0;
    game->floor_width = 0;
    game->exit_height = 0;
    game->exit_width = 0;
    game->player_height = 0;
    game->player_width = 0;
    game->wall_height = 0;
    game->wall_width = 0;
    game->collect_height = 0;
    game->collect_width = 0;
    game->mlx = NULL;
}