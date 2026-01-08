
#include <stdint.h>
#include <limits.h>
#include <stdio.h>


#define SETBIT(a,b)     ((a)|= (b))
#define CLEARBIT(a,b)     ((a) &= (~(b)))
#define TOGGLEBIT(a,b)     ((a) ^= (b))



#define STACKPTR_SIM                    0x40000000U // address simulation
#define STACKPTR                       (*((volatile uint32_t * )(STACKPTR_SIM)))

volatile uint32_t spi_data_buff[10];


typedef struct {
    uint32_t head;
    uint32_t tail;
    uint32_t max;
    uint32_t cnt;
    int32_t* buf;

}CircularBuff_t;

typedef enum {
    CB_OK = 0,
    CB_ERR_NULL,
    CB_ERR_FULL,
    CB_ERR_EMPTY
} cb_status_t;

typedef struct {
    uint32_t gpio_reg;
    uint32_t uart_reg;
    uint32_t spi_reg;
}ConfigReg_t;

cb_status_t  is_cb_empty (CircularBuff_t* hb) {
    if (!hb) return CB_ERR_NULL;
    if (hb->cnt <= 0)return CB_ERR_EMPTY;
    else return CB_OK;
}
cb_status_t  is_cb_full (CircularBuff_t* hb) {
    if (!hb) return CB_ERR_NULL;
    if (hb->cnt >= hb->max)return CB_ERR_FULL;
    else return CB_OK;
}

cb_status_t  push_cb (CircularBuff_t* hb, const int32_t val) {
    if (!hb)return CB_ERR_NULL;
    if (is_cb_full (hb)) return CB_ERR_FULL;

    hb->buf[hb->head] = val;

    hb->head++;
    hb->cnt++; // cnt overflow wont happen because early checked that buffer has sufficient space
    if (hb->head >= hb->max) {
        hb->head = 0;
    }
    return CB_OK;
}
cb_status_t  pop_cb (CircularBuff_t* hb, int32_t* out) {
    if (!hb || !out)return CB_ERR_NULL;
    if (is_cb_empty (hb)) return CB_ERR_EMPTY;

    *out = hb->buf[hb->tail];

    hb->buf[hb->tail] = 0;
    hb->tail++;
    hb->cnt--;
    if (hb->tail >= hb->max) {
        hb->tail = 0;
    }
    return CB_OK;
}

cb_status_t  print_cb (CircularBuff_t* hb) {
    // i made this becasue i specifically want to see whole buffer irrespective of heade tail
    if (!hb)  return CB_ERR_NULL;

    for (uint32_t i = 0; i < hb->max; i++) {
        printf ("%d ", hb->buf[i]);
    }
    printf ("\n");
    return CB_OK;

}
cb_status_t  CircularBuffInit (CircularBuff_t* hb, void* cbuff, const uint32_t size) {
    if (!hb || !cbuff || size <= 0)return CB_ERR_NULL;
    hb->buf = (int32_t*)cbuff;
    hb->cnt = 0;
    hb->head = 0;
    hb->tail = 0;
    hb->max = size;
    while (hb->cnt < hb->max) {
        hb->buf[hb->cnt++] = 0;
    }
    hb->cnt = 0;
    return CB_OK;
}

void setbit (volatile uint32_t* var, uint32_t bit) {
    if (var)*var |= bit;
    return;
}

uint8_t  my_memset (volatile  void* buf, const uint8_t val, uint32_t size) {
    if (!buf || size <= 0)
        return 1;
    volatile uint8_t* pt = (volatile uint8_t*)buf;

    for (uint32_t i = 0; i < size; i++) {
        pt[i] = val;
        // printf ("%x %x \n", *pt, val);
    }
    return 0;
}
int main () {
    //gcc -Wall -Wextra -Werror -Wpedantic -fmax-errors=1 -O0 p.c -o p && ./p

    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);


    // goal: 36.	Given an array of ADC readings, find max and min using pointers.
    // int adc[] = { 6,5,8,74,5,32,1,15,7,85,9,5,4,78,6,5,8,2,33,6,54,1,25,4,2,2,5,4,-5,100 };
    // int* maxpt = &adc[0];
    // int* minpt = &adc[0];
    // int* itr = &adc[1];
    // for (int i = 1; i < (sizeof (adc) / sizeof (adc[0]));i++) {
    //     if (*itr > *maxpt) {
    //         maxpt = itr;
    //     }
    //     if (*itr < *minpt) {
    //         minpt = itr;
    //     }
    //     itr++;
    // }
    // printf ("max:%d min:%d \n", *maxpt, *minpt);

    // goal: 37.	Simulate a circular buffer using pointer increment and wrap - around logic.
    int cbuff_size = 10;
    int32_t cbuff[cbuff_size];
    CircularBuff_t hcbuff;
    CircularBuffInit (&hcbuff, &cbuff[0], cbuff_size);


    push_cb (&hcbuff, 5) ? printf ("Failed\n") : printf ("push:5\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, 10) ? printf ("Failed\n") : printf ("push:10\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, 12) ? printf ("Failed\n") : printf ("push:12\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, -5) ? printf ("Failed\n") : printf ("push:-5\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, 96) ? printf ("Failed\n") : printf ("push:96\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, 1) ? printf ("Failed\n") : printf ("push:1\n");
    print_cb (&hcbuff);
    printf ("\n");

    int v1 = 0;
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    printf ("\n");

    push_cb (&hcbuff, 5) ? printf ("Failed\n") : printf ("push:5\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, 10) ? printf ("Failed\n") : printf ("push:10\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, 12) ? printf ("Failed\n") : printf ("push:12\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, -5) ? printf ("Failed\n") : printf ("push:-5\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, 96) ? printf ("Failed\n") : printf ("push:96\n");
    print_cb (&hcbuff);
    push_cb (&hcbuff, 1) ? printf ("Failed\n") : printf ("push:1\n");
    print_cb (&hcbuff);

    printf ("\n");
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    pop_cb (&hcbuff, &v1) ? printf ("Failed\n") : printf ("pop:%d \n", v1);
    print_cb (&hcbuff);
    printf ("\n");

    // goal: 38.	Use pointers to access memory - mapped I / O registers (e.g., #define PORTA (*(volatile uint8_t*)0x4000)).
    // uint32_t stackptrloc = (uint32_t*)STACKPTR;

    // goal: 39.	Demonstrate volatile keyword effect with pointers to a simulated hardware register.
    // spi_data_buff; // this buffer will be filled by SPI peripheral;

    // goal: 40.	Write a function that takes a volatile uint16_t * and sets specific bits.

    // volatile uint32_t var = 0x26589364;
    // volatile uint32_t var2 = 0x26589364;
    // setbit (&var, 5);
    // printf ("%x \n", var);


    // goal: 41.	Implement SetBit (), ClearBit (), and ToggleBit () functions using pointers and bitmasking.

    // volatile uint32_t var1 = 0xffffffff;
    // volatile uint32_t var2 = 0xffffffff;
    // volatile uint32_t var3 = 0xffffffff;

    // SETBIT (var1, 0x4852);
    // CLEARBIT (var2, 0x4852);
    // TOGGLEBIT (var3, 0x4852);
    // printf ("%x %x %x\n", var1, var2, var3);

    // goal: 42.	Use pointer arithmetic to iterate over simulated sensor data buffers.
    // volatile uint32_t adcbuf[] = { 6,5,8,8,9,4,58,5,2,6,5,4,8,3,5,4,6,9,8,5,4,6,2,5,4,2,5,5,87,9,6,5,6,9,0,29,45,5,295,625,64,6,560 };
    // uint32_t* pt = &adcbuf[0];
    // for (uint32_t i = 0; i < ((sizeof (adcbuf)) / (sizeof (adcbuf[0]))); i++) {
    //     printf ("%d ", *pt++);
    // }
    // printf ("\n");

    // goal: 43.	Access structure members using pointers to structure (-> operator).

    // CircularBuff_t obj;
    // CircularBuff_t* ptr = &obj;
    // ptr->head = 0;
    // ptr->max = 3;

    // goal: 44.	Create a pointer to a structure and use it to configure “registers” (simulate register map).

    // ConfigReg_t reg;
    // ConfigReg_t* reg_pt = &reg;
    // reg_pt->gpio_reg = 0x00005656;
    // reg_pt->spi_reg = 0x00009696;
    // reg_pt->uart_reg = 0x00001452;

    // goal: 45.	Implement memset () manually using pointer arithmetic for embedded buffer initialization.
    // volatile uint32_t spi_buf[100];

    // my_memset (&spi_buf, 0x0a, 100 * sizeof (int));

    // uint32_t* it_ptr = (void*)&spi_buf[0];

    // printf ("\n");
    // for (uint32_t i = 0; i < 100; i++) {
    //     printf ("%x ", *it_ptr++);
    // }
    // printf ("\n");

    return 0;
}