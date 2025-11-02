#ifndef DHT_H
#define DHT_H

#include <stdint.h>

// Definições do pino (conforme o diagram.json, está no Pino 7)
// Pino 7 = Bit 7 da Porta D (PD7)
#define DHT_PORT PORTD
#define DHT_DDR  DDRD
#define DHT_PIN  PIND
#define DHT_PIN_NUM 7

// Função principal
// Retorna 0 em sucesso, 1 em falha (timeout)
int8_t dht_read(int8_t *temperature, int8_t *humidity);

#endif // DHT_H