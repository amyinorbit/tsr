//===--------------------------------------------------------------------------------------------===
// tsr - A tiny software renderer -- that's it.
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <tsr/target.h>
#include <tsr/surface.h>
#include <tsr/geometry.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tsr_blend_mode_e {
    TSR_BLEND_BLEND,
    TSR_BLEND_REPLACE,
} tsr_blend_mode_t;

void tsr_blend(tsr_target_t *target, tsr_blend_mode_t mode);
void tsr_color(tsr_target_t *target, float r, float g, float b, float a);
void tsr_translate(tsr_target_t *target, int x, int y);
void tsr_move_to(tsr_target_t *target, int x, int y);

void tsr_clear(tsr_target_t *target);
void tsr_fill_box(tsr_target_t *target, int width, int height);
void tsr_box(tsr_target_t *target, int width, int height, int thickness);
void tsr_vline(tsr_target_t *target, int length, int thickness);
void tsr_hline(tsr_target_t *target, int length, int thickness);

void tsr_blit(tsr_target_t *target, tsr_surface_t *img, tsr_vec2_t pos);
void tsr_blit_ex(tsr_target_t *target, tsr_surface_t *img, tsr_vec2_t pos, const tsr_rect_t *reg);

#ifdef __cplusplus
} /* extern "C" */
#endif
