## HID auxiliary display

This is attempt to implement USB HID auxiliary display standard. First working control application is web page using web USB, but this is USB standard, so it can be controlled with with applications written in C, C++, C#, python etc.
This example has been build and tested with esp-idf 5.0.

It is also using this library to control HUB75 matrix panels; 4 panels in this example:

https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-DMA

Here is very simple website to show how it works:
https://hub75.esp32.eu.org/display/
