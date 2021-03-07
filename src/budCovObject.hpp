#pragma once

#include <memory>
#include <atomic>
#include "budCovCommon.hpp"
#include "budCovUtils.hpp"
#include "budCovIcd.h"

namespace cov {

enum class ObjectMagic : uint8_t {
    PLATFORM_MAGIC = 1,
    DEVICE_MAGIC = 2,
    CONTEXT_MAGIC = 4,
    QUEUE_MAGIC = 6,
};

// make sure all the countable class is allocated by operator new
// will be replaced by memory pool later
template<typename ObjectType>
class Countable {
public:
    template<typename... Types>
    explicit Countable(Types&... args)
        : m_object(args...),
          m_refCount(1) {}

    void retain() {m_refCount++;}
    void release()
    {
        m_refCount--;
        if (m_refCount == 0) delete this;
    }
private:
    ObjectType m_object;
    std::atomic<int> m_refCount;
};

template<typename T, T magic>
class ClObject {
    friend class Platform;
    friend class Device;
    friend class Context;
    friend class Queue;
public:
    ClObject() : m_magic(magic), m_initSuccess(true) { m_icdTable = getIcdTable(); }

    bool isValid() const { return m_magic == magic; }

    void retain() { reinterpret_cast<Countable<decltype(*this)>*>(this)->retain(); }
    void release() { reinterpret_cast<Countable<decltype(*this)>*>(this)->release(); }

    bool initSuccess() const { return m_initSuccess; }
private:
    IcdDispatch* m_icdTable;
    T m_magic;
    bool m_initSuccess;
};

template<typename ObjectType>
bool isValidObject(void* object)
{
    auto obj = reinterpret_cast<ObjectType*>(object);
    return obj->isValid();
}

}
