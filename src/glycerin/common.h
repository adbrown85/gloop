/*
 * common.h
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_COMMON_H
#define GLYCERIN_COMMON_H
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#ifdef __APPLE__
#define GL3_PROTOTYPES
#include <OpenGL/gl3.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#endif

/**
 * @defgroup geometry
 * @defgroup image
 * @defgroup math
 * @defgroup shader
 * @defgroup system
 * @defgroup texture
 * @defgroup transform
 */

#endif
