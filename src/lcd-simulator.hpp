// Author:       Petr Olivka, petr.olivka@vsb.cz, 09/2019
// Modified by:  La_Blazer

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "font8x8.hpp"

#if defined (__unix__)
#include <unistd.h>
#endif

#define LCD_WIDTH		320
#define LCD_HEIGHT		240
#define LCD_SCALING		2
#define LCD_NAME		"Virtual LCD"

// Virtual LCD
cv::Mat g_canvas(cv::Size(LCD_WIDTH, LCD_HEIGHT), CV_8UC3);

// Put color pixel on LCD (canvas)
void lcd_put_pixel(int t_x, int t_y, int t_rgb_565)
{
	if (t_x >= 0 && t_x < LCD_WIDTH && t_y >= 0 && t_y < LCD_HEIGHT) {
		// Transform the color from a LCD form into the OpenCV form.
		cv::Vec3b l_rgb_888(
			(t_rgb_565 & 0x1F) << 3,
			((t_rgb_565 >> 5) & 0x3F) << 2,
			((t_rgb_565 >> 11) & 0x1F) << 3
		);
		g_canvas.at<cv::Vec3b>(t_y, t_x) = l_rgb_888; // put pixel
	}
	else {
		std::cout << "WARNING: Bad coordinates! (x: " << t_x << ", y: " << t_y << ")" << std::endl;
	}
}

// Clear LCD
void lcd_clear()
{
	cv::Vec3b l_black(0, 0, 0);
	g_canvas.setTo(l_black);
}

// LCD Initialization 
void lcd_init()
{
	cv::namedWindow(LCD_NAME, cv::WindowFlags::WINDOW_KEEPRATIO);
	cv::resizeWindow(LCD_NAME, { LCD_WIDTH * LCD_SCALING, LCD_HEIGHT * LCD_SCALING });
	lcd_clear();
	cv::waitKey(1);
}

// Displays virtual LCD's contents
// wait =	-1 for no waiting
//	0 to wait indefinitely for key press
//	n to wait n milliseconds for key press
void lcd_show(int wait = -1) {
	if (cv::getWindowProperty(LCD_NAME, cv::WindowPropertyFlags::WND_PROP_VISIBLE)) {
		cv::imshow(LCD_NAME, g_canvas);
	}
	else {
		cv::destroyWindow(LCD_NAME);
		lcd_init();
		cv::resizeWindow(LCD_NAME, LCD_WIDTH * LCD_SCALING, LCD_HEIGHT * LCD_SCALING);
	}
	
	if(wait >= 0)
		cv::waitKey(wait);
}