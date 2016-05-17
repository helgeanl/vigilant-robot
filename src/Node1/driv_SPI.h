/*
 * driv_SPI.h
 *
 * Created: 01.10.2015 11:11:57
 *  Author: helgeanl
 */ 


#ifndef DRIV_SPI_H_
#define DRIV_SPI_H_

#define DDR_SPI DDRB
#define CS_MCP2515 DDB4
#define DD_MOSI DDB5
#define DD_MISO PINB6
#define DD_SCK DDB7


//Low level functions
void spi_send(uint8_t cData);
uint8_t spi_read();
void spi_init();



#endif /* DRIV_SPI_H_ */