/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:50:41 by lnicolau          #+#    #+#             */
/*   Updated: 2024/05/26 04:50:41 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int count_comp(char **map, char c)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
} 

int **init_visit(int hgt, int wth)
{
	int i;
	int **visit;

	i = 0;
	visit = (int **)malloc(sizeof(int *) * hgt);
	if (visit == NULL)
		ft_error();
	while (i < hgt)
	{
		visit[i] = (int *)malloc(sizeof(int) * wth);
		if (visit[i] == NULL)
			ft_error();
		i++;
	}
	return (visit);
}