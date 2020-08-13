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
#include <stdlib.h>

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

void tsr_move_to(tsr_target_t *target, int x, int y) {
    CCASSERT(target);
    target->position = tsr_vec2(x, y);
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

static inline void blend(const tsr_colorf_t *col, const uint8_t *src, uint8_t *dst) {
    if(!src[3]) return;
    const float src_a = col->a * (float)src[3] / 255.f;
    const float dst_a = (float)dst[3] / 255.f;
    const float one_minus_src_a = 1.f - src_a;

    dst[0] = min_i32(src_a * col->r * src[0] + dst[0] * one_minus_src_a, 255);
    dst[1] = min_i32(src_a * col->g * src[1] + dst[1] * one_minus_src_a, 255);
    dst[2] = min_i32(src_a * col->b * src[2] + dst[2] * one_minus_src_a, 255);
    dst[3] = 255 * clamp_f32(src_a + dst_a * one_minus_src_a, 0, 1.0);
}

void tsr_fill_box(tsr_target_t *target, int width, int height) {
    CCASSERT(target);
    if(!target->color.a) return;
    uint8_t *pixels = target->surface->pixels;

    uint8_t basic[4] = {255, 255, 255, 255};

    const tsr_vec2_t start = target->position;
    const tsr_vec2_t end = tsr_add_vv(start, tsr_vec2(width, height));
    const tsr_vec2_t vp_size = target->surface->size;

    for(int x = max_i32(start.x, 0); x < min_i32(end.x, vp_size.x); ++x) {
        for(int y = max_i32(start.y, 0); y < min_i32(end.y, vp_size.y); ++y) {
            uint32_t i = y * target->surface->size.x + x;
            blend(&target->color, basic, pixels + i * 4);
        }
    }
}

void tsr_box(tsr_target_t *target, int width, int height, int thickness) {
    CCASSERT(target);
    if(!target->color.a) return;
    uint8_t *pixels = target->surface->pixels;

    uint8_t basic[4] = {255, 255, 255, 255};

    const tsr_vec2_t start = target->position;
    const tsr_vec2_t end = tsr_add_vv(start, tsr_vec2(width, height));
    const tsr_vec2_t vp_size = target->surface->size;

    for(int x = max_i32(start.x, 0); x < min_i32(end.x, vp_size.x); ++x) {
        for(int y = max_i32(start.y, 0); y < min_i32(end.y, vp_size.y); ++y) {
            if(x >= start.x + thickness && x < end.x - thickness &&
               y >= start.y + thickness && y < end.y - thickness) continue;
            uint32_t i = y * target->surface->size.x + x;
            blend(&target->color, basic, pixels + i * 4);
        }
    }
}

void tsr_vline(tsr_target_t *target, int length, int thickness) {
    CCASSERT(target);
    tsr_translate(target, -thickness/2, 0);
    tsr_fill_box(target, thickness, length);
    tsr_translate(target, thickness/2, 0);
}

void tsr_hline(tsr_target_t *target, int length, int thickness) {
    CCASSERT(target);
    tsr_translate(target, 0, -thickness/2);
    tsr_fill_box(target, length, thickness);
    tsr_translate(target, 0, thickness/2);
}

void tsr_blit(tsr_target_t *target, tsr_surface_t *img, tsr_vec2_t pos) {
    CCASSERT(target);
    CCASSERT(img);
    tsr_rect_t region = tsr_rect(tsr_vec2(0, 0), img->size);
    tsr_blit_ex(target, img, pos, &region);
}
//
void tsr_blit_ex(tsr_target_t *target, tsr_surface_t *img, tsr_vec2_t pos, const tsr_rect_t *rp) {
    CCASSERT(target);

    tsr_vec2_t surf_size = target->surface->size;
    tsr_rect_t reg = *rp;
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
            blend(&target->color, src + src_i * 4, dst + dst_i * 4);
        }
    }
}
