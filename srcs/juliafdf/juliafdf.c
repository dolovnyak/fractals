/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   juliafdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:05:16 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 23:10:26 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractalfdf.h"

static void	set_args(t_fractalfdf *conf, cl_mem *mem_img, double step_x,
		double step_y)
{
	int			err;
	cl_kernel	kernel;

	kernel = conf->fractal.cl->kernel_juliafdf;
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), mem_img);
	err |= clSetKernelArg(kernel, 1, sizeof(double), &step_x);
	err |= clSetKernelArg(kernel, 2, sizeof(double), &step_y);
	err |= clSetKernelArg(kernel, 3, sizeof(int), &conf->fractal.depth);
	err |= clSetKernelArg(kernel, 4, sizeof(int), &conf->fractal.mlx->width);
	err |= clSetKernelArg(kernel, 5, sizeof(int), &conf->fractal.mlx->height);
	err |= clSetKernelArg(kernel, 6, sizeof(int), &conf->center_x);
	err |= clSetKernelArg(kernel, 7, sizeof(int), &conf->center_y);
	err |= clSetKernelArg(kernel, 8, sizeof(int), &conf->zoom);
	err |= clSetKernelArg(kernel, 9, sizeof(double), &conf->fractal.left_b);
	err |= clSetKernelArg(kernel, 10, sizeof(double), &conf->fractal.top_b);
	err |= clSetKernelArg(kernel, 11, sizeof(double),
			&conf->fractal.const_real);
	err |= clSetKernelArg(kernel, 12, sizeof(double),
			&conf->fractal.const_imagin);
	err |= clSetKernelArg(kernel, 13, sizeof(double), &conf->angle_x);
	err |= clSetKernelArg(kernel, 14, sizeof(double), &conf->angle_z);
	err |= clSetKernelArg(kernel, 15, sizeof(double), &conf->fractal.radius);
	err |= clSetKernelArg(kernel, 16, sizeof(int), &conf->fractal.color_mult);
	if (err != 0)
		ft_printf("set kernel arg - error\n");
}

static void	set_args_and_run(t_fractalfdf *conf, cl_mem *mem_img)
{
	double		step_x;
	double		step_y;
	size_t		global_size;
	int			err;

	global_size = conf->fractal.mlx->width * conf->fractal.mlx->height;
	step_x = (conf->fractal.right_b - conf->fractal.left_b)
		/ conf->fractal.mlx->width;
	step_y = (conf->fractal.bot_b - conf->fractal.top_b)
		/ conf->fractal.mlx->height;
	set_args(conf, mem_img, step_x, step_y);
	err = clEnqueueNDRangeKernel(conf->fractal.cl->queue,
			conf->fractal.cl->kernel_juliafdf,
			1, NULL, &global_size, NULL, 0, NULL, NULL);
	if (err != 0)
		ft_printf("NDR - error\n");
}

int			juliafdf_refresh(t_fractalfdf *conf)
{
	t_mlx	*mlx;
	int		err;
	cl_mem	mem_img;
	size_t	global_size;

	mlx = conf->fractal.mlx;
	ft_bzero((void*)mlx->img_data, mlx->size_line * mlx->height);
	global_size = mlx->width * mlx->height;
	mem_img = clCreateBuffer(conf->fractal.cl->context, CL_MEM_READ_WRITE,
			mlx->size_line * mlx->height, NULL, &err);
	err = clEnqueueWriteBuffer(conf->fractal.cl->queue, mem_img, CL_TRUE, 0,
			mlx->size_line * mlx->height, mlx->img_data, 0, NULL, NULL);
	if (err != 0)
		ft_printf("create buffer - error\n");
	set_args_and_run(conf, &mem_img);
	err = clEnqueueReadBuffer(conf->fractal.cl->queue, mem_img, CL_TRUE, 0,
			mlx->size_line * mlx->height, mlx->img_data, 0, NULL, NULL);
	if (err != 0)
		ft_printf("read buffer - error\n");
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_ptr, 0, 0);
	clReleaseMemObject(mem_img);
	return (0);
}

void		julia_fdf(t_cl *cl)
{
	t_fractalfdf	conf;
	t_mlx			mlx;

	initialization_mlx_fdf(&mlx);
	conf.fractal.cl = cl;
	conf.fractal.mlx = &mlx;
	juliafdf_initialization(&conf);
	mlx_hook(conf.fractal.mlx->win, 2, 0, &juliafdf_key_press, &conf);
	mlx_hook(conf.fractal.mlx->win, 3, 0, &commonfdf_key_release, &conf);
	mlx_hook(conf.fractal.mlx->win, 4, 0, &commonfdf_mouse_press, &conf);
	mlx_hook(conf.fractal.mlx->win, 5, 0, &commonfdf_mouse_release, &conf);
	mlx_hook(conf.fractal.mlx->win, 6, 0, &juliafdf_mouse_move, &conf);
	mlx_hook(conf.fractal.mlx->win, 17, 0, &exit_event, conf.fractal.cl);
	mlx_loop_hook(conf.fractal.mlx->mlx, &juliafdf_refresh, &conf);
	mlx_loop(conf.fractal.mlx->mlx);
}
