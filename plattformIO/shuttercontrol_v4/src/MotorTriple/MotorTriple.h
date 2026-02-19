#pragma once
#include "IMotorTriple/IMotorTriple.h"
#include "IRun/IRun.h"

typedef struct sMotorTriple tMotorTriple;

tMotorTriple *MotorTriple_create();
void *MotorTriple_destroy();

void *MotorTriple_init();
void *MotorTriple_deinit();
