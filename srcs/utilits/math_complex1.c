/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:01:23 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 00:49:52 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_complex.h"

t_complex	cx_pow_norm(t_complex z, int pow)
{
	t_complex	new_z;
	double		cash_pow_x;
	double		cash_pow_y;

	new_z = z;
	if (pow == 4)
	{
		cash_pow_x = z.x * z.x * z.x;
		cash_pow_y = z.y * z.y * z.y;
		new_z.x = cash_pow_x * z.x - 6 * z.x * z.x * z.y * z.y
			+ z.y * cash_pow_y;
		new_z.y = 4 * (cash_pow_x * z.y - z.x * cash_pow_y);
	}
	else if (pow == 5)
	{
		cash_pow_x = z.x * z.x * z.x * z.x;
		cash_pow_y = z.y * z.y * z.y * z.y;
		new_z.x = cash_pow_x * z.x + 5 * z.x * cash_pow_y
			- 10 * z.x * z.x * z.x * z.y * z.y;
		new_z.y = cash_pow_y * z.y + 5 * cash_pow_x * z.y
			- 10 * z.x * z.x * z.y * z.y * z.y;
	}
	return (new_z);
}

t_complex	cx_pow(t_complex z, int pow)
{
	t_complex	new_z;
	double		cash_pow_x;
	double		cash_pow_y;

	if (pow == 2)
	{
		new_z.x = z.x * z.x - z.y * z.y;
		new_z.y = 2 * z.x * z.y;
	}
	else if (pow == 3)
	{
		cash_pow_x = z.x * z.x;
		cash_pow_y = z.y * z.y;
		new_z.x = z.x * cash_pow_x - 3 * z.x * cash_pow_y;
		new_z.y = 3 * cash_pow_x * z.y - z.y * cash_pow_y;
	}
	else
		new_z = cx_pow_norm(z, pow);
	return (new_z);
}

t_complex	cx_dev(t_complex z1, t_complex z2)
{
	t_complex	new_z;
	double		denominator;

	denominator = z2.x * z2.x + z2.y * z2.y;
	new_z.x = (z1.x * z2.x + z1.y * z2.y) / denominator;
	new_z.y = (z1.y * z2.x - z1.x * z2.y) / denominator;
	return (new_z);
}

t_complex	cx_mult(t_complex z1, t_complex z2)
{
	t_complex	new_z;

	new_z.x = z1.x * z2.x - z1.y * z2.y;
	new_z.y = z1.x * z2.y + z2.x * z1.y;
	return (new_z);
}
