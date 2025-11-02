#include "dht.h"
#include <avr/io.h>
#include <util/delay.h>

// Função para ler o sensor
int8_t dht_read(int8_t *temperature, int8_t *humidity) {
    uint8_t bits[5] = {0, 0, 0, 0, 0};
    uint8_t i, j = 0;

    // 1. Sinal de Start (MCU Puxa para Baixo)
    DHT_DDR |= (1 << DHT_PIN_NUM);    // Configura pino como saída
    DHT_PORT &= ~(1 << DHT_PIN_NUM);  // Pino para LOW
    _delay_ms(18);                    // Espera 18ms

    DHT_PORT |= (1 << DHT_PIN_NUM);   // Pino para HIGH (libera o barramento)
    _delay_us(1);
    DHT_DDR &= ~(1 << DHT_PIN_NUM);   // Configura pino como entrada
    DHT_PORT |= (1 << DHT_PIN_NUM);   // Ativa pull-up interno
    _delay_us(39);

    // 2. Resposta do Sensor (Sensor Puxa para Baixo)
    // Checa se o sensor respondeu (puxando para LOW)
    if (bit_is_set(DHT_PIN, DHT_PIN_NUM)) {
        return 1; // Falha (sensor não respondeu)
    }
    _delay_us(80);

    // Checa se o sensor liberou o barramento (puxando para HIGH)
    if (bit_is_clear(DHT_PIN, DHT_PIN_NUM)) {
        return 1; // Falha (sensor não liberou)
    }
    _delay_us(80);

    // 3. Leitura dos 40 bits
    for (j = 0; j < 5; j++) { // Para cada um dos 5 bytes
        for (i = 0; i < 8; i++) { // Para cada um dos 8 bits

            // Espera o pino ficar LOW (início do bit)
            while (bit_is_set(DHT_PIN, DHT_PIN_NUM));

            // Espera o pino ficar HIGH (início da contagem do pulso)
            while (bit_is_clear(DHT_PIN, DHT_PIN_NUM));

            _delay_us(30); // Espera 30 microsegundos

            // Se o pino ainda estiver HIGH, é um bit '1'
            if (bit_is_set(DHT_PIN, DHT_PIN_NUM)) {
                bits[j] |= (1 << (7 - i));
            }
        }
    }

    // 4. Verificação do Checksum
    uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (sum != bits[4]) {
        return 1; // Falha de Checksum
    }

    // 5. Retorna os valores (versão DHT22)
    // No DHT22, os bytes 0 e 1 são umidade, e 2 e 3 são temperatura.
    // O trabalho pede leituras simples, então vamos usar só a parte inteira (byte 1 e 3)
    // (Nota: esta biblioteca está simplificada para o DHT22)
    *humidity = bits[0]; // Parte inteira da umidade
    *temperature = bits[2]; // Parte inteira da temperatura

    return 0; // Sucesso
}