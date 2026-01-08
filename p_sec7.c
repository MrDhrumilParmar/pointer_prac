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



    //  🧰 Bonus: Embedded-Style Mini Practice Problems


    // goal : 61.	Simulate reading 10 ADC values into an array using pointers and print average.


    // goal : 62.	Write a GetBit() and SetBit() function that takes a pointer to a hardware register address.


    // goal : 63.	Simulate memory-mapped GPIO toggle using volatile pointer.


    // goal : 64.	Create function to check checksum of a packet using pointer traversal.


    // goal : 65.	Implement pointer arithmetic to parse a Modbus frame buffer byte-by-byte.


    // goal : 66.	Write your own strlen(), strcpy(), and strcmp() using pointer arithmetic.


    // goal : 67.	Write a function that takes a buffer pointer and length and reverses it in place.


    // goal : 68.	Use function pointer to call one of three LED blinking modes.


    // goal : 69.	Simulate RTOS task callback registration using array of function pointers.


    // goal : 70.	Implement pointer-based circular task scheduler using function pointer array.



    return 0;
}