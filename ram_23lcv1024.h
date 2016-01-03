/*
 * ram_23lcv1024.h
 *
 * Created: 2014-04-06 09:30:05
 *  Author: Virtmedia
 */ 


#ifndef RAM_23LCV1024_H_
#define RAM_23LCV1024_H_

#include <avr/io.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
//SPI Library
#include "m8_spi.h"

//define ram cs pin i/o
#define RAM_CS_PORT	PORTD
#define RAM_CS_DDR	DDRD
#define RAM_CS_PIN	7
//Instruction set
#define RAM_INS_READ	0x03	//Read data from memory array beginning at selected address
#define RAM_INS_WRITE	0x02	//Write data to memory array beginning at selected address
#define RAM_INS_EDIO	0x3B	//Enter Dual I/O access
#define RAM_INS_RSTIO	0xFF	//Reset Dual I/O access
#define RAM_INS_RDMR	0x05	//Read Mode Register
#define RAM_INS_WRMR	0x01	//Write Mode Register
//Mode Register
#define RAM_MODE_BYTE	0x00
#define RAM_MODE_PAGE	0x80
#define RAM_MODE_SEQUENTIAL	0x40

uint32_t ram_address;
#define RAM_MAX_ADDRESS	0x1FFFFh
//Ustawia parametry do pracy
void ram_init(void);
//Ustawia stan niski pinu CS przypisanego do uk³adu
void ram_select(void);
//Ustawia stan wysoki pinu CS przypisanego do uk³adu
void ram_deselect(void);
//Wysy³a adres w postaci 3 bajtów
void ram_send_address(uint32_t address);
//Ustawia tryb dzia³ania pamiêci (byte, page, sequential <default>)
void ram_set_mode(uint8_t mode);
//Odczytuje tryb dzia³ania pamiêci
uint8_t ram_read_mode(void);
//Zapisuje bajt danych pod wskazany adres do pamiêci
void ram_write_byte(uint8_t data, uint32_t address);
//Zapisuje ci¹g bajtów zaczynaj¹c od wskazanego adresu w pamiêci
void ram_write_data(uint8_t *buffer, uint8_t buffer_size, uint32_t address);
//Zapisuje ci¹g bajtów zaczynaj¹c od wskazanego adresu w pamiêci FLASH
void ram_write_data_pgm(const uint8_t *buffer, uint8_t buffer_size, uint32_t address);
//Odczytuje i zwraca bajt danych znajduj¹cy siê pod wskazanym adresem
uint8_t ram_read_byte(uint32_t address);
//Przepisuje zawartoœæ pamiêci do bufora zaczynaj¹c od wskazanego adresu
void ram_read_data(uint8_t *buffer, uint8_t buffer_size, uint32_t address);
//Wype³nia okreœlon¹ iloœæ bajtów pamiêci podan¹ wartoœci¹ zaczynaj¹c od wskazanego adresu
void ram_fill_data(uint8_t value, uint32_t lenght, uint32_t address);

#endif /* RAM_23LCV1024_H_ */