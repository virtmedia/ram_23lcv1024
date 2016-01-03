/*
 * ram_23lcv1024.c
 *
 * Created: 2014-04-06 09:29:45
 *  Author: Virtmedia
 */ 

#include "ram_23lcv1024.h"

//Ustawia parametry do pracy
void ram_init(void)
{
	RAM_CS_DDR |= (1<<RAM_CS_PIN);
	spi_init();
}
//Ustawia stan niski pinu CS przypisanego do układu
void ram_select(void)
{
	RAM_CS_PORT &= ~(1<<RAM_CS_PIN);
}
//Ustawia stan wysoki pinu CS przypisanego do układu
void ram_deselect(void)
{
	RAM_CS_PORT |= (1<<RAM_CS_PIN);
}
//Wysyła adres w postaci 3 bajtów
void ram_send_address(uint32_t address)
{
	spi_send_byte((address>>16) & 0xFF);
	spi_send_byte((address>>8) & 0xFF);
	spi_send_byte((address) & 0xFF);
}
//Ustawia tryb działania pamięci (byte, page, sequential <default>)
void ram_set_mode(uint8_t mode)
{
	ram_select();
	spi_send_byte(RAM_INS_WRMR);
	spi_send_byte(mode);
	ram_deselect();
}
//Odczytuje tryb działania pamięci
uint8_t ram_read_mode(void)
{
	uint8_t data;
	ram_select();
	spi_send_byte(RAM_INS_RDMR);
	data = spi_send_byte(0);
	ram_deselect();
	return data;
}
//Zapisuje bajt danych pod wskazany adres do pamięci
void ram_write_byte(uint8_t data, uint32_t address)
{
	ram_select();
	spi_send_byte(RAM_INS_WRITE);
	ram_send_address(address);
	spi_send_byte(data);
	ram_deselect();
}
//Zapisuje ciąg bajtów zaczynając od wskazanego adresu w pamięci
void ram_write_data(uint8_t *buffer, uint8_t buffer_size, uint32_t address)
{
	ram_select();
	spi_send_byte(RAM_INS_WRITE);
	ram_send_address(address);
	for(uint8_t i=0;i<buffer_size;++i)
	{
		spi_send_byte(*(buffer+i));
	}
	ram_deselect();
}

void ram_write_data_pgm(const uint8_t *buffer, uint8_t buffer_size, uint32_t address)
{
	ram_select();
	spi_send_byte(RAM_INS_WRITE);
	ram_send_address(address);
	for(uint8_t i=0;i<buffer_size;++i)
	{
		spi_send_byte(pgm_read_byte(buffer+i));
	}
	ram_deselect();
}

//Odczytuje i zwraca bajt danych znajdujący się pod wskazanym adresem
uint8_t ram_read_byte(uint32_t address)
{
	uint8_t data;
	ram_select();
	spi_send_byte(RAM_INS_READ);
	ram_send_address(address);
	data = spi_send_byte(0);
	ram_deselect();
	return data;
}
//Przepisuje zawartość pamięci do bufora zaczynając od wskazanego adresu
void ram_read_data(uint8_t *buffer, uint8_t buffer_size, uint32_t address)
{
	ram_select();
	spi_send_byte(RAM_INS_READ);
	ram_send_address(address);
	while(buffer_size)
	{
		*buffer = spi_send_byte(0);
		++buffer;
		--buffer_size;
	}
	ram_deselect();
}
//Wypełnia określoną ilość bajtów pamięci podaną wartością zaczynając od wskazanego adresu
void ram_fill_data(uint8_t value, uint32_t lenght, uint32_t address)
{
	ram_select();
	spi_send_byte(RAM_INS_WRITE);
	ram_send_address(address);
	while(--lenght)
	{
		spi_send_byte(value);
	}
	ram_deselect();
}