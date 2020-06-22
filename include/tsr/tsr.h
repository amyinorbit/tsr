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
    TSR_BLEND_ADD,
} tsr_blend_mode_t;

void tsr_blend(tsr_target_t *target, tsr_blend_mode_t mode);
void tsr_color(tsr_target_t *target, float r, float g, float b, float a);
void tsr_translate(tsr_target_t *target, int x, int y);
void tsr_clear(tsr_target_t *target);
void tsr_rectangle(tsr_target_t *target, tsr_rect_t r);
void tsr_circle(tsr_target_t *target, tsr_vec2_t pos, int radius);
void tsr_blit(tsr_target_t *target, tsr_surface_t *surface, tsr_vec2_t pos);
void tsr_blit_region(tsr_target_t *target, tsr_surface_t *surface, tsr_vec2_t pos, tsr_rect_t reg);

#ifdef __cplusplus
} /* extern "C" */
#endif
