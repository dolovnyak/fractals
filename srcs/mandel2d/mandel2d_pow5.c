/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:30:52 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 22:58:10 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal2d.h"

static void	set_args_and_run(t_fractal2d *conf, cl_mem *mem_img)
{
	double		step_x;
	double		step_y;
	size_t		global_size;
	int			err;
	cl_kernel	kernel;

	kernel = conf->cl->kernel_mandel2d_pow5;
	global_size = conf->mlx->width * conf->mlx->height;
	step_x = (conf->right_b - conf->left_b) / conf->mlx->width;
	step_y = (conf->bot_b - conf->top_b) / conf->mlx->height;
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), mem_img);
	err |= clSetKernelArg(kernel, 1, sizeof(double), &step_x);
	err |= clSetKernelArg(kernel, 2, sizeof(double), &step_y);
	err |= clSetKernelArg(kernel, 3, sizeof(int), &conf->depth);
	err |= clSetKernelArg(kernel, 4, sizeof(int), &conf->mlx->width);
	err |= clSetKernelArg(kernel, 5, sizeof(double), &conf->left_b);
	err |= clSetKernelArg(kernel, 6, sizeof(double), &conf->top_b);
	err |= clSetKernelArg(kernel, 7, sizeof(double), &conf->radius);
	err |= clSetKernelArg(kernel, 8, sizeof(int), &conf->color_mult);
	if (err != 0)
		ft_printf("set kernel arg - error\n");
	err = clEnqueueNDRangeKernel(conf->cl->queue, kernel, 1, NULL, &global_size,
		NULL, 0, NULL, NULL);
	if (err != 0)
		ft_printf("NDR - error\n");
}

static int	mandel2d_refresh(t_fractal2d *conf)
{
	int		err;
	cl_mem	mem_img;

	mem_img = clCreateBuffer(conf->cl->context, CL_MEM_READ_WRITE,
			conf->mlx->size_line * conf->mlx->height, NULL, &err);
	if (err != 0)
		ft_printf("create buffer - error\n");
	set_args_and_run(conf, &mem_img);
	err = clEnqueueReadBuffer(conf->cl->queue, mem_img, CL_TRUE, 0,
			conf->mlx->size_line * conf->mlx->height, conf->mlx->img_data,
		0, NULL, NULL);
	if (err != 0)
		ft_printf("read buffer - error\n");
	mlx_clear_window(conf->mlx->mlx, conf->mlx->win);
	mlx_put_image_to_window(conf->mlx->mlx, conf->mlx->win,
			conf->mlx->img_ptr, 0, 0);
	clReleaseMemObject(mem_img);
	return (0);
}

void		mandelbrot_2d_pow5(t_cl *cl)
{
	t_fractal2d	conf;
	t_mlx		mlx;

	initialization_mlx2d(&mlx);
	conf.cl = cl;
	conf.mlx = &mlx;
	mandel2d_initialization(&conf);
	mlx_hook(conf.mlx->win, 2, 0, &common2d_key_press, &conf);
	mlx_hook(conf.mlx->win, 4, 0, &common2d_mouse_press, &conf);
	mlx_hook(conf.mlx->win, 17, 0, &exit_event, conf.cl);
	mlx_loop_hook(conf.mlx->mlx, &mandel2d_refresh, &conf);
	mlx_loop(conf.mlx->mlx);
}
