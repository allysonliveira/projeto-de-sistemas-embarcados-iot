#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>

// Funções principais
void ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_goto(uint8_t x, uint8_t y);
void ssd1306_string(const char *str);
void ssd1306_string_xy(uint8_t x, uint8_t y, const char *str);

#endif // SSD1306_H