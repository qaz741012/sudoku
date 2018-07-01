/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 02:20:32 by chlin             #+#    #+#             */
/*   Updated: 2018/05/27 14:20:40 by chlin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

int    ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

int    **generate_grid()
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

int    **fill_in_number(int **grid, char **argv)
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

int    check_row(int **grid, int y, int num)
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

int    check_column(int **grid, int x, int num)
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

int    check_block(int **grid, int x, int y, int num)
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

int    valid(int **grid, int x, int y, int num)
{
    return (check_row(grid, y, num) &&
            check_column(grid, x, num) &&
            check_block(grid, x, y, num));
}

int    doit(int **grid, int x, int y, int ***solution)
{
    int n;

    if (grid[y][x] != 0)
    {
        if (x == 8 && y == 8)
        {
            *solution = grid;
            return (1);
        }
        else if (x == 8)
        {
            if (doit(grid, 0, y + 1, solution))
                return (1);
        }
        else
        {
            if (doit(grid, x + 1, y, solution))
                return (1);
        }
    }
    else
    {
        n = 1;
        while (n <= 9)
        {
            if (valid(grid, x, y, n))
            {
                grid[y][x] = n;
                if (x == 8 && y == 8)
                {
                    *solution = grid;
                    return (1);
                }
                else if (x == 8)
                {
                    if (doit(grid, 0, y + 1, solution))
                        return (1);
                }
                else
                {
                    if (doit(grid, x + 1, y, solution))
                        return (1);
                }
            }
            n++;
        }
        grid[y][x] = 0;
    }
    return (0);
}

int    error_case(int argc, char **argv)
{
    int i;
    int j;

    if (argc != 10)
        return (1);
    i = 1;
    while (i <= 9)
    {
        if (ft_strlen(argv[i]) != 9)
            return (1);
        j = 0;
        while (argv[i][j] != '\0')
        {
            if (!((argv[i][j] >= '1' && argv[i][j] <= '9') ||
                  argv[i][j] == '.'))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

void    print_grid(int **grid)
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

int    main(int argc, char **argv)
{
    int **grid;
    int **result;
	
    if (error_case(argc, argv))
    {
        write(1, "Error\n", 6);
        return (0);
    }
    grid = generate_grid();
    grid = fill_in_number(grid, argv);
    result = generate_grid();
    if (doit(grid, 0, 0, &result))
        print_grid(grid);
    else
        write(1, "Error\n", 6);
    return (0);
}
