#pragma once
#include "IMotor/IMotor.h"

typedef struct sMotorQR tMotorQR;

tMotorQR *MotorQR_create();
void MotorQR_destroy(tMotorQR *me);

void MotorQR_init(tMotorQR *me);
void MotorQR_deinit(tMotorQR *me);