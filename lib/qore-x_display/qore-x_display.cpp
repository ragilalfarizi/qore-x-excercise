#include "qore-x_display.h"

/* GLOBAL VARIABLES */
lv_display_t   *disp = NULL;
static uint32_t draw_buf[DRAW_BUF_SIZE / 4];

/* STATIC FUNCTION PROTOTYPE */
static void     displayInit();
static uint32_t my_tick(void);

void qoreXLCDInit() {
  // Initialization of the display
  displayInit();
  
  // touchInit();
}

static void displayInit() {
  lv_tick_set_cb(my_tick);

  disp =
      lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, TFT_ROTATION);
}

// static void touchInit(){}

/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void) { return millis(); }