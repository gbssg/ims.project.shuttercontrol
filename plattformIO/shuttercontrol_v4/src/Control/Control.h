#pragma once

typedef struct sControl tControl;

tControl *Control_create();
void Control_destroy(tControl *me);

void Control_init(tControl *me);
void Control_deinit(tControl *me);