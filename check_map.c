/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:04:14 by lnicolau          #+#    #+#             */
/*   Updated: 2024/06/09 22:22:59 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void read_map(t_game *game, char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_error("Error opening file");
	preparation_map(game);
	reading(fd, game);
	close(fd);
	//parsing(game, str);
}
char *reading(int fd, t_game *game)
{
	char *line;
	int i;
	int j;

	i = 0;
	line = get_next_line(fd);
	if(line == NULL)
		ft_error("Ocurrió un error");
	while (line)
	{
		copy_line(game, line, i);
		j = 0;
		while (j < game->wth)
		{
			check_map_content(game, game->map[i][j], i, j);
			j++;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->map[i] = NULL;
	check_status(game);
	return NULL;
}

void check_status(t_game *game)
{
	if(!game->players)
		ft_error("Player not found");
	if(!game->exit)
		ft_error("Exit not found");
	if(game->collectibles == 0)
		ft_error("Collectibles not found");
}
void copy_line(t_game *game, char *line, int i)
{
	int j;

	j = 0;
	game->map[i] = malloc(sizeof(char) * (strlen(line) + 1));
	if (!game->map[i])
	{
    	perror("Failed to allocate memory for game->map[i]");
    	exit(EXIT_FAILURE);
	}
	while (line[j] != '\0')
	{
		game->map[i][j] = line[j];
		j++;
	}
	game->map[i][j] = '\0';
}
void check_map_content(t_game *game, char cell, int i, int j) 
{
if (cell == 'P')
	{
		if (game->players == 0)
		{
			game->player_x = j;
			game->player_y = i;
			game->players = 1;
		}
		else
		{
			ft_error("Multiple players found");
		}
	}
	else if (cell == 'C')
		game->collectibles += 1;
	else if (cell == 'E')
	{
		if (game->exit == 0)
			game->exit = 1;
		else
			ft_error("Multiple exits found");
	}
	else if (cell != '1' && cell != '0') // Validación adicional de celdas
		ft_error("Unexpected cell character");
}


void preparation_map(t_game *game)
{
	game->map = malloc(sizeof(char *) * (game->hgt + 1));
	if (!game->map)
	{
	    perror("Failed to allocate memory for map");
    	exit(EXIT_FAILURE);
	}
}
//Comprueba si el mapa es rectangular
void check_rect_map(t_game *game)
{
	int i;
	int j;
	int len;

	i = 0;
	len = ft_strlen(game->map[0]);
	if(ft_strlen(game->map[i]) <= 1)
		ft_error("Ocurrió un error");
	if(ft_strlen(game->map[0]) < 3)
		ft_error("Ocurrió un error");
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
			j++;
		if (j != len)
			ft_error("Ocurrió un error");
		i++;
	}
	if(i == 0)
		ft_error("Ocurrió un error");
	if(i < 3)
		ft_error("Ocurrió un error");
	game->wth = len;
	game->hgt = i;
}

//Comprueba si el mapa contiene los componentes necesarios
void check_components(t_game *game)
{
	int i;
	int j;
	char valid_chars[] = "10CEP";


	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] != '\0' && ft_strchr(valid_chars, game->map[i][j]) == NULL)
				ft_error("Ocurrió un error");
			j++;
		}
		i++;
	}
	if (count_comp(game->map, 'P') != 1)
		ft_error("Ocurrió un error");
	if(count_comp(game->map, 'E') != 1)
		ft_error("Ocurrió un error");
	if(count_comp(game->map, 'C') == 0)
		ft_error("Ocurrió un error");
}

void check_walls(t_game *game)
{
	int	i;
	size_t	j;

	j = 0;
	i = 0;

	while ( j < ft_strlen(game->map[0]))
	{
		if (game->map[0][j] != '1' || game->map[game->hgt - 1][j] != '1')
			ft_error("Ocurrió un error");
		j++;
	}

	while( i < game->hgt)
	{
		if (game->map[i][0] != '1' || game->map[i][game->wth - 1] != '1')
			ft_error("Ocurrió un error");
		i++;
	}
}

int **start_check_path(t_game *game, int i, int j)
{
	int **visit;
	visit = init_visit(game->hgt, game->wth);

	while(i < game->hgt)
	{
		j = 0;
		while(j < game->wth)
		{
			if (game->map[i][j] == 'P')
				check_path(game, i, j, visit);
			j++;
		}
		i++;
	}
	if (!game->exit)
		ft_error("Ocurrió un error");
		
	i = 0;
	while(i < game->hgt)
	{
		free(visit[i]);
		i++;
	}
	return(visit);
}

void check_path(t_game *game, int i, int j, int **visit)//flufli
{
	if (i < 0 || i >= game->hgt || j < 0 || j >= game->wth
		|| visit[i][j] || game->map[i][j] == '1')
		return;

	visit[i][j] = 1;
	if (game->map[i][j] == '1')
        return;

    // Si la posición actual es el punto de salida, marcar que se encontró un camino y retornar
	if (game->map[i][j] == 'E')
	{
		game->exit = 1;
		return;
	}

    // Continuar la búsqueda en las posiciones adyacentes
	check_path(game, i - 1, j, visit); // arriba
	check_path(game, i + 1, j, visit); // abajo
	check_path(game, i, j - 1, visit); // izquierda
	check_path(game, i, j + 1, visit); // derecha
}


void check_collectibles(t_game *game, int **visit)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < game->hgt)
	{
		j = 0;
		while(j < game->wth)
		{
			if (game->map[i][j] == 'C' && visit[i][j] == 1)
			{
				game->collectibles--;
			}
			j++;
		}
		i++;
	}
}