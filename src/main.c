#include <graphx.h>
#include <tice.h>
#include <sys/timers.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_1 0xD40000
#define BUFFER_2 0xD52C00

uint8_t* VRAM = (uint8_t*)BUFFER_1;
uint8_t* buffer2 = (uint8_t*)BUFFER_2;

void draw(uint8_t color) {
    for( int i = 0; i < 320*240; i++ ) {
        buffer2[i] = color;
    }
    memcpy(VRAM, buffer2, 320*240);
}

int main(void)
{
    gfx_Begin();
    draw(0x80);
    sk_key_t key;
    do {
        key = os_GetCSC();
    } while (key != sk_Enter);
    gfx_End();
    return 0;
}
