/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 08:01:15 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 18:40:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

static void	mlx_for_all(t_mlx *mlx)
{
	mlx->relation = (float)mlx->width / mlx->height;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "mandelbrot");
	mlx->img_ptr = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
			&mlx->size_line, &mlx->endian);
}

void		initialization_mlx2d(t_mlx *mlx)
{
	mlx->width = 2560;
	mlx->height = 1394;
	mlx_for_all(mlx);
}

void		initialization_mlx3d(t_mlx *mlx)
{
	mlx->width = 800;
	mlx->height = 600;
	mlx_for_all(mlx);
}

void		initialization_mlx_fdf(t_mlx *mlx)
{
	mlx->width = 1200;
	mlx->height = 1200;
	mlx_for_all(mlx);
}
