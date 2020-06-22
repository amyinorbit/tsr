//===--------------------------------------------------------------------------------------------===
// drawing - Drawing Primitives in TSR
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <tsr/target.h>
#include <tsr/geometry.h>

#ifdef __cplusplus
extern "C" {
#endif

void tsr_blend(tsr_target_t *target);
void tsr_color(tsr_target_t *target, float r, float g, float b, float a);
void tsr_translate(tsr_target_t *target, float x, float y);
void tsr_clear(tsr_target_t *target);
void tsr_rectangle(tsr_target_t *target, tsr_rect_t r);
void tsr_circle(tsr_target_t *target, tsr_vec2_t pos, float radius);
void tsr_blit(tsr_target_t *target, tsr_surface_t *surface, tsr_vec2_t pos);
void tsr_blit_region(tsr_target_t *target, tsr_surface_t *surface, tsr_vec2_t pos, tsr_rect_t reg);

#ifdef __cplusplus
} /* extern "C" */
#endif
