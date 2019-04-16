#include <OpenCL/opencl.h>
#include <stdio.h>

#define PROGRAM_FILE "test_for_OpenCl.cl"

typedef struct	s_OpenCl
{
	cl_command_queue	queue;
	cl_context			context;
	cl_kernel			kernel;
}				t_cl;

cl_device_id	get_device_id(void)
{
	cl_platform_id		platform; //Платформа дающая доступ к устройтсву
	cl_device_id		device; //устройство
	int	err;
	
	err = clGetPlatformIDs(1, &platform, NULL);
	if (err != 0)
		printf ("Get platform - error\n");
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if (err != 0)
		printf ("Get device id - error\n");
	return (device);
}

cl_kernel	get_kernel(cl_device_id *device, cl_context context)
{
	cl_program			program;
	FILE	*fd;
	char	*program_buf;
	size_t	program_size;
	int		err;
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
	kernel = clCreateKernel(program, "test", &err);
	if (err != 0)
		printf ("create kernel - bad\n");
	return (kernel);
}

void	initialization_Cl(t_cl *cl)
{
	cl_device_id		device;
	int	err;

	device = get_device_id();
	cl->context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err != 0)
		printf ("create context - bad\n");
	cl->queue = clCreateCommandQueue(cl->context, device, 0, &err);
	if (err != 0)
		printf ("create command queue - bad\n");
	cl->kernel = get_kernel(&device, cl->context);
}

int	main()
{
	int		err;
	t_cl	cl;
	initialization_Cl(&cl);
	cl_mem	memobj = NULL;
	int		memlen = 10;
	cl_int	*mem = (cl_int*)malloc(sizeof(cl_int) * memlen);
	mem[0] = 0;
	mem[1] = 10;
	mem[2] = 20;
	mem[3] = 30;
	mem[4] = 40;
	mem[5] = 50;
	mem[6] = 60;
	mem[7] = 70;
	mem[8] = 80;
	mem[9] = 90;

	memobj = clCreateBuffer(cl.context, CL_MEM_READ_WRITE, memlen * sizeof(cl_int),
			NULL, &err);
	if (err != 0)
		printf ("create buffer - bad\n");
	err = clEnqueueWriteBuffer(cl.queue, memobj, CL_TRUE, 0, memlen * sizeof(cl_int),
			mem, 0, NULL, NULL);
	if (err != 0)
		printf ("write data in buffer - bad\n");
	err = clSetKernelArg(cl.kernel, 0, sizeof(cl_mem), (void*)&memobj);
	if (err != 0)
		printf ("BAD\n");

	size_t	global_work_size[1] = { 10 };
	err = clEnqueueNDRangeKernel(cl.queue, cl.kernel, 1, NULL, global_work_size,
			NULL, 0, NULL, NULL);
	if (err != 0)
		printf ("BAD\n");
	err = clEnqueueReadBuffer(cl.queue, memobj, CL_TRUE, 0, memlen * sizeof(int),
			mem, 0, NULL, NULL);
	if (err != 0)
		printf ("BAD\n");
	int i = -1;
	while (++i < 10)
		printf ("%d\n", mem[i]);
}
