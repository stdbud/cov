#include "budCovQueue.h"

struct _cl_command_queue {
    cov::Queue m_queue;
};

namespace cov {

Queue::Queue(Context& context, Device& device, bool isOutOfOrder, bool enableProfiling)
    : m_context(context),
      m_device(device),
      m_isOutOfOrder(isOutOfOrder),
      m_enableProfiling(enableProfiling),
      m_vkQueue(context.m_vkQueue)
{
    m_initSuccess = context.m_initSuccess && device.m_initSuccess;
    if (m_initSuccess) m_context.retain();
}

Queue::~Queue()
{
    if (m_initSuccess) m_context.release();
}

cl_command_queue createCommandQueue(cl_context context,
                                    cl_device_id device,
                                    cl_command_queue_properties properties,
                                    cl_int* errcodeRet)
{
    auto c = reinterpret_cast<Context*>(context);
    auto d = reinterpret_cast<Device*>(device);
    if (!c->hasDevice(d)) {
        *errcodeRet = CL_INVALID_DEVICE;
        return nullptr;
    }

    bool isOutOfOrder = properties != CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;
    bool enableProfiling = properties == CL_QUEUE_PROFILING_ENABLE;
    auto queue = new(std::nothrow) Countable<Queue>(*c, *d, isOutOfOrder, enableProfiling);
    if (!queue) {
        *errcodeRet = CL_OUT_OF_HOST_MEMORY;
        return nullptr;
    }

    auto q = reinterpret_cast<Queue*>(queue);
    if (!q->initSuccess()) {
        q->release();
        *errcodeRet = CL_OUT_OF_RESOURCES;
        return nullptr;
    }

    *errcodeRet = CL_SUCCESS;
    return reinterpret_cast<_cl_command_queue*>(q);
}

cl_int retainCommandQueue(cl_command_queue commandQueue)
{
    auto q = reinterpret_cast<Queue*>(commandQueue);
    q->retain();
    return CL_SUCCESS;
}

cl_int releaseCommandQueue(cl_command_queue commandQueue)
{
    auto q = reinterpret_cast<Queue*>(commandQueue);
    q->release();
    return CL_SUCCESS;
}

}
