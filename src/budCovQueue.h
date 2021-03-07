#pragma once

#include "budCovCommon.hpp"
#include "budCovObject.hpp"
#include "budCovUtils.hpp"
#include "budCovContext.h"
#include "budCovDevice.h"

namespace cov {

class Queue : public ClObject<ObjectMagic, ObjectMagic::QUEUE_MAGIC> {
public:
    explicit Queue(Context& context, Device& device, bool isOutOfOrder, bool enableProfiling);
    ~Queue();
private:
    Context& m_context;
    Device& m_device;
    bool m_isOutOfOrder;
    bool m_enableProfiling;
    VkQueue m_vkQueue;
};

cl_command_queue createCommandQueue(cl_context context,
                                    cl_device_id device,
                                    cl_command_queue_properties properties,
                                    cl_int* errcodeRet);

cl_int retainCommandQueue(cl_command_queue commandQueue);

cl_int releaseCommandQueue(cl_command_queue commandQueue);

}
