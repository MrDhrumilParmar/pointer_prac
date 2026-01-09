#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define P_FAIL (printf("Failed\n"))

typedef enum {
    SENSOR_OK = 0,
    SENSOR_SOME_PROBLEM = 1,
} SensorSts_e;

typedef enum {
    DATA_OK = 0,
    DATA_ERR_NULL = 1,
} SensorFxnSts_e;

typedef struct {
    uint32_t id;
    int32_t value;
    SensorSts_e status;
} SensorData_t;

SensorFxnSts_e setSensorDataID(SensorData_t *sd, uint32_t id) {
    if (!sd)
        return DATA_ERR_NULL;
    sd->id = id;
    return DATA_OK;
}
SensorFxnSts_e setSensorDataStatus(SensorData_t *sd, SensorSts_e sts) {
    if (!sd)
        return DATA_ERR_NULL;
    sd->status = sts;
    return DATA_OK;
}
SensorFxnSts_e setID(SensorData_t *pt, uint32_t size) {

    if (!pt || size <= 0) {
        return DATA_ERR_NULL;
    }
    printf("%p", pt);

    for (uint32_t i = 0; i < size; i++) {
        pt->id = i + 1;
        pt++;
    }
    return DATA_OK;
}

SensorFxnSts_e print_arr(SensorData_t *pt, uint32_t size) {

    if (!pt || size <= 0)
        return DATA_ERR_NULL;

    printf("id val sts\n");
    for (uint32_t i = 0; i < size; i++) {
        printf("%d %d %d \n", pt->id, pt->value, pt->status);
        pt++;
    }
    return DATA_OK;
}

// Suppose there is Baseaddress from where all 8 bit register are located in order of spi, uart, pwm and flash
#define HWADDRESS (0x40000000U)
#define BASE_ADDRESS ((volatile uint32_t *)(HWADDRESS))
#define BASE_VALUE (*(BASE_ADDRESS))

typedef enum {
    REG_OK = 0,
    REG_SOME_PROBLEM = 1,
} reg_e;
typedef enum {
    MCU_FXN_OK = 0,
    MCU_FXN_SOME_PROBLEM = 1,
} mcu_fxn_sts_e;

typedef struct {
    volatile reg_e status_bit : 1;
    volatile uint8_t output_bit : 1;
    volatile uint8_t input_bit : 1;
    volatile uint8_t bit3 : 1;
    volatile uint8_t bit4 : 1;
    volatile uint8_t bit5 : 1;
    volatile uint8_t bit6 : 1;
    volatile uint8_t bit7 : 1;
} gpio_bits;

typedef union {
    gpio_bits bit;
    volatile uint8_t REGISTER;
} reg_u;

typedef enum {
    SPI = 0,
    UART,
    PWM,
    FLASH,
    MAX_MCU_PERIPHRAL_SIZE
} mcu_e;
typedef reg_u(mcu_arr_t)[MAX_MCU_PERIPHRAL_SIZE];

mcu_fxn_sts_e init_mcu(mcu_arr_t *mcu) {
    if (!mcu)
        return MCU_FXN_SOME_PROBLEM;

    // (*(mcu + SPI))->REGISTER = 0;
    mcu[SPI]->REGISTER = 0;
    mcu[UART]->REGISTER = 0;
    mcu[PWM]->REGISTER = 0;
    mcu[FLASH]->REGISTER = 0;
    return MCU_FXN_OK;
}
mcu_fxn_sts_e set_uart_reg_value(mcu_arr_t *mcu, uint8_t val) {
    if (!mcu)
        return MCU_FXN_SOME_PROBLEM;
    // (*(mcu + UART))->REGISTER = val;//
    mcu[UART]->REGISTER = val;
    return MCU_FXN_OK;
}
mcu_fxn_sts_e set_pwm_reg_value(mcu_arr_t *mcu, uint8_t val) {
    if (!mcu)
        return MCU_FXN_SOME_PROBLEM;
    // (*(mcu + PWM))->REGISTER = val;
    mcu[PWM]->REGISTER = val;

    return MCU_FXN_OK;
}
mcu_fxn_sts_e print_mcu_reg(const mcu_arr_t *mcu) {
    if (!mcu)
        return MCU_FXN_SOME_PROBLEM;
    const mcu_arr_t *it = (mcu_arr_t *)mcu;
    for (uint32_t i = 0; i < MAX_MCU_PERIPHRAL_SIZE; i++) {
        // printf("idx:%d reg:%d \n", i, (*(it + i))->REGISTER);
        printf("idx:%d reg:%d \n", i, it[i]->REGISTER);
    }

    return MCU_FXN_OK;
}

int main() {
    // gcc -Wall -Wextra -Werror -Wpedantic -fmax-errors=1 -O0 p.c -o p && ./p

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

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
    // SensorData_t arr_sensors[10] = {0};
    // SensorData_t *pt = &arr_sensors;

    // for (uint32_t i = 0; i < (sizeof(arr_sensors) / sizeof(arr_sensors[0])); i++) {
    //     printf("%d %d %d \n", pt->id, pt->value, pt->status);
    //     pt++;
    // }

    // goal :50.	Pass structure pointer to a function and modify data in it.
    // const static uint32_t size = 10;
    // SensorData_t arr_sensors[10] = {0};
    // SensorData_t *pt; //= &arr_sensors[0];

    // setID(pt, size) ? P_FAIL : 0;
    // print_arr(arr_sensors, size) ? P_FAIL : 0;

    // goal :51.	Demonstrate pointer to function inside a structure (callback).

    // goal :52.	Simulate a “driver” structure with function pointers (init, read, write) and call through it.

    // goal :53.	Implement array of struct Device and iterate with pointers to call device functions.

    // goal :54.	Use pointer to structure with bit-fields (simulate 8-bit register access).
    // reg_u GPIO;
    // GPIO.REGISTER = 0;
    // reg_u *pt;
    // pt = &GPIO;

    // pt->bit.output_bit = 1;
    // printf("%d \n", pt->REGISTER);
    // pt->bit.input_bit = 1;
    // printf("%d \n", pt->REGISTER);
    // pt->bit.bit7 = 1;
    // printf("%d \n", pt->REGISTER);
    // pt->bit.status_bit = 1;
    // pt->bit.bit3 = 1;
    // pt->bit.bit4 = 1;
    // pt->bit.bit5 = 1;
    // pt->bit.bit6 = 1;
    // pt->bit.bit7 = 1;
    // printf("%d \n", pt->REGISTER);

    // goal :55.	Write a function that updates a register map structure using pointer offset arithmetic.

    // mcu_arr_t *mcu = (mcu_arr_t *)(BASE_ADDRESS); // in actual hardware
    // mcu_arr_t mcu;
    // init_mcu(&mcu) ? P_FAIL : 0;
    // // suppose at some point in code we want to set uart reg as 35 and pwm reg as 96;
    // set_uart_reg_value(&mcu, 35);
    // set_pwm_reg_value(&mcu, 96);
    // print_mcu_reg(&mcu);

    // goal :56.	Demonstrate difference between struct *p and (*p).member vs p->member.
    // SensorData_t sen = {.id = 1, .status = 0, .value = 50};
    // SensorData_t *it = &sen;
    // printf("%d %d %d\n", it->id, it->status, it->value);
    // printf("%d %d %d\n", (*it).id, (*it).status, (*it).value);
    return 0;
}