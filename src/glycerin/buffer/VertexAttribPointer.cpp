/**
 * VertexAttribPointer.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "glycerin/buffer/VertexAttribPointer.hpp"
namespace Glycerin {

/**
 * Initializes all the parameters to their default values.
 */
VertexAttribPointer::VertexAttribPointer() {
   index = 0;
   size = 4;
   type = GL_FLOAT;
   normalized = GL_FALSE;
   offset = 0;
}

} /* namespace Glycerin */
