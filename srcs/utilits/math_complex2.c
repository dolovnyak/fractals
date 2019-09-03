/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_complex2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 00:49:48 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 00:51:10 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_complex.h"

t_complex	cx_plus(t_complex z1, t_complex z2)
{
	t_complex	new_z;

	new_z.x = z1.x + z2.x;
	new_z.y = z1.y + z2.y;
	return (new_z);
}

t_complex	cx_minus(t_complex z1, t_complex z2)
{
	t_complex	new_z;

	new_z.x = z1.x - z2.x;
	new_z.y = z1.y - z2.y;
	return (new_z);
}

t_complex	cx_mult_real(t_complex z, double num)
{
	z.x *= num;
	z.y *= num;
	return (z);
}

t_complex	cx_plus_real(t_complex z, double num)
{
	z.x += num;
	return (z);
}

t_complex	cx_minus_real(t_complex z, double num)
{
	z.x -= num;
	return (z);
}
