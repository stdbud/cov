#pragma once

#include "budCovCommon.hpp"
#include "budCovObject.hpp"
#include "budCovUtils.hpp"
#include "budCovContext.h"
#include "budCovDevice.h"

namespace cov {

class Program : public ClObject<ObjectMagic, ObjectMagic::PROGRAM_MAGIC> {
public:
    explicit Program(Context& context, std::vector<std::string>& sources);
    ~Program();
private:
    Context& m_context;
    std::vector<std::string> m_sources;
};

cl_program createProgramWithSource(cl_context context,
                                   cl_uint count,
                                   const char** strings,
                                   const size_t* lengths,
                                   cl_int* errcodeRet);

}
