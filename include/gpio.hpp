#include "stdafx.hpp"
#include <sys/mman.h>

extern volatile unsigned *gpio;

#define PAGE_SIZE (4 * 1024)
#define BLOCK_SIZE (4 * 1024)
#define GPIO_BASE 0x3F200000
#define INP_GPIO(g) *(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) *(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))
#define SET_GPIO_ALT(g, a) *(gpio + (((g) / 10))) |= (((a) <= 3 ? (a) + 4 : (a) == 4 ? 3 : 2) << (((g) % 10) * 3))
#define GPIO_SET *(gpio + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio + 10) // clears bits which are 1 ignores bits which are 0
#define GET_GPIO(g) (*(gpio + 13) & (1 << g)) // 0 if LOW, (1<<g) if HIGH
#define GPIO_PULL *(gpio + 37)	   // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio + 38) // Pull up/pull down clock

// #define LED_OFF 0
// #define LED_LIT 1
// #define LED_BLINK 2
#define LED_RED 17
#define LED_GREEN 22
#define LED_YELLOW 27

bool init_gpio(void);