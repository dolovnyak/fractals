/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:14:31 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/02 06:19:52 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	run_render(t_conf *conf, cl_mem *mem_img,
		cl_mem *mem_objects, cl_mem *mem_lights)
{
	int		err;
	size_t	global_size;

	err = clSetKernelArg(conf->cl.kernel_rt, 0, sizeof(cl_mem), mem_img);
	err |= clSetKernelArg(conf->cl.kernel_rt, 1, sizeof(int), &conf->mlx.width);
	err |= clSetKernelArg(conf->cl.kernel_rt, 2, sizeof(int), &conf->mlx.height);
	err |= clSetKernelArg(conf->cl.kernel_rt, 3, sizeof(int), &conf->objects_num);
	err |= clSetKernelArg(conf->cl.kernel_rt, 4, sizeof(int), &conf->lights_num);
	err |= clSetKernelArg(conf->cl.kernel_rt, 5, sizeof(t_canvas), &conf->canvas);
	err |= clSetKernelArg(conf->cl.kernel_rt, 6, sizeof(cl_mem), mem_objects);
	err |= clSetKernelArg(conf->cl.kernel_rt, 7, sizeof(cl_mem), mem_lights);
	if (err != 0)
		printf("set kernel arg - error\n");
	global_size = conf->mlx.width * conf->mlx.height;
	err = clEnqueueNDRangeKernel(conf->cl.queue, conf->cl.kernel_rt, 1, NULL,
			&global_size, NULL, 0, NULL, NULL);
	if (err != 0)
		printf("NDR - error\n");
	err = clEnqueueReadBuffer(conf->cl.queue, *mem_img, CL_TRUE, 0,
			conf->mlx.size_line * conf->mlx.height,
			conf->mlx.img_data, 0, NULL, NULL);
	if (err != 0)
		printf("read buffer - error\n");
}

void	get_mem_for_render(t_conf *conf, cl_mem *mem_img,
		cl_mem *mem_objects, cl_mem *mem_lights)
{
	int	err;

	*mem_img = clCreateBuffer(conf->cl.context, CL_MEM_READ_WRITE,
			conf->mlx.size_line * conf->mlx.height, NULL, &err);
	*mem_objects = clCreateBuffer(conf->cl.context, CL_MEM_READ_ONLY,
			sizeof(t_object3d) * conf->objects_num, NULL, &err);
	err = clEnqueueWriteBuffer(conf->cl.queue, *mem_objects, CL_TRUE, 0,
			sizeof(t_object3d) * conf->objects_num,
			conf->objects, 0, NULL, NULL);
	*mem_lights = clCreateBuffer(conf->cl.context, CL_MEM_READ_ONLY,
			sizeof(t_lights) * conf->lights_num, NULL, &err);
	err = clEnqueueWriteBuffer(conf->cl.queue, *mem_lights, CL_TRUE, 0,
			sizeof(t_lights) * conf->lights_num, conf->lights, 0, NULL, NULL);
	if (err != 0)
		printf("create buffer - error\n");
}

void	get_math_optimization(t_conf *conf)
{
	conf->canvas.cos_x_rotate = cos(conf->canvas.x_rotation);
	conf->canvas.sin_x_rotate = sin(conf->canvas.x_rotation);
	conf->canvas.cos_y_rotate = cos(conf->canvas.y_rotation);
	conf->canvas.sin_y_rotate = sin(conf->canvas.y_rotation);
	conf->canvas.cos_z_rotate = cos(conf->canvas.z_rotation);
	conf->canvas.sin_z_rotate = sin(conf->canvas.z_rotation);
}

int		refresh(t_conf *conf)
{
	cl_mem		mem_img;
	cl_mem		mem_objects;
	cl_mem		mem_lights;
	int			err;

/*	if (conf->flag_rotation_z_left == 1)
		conf->canvas.z_rotation += 0.05;
	if (conf->flag_rotation_z_right == 1)
		conf->canvas.z_rotation -= 0.05;
	get_math_optimization(conf); */
	get_mem_for_render(conf, &mem_img, &mem_objects, &mem_lights);
	run_render(conf, &mem_img, &mem_objects, &mem_lights);
	mlx_clear_window(conf->mlx.mlx, conf->mlx.win);
	mlx_put_image_to_window(conf->mlx.mlx, conf->mlx.win,
			conf->mlx.img_ptr, 0, 0);
	return (0);
}

int		main(void)
{
	t_conf		conf;

	initialization_cl(&conf.cl); //инициализируются сразу все ядра и для расчета фрактала и для рейтрейса
	initialization_fractal(&conf.fractal); //эта функция лежит в файле с общей инициализацией
	initialization_scene(&conf); //в этой функции будет высчитываться фрактал и записываться в массив объектов как сферы
	initialization_canvas(&conf.canvas);
	initialization_mlx(&conf.mlx);
	refresh(&conf);
	mlx_hook(conf.mlx.win, 2, 0, &key_press, &conf);
//	mlx_hook(conf.mlx.win, 3, 0, &key_release, &conf);
//	mlx_hook(conf.mlx.win, 6, 0, &mouse_move, &conf);
//	mlx_hook(conf.mlx.win, 17, 0, &exit_event, (void*)0);
	mlx_loop(conf.mlx.mlx);
	return (0);
}
