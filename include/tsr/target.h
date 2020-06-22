//===--------------------------------------------------------------------------------------------===
// target - A target is something you can draw too.
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#pragma once
#include <tsr/surface.h>

#ifdef __cplusplus
extern "C" {
#endif

/// A target is what you draw to in TSR.
typedef struct tsr_target_s tsr_target_t;

/// Creates a new target and attaches a surface to it.
tsr_target_t *tsr_target_new(tsr_surface_t *surface);

/// Deletes a target and the associated surface.
void tsr_target_delete(tsr_target_t *target);

/// Attaches a new surface to a target, and returns a pointer to the old surface.
tsr_surface_t *tsr_target_attach(tsr_target_t *target, tsr_surface_t *surface);

#ifdef __cplusplus
} /* extern "C" */
#endif
