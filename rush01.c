/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 02:20:32 by chlin             #+#    #+#             */
/*   Updated: 2018/05/27 04:23:56 by chlin            ###   ########.fr       */
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

int	check_row(int **grid, int y, int num)
{
	int x;

	x = 0;
	while (x < 9)
	{
		if (grid[y][x] == num)
			return (0);
		x++;
	}
	return (1);
}

int	check_column(int **grid, int x, int num)
{
	int y;

	y = 0;
	while (y < 9)
	{
		if (grid[y][x] == num)
			return (0);
		y++;
	}
	return (1);
}

int	check_block(int **grid, int x, int y, int num)
{
	int i;
	int j;
	
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (grid[(y / 3) * 3 + i][(x / 3) * 3 + j] == num)
			   return (0);
			j++;	
		}
		i++;
	}
	return (1);
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
	//print_grid(grid);
	printf("%d\n", check_block(grid, 3, 6, 6));
	return (0);
}
