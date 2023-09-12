#include <graphx.h>
#include <tice.h>
#include <sys/timers.h>
#include <stdlib.h>
#include <keypadc.h>
#include <string.h>

#define BUFFER_1 0xD40000
#define BUFFER_2 0xD52C00
#define WIDTH 320
#define HEIGHT 240

uint8_t* VRAM = (uint8_t*)BUFFER_1;
uint8_t* buffer2 = (uint8_t*)BUFFER_2;

void drawRect(uint8_t color, int x, int y, int width, int height) {
    for (int i = x; i<x+width; i++) {
        for (int j = y; j<y+height; j++) {
            if(i+j*WIDTH < WIDTH*HEIGHT && i+j*WIDTH >= 0){
                buffer2[i+j*WIDTH] = color;
            }
        }
    }
}
void clearBuffer() {
    memset(buffer2, 0xff, WIDTH*HEIGHT);
}

void render() {
    memcpy(VRAM, buffer2, WIDTH*HEIGHT);
}

int main(void)
{
    gfx_Begin();
    int speed = 3;

    int leftpx = 5;
    int leftpy = 100;
    int leftvy = 0;
    int leftwidth = 5;
    int leftheight = 50;

    int rightpx = 310;
    int rightpy = 100;
    int rightvy = 0;
    int rightwidth = 5;
    int rightheight = 50;

    int ballpx = 157;
    int ballpy = 117;
    int ballvx = 2;
    int ballvy = 2;
    int ballwidth = 6;
    int ballheight = 6;
 
    do {
        kb_Scan();
        if ((kb_Data[7] & kb_Up) && rightpy > 0) {
            rightvy = -speed;
        } else if ((kb_Data[7] & kb_Down) && rightpy < HEIGHT-rightheight) {
            rightvy = speed;
        } else {
            rightvy = 0;
        }

        if ((kb_Data[1] & kb_2nd) && leftpy > 0) {
            leftvy = -speed;
        } else if ((kb_Data[2] & kb_Alpha) && leftpy < HEIGHT-leftheight) {
            leftvy = speed;
        } else {
            leftvy = 0;
        }

        leftpy += leftvy;
        rightpy += rightvy;
        ballpx += ballvx;
        ballpy += ballvy;

        if (ballpy < 0 || ballpy > HEIGHT-ballheight) {
            ballvy = -ballvy;
        }

        if (ballpx < leftpx+leftwidth && ballpy > leftpy && ballpy+ballheight < leftpy+leftheight) {
            ballvx = -ballvx;
            ballvy += leftvy/2;
        }

        if (ballpx+ballwidth > rightpx && ballpy > rightpy && ballpy+ballheight < rightpy+rightheight) {
            ballvx = -ballvx;
            ballvy += rightvy/2;
        }

        if (ballpx < 0 || ballpx > WIDTH-ballwidth) {
            break;
        }

        drawRect(0x80, leftpx, leftpy, leftwidth, leftheight);
        drawRect(0x80, rightpx, rightpy, rightwidth, rightheight);
        drawRect(0x03, ballpx, ballpy, ballwidth, ballheight);
        render();
        clearBuffer();
    } while (!(kb_Data[6] & kb_Enter));
    gfx_End();
    return 0;
}
