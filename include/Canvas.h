//
// Created by desktop on 26. 3. 29..
//

#ifndef TOYRENDERER2_CANVAS_H
#define TOYRENDERER2_CANVAS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../include/library/Geometry.h"

struct Canvas {
    int width = 0, height = 0;
    std::vector<Vec3> pixels;

    Canvas(int w, int h) : width(w), height(h) {
        pixels.resize(width * height);
    }

    void setPixel(int x, int y, Vec3 color) {
        if (!(x >= 0 && x < width && y >= 0 && y < height)) return;
        pixels[x + y * width] = color;
    }

    void save_ppm(const std::string &filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file! " << filename << std::endl;
            return;
        }
        file << "P3\n" << width << " " << height << "\n255\n";

        for (const auto& p : pixels) {
            file << static_cast<int>(255.99 * p.x) << " "
                << static_cast<int>(255.99 * p.y) << " "
                << static_cast<int>(255.99 * p.z) << "\n";
        }
    }
};

#endif //TOYRENDERER2_CANVAS_H