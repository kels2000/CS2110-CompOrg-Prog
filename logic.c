#include "main.h"
#include "main.c"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/start.h"
#include "images/win.h"
#include "images/end.h"
#include "images/ball.h"

void playEscape(GBAState *state) {        //game
  setUpBricks();      //set bricks
  makePlatform();       //make draw platform
  b = setBall();            //make draw ball
  trackScore(BLACK);
  int rd = -1;    //starting direction up
  int cd = 1;     //starting direction right
  u32 buttons;
  while (*state == PLAY) {
    waitForVBlank();
    buttons = BUTTONS;
    if (KEY_DOWN(BUTTON_LEFT, buttons)) {     //move platform left
      drawRectDMA(140, p.col, 25, 5, BLACK);
      p.col--;
      p.left--;
      p.right--;
      if (p.col <= 0) {
        p.col = 0;
        p.left = p.col;
        p.right = p.col + 25;
      }
      drawRectDMA(140, p.col, 25, 5, WHITE);
    }
    if (KEY_DOWN(BUTTON_RIGHT, buttons)) {    //move platform right;
      drawRectDMA(140, p.col, 25, 5, BLACK);
      p.col++;
      p.left++;
      p.right++;
      if (p.right >= 240) {
        p.right = 240;
        p.left = p.right - 25;
        p.col = p.left;
      }
      drawRectDMA(140, p.col, 25, 5, WHITE);
    }
    drawRectDMA(b.row, b.col, 2, 2, BLACK);     //clear previous ball
    if (b.row < 0) {    //if ball reaches top border
      rd = 1;
      b.row = 0;
    } else if(b.row > 160) {      //if ball reaches bottom border
      *state = LOSECLEAR;                    //should drop through and go to lose screen
      return;
    } else if (b.row < 35) {      //all bricks above 35 so check for collisions
      for (int i = 0; i < 5; i++) {         //iterate through layerArr
        for (int j = 0; j < 9; j++) {           //iterate through arr
          int bot = layerArr[i].arr[j].botBorder;
          int top = layerArr[i].arr[j].topBorder;
          int right = layerArr[i].arr[j].rightBorder;
          int left = layerArr[i].arr[j].leftBorder;
          u16 color = layerArr[i].arr[j].color;
          if (rd > 0 && cd > 0) {         //moving down right
            if (b.bot == top && b.right > left && b.col < right) {      //hit from top
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                rd = -1;
              }
            } else if (right == left && b.row < bot && b.bot > top) {  //hit from left
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                cd = -1;
              }
            }
          } else if (rd < 0 && cd > 0) {  //moving up right
            if (b.row == bot && b.right > left && b.col < right) {          //hit from bot
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                rd = 1;
              }
            } else if (b.right == left && b.row < bot && b.bot > top) {     //hit from left
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                cd = -1;
              }
            }
          } else if (rd < 0 && cd < 0) {  //moving up left
            if (b.row == bot && b.right > left && b.col < right) {          //hit from bot
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                rd = 1;
              }
            } else if (b.col == right && b.row < bot && b.bot > top) {       //hit from right
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                cd = 1;
              }
            }
          } else if (rd > 0 && cd < 0) {  //moving down left
            if (b.bot == top && b.right > left && b.col < right) {          //hit from top
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                rd = -1;
              }
            } else if (b.col == right && b.row < bot && b.bot > top) {   //hit from right
              if (color != BLACK) {
                trackScore(color);
                layerArr[i].arr[j].color = BLACK;
                drawRectDMA(top, left, 25, 4, BLACK);
                cd = 1;
              }
            }
          }
        }
      }
    }
    if(b.col < 0) {                 //ball reach left border
      cd = 1;
      b.col = 0;
    } else if(b.col > 238) {        //ball reaches right border
      cd = -1;
      b.col = 235;
    }
    if (b.row + 2 >= p.top && b.col >= p.left && b.col + 2 <= p.right) {
      rd = -1;
      b.row = p.top - 2;
    } 
    b.row = b.row + rd;
    b.col = b.col + cd;
    b.right = b.col + 2;
    b.bot = b.row + 2;
    drawImageDMA(b.row, b.col, 5, 5, ball);
    delay(1);
    if (p.score == 135) {
      *state = WINCLEAR;
      return;
    }
    if (KEY_DOWN(BUTTON_SELECT, buttons)) {      //return to start screen
      fillScreenDMA(BLACK);
      *state = STARTBG;
      return;
    }
  }
}