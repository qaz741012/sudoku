/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 02:20:32 by chlin             #+#    #+#             */
/*   Updated: 2018/05/27 03:00:03 by chlin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int **generate_grid()
{
	int i;
	int **grid;

	grid = (int**)malloc(sizeof(*grid) * 9);
	i = 0;
	while (i < 9)
	{
		grid[i] = (int*)malloc(sizeof(**grid) * 9);
		i++;
	}
	return (grid);
}

int	**fill_in_number(int **grid, char **argv)
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if (argv[i+1][j] == '.')
				grid[i][j] = 0;
			else
				grid[i][j] = argv[i+1][j] - 48;
			j++;
		}
		i++;
	}
	return (grid);
}

void	print_grid(int **grid)
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			ft_putchar(grid[i][j] + '0');
			if (j < 8)
				ft_putchar(' ');
			else if (j == 8)
				ft_putchar('\n');
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int **grid;

	grid = generate_grid();
	grid = fill_in_number(grid, argv);
	print_grid(grid);
	return (0);
}
