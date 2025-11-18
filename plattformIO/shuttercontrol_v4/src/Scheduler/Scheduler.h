#pragma once

typedef void (*Scheduler_Run)(void);

void runAll();

void addRunable(int value);
void listRunable();