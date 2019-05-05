/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:56:56 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/04 07:23:02 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	ft_exit(t_conf *conf)
{
	clReleaseKernel(conf->cl.kernel_rt);
	clReleaseKernel(conf->cl.kernel_mandel);
	clReleaseProgram(conf->cl.program);
	clReleaseCommandQueue(conf->cl.queue);
	clReleaseContext(conf->cl.context);
	exit(0);
}
