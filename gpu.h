#pragma once

class GPU{
private:
    //framebuffer here?
public:
    GPU();

    int getPixelAddress(int width, int height);

    void setPixel(int address, int value); //value will be 1 or 0

    void decodeAndDisplay();

    void clearFrameBuffer();
};