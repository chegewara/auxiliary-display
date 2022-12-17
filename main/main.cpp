#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#include "esp_err.h"
#include "esp_log.h"

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>

#include "usb_hid.hpp"
#include "hid_display.h"

#define R1_PIN 3
#define G1_PIN 4
#define B1_PIN 5
#define R2_PIN 6
#define G2_PIN 7
#define B2_PIN 8
#define A_PIN 9
#define B_PIN 10
#define C_PIN 11
#define D_PIN 12
#define E_PIN -1 // required for 1/32 scan panels, like 64x64. Any available pin would do, i.e. IO32
#define CLK_PIN 15
#define LAT_PIN 16
#define OE_PIN 17

VirtualMatrixPanel *virtualDisp = nullptr;
#define NUM_ROWS 2                     // Number of rows of chained INDIVIDUAL PANELS
#define NUM_COLS 2                     // Number of INDIVIDUAL PANELS per ROW
#define PANEL_CHAIN NUM_ROWS *NUM_COLS // total number of panels chained one to another

// Change this to your needs, for details on VirtualPanel pls read the PDF!
#define SERPENT true
#define TOPDOWN false
MatrixPanel_I2S_DMA *dma_display = nullptr;

uint16_t myBLUE = dma_display->color565(0, 0, 255);

using namespace std;
using namespace esptinyusb;

static HIDdevice hid;


#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32 // Panel height of 64 will required PIN_E to be defined.
#define PANELS_ROWS 2
#define PANELS_COLS 2
#define PANELS_NUMBER PANELS_ROWS * PANELS_COLS // Number of chained panels, if just a single panel, obviously set to 1

extern "C" void app_main()
{
    HUB75_I2S_CFG mxconfig;
    mxconfig.mx_width = PANEL_WIDTH;       // we have 64 pix heigh panels
    mxconfig.mx_height = PANEL_HEIGHT;     // we have 64 pix heigh panels
    mxconfig.chain_length = PANELS_NUMBER; // we have 2 panels chained

    HUB75_I2S_CFG::i2s_pins _pins = {R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
    mxconfig.gpio = _pins;
    mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_20M;

    // OK, now we can create our matrix object
    dma_display = new MatrixPanel_I2S_DMA(mxconfig);

    if (dma_display->begin())
        printf("begin done\n");

    virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_WIDTH, PANEL_HEIGHT, SERPENT, TOPDOWN);
    virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));

    vTaskDelay(1000);
    hid.addHidReport(hid_report, sizeof(hid_report), 1, 64);

    hid.begin(3, NULL);
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    printf("GET => Instance: %d, reportID: %d, report_type: %d, bufsize; %d\n", instance, report_id, report_type, reqlen);
    if (report_id == 1 && report_type == HID_REPORT_TYPE_FEATURE)
    {
        buffer[0] = PANEL_WIDTH * PANELS_COLS;
        buffer[1] = PANEL_HEIGHT * PANELS_ROWS;
        buffer[2] = 0x20;
#ifdef USE_SOFT_BUTTONS
        buffer[3] = 1 << 4 | 1;
        buffer[4] = 4;
        buffer[5] = 28;

        buffer[6] = 1 << 4 | 2;
        buffer[7] = 36;
        buffer[8] = 60;

        buffer[9] = 1 << 4 | 3;
        buffer[10] = 66;
        buffer[11] = 82;

        buffer[12] = 1 << 4 | 4;
        buffer[13] = 90;
        buffer[14] = 114;
#endif
    }
    return reqlen;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    // printf("SET => Instance: %d, reportID: %d, report_type: %d, bufsize; %d\n", instance, report_id, report_type, bufsize);
    static int offset = 0;
    static int _offset = 0;
    static uint16_t colors[128 * 64 * 4] = {};

    if (report_id == 0 && report_type == 0)
    {
        static uint8_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        static auto raw_data = false;
        if (bufsize == 5 && buffer[0] == 2 && !raw_data)
        {
            x1 = buffer[1];
            y1 = buffer[2];
            x2 = buffer[3];
            y2 = buffer[4];
            raw_data = true;
            // printf("X: %d, X2: %d, y: %d, Y2: %d\n", x1, x2, y1, y2);
            // printf("start\n");
        }
        else
        {
            // ESP_LOG_BUFFER_HEX("", buffer, bufsize);
            if (bufsize == 2)
            {
                int n = 0;
                dma_display->startWrite();
                for (size_t y = y1; y < y2; y++)
                {
                    for (size_t x = x1; x < x2; x++)
                    {
                        virtualDisp->drawPixelRGB888(x, y, colors[n], colors[n + 1], colors[n + 2]);
                        n = n + 4;
                        // printf("X: %d, Y: %d => color: %d\n", x, y, *(int*)&colors[n]);
                    }
                }
                dma_display->endWrite();
                // printf("end: %d\n", offset);

                offset = 0;
                _offset = 0;
                raw_data = false;
            }
            else
            {
                auto z = 0;
                if (_offset % 1024 == 0)
                {
                    z = 1;
                }
                for (size_t i = z; i < bufsize; i++)
                {
                    uint16_t color = *(uint16_t *)&buffer[i];
                    colors[offset] = color;
                    offset++;
                }
                _offset += bufsize;
            }
        }
    }
}
