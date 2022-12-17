#pragma once

// #define USE_SOFT_BUTTONS
// #define USE_PALETTE_REPORT

uint8_t hid_report[] = {
    0x05, 0x14,       // Usage Page (Alphanumeric Display)
    0x09, 0x02,       // Usage (0x02)
    0xA1, 0x01,       // Collection (Application)
    0x09, 0x20,       //   Usage (Display Attributes Report)
    0xA1, 0x02,       //   Collection (Logical)
    0x85, 0x01,       //     Report ID (1)
    0x09, 0x80,       //     Usage (0x80) size X - width
    0x09, 0x81,       //     Usage (0x81) size Y - height
    // 0x09, 0x82,       //     Max blit size
    0x09, 0x83,       //     Usage (0x83) pallete - 0x14 8 bit - 555
    0x15, 0x00,       //     Logical Minimum (0)
    0x26, 0xFF, 0x00, //     Logical Maximum (255)
    0x75, 0x08,       //     Report Size (8)
    0x95, 0x03,       //     Report Count (3)
    0xB1, 0x03,       //     Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
#ifdef USE_SOFT_BUTTONS
    0x09, 0x90,       //     Usage (0x90)
    0xA1, 0x02,       //     Collection (Logical)
    0x09, 0x91,       //       Usage (0x91)
    0x09, 0x92,       //       Usage (0x92)
    0x75, 0x04,       //       Report Size (4)
    0x95, 0x02,       //       Report Count (2)
    0x25, 0x0F,       //       Logical Maximum (15)
    0xB1, 0x03,       //       Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0x93,       //       Usage (0x93)
    0x09, 0x94,       //       Usage (0x94)
    0x75, 0x08,       //       Report Size (8)
    0x26, 0xFF, 0x00, //       Logical Maximum (255)
    0xB1, 0x03,       //       Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,             //     End Collection

    0x09, 0x90,       //     Usage (0x90)
    0xA1, 0x02,       //     Collection (Logical)
    0x09, 0x91,       //       Usage (0x91)
    0x09, 0x92,       //       Usage (0x92)
    0x75, 0x04,       //       Report Size (4)
    0x25, 0x0F,       //       Logical Maximum (15)
    0xB1, 0x03,       //       Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0x93,       //       Usage (0x93)
    0x09, 0x94,       //       Usage (0x94)
    0x75, 0x08,       //       Report Size (8)
    0x26, 0xFF, 0x00, //       Logical Maximum (255)
    0xB1, 0x03,       //       Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,             //     End Collection

    0x09, 0x90,       //     Usage (0x90)
    0xA1, 0x02,       //     Collection (Logical)
    0x09, 0x91,       //       Usage (0x91)
    0x09, 0x92,       //       Usage (0x92)
    0x75, 0x04,       //       Report Size (4)
    0x25, 0x0F,       //       Logical Maximum (15)
    0xB1, 0x03,       //       Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0x93,       //       Usage (0x93)
    0x09, 0x94,       //       Usage (0x94)
    0x75, 0x08,       //       Report Size (8)
    0x26, 0xFF, 0x00, //       Logical Maximum (255)
    0xB1, 0x03,       //       Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,             //     End Collection

    0x09, 0x90,       //     Usage (0x90)
    0xA1, 0x02,       //     Collection (Logical)
    0x09, 0x91,       //       Usage (0x91)
    0x09, 0x92,       //       Usage (0x92)
    0x75, 0x04,       //       Report Size (4)
    0x25, 0x0F,       //       Logical Maximum (15)
    0xB1, 0x03,       //       Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0x93,       //       Usage (0x93)
    0x09, 0x94,       //       Usage (0x94)
    0x75, 0x08,       //       Report Size (8)
    0x26, 0xFF, 0x00, //       Logical Maximum (255)
    0xB1, 0x03,       //       Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,             //     End Collection
#endif
    0xC0,             //   End Collection
    0x09, 0x2D, //   Usage (Display Status)
    0xA1, 0x02, //   Collection (Logical)
    0x09, 0x2E, //     Usage (Stat Not Ready)
    0x09, 0x2F, //     Usage (Stat Ready)
    0x75, 0x08, //     Report Size (8)
    0x95, 0x01, //     Report Count (1)
    0x25, 0x01, //     Logical Maximum (1)
    0x81, 0x40, //     Input (Data,Array,Abs,No Wrap,Linear,Preferred State,Null State)
    0xC0,       //   End Collection
#ifdef USE_PALETTE_REPORT
    0x09, 0x85,       //   Usage (0x85)
    0xA1, 0x02,       //   Collection (Logical)
    0x09, 0x86,       //     Usage (0x86)
    0x09, 0x87,       //     Usage (0x87)
    0x75, 0x08,       //     Report Size (8)
    0x95, 0x02,       //     Report Count (2)
    0x91, 0x42,       //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State,Non-volatile)
    0x09, 0x88,       //     Usage (0x88)
    0x75, 0x08,       //     Report Size (8)
    0x96, 0x00, 0x01, //     Report Count (256)
    0x92, 0x02, 0x01, //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile,Buffered Bytes)
    0xC0,             //   End Collection
#endif
    0x09, 0x8A,       //   Usage (0x8A) - blit buffer report
    0xA1, 0x02,       //   Collection (Logical)
    0x85, 0x02,       //     Report ID (2)
    0x09, 0x8B,       //     Usage (0x8B) - X1
    0x09, 0x8C,       //     Usage (0x8C) - Y1
    0x09, 0x8D,       //     Usage (0x8D) - X2
    0x09, 0x8E,       //     Usage (0x8E) - Y2
    0x75, 0x08,       //     Report Size (8)
    0x95, 0x04,       //     Report Count (4)
    0x25, 0x7F,       //     Logical Maximum (127)
    0x91, 0x02,       //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0x8F,       //     Usage (0x8F)
    0x75, 0x08,       //     Report Size (8)
    0x96, 0x00, 0x04, //     Report Count (256)
    0x26, 0xFF, 0x00, //     Logical Maximum (255)
    0x92, 0x02, 0x01, //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile,Buffered Bytes)
    0xC0,             //   End Collection

#ifdef USE_SOFT_BUTTONS
    0x09, 0x95,       //   Usage (0x95) soft button report
    0xA1, 0x02,       //   Collection (Logical)
    0x05, 0x09,       //     Usage Page (Button)
    0x19, 0x01,       //     Usage Minimum (0x01)
    0x29, 0x04,       //     Usage Maximum (0x04)
    0x75, 0x01,       //     Report Size (1)
    0x95, 0x04,       //     Report Count (4)
    0x25, 0x01,       //     Logical Maximum (1)
    0x81, 0x02,       //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x04,       //     Report Size (4)
    0x95, 0x01,       //     Report Count (1)
    0x81, 0x03,       //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,             //   End Collection
#endif
    0xC0,             // End Collection (Application)

    // 235 bytes
};
