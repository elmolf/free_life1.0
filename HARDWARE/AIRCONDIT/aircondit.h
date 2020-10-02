/**
 * @file aircondit.h
 * @author linf (elmo_lf@126.com)
 * @brief 
 * @version 1.0
 * @date 2020-10-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __AIRCONDIT_H
#define __AIRCONDIT_H

#include "sys.h"

#define AIRCOND_EVENT (1)
#define AIRCOND_MODE_NORMAL (1)
#define AIRCOND_MODE_SLEEP (2)
#define AIRCOND_MODE_POWEROFF (3)



void AIRCOND_send_commd(u8 commd_type);
void AIRCOND_init(void);
#endif
