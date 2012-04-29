/*
 * BufferLayoutBuilder.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYCERIN_BUFFERLAYOUTBUILDER_HPP
#define GLYCERIN_BUFFERLAYOUTBUILDER_HPP
#include <set>
#include "glycerin/common.h"
#include "glycerin/buffer/BufferRegion.hpp"
#include "glycerin/buffer/BufferLayout.hpp"
namespace Glycerin {


/**
 * Utility for building a buffer layout.
 *
 * <i>%BufferLayoutBuilder</i> creates <i>%BufferLayout</i> instances.  The user
 * defines the desired properties for the regions, and then directs the builder
 * to create the layout.  The state of each property is maintained from region
 * to region unless changed by the user, making most layouts very easy to make.
 *
 * To get started with <i>%BufferLayoutBuilder</i>, first create one.
 * @code
 * BufferLayoutBuilder builder;
 * @endcode
 *
 * Then start defining the properties of the first region you'd like in the
 * buffer layout.  You can specify the number of components per vector with
 * <i>components</i>, the number of vectors per region with <i>count</i>,
 * whether the vector components should be normalized with <i>normalized</i>,
 * and the data type of the vector components with <i>type</i>.
 *
 * @code
 * builder.components(3);
 * builder.count(24);
 * builder.normalized(false);
 * builder.type(GL_FLOAT);
 * @endcode
 *
 * Since the builder starts with valid default values for the <i>component</i>,
 * <i>normalized</i>, and <i>type</i> properties, the user can leave them
 * unspecified if desired.  The <i>components</i> property starts with <i>4</i>,
 * <i>normalized</i> starts with <i>false</i>, and <i>type</i> starts with
 * <i>GL_FLOAT</i>.  Therefore the following code segment is equivalent to the
 * one above.
 *
 * @code
 * builder.components(3);
 * builder.count(24);
 * @endcode
 *
 * Then add the first region using <i>region</i>, giving it the name that you
 * want to refer to it by later.  The current state of the builder's properties
 * will be captured and used for the region when the buffer layout is built
 * later.
 *
 * @code
 * builder.region("MCVertex");
 * @endcode
 *
 * From there, more regions can be added by changing properties and calling
 * <i>region</i> again with different names.  If you don't change a property
 * when you add a new region, that property will have the same value as the
 * previous region.  For example, the two regions that are added below will
 * still include <i>24</i> vectors, be of type <i>GL_FLOAT</i>, and should not
 * be normalized.  However, the <i>Normal</i> region will have three components
 * per vector whereas the <i>TexCoord0</i> region will only have two.
 *
 * @code
 * builder.region("Normal");
 * builder.components(2);
 * builder.region("TexCoord0");
 * @endcode
 *
 * To make things even easier, most calls can be chained together.  For example,
 * the first three regions could have been added with the more compact form
 * below.  Notice that often the only property that needs to change is
 * <i>components</i>.
 *
 * @code
 * builder.count(24);
 * builder.components(3).region("MCVertex");
 * builder.components(4).region("Color");
 * builder.components(2).region("TexCoord0");
 * @endcode
 *
 * In addtion, if the number of vectors in each region is the same, the regions
 * can be interleaved.  An interleaved buffer layout will alternate vectors from
 * each region, often making it easier for the video card to iterate through.
 * However, it is generally harder to update an interleaved buffer, since all
 * the vectors for one region are no longer together.
 *
 * @code
 * builder.interleaved(true);
 * @endcode
 *
 * When all the regions have been added, call <i>build</i> to make the buffer
 * layout.
 *
 * @code
 * const BufferLayout layout = builder.build();
 * @endcode
 *
 * The offset and stride, as well as all the properties you specified can be
 * retrieved using the accessors of each region.  The code segment below sets up
 * vertex attribute pointers for a buffer by iterating through the regions in
 * the layout.
 *
 * @code
 * for (BufferLayout::const_iterator r = layout.begin(); r != layout.end(); ++r) {
 *     const char* name = r->name().c_str();
 *     const GLuint location = glGetAttribLocation(program, name);
 *     glEnableVertexAttribArray(location);
 *     glVertexAttribPointer(
 *             location,
 *             r->components(),
 *             r->type(),
 *             r->normalized(),
 *             r->stride(),
 *             r->offset());
 * }
 * @endcode
 */
class BufferLayoutBuilder {
public:
// Methods
    BufferLayoutBuilder();
    virtual ~BufferLayoutBuilder();
    BufferLayout build();
    BufferLayoutBuilder& components(GLuint components);
    BufferLayoutBuilder& count(GLuint count);
    BufferLayoutBuilder& interleaved(bool interleaved);
    BufferLayoutBuilder& normalized(bool normalized);
    BufferLayoutBuilder& region(const std::string& name);
    BufferLayoutBuilder& type(GLenum type);
private:
// Types
    class State;
    class InterleavedState;
    class NonInterleavedState;
    typedef std::vector<BufferRegion>::iterator iterator;
    typedef std::pair<iterator,iterator> iterator_pair;
    typedef std::vector<BufferRegion>::const_iterator const_iterator;
    typedef std::pair<const_iterator,const_iterator> const_iterator_pair;
// Attributes
    GLuint _components;
    GLuint _count;
    std::set<std::string> _names;
    bool _normalized;
    std::vector<BufferRegion> _regions;
    State* _state;
    GLenum _type;
// Methods
    BufferLayoutBuilder(const BufferLayoutBuilder&);
    BufferLayoutBuilder& operator=(const BufferLayoutBuilder&);
    static bool isValidType(GLenum type);
    iterator_pair regions();
    const_iterator_pair regions() const;
    static GLsizei sizeOf(GLenum type);
// Constants
    static const GLsizei DEFAULT_COMPONENTS = 4;
    static const GLuint DEFAULT_COUNT = 0;
    static const bool DEFAULT_NORMALIZED = false;
    static const GLsizei DEFAULT_OFFSET = 0;
    static const GLsizei DEFAULT_STRIDE = 0;
    static const GLenum DEFAULT_TYPE = GL_FLOAT;
    static State* INTERLEAVED;
    static State* NON_INTERLEAVED;
    static const size_t MIN_REGION_COMPONENTS = 1;
    static const size_t MAX_REGION_COMPONENTS = 4;
    static const size_t MIN_REGION_COUNT = 1;
    static const size_t MAX_REGION_COUNT = SIZE_MAX;
};


class BufferLayoutBuilder::State {
public:
    virtual void computeStrides(iterator_pair regions) = 0;
    virtual void computeOffsets(iterator_pair regions) = 0;
};


class BufferLayoutBuilder::InterleavedState : public BufferLayoutBuilder::State {
public:
    virtual void computeStrides(iterator_pair regions);
    virtual void computeOffsets(iterator_pair regions);
};


class BufferLayoutBuilder::NonInterleavedState : public BufferLayoutBuilder::State {
public:
    virtual void computeStrides(iterator_pair regions);
    virtual void computeOffsets(iterator_pair regions);
};

} /* namespace Glycerin */
#endif
