/**
 * Effect: Controllable RGB values
 *
 * Copyright (c) 2014--2015 Coredump Rapperswil
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

// Get arduino headers
#include <Arduino.h>

// Get pin definitions
#include "pins.h"

int unten_ab(int i);

// Main loop
void effect_rgb_control(void) {
    
    // Get poti values and map them to 0..255
    int val_r = analogRead(POT_1)/4;
    int val_g = analogRead(POT_2)/4;
    int val_b = analogRead(POT_3)/4;

    val_r = unten_ab(val_r);
    val_g = unten_ab(val_g);
    val_b = unten_ab(val_b);

    // Set colors
    analogWrite(LED_R, 255-val_r);
    analogWrite(LED_G, 255-val_g);
    analogWrite(LED_B, 255-val_b);

    // Sleep
    delay(1);
}

// Schneide unten den Bereich ab
int unten_ab(int i) {
  if (i < 5) {
    return 0;
  }
  return i;
}

