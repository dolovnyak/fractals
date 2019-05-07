#ifndef TEST_PROGRAM_H
# define TEST_PROGRAM_H

#include <OpenCL/opencl.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct  s_cl
{
	cl_command_queue    queue;
	cl_context          context;
	cl_kernel           kernel;
}               t_cl;

typedef struct	s_conf
{
	int                 x_len;
	int                 y_len;
	int                 z_len;
}				t_conf;
	
typedef struct  s_sphera
{
	float    x;
	float    y;
	float    z;
	float    radius;
	int      r;
	int      g;
	int      b;
	int      flag;
}               t_sphera;

void	initialization_CL(t_cl *cl);
void	initialization_conf(t_conf *conf);

#endif
