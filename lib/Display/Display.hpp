#pragma once

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include <stdio.h>

#include <gfx_cpp14.hpp>
#include <ili9341.hpp>

#include "Cheva.h"

using namespace gfx;
using namespace arduino;

#define LCD_HOST VSPI
#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK 19
#define PIN_NUM_CS 22
#define LCD_WRITE_SPEED_PERCENT 400  // 40MHz
#define LCD_READ_SPEED_PERCENT 200   // 20MHz
#define PIN_NUM_DC 21
#define PIN_NUM_RST 18
#define PIN_NUM_BKL 5
#define LCD_ROTATION 1
#define LCD_BKL_HIGH true
#define LCD_SOMETHING false

constexpr static const size16 screen_size(320, 240);

struct DisplayState {
  uint16_t speed = 0;
  uint16_t rpm = 0;
  float batteryVoltage = 12;
};

struct Display {
  using bus_type = tft_spi_ex<LCD_HOST, PIN_NUM_CS, PIN_NUM_MOSI, PIN_NUM_MISO,
                              PIN_NUM_CLK, SPI_MODE0, LCD_SOMETHING>;
  using lcd_type =
      ili9341<PIN_NUM_DC, PIN_NUM_RST, PIN_NUM_BKL, bus_type, LCD_ROTATION,
              LCD_BKL_HIGH, LCD_WRITE_SPEED_PERCENT, LCD_READ_SPEED_PERCENT>;
  using lcd_color = color<rgb_pixel<16>>;
  static lcd_type lcd;

  using bmp_type = bitmap<decltype(lcd)::pixel_type>;
  using bmp_color = color<typename bmp_type::pixel_type>;
  using frame_buffer_type = large_bitmap<rgb_pixel<16>>;
  using frame_buffer_color = color<typename frame_buffer_type::pixel_type>;

  static open_font &font;
  static bool displayFg;
  static frame_buffer_type bg;
  static uint8_t bgBuf[frame_buffer_type::sizeof_buffer(screen_size)];
  static frame_buffer_type fg;
  static uint8_t fgBuf[frame_buffer_type::sizeof_buffer(screen_size)];

  bool init();
  void update(const DisplayState state);
};

#endif
