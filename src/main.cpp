#include "lcd-simulator.cpp"

int main()
{
	lcd_init();
	lcd_clear();

	// Demo code
	int l_color_red = 0xF800;
	int l_color_green = 0x07E0;
	int l_color_blue = 0x001F;
	int l_color_white = 0xFFFF;

	float time = 0.;
	int centerX = LCD_WIDTH / 2, centerY = LCD_HEIGHT / 2;
	const float scale = 50.;
	while (1) {
		lcd_clear();

		time += 0.05;

		lcd_put_pixel(centerX + (int)(sin(time) * scale), centerY + (int)(cos(time) * scale), l_color_red);
		lcd_put_pixel(centerX + (int)(sin(time + 0.2) * scale), centerY + (int)(cos(time + 0.2) * scale), l_color_green);
		lcd_put_pixel(centerX + (int)(sin(time + 0.4) * scale), centerY + (int)(cos(time + 0.4) * scale), l_color_blue);
		lcd_put_pixel(centerX + (int)(sin(time + 0.6) * scale), centerY + (int)(cos(time + 0.6) * scale), l_color_white);

		lcd_show(25);
	}
}
