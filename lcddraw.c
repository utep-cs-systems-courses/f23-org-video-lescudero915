/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"

/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}


void initialMenu()
{
  clearScreen(COLOR_WHITE);
  fillRectangle(5, 5, 55, 55, COLOR_GREEN);
  fillRectangle(70, 5, 55, 55, COLOR_BLUE);
  fillRectangle(5, 75, 55, 55, COLOR_PINK);
  fillRectangle(70, 75, 55, 55, COLOR_YELLOW);
  drawString5x7(40, 140, "Welcome!", COLOR_BLACK, COLOR_WHITE);
  drawString5x7(15, 150, "Press any button!", COLOR_BLACK, COLOR_WHITE);

}

void blinkingMenu()
{
  clearScreen(COLOR_WHITE);
  fillRectangle(70, 5, 55, 55, COLOR_BLUE);
  drawString5x7(40, 140, "Blinking!", COLOR_BLACK, COLOR_WHITE);

}

void jingleMenu()
{
  clearScreen(COLOR_BLUE);
  fillRectangle(5, 75, 55, 55, COLOR_WHITE);
  drawString5x7(40, 140, "Jingle!", COLOR_WHITE, COLOR_BLUE);

}
void mixedMenu()
{
  clearScreen(COLOR_WHITE);
  fillRectangle(70, 75, 55, 55, COLOR_YELLOW);
  drawString5x7(40, 140, "Mixed!", COLOR_BLACK, COLOR_WHITE);

}

// Function to draw a filled circle
void drawFilledCircle(u_char centerX, u_char centerY, u_char radius, u_int colorBGR) 
{
  int x = radius;
  int y = 0;
  int radiusError = 1 - x;

  while (x >= y) {
    // Draw two horizontal lines for each symmetric point
    fillRectangle(centerX - x, centerY - y, 2 * x, 1, colorBGR);
    fillRectangle(centerX - x, centerY + y, 2 * x, 1, colorBGR);

    fillRectangle(centerX - y, centerY - x, 2 * y, 1, colorBGR);
    fillRectangle(centerX - y, centerY + x, 2 * y, 1, colorBGR);

    y++;

    if (radiusError < 0) {
      radiusError += 2 * y + 1;
    } else {
      x--;
      radiusError += 2 * (y - x + 1);
    }
  }
}

// Function to draw a snowfall effect with multiple smaller circles
void drawSnowfall(u_int numCircles, u_char circleRadius, u_int colorBGR) 
{
  for (u_int i = 0; i < numCircles; i++) {
    // Randomize the position of each circle within the screen boundaries
    u_char randX = rand() % screenWidth;
    u_char randY = rand() % screenHeight;

    // Draw a filled circle at the randomized position
    drawFilledCircle(randX, randY, circleRadius, colorBGR);
  }
}

// Example usage in your main loop or update function
void updateScreen()
{
  clearScreen(COLOR_BLUE);
  drawSnowfall(20, 3, COLOR_WHITE);  // Adjust the number, radius, and color as needed
}







/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

