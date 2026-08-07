void tft_send_command(uint8_t cmd){
	gpio_put(PIN_DC, 0);
	spi_write_blocking(SPI_ID, &cmd, 1);
}

void tft_send_data(uint8_t data){
	gpio_put(PIN_DC, 1);
	spi_write_blocking(SPI_ID, &data, 1);
}

void tft_init(void)
{
    gpio_put(PIN_CS, 0);

    // Sleep Out
    tft_send_command(0x11);
    sleep_ms(120);

    // Pixel Format = RGB565
    tft_send_command(0x3A);
    tft_send_data(0x55);

    // Memory Access Control
    tft_send_command(0x36);
    tft_send_data(0x48);

    // Display ON
    tft_send_command(0x29);
    sleep_ms(20);

    gpio_put(PIN_CS, 1);
}

void tft_reset(void)
{
    gpio_put(PIN_RST, 0);
    sleep_ms(10);

    gpio_put(PIN_RST, 1);
    sleep_ms(120);
}

void tft_set_address_window(
    uint16_t x0,
    uint16_t y0,
    uint16_t x1,
    uint16_t y1
)
{
	uint8_t x0_higher = x0>>8;
	uint8_t x0_lower  = x0 & (0x00FF);
	uint8_t x1_higher = x1>>8;
	uint8_t x1_lower  = x1 & (0x00FF);

	uint8_t y0_higher = y0>>8;
	uint8_t y0_lower  = y0 & (0x00FF);
	uint8_t y1_higher = y1>>8;
	uint8_t y1_lower  = y1 & (0x00FF);

	gpio_put(PIN_CS, 0);
	tft_send_command(0x2A);
	tft_send_data(x0_higher);
	tft_send_data(x0_lower);
	tft_send_data(x1_higher);
	tft_send_data(x1_lower);
	

	tft_send_command(0x2B);
	tft_send_data(y0_higher);
	tft_send_data(y0_lower);
	tft_send_data(y1_higher);
	tft_send_data(y1_lower);
	
	tft_send_command(0x2C);
}	

void tft_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
	uint8_t color_upper =color >> 8;
	uint8_t color_lower = color & (0x00FF);

	tft_set_address_window(x,y,x,y);
	tft_send_data(color_upper);
	tft_send_data(color_lower);
	gpio_put(PIN_CS, 1);
}

void tft_fill_rect(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint16_t color)
{
    uint8_t color_high = color >> 8;
    uint8_t color_low = color & 0xFF;

    tft_set_address_window(x,y,x + width - 1,y + height - 1);

    for(int i = 0; i < width * height; i++)
    {
        tft_send_data(color_high);
        tft_send_data(color_low);
    }

    gpio_put(PIN_CS, 1);
}
