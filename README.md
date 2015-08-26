# RGB LED Board - Firmware

This is the firmware for the RGB LED project. You can also find it on
[Github][0] and [Hackster][1].

The firmware is based on the Arduino framework to make it easier for beginners.

## Getting started

The main entry point can be found at `src/src.ino`.

The file includes all the different available effects.

You can choose one of the effects by setting the `effects` variable:

    static const Effect effect = HSIControl;

If you want to see a very simple effect for reference, take a look at
`src/effect_rgb_control.cpp`.

In case you add new effects, pull requests are welcome!

## License

MIT License.

[0]: https://github.com/coredump-ch/rgb-led 
[1]: https://www.hackster.io/2460/arduino-controlled-rgb-led-strip
