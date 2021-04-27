/*****************************************************************************
 * Slave.c
 *****************************************************************************/

#include <sys/platform.h>
#include <defBF537.h>
#include <cdefBF537.h>
#include <ccblkfn.h>
#include "adi_initialize.h"
#include "Slave.h"

/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

void spiInitialization()
{

	// Enable PF11(MOSI) & PF13(SCK) as input
	*pPORTFIO_INEN = (1<<11) | (1<<13);


	// Initialize device as slave device,
	// by activating bit 12 of the
	// SPI_CTL Register

	*pSPI_CTL |= (1<<12);

	// also set TIMOD to 00,
	// so that it starts transfer with a read
	// of SPI_RDBR (an interrupt is issued
	// when RDBR is full)
	*pSPI_CTL &= ~(1<<0);
}

void readData()
{
	int i=0;

	while(*pSPI_CTL==0x0000)
	{
		data[i].data = *pSPI_RDBR;
		i++;
	}

}


int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();

	spiInitialization();

	readData();


	return 0;
}

