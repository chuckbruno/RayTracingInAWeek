// PPM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"
#include <stdlib.h>

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX)) - vec3(1, 1, 1);

	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 color(const ray& r, hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0f, FLT_MAX, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color(ray(rec.p, target-rec.p), world);
	}
	else {
		vec3 unit_dirction = unit_vector(r.direction());
		float t = 0.5 * (unit_dirction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

//vec3 color(const ray& r) {
//	float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
//	if (t > 0.0) {
//		//return vec3(1, 0, 0);
//		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
//		return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
//	}
//
//	vec3 unit_dirction = unit_vector(r.direction());
//	t = 0.5 * (unit_dirction.y() + 1.0);
//	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//}


int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 10;

	//vec3 col1(1.3f, 2.5f, 3.9f);
	//vec3 col2(2.3f, 5.5f, 6.9f);

	//std::cout << col1.length() << std::endl;
	//col1 += col2;
	//col1 + col2;
	//	//1.3f, 2.5f, 3.9f
	//col1.make_unit_vector();
	//std::cout << col1 + col2 << std::endl;
	//std::cout << col1 - col2 << std::endl;
	//std::cout << col1 * col2 << std::endl;
	//std::cout << col1 / col2 << std::endl;
	//std::cout << col1.length()<< std::endl;
	//std::cout << col2.length() << std::endl;
	//col2 *= 3;
	//col2 *= col1;
	//std::cout << col2 << std::endl;

	std::string file_path = "image.ppm";
	std::ofstream fout(file_path.c_str());
	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	fout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {

			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float rand_num = ((float)rand() / (RAND_MAX));
				float u = float(i + rand_num) / float(nx);
				float v = float(j + rand_num) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}

			col /= float(ns);
			col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
			//std::cout << col << std::endl;
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			fout << ir << " " << ig << " " << ib << "\n";
		}
	}

	fout.close();
	std::cout << "Hello World!\n";
}
