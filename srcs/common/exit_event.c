/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:54:57 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 21:40:04 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		exit_event(t_cl *cl)
{
	clReleaseKernel(cl->kernel_mandel2d);
	clReleaseKernel(cl->kernel_mandel2d_pow5);
	clReleaseKernel(cl->kernel_mandelfdf);
	clReleaseKernel(cl->kernel_mandel3d);
	clReleaseKernel(cl->kernel_julia2d);
	clReleaseKernel(cl->kernel_juliafdf);
	clReleaseKernel(cl->kernel_julia2d_pow5);
	clReleaseKernel(cl->kernel_julia3d);
	clReleaseKernel(cl->kernel_burning_ship2d);
	clReleaseKernel(cl->kernel_burning_ship2d_pow5);
	clReleaseKernel(cl->kernel_newton1);
	clReleaseKernel(cl->kernel_newton2);
	clReleaseKernel(cl->kernel_fractal_dick);
	clReleaseKernel(cl->kernel_rt_safety);
	clReleaseKernel(cl->kernel_rt_fast);
	clReleaseCommandQueue(cl->queue);
	clReleaseProgram(cl->program);
	clReleaseContext(cl->context);
	exit(0);
}
