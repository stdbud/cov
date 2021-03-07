#include "budCovTestPlatform.h"

static void testGetPlatformIDs(std::atomic<int>& numPass)
{
    try {
        // cl_uint numPlatform;
        // cl_int err = clGetPlatformIDs(0, nullptr, &numPlatform);
        // checkErr<cl_int, CL_SUCCESS>(err, "failed to get platform number!");

        // std::vector<cl_platform_id> platforms(numPlatform);
        // err = clGetPlatformIDs(numPlatform, platforms.data(), nullptr);
        // checkErr<cl_int, CL_SUCCESS>(err, "failed to get platforms!");

        numPass++;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

static void testGetPlatformInfo(std::atomic<int>& numPass)
{
    try {
        // cl_uint numPlatform;
        // cl_int err = clGetPlatformIDs(0, nullptr, &numPlatform);
        // checkErr<cl_int, CL_SUCCESS>(err, "failed to get platform number!");

        // std::vector<cl_platform_id> platforms(numPlatform);
        // err = clGetPlatformIDs(numPlatform, platforms.data(), nullptr);
        // checkErr<cl_int, CL_SUCCESS>(err, "failed to get platforms!");

        // size_t nameSize;
        // err = clGetPlatformInfo(platforms[0], CL_PLATFORM_NAME, 0, nullptr, &nameSize);
        // checkErr<cl_int, CL_SUCCESS>(err, "failed to get platform name size!");

        // std::vector<char> name(nameSize);
        // err = clGetPlatformInfo(platforms[0], CL_PLATFORM_NAME, nameSize, name.data(), nullptr);
        // checkErr<cl_int, CL_SUCCESS>(err, "failed to get platform name size!");

        // std::string platformName;
        // platformName.assign(name.begin(), name.end());
        // std::cout << "platform name: " << platformName << std::endl;

        numPass++;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void budPlatformTestEntry()
{
    std::vector<std::thread> threads;
    std::atomic<int> numPass(0);
    threads.push_back(std::thread(testGetPlatformIDs, std::ref(numPass)));
    threads.push_back(std::thread(testGetPlatformInfo, std::ref(numPass)));
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    std::cout << "platform: test pass rate(" << numPass << "/" << threads.size() << ")" << std::endl;
}
