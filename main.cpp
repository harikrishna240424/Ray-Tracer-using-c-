#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <stdlib.h> //just to clear console screan.(system("cls")) and rand()
using namespace std;

int main()
{

    system("cls");

    // World

    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<dielectric>(1.00 / 1.33);
    auto material_left = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    auto material_mini1 = make_shared<metal>(color(1, 0.0, 0.0), 0.5);
    auto material_mini2 = make_shared<metal>(color(1, 0.6, 0.0), 0.5);
    auto material_mini3 = make_shared<dielectric>(1.00 / 1.33);
    auto material_mini4 = make_shared<dielectric>(1.00 / 1.50);
    auto material_mini5 = make_shared<lambertian>(color(0.0, 0.95, 1.0));
    auto material_mini6 = make_shared<lambertian>(color(0.0, 0.25, 1.0));
    auto material_mini7 = make_shared<metal>(color(1, 0.0, 0.85), 1.0);
    auto material_mini8 = make_shared<lambertian>(color(1, 0.65, 0.95));

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.4, material_right));

    world.add(make_shared<sphere>(point3(2.0, 0.0, -0.5), 0.2, material_mini1));
    world.add(make_shared<sphere>(point3(-1.7, 0.0, 0.0), 0.2, material_mini2));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -2.2), 0.2, material_mini3));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, 0.6), 0.2, material_mini4));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -2.2), 0.2, material_mini5));
    world.add(make_shared<sphere>(point3(0.0, 0.0, 0.6), 0.2, material_mini6));
    world.add(make_shared<sphere>(point3(1.4, 0.0, 0.5), 0.2, material_mini7));
    world.add(make_shared<sphere>(point3(-1.7, 0.0, -0.8), 0.2, material_mini8));

    // defining camera
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vup = vec3(0, 1, 0);

    for (int i = 1; i < 251; i++)
    {
        cout << "frame" << i;
        // ppm file
        string filename = "frames/frame";
        // creating different filename for every frame with converting integer to string
        string integ;
        if (i < 10)
        {
            integ = "00" + to_string(i);
        }
        else if (i < 100)
        {
            integ = "0" + to_string(i);
        }
        else
        {
            integ = to_string(i);
        }
        filename += integ;
        filename += ".ppm";
        ofstream ppmfile(filename);

        // changing camera angles for every frame

        double theta = ((i - 1) * degrees_to_radians(360)) / 250;
        cam.lookfrom = point3(5 * sin(theta), 2, 5 * cos(theta));
        cam.lookat = point3(0, 0, -1);

        // for camera zoom in- zoom out effect
        cam.vfov = 40 + 20 * sin(theta);

        cam.render(world, ppmfile, i);

        ppmfile.close();
    }
}