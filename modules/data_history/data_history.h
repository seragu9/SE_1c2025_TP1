//=====[#include guards - begin]===============================================

#ifndef _DATA_HISTORY_H_
#define _DATA_HISTORY_H_

//=====[Declaration of public defines]=========================================
#define MAX_REG                 20
#define TAG_LEN               32

//=====[Declaration of public data types]======================================
typedef struct {
    char datetime[20];  // formato: "2025-06-20 22:10"
    float bpm;
    char tag[TAG_LEN];
} Register_t;

extern Register_t registers[MAX_REG];
extern int historialIndex;
//=====[Declarations (prototypes) of public functions]=========================

void addRegisterData(float bpm, const char* tag);

//=====[#include guards - end]=================================================

#endif // _DATA_HISTORY_H_