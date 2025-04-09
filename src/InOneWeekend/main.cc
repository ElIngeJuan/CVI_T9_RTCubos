#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"

// Genera una caja con su material
shared_ptr<hittable> make_box(const point3& p0, const point3& p1, shared_ptr<material> mat) {
    return box(p0, p1, mat);
}

// Genera el plano del suelo
shared_ptr<hittable> create_ground() {
    auto ground_mat = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    return make_box(point3(-25, -0.01, -25), point3(25, 0, 25), ground_mat);
}

// Genera una colección de cajas aleatorias distribuidas en una cuadrícula
hittable_list generate_random_scene() {
    hittable_list objects;

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2 - 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> mat;

                if (choose_mat < 0.8) {
                    // Diffuse
                    auto albedo = color::random() * color::random();
                    mat = make_shared<lambertian>(albedo);
                } else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = color::random(0.5, 1.0);
                    auto fuzz = random_double(0, 0.5);
                    mat = make_shared<metal>(albedo, fuzz);
                } else {
                    // Glass
                    mat = make_shared<dielectric>(1.5);
                }

                // Define una caja centrada en el origen
                auto raw_box = make_box(point3(-0.2, 0.0, -0.2), point3(0.2, 0.4, 0.2), mat);
                
                // Rota la caja 45 grados alrededor del eje Y
                raw_box = make_shared<rotate_y>(raw_box, 45);

                // Traslada la caja al centro deseado
                raw_box = make_shared<translate>(raw_box, center);

                objects.add(raw_box);
            }
        }
    }

    return objects;
}


// Añade objetos principales visibles en primer plano
void add_main_objects(hittable_list& world) {
    auto glass = make_shared<dielectric>(1.5);
    auto diffuse = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    auto metal_mat = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);

    // Caja de vidrio rotada
    auto glass_box = make_box(point3(-0.5, 0.0, -0.5), point3(0.5, 1.0, 0.5), glass);
    glass_box = make_shared<rotate_y>(glass_box, 45);
    glass_box = make_shared<translate>(glass_box, vec3(0, 0, 0));
    world.add(glass_box);

    // Caja difusa rotada
    auto diffuse_box = make_box(point3(-0.5, 0.0, -0.5), point3(0.5, 1.0, 0.5), diffuse);
    diffuse_box = make_shared<rotate_y>(diffuse_box, 45);
    diffuse_box = make_shared<translate>(diffuse_box, vec3(-4, 0, 0));
    world.add(diffuse_box);

    // Caja metálica rotada
    auto metal_box = make_box(point3(-0.5, 0.0, -0.5), point3(0.5, 1.0, 0.5), metal_mat);
    metal_box = make_shared<rotate_y>(metal_box, 45);
    metal_box = make_shared<translate>(metal_box, vec3(4, 0, 0));
    world.add(metal_box);
}

// Configura la cámara
camera setup_camera() {
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1200;
    cam.samples_per_pixel = 10;
    cam.max_depth = 20;

    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    return cam;
}

int main() {
    hittable_list world;

    world.add(create_ground());
    hittable_list random_objects = generate_random_scene();
    for (const auto& obj : random_objects.objects) {
        world.add(obj);
    }

    add_main_objects(world);

    camera cam = setup_camera();
    cam.render(world);
}