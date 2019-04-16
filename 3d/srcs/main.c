/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 07:30:52 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/16 11:03:44 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		check_pixel(int x, int y, int z, t_fractol fractol)
{
	register int i;
	float	comp_x;
	float	comp_y;
	float	comp_z;
	float	rx;
	float	iy;
	float	jz;
	float	tmp;

	rx = 0.0;
	iy = 0.0;
	jz = 0.0;
	comp_x = ((fractol.right_b - fractol.left_b) / fractol.x_len) * x;
	comp_y = ((fractol.bot_b - fractol.top_b) / fractol.y_len) * y;
	comp_z = ((fractol.front_b - fractol.back_b) / fractol.z_len) * z;
	i = -1;
	while (++i < fractol.depth && jz * jz + rx * rx + iy * iy < 4)
	{
		tmp = rx * rx - iy * iy - jz * jz + comp_x;
		iy = 2 * rx * iy + comp_y;
		jz = 2 * rx * jz + comp_z;
		rx = tmp;
	}
	if (i < fractol.depth)
		return (i);
	else
		return (0);
}

int		refresh(t_conf *conf)
{
	float			step_x;
	float			step_y;
	float			step_z;
	size_t			global_size;
	cl_mem			mem_arr_structs;
	t_cl_sphera		*spheres;
	int				i;
	t_cl_sphera		**all_spheres;
	int				err;

	ft_bzero((void*)conf->mlx->img_data, conf->mlx->size_line * conf->mlx->height);
	all_spheres = (t_cl_sphera**)malloc(sizeof(t_cl_sphera*) * conf->fractol.z_len);
	step_x = (conf->fractol.right_b - conf->fractol.left_b) / conf->fractol.x_len;
	step_y = (conf->fractol.bot_b - conf->fractol.top_b) / conf->fractol.y_len;
	step_z = (conf->fractol.bot_b - conf->fractol.top_b) / conf->fractol.z_len;
	global_size = conf->fractol.x_len * conf->fractol.y_len;
	i = -1;
	while (++i < conf->fractol.z_len)
	{
		spheres = (t_cl_sphera*)ft_memalloc(sizeof(t_cl_sphera) * global_size);
		mem_arr_structs = clCreateBuffer(conf->CL.context, CL_MEM_READ_WRITE,
				global_size * sizeof(t_cl_sphera), NULL, &err);
		if (err != 0)
			printf ("create buffer - error\n");
		err = clSetKernelArg(conf->CL.kernel, 0, sizeof(cl_mem), &mem_arr_structs);
		err = clSetKernelArg(conf->CL.kernel, 1, sizeof(int), &i);
		err = clSetKernelArg(conf->CL.kernel, 2, sizeof(float), &step_x);
		err = clSetKernelArg(conf->CL.kernel, 3, sizeof(float), &step_y);
		err = clSetKernelArg(conf->CL.kernel, 4, sizeof(float), &step_z);
		err = clSetKernelArg(conf->CL.kernel, 5, sizeof(int), &conf->fractol.depth);
		err = clSetKernelArg(conf->CL.kernel, 6, sizeof(int), &conf->fractol.x_len);
		err = clSetKernelArg(conf->CL.kernel, 7, sizeof(int), &conf->fractol.y_len);
		err = clSetKernelArg(conf->CL.kernel, 8, sizeof(int), &conf->fractol.z_len);
		err = clSetKernelArg(conf->CL.kernel, 9, sizeof(float), &conf->fractol.left_b);
		err = clSetKernelArg(conf->CL.kernel, 10, sizeof(float), &conf->fractol.top_b);
		err = clSetKernelArg(conf->CL.kernel, 11, sizeof(float), &conf->fractol.back_b);
		if (err != 0)
			printf ("set kernel arg - error\n");
		err = clEnqueueNDRangeKernel(conf->CL.queue, conf->CL.kernel, 1, NULL, &global_size,
				NULL, 0, NULL, NULL);
		if (err != 0)
			printf("NDR - error\n");
		err = clEnqueueReadBuffer(conf->CL.queue, mem_arr_structs, CL_TRUE, 0, global_size * sizeof(t_cl_sphera),
				spheres, 0, NULL, NULL);
		if (err != 0)
			printf ("read buffer - error\n");
		all_spheres[i] = spheres;
	//	printf ("(%f, %f, %f)\n", all_spheres[i][0].x, all_spheres[i][0].y, all_spheres[i][0].z);
	}
	int objects_num = 0;
	i = -1;
	int j = -1;
	while (++i < conf->fractol.z_len)
	{
		while (++j < conf->fractol.y_len)
			if (all_spheres[i][j].flag == 1)
			{
				printf ("%f, ", all_spheres[i][j].z);
				objects_num++;
			}
		j = -1;
	}
	printf ("\n%d\n", objects_num);
	mlx_clear_window(conf->mlx->mlx, conf->mlx->win);
	mlx_put_image_to_window(conf->mlx->mlx, conf->mlx->win, conf->mlx->img_ptr, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_conf		conf;

	initialization_CL(&conf);
	initialization_fractol(&conf);
	initialization_mlx(&conf);
	initialization_scene(&conf);
	//	mlx_hook(all.win, 2, 0, &keyboard_event, &all);
	//	mlx_hook(all.win, 4, 0, &mouse_event, &all);
	refresh(&conf);
	//	mlx_loop_hook(all.mlx, &refresh, &all);
	mlx_loop(conf.mlx->mlx);
	exit(0);
}
