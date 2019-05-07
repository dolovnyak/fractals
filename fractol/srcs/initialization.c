/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 07:49:04 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 09:26:08 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void    initialization_mlx(t_mlx *mlx)
{
//	mlx->width = 2400;
//	mlx->height = 1200;
	mlx->width = 2560;
	mlx->height = 1394;
	mlx->relation = (float)mlx->width / mlx->height;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "mandelbrot");
	mlx->img_ptr = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->size_line, &mlx->endian);
}
