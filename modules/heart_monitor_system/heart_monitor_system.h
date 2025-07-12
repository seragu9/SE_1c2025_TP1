//=====[#include guards - begin]===============================================

#ifndef _HEART_MONITOR_SYSTEM_H_
#define _HEART_MONITOR_SYSTEM_H_

  
//=====[Declaration of public defines]=========================================
#define TIME_INCREMENT_MS 10
#define TIME_ALARM       30000

#define DEFAULT_LOW_THRESHOLD       20
#define DEFAULT_HIGH_THRESHOLD       150
#define DEFAULT_TAG         "Default"
#define MAX_CHAR_TAG         100

//=====[Declaration of public data types]======================================

extern bool readingState;
extern int  low_limit;
extern int  high_limit;
extern char tag_name[MAX_CHAR_TAG];
extern bool alertaActiva;
//=====[Declarations (prototypes) of public functions]=========================

void heartMonitorSystemInit();
void heartMonitorSystemUpdate();

//=====[#include guards - end]=================================================

#endif // _HEART_MONITOR_SYSTEM_H_