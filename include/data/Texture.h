//
// Created by desktop on 26. 7. 4..
//

#ifndef TOYRENDERER2_TEXTURE_H
#define TOYRENDERER2_TEXTURE_H
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>

#include "../library/stb_img.h"
#include "../library/Geometry.h"

class Texture {
private:
    stbi_uc *data;
    int width, height, channels;

public:
    explicit Texture(const char* filename) : data(nullptr), width(0), height(0), channels(0) {
        if (!filename || std::string(filename).empty()) {
            std::cerr << "ERROR: Texture filename is empty." << std::endl;
        }
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(filename, &width, &height, &channels, 0);

        if (!data) {
            std::cerr << "Missing file -> " << filename << '\n'
                << "use default Texture " << std::endl;
        }
    }

    ~Texture() {
        if (data) stbi_image_free(data);
    }

    [[nodiscard]] Vec3 get_color(const float u, const float v) const {
        Vec3 color;
        if (!data) {
            return {1.0f, 0.0f, 1.0f};
        }
        int x = static_cast<int>(u * width);
        int y = static_cast<int>(v * height);

        if (x < 0) x = 0; if (x >= width) x = width - 1;
        if (y < 0) y = 0; if (y >= height) y = height - 1;

        const int idx = (y * width + x) * channels;
        return {data[idx] / 255.0f, data[idx+1] / 255.0f, data[idx+2] / 255.0f};
    }
};

#endif //TOYRENDERER2_TEXTURE_H