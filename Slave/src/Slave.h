/*****************************************************************************
 * Slave.h
 *****************************************************************************/

#ifndef __SLAVE_H__
#define __SLAVE_H__

typedef struct SPI_DATA
{
	uint16_t data;

}SPI_DATA;

SPI_DATA data[1000];

void readData();

void spiInitialization();

#endif /* __SLAVE_H__ */
