//===--------------------------------------------------------------------------------------------===
// surface - Stores a collection of pixels
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tsr_surface_t tsr_surface_t;

/// Creates a new surface of [width] x [height] pixels.
tsr_surface_t *tsr_surface_new(uint32_t width, uint32_t height);

/// Creates a new surface by loading the image at [path].
tsr_surface_t *tsr_surface_load(const char *path);

/// Creates a new surface from RGBA [data] already in memory.
tsr_surface_t *tsr_surface_copy(uint32_t width, uint32_t height, const uint8_t *data);

/// Deletes a surface's image memory.
void tsr_surface_delete(tsr_surface_t *surface);

/// Returns a pointer to the pixel store of a surface.
const uint8_t *tsr_surface_pixels(tsr_surface_t *surface);

#ifdef __cplusplus
} /* extern "C" */
#endif
