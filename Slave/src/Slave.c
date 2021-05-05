/*****************************************************************************
 * Slave.c
 *****************************************************************************/

#include <sys/platform.h>
#include <defBF537.h>
#include <cdefBF537.h>
#include <ccblkfn.h>
#include "adi_initialize.h"
#include "Slave.h"

//signals used in SPI transfers

#define MOSI (1<<11)
#define MISO (1<<12)
#define SCK  (1<<13)
#define _SPISS (1<<14)

//build the SPI_CTL register

/*#define SPI_ENABLE (1<<14)
#define WOM (0<<13)
#define SLAVE_SET (0<<12)
#define CPOL (0<<11)
#define CPHA (0<<10)
#define LSBF (1<<9)
#define WORD_SIZE (1<<8)
#define EMISO (0<<5)
#define PSSE (1<<4)
#define GM (1<<3)
#define SZ (1<<2)
#define TIMOD1 (0<<1)
#define TIMOD0 0*/
#define SLAVE_SET (0<<12)
#define WORD_SIZE (1<<8)
#define TIMOD1 (0<<1)
#define TIMOD0 0

/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

void spiInitialization()
{

	// Enable PF11(MOSI) & PF13(SCK) as input,
	// Enable PF12(MISO) as output
	// SCK is enabled as input because
	// it receives the clock signal from
	// the master(they should be in sync)

	*pPORTFIO_INEN = MOSI | MISO | SCK;

	// Select this device as a slave

	*pPORTF_FER |= _SPISS;

	// Set the bits from the CTL register

	*pSPI_CTL = SPE | WOM | SLAVE_SET | CPOL | CPHA | LSBF | WORD_SIZE | EMISO | PSSE |
			GM | SZ | TIMOD1 | TIMOD0;
}

void readData()
{
	int i=0;

	while(*pSPI_STAT!=0x0001)
	{// While bit 1 from SPI_STAT is not set to 1,
		// which indicates a successful word transfer,
		// continue reading data from SPI_RDBR
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

