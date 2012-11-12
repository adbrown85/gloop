/**
 * VertexAttribPointer.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "gloop/VertexAttribPointer.hxx"
namespace Gloop {

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

} /* namespace Gloop */
