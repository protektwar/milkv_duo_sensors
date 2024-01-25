#ifndef _DISPLAY_ST77XX_H_
#define _DISPLAY_ST77XX_H_

#define ST7735_DISPLAY_WIDTH_128  128  // for 1.44 and mini
#define ST7735_DISPLAY_WIDTH_80   80   // for mini
#define ST7735_DISPLAY_HEIGHT_128 128  // for 1.44" display
#define ST7735_DISPLAY_HEIGHT_160 160  // for 1.8" and mini display

#define ST_CMD_DELAY 0x80 // special signifier for command lists

#define ST77XX_NOP 0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID 0x04
#define ST77XX_RDDST 0x09

#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_PTLON 0x12
#define ST77XX_NORON 0x13

#define ST77XX_INVOFF 0x20
#define ST77XX_INVON 0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_RAMRD 0x2E

#define ST77XX_PTLAR 0x30
#define ST77XX_TEOFF 0x34
#define ST77XX_TEON 0x35
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A

#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x00

#define ST77XX_RDID1 0xDA
#define ST77XX_RDID2 0xDB
#define ST77XX_RDID3 0xDC
#define ST77XX_RDID4 0xDD

typedef struct{
	uint16_t w;
	uint16_t h;
	int8_t _CS;
	int8_t _DC;
	int8_t _MOSI;
	int8_t _MISO;
	int8_t _SCLK;
	int8_t _RST;
	int8_t start_col, start_row;
	uint32_t freq;
	uint8_t *cmd_list;
	uint8_t *addr;
} display_ST77XX;

void display_ST77xx_ctor(display_ST77XX* const me, uint16_t w, uint16_t h, int8_t _CS, int8_t _DC, int8_t _MOSI,
                                                   int8_t _SCLK, int8_t _RST = -1, int8_t _MISO = -1);

void display_ST77XX_set_addr_window(display_ST77XX* const me, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void display_ST77XX_set_rotation(display_ST77XX* const me, uint8_t r);
void display_ST77XX_enable_display(display_ST77XX* const me, boolean enable);
void display_ST77XX_enable_tearing(display_ST77XX* const me, boolean enable);
void display_ST77XX_enable_sleep(display_ST77XX* const me, boolean enable);

//protected:
uint8_t _colstart = 0,   ///< Some displays need this changed to offset
        _rowstart = 0,       ///< Some displays need this changed to offset
        spiMode = SPI_MODE0; ///< Certain display needs MODE3 instead

void display_ST77XX_begin(display_ST77XX* const me. uint32_t freq = 0);
void display_ST77XX_common_init(display_ST77XX* const me, const uint8_t *cmdList);
void display_ST77XX_display_init(display_ST77XX* const me, const uint8_t *addr);
void display_ST77XX_set_col_row_start(display_ST77XX* const me, int8_t col, int8_t row);
//protected
#endif
