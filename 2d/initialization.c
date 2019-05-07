/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 22:06:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 08:17:19 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

cl_device_id    get_device_id(void)
{
	cl_platform_id      platform; //Платформа дающая доступ к устройтсву
	cl_device_id        device; //устройство
	int err;

	err = clGetPlatformIDs(1, &platform, NULL);
	if (err != 0)
		printf ("Get platform - error\n");
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if (err != 0)
		printf ("Get device id - error\n");
	return (device);
}

cl_kernel   get_kernel(cl_device_id *device, cl_context context)
{
	cl_program          program;
	FILE    *fd;
	char    *program_buf;
	size_t  program_size;
	int     err;
	cl_kernel kernel;

	fd = fopen(PROGRAM_FILE, "r");
	if (!fd)
		printf ("Open kernel file - bad\n");
	fseek(fd, 0, SEEK_END); //сместить указатель в файле на конец файла
	program_size = ftell(fd); //кол-во байт в файле
	rewind(fd); //вернуть указатель на начало фалйа
	program_buf = (char*)malloc(program_size + 1);
	fread(program_buf, sizeof(char), program_size, fd);
	program_buf[program_size] = '\0';
	fclose(fd);
	program = clCreateProgramWithSource(context, 1, (const char**)&program_buf,
			(const size_t*)&program_size, &err);
	err = clBuildProgram(program, 1, device, NULL, NULL, NULL);
	if (err != 0)
		printf ("build program - bad\n");
	kernel = clCreateKernel(program, "mandelbrot", &err);
	if (err != 0)
		printf ("create kernel - bad\n");
	return (kernel);
}

void    initialization_Cl(t_all *all)
{
	cl_device_id        device;
	int err;

	device = get_device_id();
	all->context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err != 0)
		printf ("create context - bad\n");
	all->queue = clCreateCommandQueue(all->context, device, 0, &err);
	if (err != 0)
		printf ("create command queue - bad\n");
	all->kernel = get_kernel(&device, all->context);
}

void	initialization_all(t_all *all)
{
	all->s_width = 1200;
	all->s_height = 1200;
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->s_width, all->s_height, "fractol");
	all->img_ptr = mlx_new_image(all->mlx, all->s_width, all->s_height);
	all->img_data = mlx_get_data_addr(all->img_ptr, &all->bpp, &all->size_line, &all->endian);
	all->zoom = 0;
	all->left_b = -2.0;
	all->right_b = 1.0;
	all->top_b = -1.5;
	all->bot_b = 1.5;
	all->depth = 1000;
}
