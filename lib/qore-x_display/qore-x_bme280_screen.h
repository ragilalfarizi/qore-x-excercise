#pragma once

#include "qore-x_display.h"
#include "common.h"

extern BMEData bmeData;

#ifdef __cplusplus
extern "C" {
#endif


lv_obj_t *createBME280Screen();

#ifdef __cplusplus
}
#endif