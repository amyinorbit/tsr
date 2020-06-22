//===--------------------------------------------------------------------------------------------===
// target - A target is something you can draw too.
//
// Created by Amy Parent <amy@amyparent.com>
// Copyright (c) 2020 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include "tsr_private.h"
#include <tsr/target.h>
#include <ccore/log.h>
#include <ccore/memory.h>

tsr_target_t *tsr_target_new(tsr_surface_t *surface) {
    CCASSERT(surface);

    tsr_target_t *target = cc_alloc(sizeof(tsr_target_t));

    target->surface = surface;
    target->position = tsr_vec2(0, 0);
    target->color = tsr_colorf(0, 0, 0, 1);

    return target;
}

void tsr_target_delete(tsr_target_t *target) {
    CCASSERT(target);
    if(target->surface) tsr_surface_delete(target->surface);
    cc_free(target);
}

tsr_surface_t *tsr_target_attach(tsr_target_t *target, tsr_surface_t *surface) {
    CCASSERT(target);
    CCASSERT(surface);
    tsr_surface_t *old = target->surface;
    target->surface = surface;
    return old;
}
