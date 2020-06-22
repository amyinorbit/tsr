//===--------------------------------------------------------------------------------------------===
// drawing - Implementation of TSR's drawing primitives.
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include "tsr_private.h"
#include <ccore/log.h>
#include <ccore/math.h>

void tsr_blend(tsr_target_t *target, tsr_blend_mode_t mode) {
    CCASSERT(target);
    target->blend_mode = mode;
}

void tsr_color(tsr_target_t *target, float r, float g, float b, float a) {
    CCASSERT(target);
    target->color = tsr_colorf(r, g, b, a);
}

void tsr_translate(tsr_target_t *target, int x, int y) {
    CCASSERT(target);
    target->position = tsr_add_vv(target->position, tsr_vec2(x, y));
}

void tsr_clear(tsr_target_t *target) {
    CCASSERT(target);
    uint8_t *pixels = target->surface->pixels;
    uint8_t r = target->color.r * 0xff;
    uint8_t g = target->color.g * 0xff;
    uint8_t b = target->color.b * 0xff;
    uint8_t a = target->color.a * 0xff;
    const uint32_t num_pixels = target->surface->size.x * target->surface->size.y;
    for(uint32_t i = 0; i < num_pixels; ++i) {
        pixels[i * 4 + 0] = r;
        pixels[i * 4 + 1] = g;
        pixels[i * 4 + 2] = b;
        pixels[i * 4 + 3] = a;
    }
}

static inline void blend(const uint8_t *src, uint8_t *dst) {
    if(!src[3]) return;
    const float src_a = (float)src[3] / 255.f;
    const float dst_a = (float)dst[3] / 255.f;
    const float one_minus_src_a = 1.f - src_a;

    dst[0] = min_i32(src_a * src[0] + dst[0] * one_minus_src_a, 255);
    dst[1] = min_i32(src_a * src[1] + dst[1] * one_minus_src_a, 255);
    dst[2] = min_i32(src_a * src[2] + dst[2] * one_minus_src_a, 255);
    dst[3] = 255 * clamp_f32(src_a + dst_a * one_minus_src_a, 0, 1.0);
}

void tsr_rectangle(tsr_target_t *target, tsr_rect_t rect) {
    CCASSERT(target);
    if(!target->color.a) return;
    uint8_t *pixels = target->surface->pixels;

    uint8_t color[4] = {
        target->color.r * 255,
        target->color.g * 255,
        target->color.b * 255,
        target->color.a * 255,
    };

    const tsr_vec2_t start = tsr_add_vv(target->position, rect.origin);
    const tsr_vec2_t end = tsr_add_vv(start, rect.size);
    const tsr_vec2_t vp_size = target->surface->size;

    for(int x = max_i32(start.x, 0); x < min_i32(end.x, vp_size.x); ++x) {
        for(int y = max_i32(start.y, 0); y < min_i32(end.y, vp_size.y); ++y) {
            uint32_t i = y * target->surface->size.x + x;
            blend(color, pixels + i);
        }
    }
}

// void tsr_circle(tsr_target_t *target, tsr_vec2_t pos, int radius) {
//     CCASSERT(target);
//
// }
//
void tsr_blit(tsr_target_t *target, tsr_surface_t *img, tsr_vec2_t pos) {
    CCASSERT(target);
    CCASSERT(img);
    tsr_rect_t region = tsr_rect(tsr_vec2(0, 0), img->size);
    tsr_blit_region(target, img, pos, region);
}
//
void tsr_blit_region(tsr_target_t *target, tsr_surface_t *img, tsr_vec2_t pos, tsr_rect_t reg) {
    CCASSERT(target);

    tsr_vec2_t surf_size = target->surface->size;

    tsr_vec2_t dest_start = tsr_add_vv(target->position, pos);
    tsr_vec2_t end = tsr_add_vv(dest_start, reg.size);

    if(dest_start.x < 0) {
        reg.origin.x -= dest_start.x;
        reg.size.x += dest_start.x;
        dest_start.x = 0;
    }

    if(dest_start.y < 0) {
        reg.origin.y -= dest_start.y;
        reg.size.y += dest_start.y;
        dest_start.y = 0;
    }

    if(end.x > surf_size.x) reg.size.x -= (end.x - surf_size.x);
    if(end.y > surf_size.y) reg.size.y -= (end.y - surf_size.y);
    if(reg.size.x <= 0 || reg.size.y <= 0) return;

    uint8_t *src = img->pixels;
    uint8_t *dst = target->surface->pixels;

    for(int x = 0; x < reg.size.x; ++x) {
        for(int y = 0; y < reg.size.y; ++y) {
            uint32_t src_i = (reg.origin.x + x) + (reg.origin.y + y) * img->size.x;
            uint32_t dst_i = (dest_start.x + x) + (dest_start.y + y) * surf_size.x;
            blend(src + src_i * 4, dst + dst_i * 4);
        }
    }
}
