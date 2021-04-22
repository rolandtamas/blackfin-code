/*****************************************************************************
 * Slave.c
 *****************************************************************************/

#include <sys/platform.h>
<<<<<<< HEAD
#include <defBF537.h>
=======
#include <cdefBF537.h>
>>>>>>> 5b49b33e1bf08c8e0f1664c0def4ccafc179f59d
#include <ccblkfn.h>
#include "adi_initialize.h"
#include "Slave.h"

/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

<<<<<<< HEAD
void spiInitialization()
{
	uint16_t controlRegister = SPI_CTL;

	// Enable PF11(MOSI) & PF13(SCK) as input
	*pPORTFIO_INEN = (1<<11) | (1<<13);


	//initialize device as slave device,
	//by activating bit 12 of the
	//SPI_CTL Register
	controlRegister |= 0x1000;
}

=======
>>>>>>> 5b49b33e1bf08c8e0f1664c0def4ccafc179f59d
int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
<<<<<<< HEAD
	spiInitialization();
=======
	

>>>>>>> 5b49b33e1bf08c8e0f1664c0def4ccafc179f59d

	return 0;
}

<<<<<<< HEAD
=======
void SPIInitialization()
{
	//set PF11 as input pin
	*pPORTFIO_INEN = 0x0800;

	//enable this device as a slave
	SPI_CTL = 0x0010;


}

>>>>>>> 5b49b33e1bf08c8e0f1664c0def4ccafc179f59d
