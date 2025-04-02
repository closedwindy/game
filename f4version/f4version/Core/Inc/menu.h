//
// Created by hhw on 2025/4/1.
//

#ifndef F4VERSION_MENU_H
#define F4VERSION_MENU_H


#include "stm32f4xx_hal.h"
#include "io.h"
#include "u8g2.h"


extern int Desktop1_x;
extern int Desktop1_y;
extern int Desktop1_direction;

extern int Desktop2_SETx;
extern int Desktop2_SETy;
extern int Desktop2_SETdirection;

void Desktop1(void);
void Desktop2_SET(int direction);
void HELL(void);
void Desktop2_VCU(void);
#endif //F4VERSION_MENU_H
