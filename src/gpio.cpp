#include "gpio.hpp"

int mem_fd;
void *gpio_map;
volatile unsigned *gpio;

bool init_gpio(void)
{
	/* open /dev/mem */
	if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
	{
		printf("can't open /dev/mem");
		return false;
	}

	/* mmap GPIO */
	gpio_map = mmap(
		NULL,					//Any adddress in our space will do
		BLOCK_SIZE,				//Map length
		PROT_READ | PROT_WRITE, // Enable reading & writting to mapped memory
		MAP_SHARED,				//Shared with other processes
		mem_fd,					//File to map
		GPIO_BASE				//Offset to GPIO peripheral
	);

	close(mem_fd); //No need to keep mem_fd open after mmap

	if (gpio_map == MAP_FAILED)
	{
		printf("mmap error %d\n", (int)gpio_map); //errno also set!
		return false;
	}

	// Always use volatile pointer!
	gpio = (volatile unsigned *)gpio_map;

	// Set LED IN/OUT mode
	INP_GPIO(LED_RED); // must use INP_GPIO before we can use OUT_GPIO
	OUT_GPIO(LED_RED);
	INP_GPIO(LED_YELLOW); // must use INP_GPIO before we can use OUT_GPIO
	OUT_GPIO(LED_YELLOW);
	INP_GPIO(LED_GREEN); // must use INP_GPIO before we can use OUT_GPIO
	OUT_GPIO(LED_GREEN);
    INP_GPIO(2); 
	OUT_GPIO(2);
    INP_GPIO(3); 
	OUT_GPIO(3);

	return true;

} // setup_io