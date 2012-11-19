/*
 * Copyright (c) 2012, Andrew Brown
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef GLOOP_TEXTUREOBJECT_HXX
#define GLOOP_TEXTUREOBJECT_HXX
#include "gloop/common.h"
namespace Gloop {


/**
 * Handle for texture data that can be bound to a texture target.
 *
 * Texture objects are created using @ref TextureObject::generate().  Using
 * _generate_ a new OpenGL texture object is automatically created for you.
 *
 * ~~~
 *     TextureObject to = TextureObject::generate();
 * ~~~
 *
 * Or, if you have the raw OpenGL identifier already you can also use @ref
 * TextureObject::fromId(GLuint).
 *
 * ~~~
 *     TextureObject to = TextureObject::fromId(37);
 * ~~~
 *
 * You can change which underlying OpenGL texture object an instance represents
 * using the assignment operator.
 *
 * ~~~
 *     to = TextureObject::generate();
 * ~~~
 *
 * If you don't plan on changing which texture object the instance points to,
 * you can mark it `const`.  Because the instance is just a _handle_ to the
 * texture object, you can still modify the underlying OpenGL texture object all
 * you want.  All `const` does in this case is prevent you from accidentally
 * changing which OpenGL texture object it represents.
 *
 * ~~~
 *     const TextureObject to = TextureObject::generate();
 * ~~~
 *
 * To see if two instances represent the same OpenGL texture object, you can
 * just use `==`.  Similarly with `!=` and `<`.
 *
 * ~~~
 *    if (t1 == t2) {
 *        cout << "Texture objects are the same!" << endl;
 *    }
 * ~~~
 *
 * To get the raw OpenGL identifier of the texture object, use the @ref
 * TextureObject::id() method.  Since _TextureObject_ stores no state behind the
 * scenes, you can always pass the ID to any OpenGL function as normal without
 * worry.
 *
 * ~~~
 *     const GLuint id = to.id();
 * ~~~
 *
 * Lastly, to delete the underlying OpenGL texture object, use @ref
 * TextureObject::dispose().  The destructor for _TextureObject_ does not do
 * do so automatically.
 *
 * ~~~
 *     to.dispose();
 * ~~~
 */
class TextureObject {
// Friends
    friend std::ostream& operator<<(std::ostream& stream, const TextureObject& textureObject);
public:
// Methods
    TextureObject(const TextureObject& textureObject);
    virtual ~TextureObject();
    void dispose() const;
    static TextureObject fromId(GLuint id);
    static TextureObject generate();
    GLuint id() const;
    bool operator!=(const TextureObject& textureObject) const;
    bool operator<(const TextureObject& textureObject) const;
    TextureObject& operator=(const TextureObject& textureObject);
    bool operator==(const TextureObject& textureObject) const;
private:
// Attributes
    GLuint _id;
// Methods
    TextureObject(GLuint id);
};

} /* namespace Gloop */

#endif
