#include "test_program.h"

int main()
{
	int			err;
	t_cl		cl;
	t_conf		conf;
	cl_mem		mem_arr_structs;
	t_sphera	*spheres;

	printf ("MAX_SIZE: %d\n", CL_DEVICE_GLOBAL_MEM_SIZE);
	printf ("t_sphere: %lu\n", sizeof(t_sphera));
	size_t arrlen = 800 * 800 * 17 + 304810;
	printf ("CHECK1\n");
	spheres = (t_sphera*)ft_memalloc(sizeof(t_sphera) * arrlen);
	initialization_CL(&cl);
	initialization_conf(&conf);
	mem_arr_structs = clCreateBuffer(cl.context, CL_MEM_READ_WRITE, arrlen * sizeof(t_sphera),
			NULL, &err);
	if (err != 0)
		printf("create buffer - error\n");
	printf ("CHECK2\n");
	err = clEnqueueWriteBuffer(cl.queue, mem_arr_structs, CL_TRUE, 0,
			arrlen * sizeof(t_sphera), spheres, 0, NULL, NULL);
	if (err != 0)
		printf ("write data in buffer - error\n");
	err = clSetKernelArg(cl.kernel, 0, sizeof(cl_mem), &mem_arr_structs);
	if (err != 0)
		printf("set arg - error\n");
	printf ("CHECK3\n");
	err = clEnqueueNDRangeKernel(cl.queue, cl.kernel, 1, NULL, &arrlen,
		NULL, 0, NULL, NULL);
	if (err != 0)
		printf ("NDRange - error\n");
	err = clEnqueueReadBuffer(cl.queue, mem_arr_structs, CL_TRUE, 0, arrlen * sizeof(t_sphera),
		spheres, 0, NULL, NULL);
	if (err != 0)
		printf ("error\n");
}
