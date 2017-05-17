#include <LPC11Uxx.h>

void SystemInit()
{
}

void delay_ms(int ms)
{
	while (ms--) {
		int ticks = 2*1000;
		while (ticks--);
	}
}

int main()
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // Enables clock for I/O configuration block.
	// set pin functions
	LPC_IOCON->PIO0_20 &= ~0x1F; // clear bits [7:0]
	LPC_IOCON->PIO0_20 |= 0u; // set bits[2:0] as PIO0_20 function.
	LPC_IOCON->PIO0_20 |= (0u << 2); // set bits[4:3] as Inactive mode.
	LPC_IOCON->PIO0_20 |= (1u << 10); // Open-drain mode.
	
	LPC_IOCON->PIO0_21 &= ~0x1F; // clear bits [7:0]
	LPC_IOCON->PIO0_21 |= 0u; // set bits[2:0] as PIO0_21 function.
	LPC_IOCON->PIO0_21 |= (0u << 2); // set bits[4:3] as Inactive mode.
	LPC_IOCON->PIO0_21 |= (1u << 10); // Open-drain mode.

	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // Disables clock for I/O configuration block.

	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); // Enables clock for GPIO port registers.

	// set GPIO directions
	LPC_GPIO->DIR[0] |= (1u << 20); // PIO0_20 for output
	LPC_GPIO->DIR[0] |= (1u << 21); // PIO0_21 for output

	// PIO0_20, PIO0_21
	while (1) {
		LPC_GPIO->SET[0] |= (1u << 21); delay_ms(1000);
		LPC_GPIO->CLR[0] |= (1u << 21); delay_ms(1000);
		LPC_GPIO->B0[20] ^= 0x1; // flip bit
		delay_ms(1000);
	}
}
