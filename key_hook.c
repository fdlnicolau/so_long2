/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:12:29 by lnicolau          #+#    #+#             */
/*   Updated: 2024/06/09 13:12:29 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	init_key_hook(mlx_key_data_t keydata, void *game)
{
    t_game *data;
    data = (t_game *)game;
    key_hook(keydata, data);
}

void key_hook(mlx_key_data_t keydata, t_game *data)
{
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        ft_move(data, UP, data->player_y - 1, data->player_x);
    if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
        ft_move(data, DOWN, data->player_y + 1, data->player_x);
    if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
        ft_move(data, RIGHT, data->player_y, data->player_x + 1);
    if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
        ft_move(data, LEFT, data->player_y, data->player_x - 1);
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        exit(EXIT_SUCCESS);
}