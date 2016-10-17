
/**
 * Effect: Controllable RGB values
 *
 * Copyright (c) 2014--2016 Coredump Rapperswil
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

//#include <array>

// Get arduino headers
#include <Arduino.h>

// Get pin definitions
#include "pins.h"



struct rgb { 
  uint8_t r, g, b;
};

double localRandom() {
  static int64_t seed = 0x5eeed;
  constexpr double MAX_VAL = 1 << 63;

  int64_t s = seed;
  seed = (s << 42) + s;
  if (s < 0) {
    return (42 - s) / MAX_VAL;
  } else {
    return s / MAX_VAL;
  }
}

void set_color(const rgb& c) {
  analogWrite(LED_R, min(c.r + 50, 255));
  analogWrite(LED_G, c.g / 3);
  analogWrite(LED_B, c.b);
}

constexpr uint8_t WHEEL_LENGTH = 4;
rgb wheel[] = {
    { 222, 128, 20 },
    { 20, 10, 10 },
    { 255, 255, 42 },
    { 142, 84, 23 },
};
rgb current = rgb { r: 222, g: 128, b: 20 };
rgb target  = rgb { r: 200, g: 100, b: 0 };
auto off = rgb { r: 60, g: 10, b: 10 };
auto red = rgb { r: 255, g: 0, b: 0 };
constexpr int8_t step_size = 3;
int8_t wheel_step = 0;
double P_NEXT_COLOR = 0.23;
double P_OFF = 0.001;

int8_t safe_step(int8_t c, int8_t t) {
  if (c < t) {
    return max(c - t, step_size);
  }
  if (c > t) {
    return min(c - t, -step_size);
  }
  return 0;
}

void effect_candle() {
  static uint8_t i = 0;
  ++i;
  double r = random(0, 20480) / 20480.0;
  //double r = localRandom();
  if (r < P_OFF) {
    set_color(off);
    delay(42);
  } /* else if (i == 0) {
    set_color(red);
    delay(42);
  }*/ else if (r < P_NEXT_COLOR) {
    wheel_step = ++wheel_step % WHEEL_LENGTH;
    target = wheel[wheel_step];
  } else {
    current.r += safe_step(current.r, target.r);
    current.g += safe_step(current.g, target.g);
    current.b += safe_step(current.b, target.b);
  }

  set_color(current);
  delay(42);
}

