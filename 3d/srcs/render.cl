#include "config_cl.h"

void        put_pixel(int x, int y, t_color color, __global char* img, int width, int height)
{
    int a;

    y = height - y;
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        a = x * 4 + y * width * 4;
        img[a] = color.b;
        img[a + 1] = color.g;
        img[a + 2] = color.r;
        img[a + 3] = 0;
    }
}

t_vector3d	rotation(t_vector3d A, float cos_x_rotate, float sin_x_rotate, 
				float cos_y_rotate, float sin_y_rotate, float cos_z_rotate, float sin_z_rotate)
{
	t_vector3d	res;

//	res.x = A.x;
	res.y = A.y * cos_x_rotate - A.z * sin_x_rotate;
	res.z = A.y * sin_x_rotate + A.z * cos_x_rotate;
	A = res;
	res.x = A.x * cos_y_rotate + A.z * sin_y_rotate;
//	res.y = A.y;
	res.z = A.z * cos_y_rotate - A.x * sin_y_rotate;
	A = res;
	res.x = A.x * cos_z_rotate - A.y * sin_z_rotate;
	res.y = A.x * sin_z_rotate + A.y * cos_z_rotate;
	return (res);
}

__kernel void render(__global char* img, int width, int height, int y,
		int objects_num, int lights_num, t_canvas canvas,
		__global t_object3d* objects, __global t_lights* lights)
{
	int			gid;
	t_scene		scene;
	t_color		color;
	t_vector3d	cam_ray;

	gid = get_global_id(0);
	scene.objects_num = objects_num;
	scene.lights_num = lights_num;
	scene.objects = objects;
	scene.lights = lights;
	scene.min_distance = canvas.min_distance;
	scene.max_distance = canvas.max_distance;
	cam_ray = get_cam_ray(gid % width, y, canvas, width, height);
	cam_ray = rotation(cam_ray, canvas.cos_x_rotate, canvas.sin_x_rotate,
				canvas.cos_y_rotate, canvas.sin_y_rotate, canvas.cos_z_rotate, canvas.sin_z_rotate);
	color = ray_trace(canvas.camera, cam_ray, &scene);
	put_pixel(gid % width, y, color, img, width, height);
}
