/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 12:26:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 11:05:20 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		main(int argc, char **argv)
{
	t_cl	cl;
	t_mlx	mlx;

	if (argc != 2)
	{
		printf("KAAAAAAAA!!!\n");
		return (0);
	}
	initialization_cl(&cl);
	initialization_mlx(&mlx);
	if (ft_strequ(argv[1], "mandelbrot"))
		mandelbrot_2d(&cl, &mlx);
	else if (ft_strequ(argv[1], "mandelbrot_fdf"))
		mandelbrot_fdf(&cl, &mlx);
/*	else if (ft_strequ(argv[1], "mandelbrot_3d_fast"))
		mandelbrot_3d_fast(&cl, &mlx);
	else if (ft_strequ(argv[1], "mandelbrot_3d_safety"))
		mandelbrot_3d_safety(&cl, &mlx);*/
	else
		printf("KUUUUUUUUUUUU!!!\n");
	exit(0);
}
