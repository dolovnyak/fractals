/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 22:06:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/18 12:31:27 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_program.h"

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

char	*get_program_buf(const char *name, size_t *program_size)
{
	size_t	file_size;
	FILE	*fd;
	char	*buf;

	fd = fopen(name, "r");
	if (!fd)
		printf ("Open kernel file - bad\n");
	fseek(fd, 0, SEEK_END);
	file_size = ftell(fd);
	rewind(fd);
	buf = (char*)malloc(file_size + 1);
	fread(buf, sizeof(char), file_size, fd);
	buf[file_size] = '\0';
	fclose(fd);
	*program_size = file_size;
	return (buf);
}

cl_kernel   get_kernel(cl_device_id *device, cl_context context)
{
	cl_program          program;
	FILE    *fd;
	char	**program_buf;
	size_t  *program_size;
	int     err;
	cl_kernel kernel;

	int	files_num = 2;
	program_buf = (char**)malloc(sizeof(char*) * files_num);
	program_size = (size_t*)malloc(sizeof(size_t) * files_num);
	program_buf[0] = get_program_buf("check_struct.cl", &program_size[0]);
	program_buf[1] = get_program_buf("ft_printf.cl", &program_size[1]);
	program = clCreateProgramWithSource(context, files_num, (const char**)program_buf,
			(const size_t*)program_size, &err);
	err = clBuildProgram(program, 1, device, NULL, NULL, NULL);
	if (err != 0)
		printf ("build program - error\n");
	kernel = clCreateKernel(program, "check_struct", &err);
	if (err != 0)
		printf ("create kernel - error\n");
	return (kernel);
}

void    initialization_CL(t_cl *cl)
{
	cl_device_id        device;
	int err;

	device = get_device_id();
	cl->context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err != 0)
		printf ("create context - bad\n");
	cl->queue = clCreateCommandQueue(cl->context, device, 0, &err);
	if (err != 0)
		printf ("create command queue - bad\n");
	cl->kernel = get_kernel(&device, cl->context);
}

void	initialization_conf(t_conf *conf)
{
	conf->x_len = 800;
	conf->y_len = 800;
	conf->z_len = 800;
}
