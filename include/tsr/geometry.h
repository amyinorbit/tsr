//===--------------------------------------------------------------------------------------------===
// geometry - Geometry primitives and manipulation in TSR
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// A integer-valued, 2-dimension vector.
typedef struct tsr_vec2_s { int x, y; } tsr_vec2_t;

/// A integer-valued, axis-aligned rectangle.
typedef struct tsr_rect_s { tsr_vec2_t origin; tsr_vec2_t size; } tsr_rect_t;

static inline tsr_vec2_t tsr_vec2(int x, int y) { return (tsr_vec2_t){x, y}; };
static inline tsr_rect_t tsr_rect(tsr_vec2_t o, tsr_vec2_t s) { return (tsr_rect_t){o, s}; }

static inline tsr_vec2_t tsr_add_vv(tsr_vec2_t a, tsr_vec2_t b) {
    return tsr_vec2(a.x + b.x, a.y + b.y);
}

static inline tsr_vec2_t tsr_sub_vv(tsr_vec2_t a, tsr_vec2_t b) {
    return tsr_vec2(a.x - b.x, a.y - b.y);
}

static inline tsr_vec2_t tsr_mul_vv(tsr_vec2_t a, tsr_vec2_t b) {
    return tsr_vec2(a.x * b.x, a.y * b.y);
}

static inline tsr_vec2_t tsr_mul_vf(tsr_vec2_t a, float b) {
    return tsr_vec2(a.x * b, a.y * b);
}

static inline tsr_vec2_t tsr_div_vv(tsr_vec2_t a, tsr_vec2_t b) {
    return tsr_vec2(a.x / b.x, a.y / b.y);
}

static inline tsr_vec2_t tsr_div_vf(tsr_vec2_t a, float b) {
    return tsr_vec2(a.x / b, a.y / b);
}

#ifdef __cplusplus
} /* extern "C" */
#endif
