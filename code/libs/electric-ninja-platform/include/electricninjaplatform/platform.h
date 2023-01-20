#ifndef electricninjaplatform_platform_H
#define electricninjaplatform_platform_H

#include "electricninjaplatform/platformPort.h"

namespace platform {

void initialize();
void start();
void reboot();
void blockPreemption();
void resumePreemption();
void delay(size_t ticks);
int msleep(unsigned int milliseconds);
unsigned int sleep(unsigned int seconds);
void disableInterrupts();
void enableInterrupts();
void enterCriticalSection();
void leaveCriticalSection();

} // namespace platform

#endif
