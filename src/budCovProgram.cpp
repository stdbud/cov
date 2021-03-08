#include "budCovProgram.h"

struct _cl_program {
    cov::Program m_program;
};

namespace cov {

Program::Program(Context& context, std::vector<std::string>& sources)
    : m_context(context),
      m_sources(std::move(sources))
{
    m_initSuccess = true; // fixme
    if (m_initSuccess) m_context.retain();
}

Program::~Program()
{
    if (m_initSuccess) m_context.release();
}

cl_program createProgramWithSource(cl_context context,
                                   cl_uint count,
                                   const char** strings,
                                   const size_t* lengths,
                                   cl_int* errcodeRet)
{
    auto c = reinterpret_cast<Context*>(context);

    std::vector<std::string> sources(count);
    for (size_t i = 0; i < sources.size(); i++) {
        if (lengths) {
            sources[i] = std::string(strings[i], lengths[i]);
        } else {
            sources[i] = std::string(strings[i]);
        }
    }
    auto program = new(std::nothrow) Countable<Program>(*c, sources);
    if (!program) {
        *errcodeRet = CL_OUT_OF_HOST_MEMORY;
        return nullptr;
    }

    auto p = reinterpret_cast<Program*>(program);
    if (!p->initSuccess()) {
        p->release();
        *errcodeRet = CL_OUT_OF_RESOURCES;
        return nullptr;
    }

    *errcodeRet = CL_SUCCESS;
    return reinterpret_cast<_cl_program*>(p);
}

}
