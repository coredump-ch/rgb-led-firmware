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

float time_r = 0.0f;
float time_g = 0.0f;
float time_b = 0.0f;

float speed_r = 0.5f;
float speed_g = 0.5f;
float speed_b = 0.5f;

constexpr float daempfung = 0.23;

// Main loop
void effect_sinus_runner(void) {

    // get speed, and filter it (IIR) to avoid noise [0..1023]
    speed_r = speed_r*0.5f + analogRead(POT_1)*0.5f/1023.0f;
    speed_g = speed_g*0.5f + analogRead(POT_2)*0.5f/1023.0f;
    speed_b = speed_b*0.5f + analogRead(POT_3)*0.5f/1023.0f;

    // calculate sinus value according to time [-1.0..1.0]
    const float sinus_value_r = sin(PI*time_r/180.0f);
    const float sinus_value_g = sin(PI*time_g/180.0f);
    const float sinus_value_b = sin(PI*time_b/180.0f);
    // scale sinus to be between 0 and 1 [0.0..1.0]
    const float sinus_scaled_r = (sinus_value_r +1.0f)/2.0f;
    const float sinus_scaled_g = (sinus_value_g +1.0f)/2.0f;
    const float sinus_scaled_b = (sinus_value_b +1.0f)/2.0f;
    // by using an exponantial scale we make it more human eye friendly. Then we
    // scale it to x..255
    const int val_r = exp(-3*sinus_scaled_r)*255.0f +0.5f;
    const int val_g = exp(-3*sinus_scaled_g)*255.0f +0.5f;
    const int val_b = exp(-3*sinus_scaled_b)*255.0f +0.5f;

    // Set colors
    //analogWrite(LED_R, 0);
    //analogWrite(LED_G, 0);
    analogWrite(LED_R, (speed_r < 0.001 ? 0 : val_r) * daempfung);
    analogWrite(LED_G, (speed_g < 0.001 ? 0 : val_g) * daempfung);
    analogWrite(LED_B, (speed_b < 0.001 ? 0 : val_b) * daempfung);

    // Sleep
    delay(1);

    time_r += speed_r;
    time_g += speed_g;
    time_b += speed_b;
    if(time_r >= 360.0f) {
        time_r -= 360.0f;
    }
    if(time_g >= 360.0f) {
        time_g -= 360.0f;
    }
    if(time_b >= 360.0f) {
        time_b -= 360.0f;
    }
}

