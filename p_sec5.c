#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>


#define P_FAIL  (printf("Failed\n"))


typedef enum {
    SENSOR_OK = 0,
    SENSOR_SOME_PROBLEM = 1,
}SensorSts_e;

typedef enum {
    DATA_OK = 0,
    DATA_ERR_NULL = 1,
}SensorFxnSts_e;

typedef struct {
    uint32_t id;
    int32_t value;
    SensorSts_e status;
} SensorData_t;

SensorFxnSts_e setSensorDataID (SensorData_t* sd, uint32_t id) {
    if (!sd)return DATA_ERR_NULL;
    sd->id = id;
    return DATA_OK;
}
SensorFxnSts_e  setSensorDataStatus (SensorData_t* sd, SensorSts_e sts) {
    if (!sd)return DATA_ERR_NULL;
    sd->status = SENSOR_SOME_PROBLEM;
    return DATA_OK;
}
int main () {
    //gcc -Wall -Wextra -Werror -Wpedantic -fmax-errors=1 -O0 p.c -o p && ./p

    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);

    // goal :46.	Define a structure SensorData with members: id, value, status.
    // SensorData_t pot;
    // pot.id = 1;
    // pot.value = 15;//value will comes from adc but for now i have written hard code
    // pot.status = SENSOR_OK;

    // goal :47.	Create array of structures and access via pointer arithmetic.
    // SensorData_t ct[10]; // current transformer sensors
    // ct[0].id = 1;
    // ct[1].id = 2;
    // ct[2].id = 3;
    // ct[3].id = 4;
    // ct[4].id = 5;
    // SensorData_t* itSensors;
    // itSensors = &ct[0];
    // printf ("%d \n", itSensors[0].id);
    // printf ("%d \n", itSensors[1].id);
    // printf ("%d \n", itSensors[2].id);
    // printf ("%d \n", itSensors[3].id);
    // printf ("%d \n", itSensors[4].id);

    // goal :48.	Write a function that accepts a pointer to SensorData and updates its members.
    // SensorData_t pot;
    // SensorData_t* it = &pot;
    // setSensorDataID (it, 5) ? P_FAIL : 0;
    // setSensorDataStatus (it, SENSOR_OK) ? P_FAIL : 0;

    // goal :49.	Create an array of structures and use pointer to loop through and print all.


    // goal :50.	Pass structure pointer to a function and modify data in it.

    // goal :51.	Demonstrate pointer to function inside a structure (callback).

    // goal :52.	Simulate a “driver” structure with function pointers (init, read, write) and call through it.

    // goal :53.	Implement array of struct Device and iterate with pointers to call device functions.

    // goal :54.	Use pointer to structure with bit-fields (simulate 8-bit register access).

    // goal :55.	Write a function that updates a register map structure using pointer offset arithmetic.

    // goal :56.	Demonstrate difference between struct *p and (*p).member vs p->member.


    return 0;
}