#ifndef H_RAY_TRACING
#define H_RAY_TRACING
#include "crossable_amp.h"
using namespace ray_tracing;

#define init_triangle(ax, ay, az, bx, by, bz, cx, cy, cz, material_id)	\
	{{ax, ay, az}, {bx, by, bz}, {cx, cy, cz}, \
	normalize(cross(float_3(bx, by, bz) - float_3(ax, ay, az), \
	float_3(cx, cy, cz) - float_3(ax, ay, az))), material_id, \
	/*{max(max(ax, bx), cx), max(max(ay, by), cy), max(max(az, bz), cz)},	\
	{min(min(ax, bx), cx), min(min(ay, by), cy), min(min(az, bz), cz)}*/}

#define init_sphere(ox, oy, oz, r, material_id, visible)	\
	{{ox, oy, oz}, r, material_id, visible/*, {ox + r, oy + r, oz + r}, {ox - r, oy - r, oz - r}*/}

#define init_color(r, g, b) \
	{0x##r / 255.0f, 0x##g / 255.0f, 0x##b / 255.0f}

const uint VIEW_ROW = 600u;
const uint VIEW_COL = 800u;
const uint RANDOM_TABLE_SIZE = 100000u;
const float FOV = 60.0f;
const float MIN_VIEW = 0.1f;

struct ray_tracing_controller {
	ray_tracing_controller();
	void render();
private:
	void update_messages();
	void set_results();

	float results[VIEW_ROW][VIEW_COL][3];	//rgb

	array_view<float, 1> self_arr_random = array_view<float, 1>(RANDOM_TABLE_SIZE);
	array_view<uint, 2> self_arr_random_init = array_view<uint, 2>((int)VIEW_ROW, (int)VIEW_COL);

	float view_resolusion;
	float_3 eye;
	float_3 look_at;
	float_3 camera_up;

	triangle triangles[2];

	sphere spheres[10];
};

#endif