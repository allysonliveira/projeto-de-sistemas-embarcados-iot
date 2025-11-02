#include "ssd1306.h" // Nossa biblioteca do display
#include <util/delay.h> // Para o delay

int main(void) {
    // 1. Inicializa o display (com o endereço 0x3C)
    // (Se você ainda estiver com 0x3D no seu ssd1306.c, volte para 0x3C)
    ssd1306_init();

    // 2. Limpa a tela
    ssd1306_clear();

    // 3. Escreve o texto estático
    ssd1306_string_xy(0, 0, "Estufa IoT");
    ssd1306_string_xy(0, 2, "Display OK!");

    // 4. Loop infinito
    while (1) {
        // Não faz nada, apenas mantém o display aceso
    }

    return 0;
}