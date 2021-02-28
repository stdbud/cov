#pragma once

#include <memory>
#include "budCovCommon.hpp"
#include "budCovUtils.hpp"
#include "budCovIcd.h"

namespace cov {

enum class ObjectMagic : uint32_t {
    PLATFORM_MAGIC = 4,
};

template<typename T, T magic>
class ClObject {
public:
    explicit ClObject() : m_magic(magic) {}

    bool isValid() const { return m_magic == magic; }
private:
    T m_magic;
};

template<typename ObjectType>
inline std::shared_ptr<ObjectType> castObjectPointer(void* object)
{
    struct _cl_object {
        IcdDispatch* m_icdTable;
        std::shared_ptr<ObjectType> m_object;
    };
    return static_cast<_cl_object*>(object)->m_object;
}

template<typename ObjectType>
bool isValidObject(void* object)
{
    auto obj = castObjectPointer<ObjectType>(object);
    return obj->isValid();
}

}
