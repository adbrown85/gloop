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
#include "config.h"
#include "gloop/Variable.hxx"
namespace Gloop {

/**
 * Constructs a variable.
 *
 * @param location Location in program
 * @param name Name of variable in shader
 * @param program ID of the program variable is from
 * @param size Number of components
 * @param type Data type of components, as in `GL_FLOAT`
 */
Variable::Variable(GLint location,
                   const std::string& name,
                   GLuint program,
                   GLint size,
                   GLenum type) {
   this->_location = location;
   this->_name = name;
   this->_program = program;
   this->_size = size;
   this->_type = type;
}

/**
 * Destructs a variable.
 */
Variable::~Variable() {
    // empty
}

/**
 * Retrieves the location of this variable in the program it is from.
 *
 * @return Location of this variable in the program it is from
 */
GLint Variable::location() const {
    return _location;
}

/**
 * Retrieves the name of this variable in the shader it is from.
 *
 * @return Name of this variable in the shader it is from
 */
std::string Variable::name() const {
    return _name;
}


/**
 * Retrieves the ID of the program this variable is from.
 *
 * @return ID of the program this variable is from
 */
GLuint Variable::program() const {
   return _program;
}

/**
 * Retrieves the number of components in this variable.
 *
 * @return Number of components in this variable
 */
GLint Variable::size() const {
   return _size;
}

/**
 * Retrieves the data type of this variable, as in `GL_FLOAT`.
 *
 * @return Data type of this variable, as in `GL_FLOAT`
 */
GLenum Variable::type() const {
   return _type;
}

} /* namespace Gloop */
