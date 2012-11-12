/*
 * BufferLayout.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_BUFFERLAYOUT_HXX
#define GLOOP_BUFFERLAYOUT_HXX
#include "gloop/common.h"
#include "gloop/BufferRegion.hxx"
namespace Gloop {


/**
 * Layout of a buffer.
 *
 * @ingroup extensions
 */
class BufferLayout {
public:
// Types
    typedef std::vector<BufferRegion>::const_iterator const_iterator; ///< Iterator over regions in layout
// Methods
    BufferLayout(const BufferLayout& layout);
    virtual ~BufferLayout();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator find(const std::string& name) const;
    bool interleaved() const;
    BufferLayout& operator=(const BufferLayout& layout);
private:
// Types
    typedef std::pair<const_iterator,const_iterator> const_iterator_pair;
    typedef std::vector<BufferRegion>::iterator iterator;
    typedef std::pair<iterator,iterator> iterator_pair;
// Attributes
    std::map<std::string,int> _indices;
    bool _interleaved;
    std::vector<BufferRegion> _regions;
// Methods
    BufferLayout();
    BufferLayout(const_iterator_pair regions, bool interleaved);
// Friends
    friend class BufferLayoutBuilder;
};

} /* namespace Gloop */
#endif
