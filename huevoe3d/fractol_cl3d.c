/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:30:52 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/03 06:24:36 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <time.h>

int		refresh(t_all *all)
{
	int		z_len;
	size_t	global_size;
	int		err;
	double	step_x;
	double	step_y;
	int		color;
	int		depth;
	cl_mem	memimg;

	z_len = 1200;
	global_size = all->s_width * all->s_height;
	step_x = (all->right_b - all->left_b) / all->s_width;
	step_y = (all->bot_b - all->top_b) / all->s_height;
	memimg = clCreateBuffer(all->context, CL_MEM_READ_WRITE, all->size_line * all->s_height, NULL, &err);
	if (err != 0)
		printf ("create buffer - error\n");
	/* если будет нужен очищеный img
	 * err = clEnqueueWriteBuffer(all->queue, memimg, CL_TRUE, 0, all->size_line, all->img_data, 0, NULL, NULL);
	 */
	err = clSetKernelArg(all->kernel, 0, sizeof(cl_mem), &memimg);
	err |= clSetKernelArg(all->kernel, 1, sizeof(double), &step_x);
	err |= clSetKernelArg(all->kernel, 2, sizeof(double), &step_y);
	err |= clSetKernelArg(all->kernel, 3, sizeof(int), &all->depth);
	err |= clSetKernelArg(all->kernel, 4, sizeof(int), &all->s_width);
	err |= clSetKernelArg(all->kernel, 5, sizeof(int), &all->s_height);
	err |= clSetKernelArg(all->kernel, 6, sizeof(int), &all->center_x);
	err |= clSetKernelArg(all->kernel, 7, sizeof(int), &all->center_y);
	err |= clSetKernelArg(all->kernel, 8, sizeof(int), &all->zoom);
	err |= clSetKernelArg(all->kernel, 9, sizeof(double), &all->left_b);
	err |= clSetKernelArg(all->kernel, 10, sizeof(double), &all->top_b);
	err |= clSetKernelArg(all->kernel, 11, sizeof(double), &all->angle_x);
	err |= clSetKernelArg(all->kernel, 12, sizeof(double), &all->angle_z);
	if (err != 0)
		printf ("set kernel arg - error\n");

	err = clEnqueueNDRangeKernel(all->queue, all->kernel, 1, NULL, &global_size,
		NULL, 0, NULL, NULL);
	if (err != 0)
		printf("NDR - error\n");
	err = clEnqueueReadBuffer(all->queue, memimg, CL_TRUE, 0, all->size_line * all->s_height, all->img_data,
		0, NULL, NULL);
	if (err != 0)
		printf ("read buffer - error\n");
	mlx_clear_window(all->mlx, all->win);
	mlx_put_image_to_window(all->mlx, all->win, all->img_ptr, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	all;

	initialization_Cl(&all);
	initialization_all(&all);
	mlx_hook(all.win, 2, 0, &keyboard_event, &all);
	mlx_hook(all.win, 4, 0, &mouse_event, &all);
	mlx_hook(all.win, 5, 0, &mouse_release, &all);
	mlx_hook(all.win, 3, 0, &key_release, &all);
	mlx_hook(all.win, 6, 0, &mouse_move, &all);
	mlx_hook(all.win, 17, 0, &exit_event, (void*)0);
	mlx_loop_hook(all.mlx, &refresh, &all);
	mlx_loop(all.mlx);
	exit(0);
}
