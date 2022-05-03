// PPM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "sphere.h"
#include "hitable.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"
#include <stdlib.h>
#include "random.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"


vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 7 && rec.mat_ptr != nullptr && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        else {
            return vec3(0, 0, 0);
        }
        //vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        //return 0.5*color(ray(rec.p, target-rec.p), world);
    }
    else {
        vec3 unit_dirction = unit_vector(r.direction());
        float t = 0.5 * (unit_dirction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}


//vec3 color(const ray& r) {
//  float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
//  if (t > 0.0) {
//      //return vec3(1, 0, 0);
//      vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
//      return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
//  }
//
//  vec3 unit_dirction = unit_vector(r.direction());
//  t = 0.5 * (unit_dirction.y() + 1.0);
//  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//}

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n + 1];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = random_double();
            vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(random_double()*random_double(),
                                                                            random_double()*random_double(),
                                                                            random_double()*random_double())));
                }
                else if (choose_mat < 0.95) {
                    list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1 + random_double()*random_double()), 
                                                                       0.5*(1 + random_double()*random_double()),
                                                                       0.5*(1 + random_double()*random_double())),
                                                                        0.5*random_double()));
                }
                else {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list, i);
}


int main()
{
    int nx = 1920;
    int ny = 1080;
    int ns = 10;

    //vec3 col1(1.3f, 2.5f, 3.9f);
    //vec3 col2(2.3f, 5.5f, 6.9f);

    //std::cout << col1.length() << std::endl;
    //col1 += col2;
    //col1 + col2;
    //  //1.3f, 2.5f, 3.9f
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

    hitable *world = random_scene();
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    //hitable *list[5];
    //list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    //list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    //list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0));
    //list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    //list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
    //float R = cos(M_PI / 4);
    //list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
    //list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
    //hitable *world = new hitable_list(list, 5);
    //vec3 lookfrom(-2, 2, 1);
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);

    //float dist_to_focus = (lookfrom - lookat).length();
    float dist_to_focus = 10;
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vup, 20, float(nx)/float(ny), aperture, dist_to_focus);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {

            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                ray r = cam.get_ray(u, v);
                //vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
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


