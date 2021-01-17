#pragma once

#include "clvk_common.hpp"
#include "clvk_utils.hpp"

namespace clvk {

using IcdDispatch = cl_icd_dispatch;
extern IcdDispatch icdTable;

enum class ObjectMagic : uint32_t {
    PLATFORM_MAGIC = 4,
};

template<typename T, T magic>
class ClObject {
public:
    explicit ClObject()
        : m_icdTable(&icdTable),
          m_magic(magic) {}

    bool isValid() const { return m_magic == magic; }
private:
    IcdDispatch* m_icdTable;
    T m_magic;
};

template<typename Object>
class RefCounter {
public:
    explicit RefCounter()
        : m_refCount(1) {}

    virtual ~m_refCount() {}

    bool retain()
    {
        if (m_refCount == UINT32_MAX) {
            printError("[clvk] The reference count of this object is too big.");
            return false;
        }

        m_refCount++;
        return true;
    }

    bool release(Object* object)
    {
        if (m_refCount == 0) {
            printError("[clvk] The reference count of this object has already been 0, and can not be released.");
            return false;
        }

        m_refCount--;
        if (m_refCount == 0) {
            object->~Object();
        }
        return true;
    }

    uint32_t getRefCount() const
    {
        return m_refCount;
    }
private:
    std::atomic<uint32_t> m_refCount;
};

template<typename ObjectPtr>
inline ObjectPtr castObjectPointer(void* object)
{
    return static_cast<ObjectPtr>(object);
}

template<typename ObjectPtr>
bool isValidObject(void* object)
{
    auto obj = castObjectPointer<ObjectPtr>(object);
    return obj->isValid();
}

}
