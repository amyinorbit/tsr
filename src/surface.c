//===--------------------------------------------------------------------------------------------===
// surface - Stores a collection of pixels
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include "tsr_private.h"
#include <tsr/surface.h>
#include <ccore/log.h>
#include <ccore/memory.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

tsr_surface_t *tsr_surface_new(uint32_t width, uint32_t height) {
    size_t size = width * height * 4;
    tsr_surface_t *surface = cc_alloc(sizeof(tsr_surface_t) + size);
    surface->size = tsr_vec2(width, height);
    memset(surface->pixels, 0, size);
    return surface;
}

tsr_surface_t *tsr_surface_load(const char *path) {
    CCUNUSED(path);
    int w, h;
    int components;
    uint8_t * data = stbi_load(path, &w, &h, &components, 4);
    if(!data) {
        CCERROR("unable to load image at %s", path);
        return NULL;
    }
    if(components != 4) {
        cc_free(data);
        CCERROR("unable to read image: %d components found", components);
        return NULL;
    }

    CCASSERT(w);
    CCASSERT(h);
    tsr_surface_t *surface = tsr_surface_copy(w, h, data);
    cc_free(data);
    return surface;
}

tsr_surface_t *tsr_surface_copy(uint32_t width, uint32_t height, const uint8_t *data) {
    tsr_surface_t *surface = tsr_surface_new(width, height);
    memcpy(surface->pixels, data, 4 * width * height);
    return surface;
}

tsr_vec2_t tsr_surface_size(const tsr_surface_t *surface) {
    CCASSERT(surface);
    return surface->size;
}

void tsr_surface_delete(tsr_surface_t *surface) {
    CCASSERT(surface);
    cc_free(surface);
}

const uint8_t *tsr_surface_pixels(const tsr_surface_t *surface) {
    CCASSERT(surface);
    return surface->pixels;
}
