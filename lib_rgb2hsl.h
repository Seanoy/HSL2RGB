#ifndef LIB_RGB2HLS_H_
#define LIB_RGB2HLS_H_

#define HLS_MAX 240.0f
#define RGB_MAX 255.0f

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} rgbInfo;

typedef struct
{
    float hue;
    float luminance;
    float saturation;
} hlsInfo;

extern rgbInfo rgbColor;
extern hlsInfo hlsColor;

void HSL2RGB(rgbInfo *rgbTemp, hlsInfo hlsTemp);
void RGB2HSL(rgbInfo rgbTemp, hlsInfo *hlsTemp);
void rgb2hsl_test(void);

#endif
