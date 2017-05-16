#include <LPC11Uxx.h>

void SystemInit()
{
}

void delay_ms(int ms)
{
	while (ms--) {
		int ticks = 12*1000;
		while (ticks--);
	}
}

int main()
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // Enables clock for I/O configuration block.
	// set pin functions
	LPC_IOCON->TDI_PIO0_11 &= ~0x1F; // clear bits [4:0]
	LPC_IOCON->TDI_PIO0_11 |= 0x1; // set bits[2:0] as 0x1, PIO0_11 function.
	LPC_IOCON->TDI_PIO0_11 |= (0x1 << 2); // set bits[4:3] as 0x1, Pull-down mode.
	
	LPC_IOCON->PIO0_20 &= ~0x01F; // clear bits [4:0]
	LPC_IOCON->PIO0_20 |= 0x0; // set bits[2:0] as PIO0_20 function.
	LPC_IOCON->PIO0_20 |= (0x0 << 2); // set bits[4:3] as Inactive mode.
	
	LPC_IOCON->PIO0_21 &= ~0x1F; // clear bits [4:0]
	LPC_IOCON->PIO0_21 |= 0x0; // set bits[2:0] as PIO0_21 function.
	LPC_IOCON->PIO0_21 |= (0x1 << 2); // set bits[4:3] as Pull-down mode.

	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // Disables clock for I/O configuration block.

	// set GPIO directions
	LPC_GPIO->DIR[0] |= (1<<11); // PIO0_11 for output
	LPC_GPIO->DIR[0] |= (1<<20); // PIO0_20 for output
	LPC_GPIO->DIR[0] |= (1<<21); // PIO0_21 for output

	// PIO0_11, PIO0_20, PIO0_21
	LPC_GPIO->B0[11] = 0x0;
	LPC_GPIO->B0[21] = 0x0;

	while (1) {
		LPC_GPIO->B0[20] ^= 0x1; // flip bit
		delay_ms(1000);
	}
}
