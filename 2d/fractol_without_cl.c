/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:30:52 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/01 19:37:52 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <OPENCL/opencl.h>
#include <time.h>

void	initialization(t_all *all)
{
	all->s_width = 1200;
	all->s_height = 1200;
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->s_width, all->s_height, "fractol");
	all->img_ptr = mlx_new_image(all->mlx, all->s_width, all->s_height);
	all->img_data = mlx_get_data_addr(all->img_ptr, &all->bpp, &all->size_line, &all->endian);
	all->center_x = 0;
	all->center_y = 0;
	all->zoom = 0;
	all->relation_x = all->s_width / 3;
	all->relation_y = all->s_height / 3;
	all->left_b = -2.0;
	all->right_b = 1.0;
	all->top_b = -1.5;
	all->bot_b = 1.5;
//	all->realr_b = 
	all->depth = 250;
}

void	put_pixel(int x, int y, int color, t_all *all)
{
	register int	a;
	int				*img;

	
	img = (int*)all->img_data;
	if (color != 0)
	{
	//	img[all->s_width * y + x] = color * 100000;
	//	img[all->s_width * y + x] = color * 900000;
		img[all->s_width * y + x] = color * 2000000;
//		img[all->s_width * y + x] = color * all->color_mult;
	}
	else
	{
//		img[all->s_width * y + x] = all->color_mult;
		a = all->s_width * 4 * y + x * 4;
		all->img_data[a] = 0;
		all->img_data[a + 1] = 0;
		all->img_data[a + 2] = (unsigned)255;
		all->img_data[a + 3] = rand() % 250;
	}
}

int		check_pixel(int x, int y, t_all *all)
{
	register int i;
	double	comp_x;
	double	comp_y;
	double	comp_z;
	double	real;
	double	imaginary;
	double	tmp;

	real = 0.0;
	imaginary = 0.0;
	comp_x = all->left_b + ((all->right_b - all->left_b) / all->s_width) * x;
	comp_y = all->top_b + ((all->bot_b - all->top_b) / all->s_height) * y;
	comp_z = 
		i = -1;
	while (++i < all->depth && sqrt(real * real + imaginary * imaginary) < 2)
	{
		tmp = real * real - imaginary * imaginary;
		imaginary = 2 * real * imaginary + comp_y;
		real = tmp + comp_x;
	}
	if (i < all->depth)
		return (i);
	else
		return (0);
}

int		refresh(t_all *all)
{
	int	x;
	int	y;
	int	z;
	int k;
	int		color;
	int		depth;

	ft_bzero((void*)all->img_data, all->size_line * all->s_height);
	x = -1;
	y = -1;
	z = -1;
	//	while (++z < 100)
	//	{
	while (++x < all->s_width)
	{
		while (++y < all->s_height)
		{
			color = check_pixel(x, y, all);
			put_pixel(x, y, color, all);
		}
		y = -1;
	}
	x = -1;
	//	}
	mlx_clear_window(all->mlx, all->win);
	mlx_put_image_to_window(all->mlx, all->win, all->img_ptr, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	all;

	initialization(&all);
	mlx_hook(all.win, 2, 0, &keyboard_event, &all);
	mlx_hook(all.win, 4, 0, &mouse_event, &all);
	mlx_loop_hook(all.mlx, &refresh, &all);
	mlx_loop(all.mlx);
	exit(0);
}
