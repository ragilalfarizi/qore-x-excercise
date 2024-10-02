#pragma once

#include "common.h"
#include "qore-x_display.h"

extern IMUData imuData;

#ifdef __cplusplus
extern "C" {
#endif

lv_obj_t *createICM2094Screen();

#ifdef __cplusplus
}
#endif