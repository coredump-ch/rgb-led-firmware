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

static float time = 0.0f;
static float speed = 0.5f;

// Main loop
void effect_sinus_runner2(void) {

    // get speed, and filter it (IIR) to avoid noise [0..1023]
    int speedValue = analogRead(POT_1); // 0 ... 1023
    int angle      = analogRead(POT_2); // 0 ... 1023
    int amplitude  = analogRead(POT_3); // 0 ... 1023
    
    speed = speed*0.5 + speedValue*0.5/1023.0;
    const int angle_scaled = angle / 1023. * 360.;
    const float amplitude_scaled = amplitude / 1023.;

    // calculate sinus value according to time [-1.0..1.0]
    const float sinus_value_r = sin(PI*(time + 0)               /180.0f);
    const float sinus_value_g = sin(PI*(time + angle_scaled)    /180.0f);
    const float sinus_value_b = sin(PI*(time + 2 * angle_scaled)/180.0f);
    // scale sinus to be between 0 and 1 [0.0..1.0]
    const float sinus_scaled_r = (sinus_value_r +1.0f)/2.0f * amplitude_scaled;
    const float sinus_scaled_g = (sinus_value_g +1.0f)/2.0f * amplitude_scaled;
    const float sinus_scaled_b = (sinus_value_b +1.0f)/2.0f * amplitude_scaled;
    // by using an exponantial scale we make it more human eye friendly. Then we
    // scale it to x..255
    const int val_r = exp(-3*sinus_scaled_r)*255.0f +0.5f;
    const int val_g = exp(-3*sinus_scaled_g)*255.0f +0.5f;
    const int val_b = exp(-3*sinus_scaled_b)*255.0f +0.5f;

    // Set colors
    //analogWrite(LED_R, 0);
    //analogWrite(LED_G, 0);
    analogWrite(LED_R, val_r);
    analogWrite(LED_G, val_g);
    analogWrite(LED_B, val_b);

    // Sleep
    delay(1);

    time += speed;
    if(time >= 360.0f) {
        time -= 360.0f;
    }
}

