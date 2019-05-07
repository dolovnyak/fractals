/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelfdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:09:09 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 11:06:02 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelfdf.h"
#include <time.h> //TODO

static int		refresh(t_mandelfdf *conf)
{
	size_t	global_size;
	int		err;
	double	step_x;
	double	step_y;
	cl_mem	memimg;
	cl_kernel	kernel;

	kernel = conf->cl->kernel_mandelfdf;
	global_size = conf->mlx->width * conf->mlx->height;
	step_x = (conf->right_b - conf->left_b) / conf->mlx->width;
	step_y = (conf->bot_b - conf->top_b) / conf->mlx->height;
	memimg = clCreateBuffer(conf->cl->context, CL_MEM_READ_WRITE, conf->mlx->size_line * conf->mlx->height, NULL, &err);
	if (err != 0)
		printf ("create buffer - error\n");
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memimg);
	err |= clSetKernelArg(kernel, 1, sizeof(double), &step_x);
	err |= clSetKernelArg(kernel, 2, sizeof(double), &step_y);
	err |= clSetKernelArg(kernel, 3, sizeof(int), &conf->depth);
	err |= clSetKernelArg(kernel, 4, sizeof(int), &conf->mlx->width);
	err |= clSetKernelArg(kernel, 5, sizeof(int), &conf->mlx->height);
	err |= clSetKernelArg(kernel, 6, sizeof(int), &conf->center_x);
	err |= clSetKernelArg(kernel, 7, sizeof(int), &conf->center_y);
	err |= clSetKernelArg(kernel, 8, sizeof(int), &conf->zoom);
	err |= clSetKernelArg(kernel, 9, sizeof(double), &conf->left_b);
	err |= clSetKernelArg(kernel, 10, sizeof(double), &conf->top_b);
	err |= clSetKernelArg(kernel, 11, sizeof(double), &conf->angle_x);
	err |= clSetKernelArg(kernel, 12, sizeof(double), &conf->angle_z);
	if (err != 0)
		printf ("set kernel arg - error\n");
	err = clEnqueueNDRangeKernel(conf->cl->queue, kernel, 1, NULL, &global_size,
		NULL, 0, NULL, NULL);
	if (err != 0)
		printf("NDR - error\n");
	err = clEnqueueReadBuffer(conf->cl->queue, memimg, CL_TRUE, 0,
			conf->mlx->size_line * conf->mlx->height, conf->mlx->img_data,
		0, NULL, NULL);
	if (err != 0)
		printf ("read buffer - error\n");
	mlx_clear_window(conf->mlx->mlx, conf->mlx->win);
	mlx_put_image_to_window(conf->mlx->mlx, conf->mlx->win, conf->mlx->img_ptr, 0, 0);
	return (0);
}

void	mandelbrot_fdf(t_cl *cl, t_mlx *mlx)
{
	t_mandelfdf	conf;

	conf.cl = cl;
	conf.mlx = mlx;
	mandelfdf_initialization(&conf);
	mlx_hook(conf.mlx->win, 2, 0, &mandelfdf_keyboard_press, &conf);
	mlx_hook(conf.mlx->win, 4, 0, &mandelfdf_mouse_press, &conf);
	mlx_hook(conf.mlx->win, 5, 0, &mandelfdf_mouse_release, &conf);
	mlx_hook(conf.mlx->win, 3, 0, &mandelfdf_key_release, &conf);
	mlx_hook(conf.mlx->win, 6, 0, &mandelfdf_mouse_move, &conf);
//	mlx_hook(conf.mlx->win, 17, 0, &exit_event, (void*)0);
	mlx_loop_hook(conf.mlx->mlx, &refresh, &conf);
	mlx_loop(conf.mlx->mlx);
	exit(0);
}
