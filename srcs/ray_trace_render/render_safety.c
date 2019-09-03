/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:14:31 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 23:14:48 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	error_processing(int err, int flag)
{
	if (err != 0)
	{
		if (flag == 1)
			ft_printf("set kernel arg - error\n");
		else if (flag == 2)
			ft_printf("NDR - error\n");
		else if (flag == 3)
			ft_printf("read buffer - error\n");
	}
}

static void	run_render(t_render *conf, int y)
{
	int			err;
	size_t		global_size;
	cl_kernel	kernel;

	kernel = conf->cl->kernel_rt_safety;
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &conf->mem_img);
	err |= clSetKernelArg(kernel, 1, sizeof(int), &conf->mlx->width);
	err |= clSetKernelArg(kernel, 2, sizeof(int), &conf->mlx->height);
	err |= clSetKernelArg(kernel, 3, sizeof(int), &y);
	err |= clSetKernelArg(kernel, 4, sizeof(int), &conf->objects_num);
	err |= clSetKernelArg(kernel, 5, sizeof(int), &conf->lights_num);
	err |= clSetKernelArg(kernel, 6, sizeof(t_canvas), &conf->canvas);
	err |= clSetKernelArg(kernel, 7, sizeof(cl_mem), &conf->mem_objects);
	err |= clSetKernelArg(kernel, 8, sizeof(cl_mem), &conf->mem_lights);
	error_processing(err, 1);
	global_size = conf->mlx->width;
	err = clEnqueueNDRangeKernel(conf->cl->queue, kernel, 1, NULL,
			&global_size, NULL, 0, NULL, NULL);
	error_processing(err, 2);
	err = clEnqueueReadBuffer(conf->cl->queue, conf->mem_img, CL_TRUE, 0,
			conf->mlx->size_line * conf->mlx->height,
			conf->mlx->img_data, 0, NULL, NULL);
	error_processing(err, 3);
}

static void	get_mem_for_render(t_render *conf)
{
	int	err;

	conf->mem_img = clCreateBuffer(conf->cl->context, CL_MEM_READ_WRITE,
			conf->mlx->size_line * conf->mlx->height, NULL, &err);
	conf->mem_objects = clCreateBuffer(conf->cl->context, CL_MEM_READ_ONLY,
			sizeof(t_object3d) * conf->objects_num, NULL, &err);
	err = clEnqueueWriteBuffer(conf->cl->queue, conf->mem_objects, CL_TRUE, 0,
			sizeof(t_object3d) * conf->objects_num,
			conf->objects, 0, NULL, NULL);
	conf->mem_lights = clCreateBuffer(conf->cl->context, CL_MEM_READ_ONLY,
			sizeof(t_lights) * conf->lights_num, NULL, &err);
	err = clEnqueueWriteBuffer(conf->cl->queue, conf->mem_lights, CL_TRUE, 0,
			sizeof(t_lights) * conf->lights_num, conf->lights, 0, NULL, NULL);
	if (err != 0)
		ft_printf("create buffer - error\n");
}

int			refresh_rt_safety(t_render *conf)
{
	register int	i;

	conf->canvas.cos_x_rotate = cos(conf->canvas.x_rotation);
	conf->canvas.sin_x_rotate = sin(conf->canvas.x_rotation);
	conf->canvas.cos_y_rotate = cos(conf->canvas.y_rotation);
	conf->canvas.sin_y_rotate = sin(conf->canvas.y_rotation);
	conf->canvas.cos_z_rotate = cos(conf->canvas.z_rotation);
	conf->canvas.sin_z_rotate = sin(conf->canvas.z_rotation);
	i = -1;
	get_mem_for_render(conf);
	while (++i <= conf->mlx->height)
	{
		run_render(conf, i);
		if (i % 100 == 0)
			ft_printf("pixels: %d \\ %d\n", (i + 1) * conf->mlx->width,
					conf->mlx->width * conf->mlx->height);
	}
	mlx_clear_window(conf->mlx->mlx, conf->mlx->win);
	mlx_put_image_to_window(conf->mlx->mlx, conf->mlx->win,
			conf->mlx->img_ptr, 0, 0);
	clReleaseMemObject(conf->mem_img);
	clReleaseMemObject(conf->mem_objects);
	clReleaseMemObject(conf->mem_lights);
	return (0);
}

void		render_safety(t_cl *cl, t_render *conf)
{
	t_mlx	mlx;

	initialization_mlx3d(&mlx);
	conf->cl = cl;
	conf->mlx = &mlx;
	initialization_fractal3d_safety(conf->fractal);
	initialization_scene(conf);
	initialization_canvas(&conf->canvas, conf->mlx->relation);
	refresh_rt_safety(conf);
	mlx_hook(conf->mlx->win, 2, 0, &rt_key_press_safety, conf);
	mlx_hook(conf->mlx->win, 17, 0, &exit_event, conf->cl);
	mlx_loop(conf->mlx->mlx);
}
