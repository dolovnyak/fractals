#include "fractol.h"

int		mouse_event(int button, int x, int y, t_all *all)
{
	double  basis;
	double  comp_x;
	double  comp_y;
	double	dx, dy, tmp_x;

	dx = all->zoom * (x - all->s_width / 2);
	dy = all->zoom * (y - all->s_height / 2);
	tmp_x = all->center_x + dx * cos(all->angle_z) - dy * sin(all->angle_z);
	dy = all->center_y - dy * cos(all->angle_z) + dx * sin(all->angle_z);
	dx = tmp_x;
	if (button == 4 && all->control_flag == 1)
	{
		comp_x = (all->right_b - all->left_b) / all->s_width * dx;
		comp_y = (all->bot_b - all->top_b) / all->s_height * dy;
		all->left_b = all->left_b + comp_x /8;
		all->right_b = all->right_b - ((all->right_b - all->left_b) - comp_x) / 8;
		all->top_b = all->top_b + comp_y / 8;
		all->bot_b = all->bot_b - ((all->bot_b - all->top_b) - comp_y) / 8;
		//	all->up_height += 0.5;
	}
	else if (button == 4)
		all->zoom += 1;
	if (button == 5 && all->control_flag == 1)
	{
		comp_x = (all->right_b - all->left_b) / 8;
		comp_y = (all->bot_b - all->top_b) / 8;
		all->left_b -= comp_x;
		all->right_b += comp_x;
		all->top_b -= comp_y;
		all->bot_b += comp_y;
		//	all->up_height -= 0.5;
	}
	else if (button == 5 && all->zoom > 1)
		all->zoom -= 1;
	if (button == 1 && all->button_flag == 0)
	{
		all->button_flag = 1;
		all->mouse_x = x;
		all->mouse_y = y;
	}
	return (0);
}

int		mouse_release(int button, int x, int y, t_all *all)
{
	if (button == 1)
		all->button_flag = 0;
	x = 0;
	y = 0;
	return (0);
}

int		mouse_move(int x, int y, t_all *all)
{
	if (all->button_flag == 1)
	{
		if (x < all->mouse_x)
		{
			all->angle_z += 0.05;
			all->mouse_x = x;
		}
		else if (x > all->mouse_x)
		{
			all->angle_z -= 0.05;
			all->mouse_x = x;
		}
		if (y < all->mouse_y && all->angle_x >= 0)
		{
			all->angle_x -= 0.02;
			all->mouse_y = y;
		}
		else if (y > all->mouse_y && all->angle_x <= 3.14159)
		{
			all->angle_x += 0.02;
			all->mouse_y = y;
		}
	}
	return (0);
}
