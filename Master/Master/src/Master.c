/*****************************************************************************
 * Master.c
 *****************************************************************************/

#include <sys/platform.h>
#include <drivers/spi/adi_spi.h>
#include <stdio.h>
#include "adi_initialize.h"
#include "Master.h"

/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

/*FILE *open_output_file(void)
{
	// Open file for writing as binary
	FILE *handle = fopen("output.dat", "wb");
	if(handle == NULL)  exit(1);

	return handle;
}*/

/*int main(int argc, char *argv[])
{
	FILE *output_file;
	output_file = open_output_file();

	fclose(output_file);
}*/




/* flag indicating if SPI processing is complete */
static bool bComplete = false;

/* SPI callback */
void SpiCallback(void* pHandle, uint32_t u32Arg, void* pArg)
{
    ADI_SPI_HANDLE pDevice = (ADI_SPI_HANDLE *)pHandle;
    ADI_SPI_EVENT event = (ADI_SPI_EVENT)u32Arg;
    uint16_t *data = (uint16_t*)pArg;

    switch (event) {
        case ADI_SPI_TRANSCEIVER_PROCESSED:
            bComplete = true;
            break;
    default:
        break;
    }
}

/* SPI driver memory */
uint8_t SPIDriverMemory[ADI_SPI_INT_MEMORY_SIZE];

int main(void)
{
    /* SPI driver handle */
    ADI_SPI_HANDLE hDevice;

    /* driver API result code */
	ADI_SPI_RESULT result;

	/* transceiver buffers */
	uint8_t Prologue[4]  = {0x00, 0x01, 0x02, 0x03};
	uint8_t TxBuffer[8]  = {0x00, 0x01, 0x02, 0x03, 0x00, 0x01, 0x02, 0x03};
	uint8_t RxBuffer[8];

	uint16_t clock_freq = 0x1;
	/* transceiver configurations */
	ADI_SPI_TRANSCEIVER Transceiver1  = {&Prologue[0], 4, &TxBuffer[0], 8, &RxBuffer[0], 8};
	ADI_SPI_TRANSCEIVER Transceiver2  = {NULL,         4, &TxBuffer[0], 8, NULL,         0 };

	printf("%x", Transceiver1.ReceiverBytes);

	/* Initialize managed drivers and/or services */
	adi_initComponents();

    /* open the SPI driver */
    result = adi_spi_Open(0, SPIDriverMemory, (uint32_t)ADI_SPI_DMA_MEMORY_SIZE, &hDevice);




     result = adi_spi_SetMaster(hDevice,true);
     result = adi_spi_SetHwSlaveSelect(hDevice,true);
     result = adi_spi_SetSlaveSelect(hDevice,ADI_SPI_SSEL_ENABLE1);
     result = adi_spi_SetWordSize(hDevice, ADI_SPI_TRANSFER_8BIT);
     result = adi_spi_SetClock(hDevice, clock_freq);

     //set msb,lsb

    /* No callbacks required*/
	//result = adi_spi_RegisterCallback(hDevice, NULL, NULL); //////////

    /* Disable DMA */
	result = adi_spi_EnableDmaMode(hDevice, false);

    /* submit the SPI transceiver's buffers */
	//result = adi_spi_ReadWrite(hDevice, &Transceiver1);/////////////////
	//result = adi_spi_ReadWrite(hDevice, &Transceiver2);/////////////////

	/* Register a callback for the DMA */
		result = adi_spi_RegisterCallback(hDevice, SpiCallback, NULL);

	    /* submit the SPI transceiver's buffers */
		result = adi_spi_SubmitBuffer(hDevice, &Transceiver1);
		result = adi_spi_SubmitBuffer(hDevice, &Transceiver2);

	    while(!bComplete)
	    {

		    /* do other processing here while SPI is processing */
	    }


		printf("%x", Transceiver1.pReceiver);


	/* close the SPI driver */
	result = adi_spi_Close(hDevice);

    return 0;
}
