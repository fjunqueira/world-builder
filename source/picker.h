#ifndef WORLD_BUILDER_PICKER_H
#define WORLD_BUILDER_PICKER_H

#include <GL/glew.h>

class Picker
{
   public:
    const int Pick(float cursor_x, float cursor_y, int width, int height) const;
};

#endif  // WORLD_BUILDER_PICKER_H