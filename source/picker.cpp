#include "picker.h"

const int Picker::Pick(float cursor_x, float cursor_y, int width, int height) const
{
    glFlush();
    glFinish();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned char data[4];
    glReadPixels(cursor_x, (float)height-cursor_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    int pick_id = data[0] + data[1] * 256 + data[2] * 256 * 256;

    return pick_id;
}