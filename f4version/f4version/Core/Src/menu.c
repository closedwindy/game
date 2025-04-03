#include "menu.h"
#include "bmp.h"
#include <stdio.h>
#include <string.h>





int Desktop1_direction=0;
int Desktop1_x=0,Desktop1_y=0;


int Desktop2_SETdirection=0;
int Desktop2_SETx=0,Desktop2_SETy=0;


extern u8g2_t u8g2;


void Desktop1(void)
{

    u8g2_SetDrawColor(&u8g2,1);
    if(Desktop1_direction>126){Desktop1_direction=42;Desktop1_x=0;}
    else if(Desktop1_direction<-126){Desktop1_direction=-42;Desktop1_x=0;}

    if(Desktop1_x<Desktop1_direction)Desktop1_x=Desktop1_x+7;
    else if(Desktop1_x>Desktop1_direction)Desktop1_x=Desktop1_x-7;//???????????????42???????
    else if(Desktop1_x==Desktop1_direction)Desktop1_x=Desktop1_direction;

    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_8x13B_tr);
    u8g2_DrawRFrame(&u8g2,44,14,42,36,3);

    Desktop1_y=Desktop1_x;
    u8g2_DrawXBMP(&u8g2,5+Desktop1_y,16,32,32,BMP1);
    u8g2_DrawStr(&u8g2,9+Desktop1_y,64,"SET");
    if(Desktop1_y>91)Desktop1_y=Desktop1_y-128;
    else if(Desktop1_y<-5)Desktop1_y=Desktop1_y+128;
    u8g2_DrawXBMP(&u8g2,5+Desktop1_y,16,32,32,BMP1);
    u8g2_DrawStr(&u8g2,9+Desktop1_y,64,"SET");


    Desktop1_y=Desktop1_x;
    u8g2_DrawXBMP(&u8g2,48+Desktop1_y,16,32,32,BMP4);
    u8g2_DrawStr(&u8g2,47+Desktop1_y,64,"hell");
    if(Desktop1_y>48)Desktop1_y=Desktop1_y-128;
    else if(Desktop1_y<-48)Desktop1_y=Desktop1_y+128;
    u8g2_DrawXBMP(&u8g2,48+Desktop1_y,16,32,32,BMP4);
    u8g2_DrawStr(&u8g2,47+Desktop1_y,64,"hell");



    Desktop1_y=Desktop1_x;
    u8g2_DrawXBMP(&u8g2,88+Desktop1_y,16,32,32,BMP3);
    u8g2_DrawStr(&u8g2,92+Desktop1_y,64,"START");
    if(Desktop1_y>5)Desktop1_y=Desktop1_y-128;
    else if(Desktop1_y<-91)Desktop1_y=Desktop1_y+128;
    u8g2_DrawXBMP(&u8g2,91+Desktop1_y,16,32,32,BMP3);
    u8g2_DrawStr(&u8g2,88+Desktop1_y,64,"START");

    u8g2_SendBuffer(&u8g2);
}

void Desktop2_SET(int direction)
{

    int a=0;
    int b=0;

    a=strlen("Easy");
    b=strlen("Mid");

    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_8x13B_tr);
    u8g2_DrawStr(&u8g2,0,16,"Easy");
    u8g2_DrawStr(&u8g2,0,32,"Mid");
    u8g2_DrawStr(&u8g2,0,48,"Hard");

    u8g2_SetDrawColor(&u8g2,2);

    if(Desktop2_SETy<direction)Desktop2_SETy=Desktop2_SETy+4;
    else if(Desktop2_SETy>direction)Desktop2_SETy=Desktop2_SETy-4;
    else if(Desktop2_SETy==direction)Desktop2_SETy=Desktop2_SETy;

    if(direction>0&&direction<=16)
    {

        if(Desktop2_SETx<b)Desktop2_SETx=Desktop2_SETx+1;
        else if(Desktop2_SETx>b)Desktop2_SETx=Desktop2_SETx-1;
        else if(Desktop2_SETx==b)Desktop2_SETx=Desktop2_SETx;
    }
    else
    {
        if(Desktop2_SETx<a)Desktop2_SETx=Desktop2_SETx+1;
        else if(Desktop2_SETx>a)Desktop2_SETx=Desktop2_SETx-1;
        else if(Desktop2_SETx==a)Desktop2_SETx=Desktop2_SETx;
    }



    u8g2_DrawBox(&u8g2,0,Desktop2_SETy+4,Desktop2_SETx*8,14);
    u8g2_SendBuffer(&u8g2);
    printf("direction=%d    Desktop2_SETy=%d\r\n",direction,Desktop2_SETy);
}
//void Desktop2_SET(int direction)
//{
//    // Pre-calculate string lengths and positions
//    const char *easyStr = "Easy";
//    const char *midStr = "Mid";
//    const char *hardStr = "Hard";
//
//    const int a = strlen(easyStr);
//    const int b = strlen(midStr);
//    const int c = strlen(hardStr);
//
//    // Y positions for menu items
//    const int easyY = 16;
//    const int midY = 32;
//    const int hardY = 48;
//
//    // Height of selection box
//    const int boxHeight = 16;
//
//    // Clear the buffer and draw menu
//    u8g2_ClearBuffer(&u8g2);
//    u8g2_SetFont(&u8g2, u8g2_font_8x13B_tr);
//    u8g2_DrawStr(&u8g2, 0, easyY, easyStr);
//    u8g2_DrawStr(&u8g2, 0, midY, midStr);
//    u8g2_DrawStr(&u8g2, 0, hardY, hardStr);
//
//    // Set draw color for selection box
//    u8g2_SetDrawColor(&u8g2, 2);
//
//    // Handle vertical movement (Desktop2_SETy)
//    if (Desktop2_SETy < direction) {
//        Desktop2_SETy += 4;
//    }
//    else if (Desktop2_SETy > direction) {
//        Desktop2_SETy -= 4;
//    }
//    // else remains the same
//
//    // Handle horizontal movement (Desktop2_SETx) based on direction
//    int targetWidth = (direction > 0) ? b : a;
//
//    if (Desktop2_SETx < targetWidth) {
//        Desktop2_SETx += 1;
//    }
//    else if (Desktop2_SETx > targetWidth) {
//        Desktop2_SETx -= 1;
//    }
//    // else remains the same
//
//    // Draw selection box
//    u8g2_DrawBox(&u8g2, 0, Desktop2_SETy, Desktop2_SETx * 8, boxHeight);
//
//    // Send buffer to display
//    u8g2_SendBuffer(&u8g2);
//
//    // Debug output
//    printf("direction=%d    Desktop2_SETy=%d\r\n", direction, Desktop2_SETy);
//}
void HELL(void)
{





}

void Desktop2_VCU(void)
{
    u8g2_SetDrawColor(&u8g2,1);
    u8g2_ClearBuffer(&u8g2);

    u8g2_SetFont(&u8g2, u8g2_font_8x13B_tr);
    u8g2_DrawStr(&u8g2,0,16,"MaximumSpeed:");
    u8g2_DrawStr(&u8g2,0,32,"MinimumSpeed:");

    u8g2_SendBuffer(&u8g2);

}

