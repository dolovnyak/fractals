/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 12:26:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/09/04 15:28:26 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "render.h"

static int	check_julia_arg(char **argv, t_cl *cl)
{
	t_render	render_data;

	if (ft_strequ(argv[1], "julia_2d"))
		julia_2d(cl);
	else if (ft_strequ(argv[1], "julia_2d_pow5"))
		julia_2d_pow5(cl);
	else if (ft_strequ(argv[1], "julia_3d_safety"))
	{
		render_data.get_fractal = julia_3d;
		render_data.fractal = (t_fractal3d*)malloc(sizeof(t_fractal3d));
		render_safety(cl, &render_data);
	}
	else if (ft_strequ(argv[1], "julia_3d_fast"))
	{
		render_data.get_fractal = julia_3d;
		render_data.fractal = (t_fractal3d*)malloc(sizeof(t_fractal3d));
		render_fast(cl, &render_data);
	}
	else if (ft_strequ(argv[1], "julia_fdf"))
		julia_fdf(cl);
	return (0);
}

static int	check_mabdelbrot_arg(char **argv, t_cl *cl)
{
	t_render	render_data;

	if (ft_strequ(argv[1], "mandelbrot_2d"))
		mandelbrot_2d(cl);
	else if (ft_strequ(argv[1], "mandelbrot_2d_pow5"))
		mandelbrot_2d_pow5(cl);
	else if (ft_strequ(argv[1], "mandelbrot_fdf"))
		mandelbrot_fdf(cl);
	else if (ft_strequ(argv[1], "mandelbrot_3d_fast"))
	{
		render_data.get_fractal = mandelbrot_3d;
		render_data.fractal = (t_fractal3d*)malloc(sizeof(t_fractal3d));
		render_fast(cl, &render_data);
	}
	else if (ft_strequ(argv[1], "mandelbrot_3d_safety"))
	{
		render_data.get_fractal = mandelbrot_3d;
		render_data.fractal = (t_fractal3d*)malloc(sizeof(t_fractal3d));
		render_safety(cl, &render_data);
	}
	else if (ft_strequ(argv[1], "burning_ship_2d"))
		burning_ship_2d(cl);
	else if (ft_strequ(argv[1], "burning_ship_2d_pow5"))
		burning_ship_2d_pow5(cl);
	return (0);
}

static void	print_usage(void)
{
	ft_printf("input:\n");
	ft_printf("mandelbrot_2d, mandelbrot_2d_pow5, mandelbrot_fdf, mandelbrot_3d_fast, mandelbrot_3d_safety;\n");
	ft_printf("julia_2d, julia_2d_pow5, julia_fdf, julia_3d_fast, julia_3d_safety;\n");
	ft_printf("burning_ship_2d, burning_ship_2d_pow5;\n");
	ft_printf("newton1, newton2\n");
	ft_printf("fractal_dick\n");
}

int			main(int argc, char **argv)
{
	t_cl		cl;

	if (argc != 2)
	{
		print_usage();
		return (0);
	}
	initialization_cl(&cl);
	if (check_mabdelbrot_arg(argv, &cl))
		return (0);
	else if (check_julia_arg(argv, &cl))
		return (0);
	else if (ft_strequ(argv[1], "newton1"))
		newton1(&cl);
	else if (ft_strequ(argv[1], "newton2"))
		newton2(&cl);
	else if (ft_strequ(argv[1], "fractal_dick"))
		fractal_dick(&cl);
	else
		print_usage();
	exit_event(&cl);
	return (0);
}
