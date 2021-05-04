#include <sys/platform.h>
#include "adi_initialize.h"
#include "Master.h"
#include <cdefBF537.h>
#include <cdefbf537.h>
#include <ccblkfn.h>
#include <sys/exception.h>
#include <stdint.h>


//Set value for SPI_CTL register
#define SPI_CTL_SPE 1 << 14     //enable SPI
#define SPI_CTL_WOM 0 << 13     // normal
#define SPI_CTL_MSTR 1 << 12    // on 1 set as master
#define SPI_CTL_CPOL 0 << 11    // active high SCK
#define SPI_CTL_CPHA 0 << 10    // SCK toggles form the middle of the first data bit, slave select pins are controlled by HW
#define SPI_CTL_LSBF 1 << 9     // LSB sent/received first
#define SPI_CTL_SIZE 1 << 8     //transfer size of 16 bits
#define SPI_CTL_EMISO 0 << 5    //do not configure MISO pin as output
#define SPI_CTL_PSSE 0 << 4     //do not enable SPISS input for master
#define SPI_CTL_GM 1 << 3       // When SPI_RDBR is full: discard incoming data(set bit on 0), get more data and overwrite prev data (set on 1)
#define SPI_CTL_SZ 1 << 2       //when SPI_TDBR is empty: send last word (bit on 0), send zeros (bit on 1)
#define SPI_CTL_TIMOD1 0 << 1   //set TIMOD[1:0] to 01 to initiate a transfer when transmit buffer is written
#define SPI_CTL_TIMOD0 0

#define SPI_CTL_REG (SPI_CTL_SPE | SPI_CTL_WOM | SPI_CTL_MSTR | SPI_CTL_CPOL |SPI_CTL_CPHA | SPI_CTL_LSBF | SPI_CTL_SIZE | SPI_CTL_EMISO | SPI_CTL_PSSE | SPI_CTL_GM | SPI_CTL_SZ | SPI_CTL_TIMOD1 | SPI_CTL_TIMOD0)



//Set value for PORT_FER register
#define SPI_PORT_FER 0x3C00 //set bit 13 for SCK, bit 12 for MISO, bit 11 for MOSI and bit 10 SPISSE1




//Set value for SPI_BAUD register
#define SPI_BAUD_REG 0x000F;   //set on 0x0005 later

EX_INTERRUPT_HANDLER(SPI_ISR);

char __argv_string[] = "";


volatile int cnt = 0;
volatile uint16_t data_in;
uint16_t data_out;




void spi_init_port(void)
{
	*pPORTF_FER = SPI_PORT_FER;
	//uint16_t a = *pPORTF_FER;
	ssync();
}

void spi_init_master(void)
{
	uint16_t data = 0;
	//data = *pPLL_DIV;


	*pSPI_FLG = 0x0202; //set bit 1 in order to enable SPISSEL1 and bit 9 to 1 in order to deactivate transmission
	uint16_t a = *pSPI_FLG;
	*pSPI_BAUD = SPI_BAUD_REG;
	//uint16_t b = *pSPI_BAUD;
	*pSPI_CTL = SPI_CTL_REG;
	//uint16_t c = *pSPI_CTL;
	ssync();

	data = *pSPI_RDBR;
}


void initInterrupts(void)
{
	//*pSIC_IAR3 |= 0x3FF;
	*pSIC_IMASK |= 0x400;
	register_handler(ik_ivg10, SPI_ISR);
	ssync();
}


void spi_init_data(void)
{
	data_out = 0x1234;
}

EX_INTERRUPT_HANDLER(SPI_ISR)
{
	if (*pSPI_STAT & TXS == 1)
	{
		*pSPI_TDBR = data_out;
		ssync();
	}

	if (*pSPI_STAT & RXS == 1)
	{
		data_in = *pSPI_RDBR;
	}

	cnt = 1;

	//*pSPI_CTL &= 0xBFFF;
}

void main(int argc, char* argv[])
{
	adi_initComponents();
	spi_init_port();
	initInterrupts();
	spi_init_data();
	spi_init_master();

	//*pSPI_TDBR = data_out;
	uint16_t data = 0;
	data = *pSPI_RDBR;
	while (cnt == 0)
	{
		;
	}
}
