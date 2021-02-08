#include "lib_rgb2hsl.h"
#include <stdio.h>

float Hue2RGB(float v1, float v2, float vH);
float qMax(float x, float y);
float qMin(float x, float y);
int qRound(float d);

rgbInfo rgbColor;
hlsInfo hlsColor;

inline float qMax(float x, float y)
{
    if (x < y)
    {
        return y;
    }
    else
    {
        return x;
    }
}

inline float qMin(float x, float y)
{
    if (x > y)
    {
        return y;
    }
    else
    {
        return x;
    }
}

inline int qRound(float d)
{
    return d >= 0.0 ? (int)(d + 0.5) : (int)(d - (float)((int)(d - 1)) + 0.5) + (int)(d - 1);
}

inline float Hue2RGB(float v1, float v2, float vH)
{
    if (vH < 0)
    {
        vH += 1;
    }
    if (vH > 1)
    {
        vH -= 1;
    }
    if (6.0 * vH < 1)
    {
        return v1 + (v2 - v1) * 6.0 * vH;
    }
    if (2.0 * vH < 1)
    {
        return v2;
    }
    if (3.0 * vH < 2)
    {
        return v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;
    }
    return (v1);
}

void RGB2HSL(rgbInfo rgbTemp, hlsInfo *hlsTemp)
{
    float R, G, B, Max, Min, delta_R, delta_G, delta_B, delta_Max;
    R = rgbTemp.red / RGB_MAX;
    G = rgbTemp.green / RGB_MAX;
    B = rgbTemp.blue / RGB_MAX;

    Min = qMin(R, qMin(G, B));
    Max = qMax(R, qMax(G, B));
    delta_Max = Max - Min;

    hlsTemp->saturation = (Max + Min) / 2.0;

    if (delta_Max == 0)
    { /* gray */
        hlsTemp->hue = 0;
        hlsTemp->luminance = 0;
    }
    else
    {
        if (hlsTemp->saturation < 0.5)
        {
            hlsTemp->luminance = delta_Max / (Max + Min);
        }
        else
        {
            hlsTemp->luminance = delta_Max / (2 - Max - Min);
        }

        delta_R = (((Max - R) / 6.0) + (delta_Max / 2.0)) / delta_Max;
        delta_G = (((Max - G) / 6.0) + (delta_Max / 2.0)) / delta_Max;
        delta_B = (((Max - B) / 6.0) + (delta_Max / 2.0)) / delta_Max;

        if (R == Max)
        {
            hlsTemp->hue = delta_B - delta_G;
        }
        else if (G == Max)
        {
            hlsTemp->hue = (1.0 / 3.0) + delta_R - delta_B;
        }
        else if (B == Max)
        {
            hlsTemp->hue = (2.0 / 3.0) + delta_G - delta_R;
        }
        if (hlsTemp->hue < 0)
            hlsTemp->hue += 1;
        if (hlsTemp->hue > 1)
            hlsTemp->hue -= 1;
    }

    hlsTemp->hue *= HLS_MAX;//qRound(h * HLS_MAX);
    hlsTemp->luminance *= HLS_MAX;//qRound(s * HLS_MAX);
    hlsTemp->saturation *= HLS_MAX;//qRound(l * HLS_MAX);
    //printf("H:%f S:%f L:%f\r\n", hlsTemp->hue, hlsTemp->luminance, hlsTemp->saturation);
}

void HSL2RGB(rgbInfo *rgbTemp, hlsInfo hlsTemp)
{
    float R, G, B;
    float var_1, var_2;
    float H, S, L;

    H = hlsTemp.hue / HLS_MAX;
    S = hlsTemp.saturation / HLS_MAX;
    L = hlsTemp.luminance / HLS_MAX;

    if (S == 0)
    {
        R = L * 255.0;
        G = L * 255.0;
        B = L * 255.0;
    }
    else
    {
        if (L < 0.5)
        {
            var_2 = L * (1 + S);
        }
        else
        {
            var_2 = (L + S) - (S * L);
        }

        var_1 = 2.0 * L - var_2;

        R = 255.0 * Hue2RGB(var_1, var_2, H + (1.0 / 3.0));
        G = 255.0 * Hue2RGB(var_1, var_2, H);
        B = 255.0 * Hue2RGB(var_1, var_2, H - (1.0 / 3.0));
    }
    rgbColor.red = qRound(R);
    rgbColor.green = qRound(G);
    rgbColor.blue = qRound(B);
    //printf("R:%d G:%d B:%d\r\n", rgbColor.red, rgbColor.green, rgbColor.blue);
}

void rgb2hsl_test(void)
{
#if 0
    hlsColor.hue = 77;
    hlsColor.saturation = 240;
    hlsColor.luminance = 125;
    HSL2RGB(&rgbColor, hlsColor);
    rgbColor.red = 29;
    rgbColor.green = 255;
    rgbColor.blue = 11;
    RGB2HSL(rgbColor, &hlsColor);
#endif
    unsigned char rgbTable[3] = {0};
    hlsColor.hue = 0;   /* E of ESL */
    hlsColor.saturation = 240; /* S of ESL */
    hlsColor.luminance = 120;  /* L of ESL */

    for(; hlsColor.hue < 239; hlsColor.hue += 5){
        HSL2RGB(&rgbColor, hlsColor);
        rgbTable[0] = rgbColor.red;
        rgbTable[1] = rgbColor.green;
        rgbTable[2] = rgbColor.blue;
        printf("R:%d G:%d B:%d\r\n", rgbTable[0], rgbTable[1], rgbTable[2]);
    }
}

int main(void)
{/*
    hlsColor.hue = 77;
    hlsColor.luminance = 240;
    hlsColor.saturation = 125;
    HSL2RGB(&rgbColor, hlsColor);
    rgbColor.red = 29;
    rgbColor.green = 255;
    rgbColor.blue = 11;
    RGB2HSL(rgbColor, &hlsColor);
    */
    rgb2hsl_test();
    return 0;
}
