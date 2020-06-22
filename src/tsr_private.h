//===--------------------------------------------------------------------------------------------===
// tsr_private - private structures used by TSR
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <tsr/tsr.h>
#include <tsr/geometry.h>
#include <stdint.h>

typedef struct tsr_surface_s {
    tsr_vec2_t size;
    uint8_t pixels[];
} tsr_surface_t;

typedef struct tsr_target_s {
    tsr_surface_t *surface;
    tsr_vec2_t position;
    tsr_colorf_t color;
    tsr_blend_mode_t blend_mode;
} tsr_target_t;
