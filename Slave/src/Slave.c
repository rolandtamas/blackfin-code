/*****************************************************************************
 * Slave.c
 *****************************************************************************/

#include <sys/platform.h>
#include <cdefBF537.h>
#include <ccblkfn.h>
#include "adi_initialize.h"
#include "Slave.h"

/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	


	return 0;
}

void SPIInitialization()
{
	//set PF11 as input pin
	*pPORTFIO_INEN = 0x0800;

	//enable this device as a slave
	SPI_CTL = 0x0010;


}

