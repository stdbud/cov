#include <string>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include "budCovTestPlatform.h"

int main(int argc, const char** argv)
{
    std::vector<std::thread> threads;
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        if (arg == "platform") {
            threads.push_back(std::thread(budPlatformTestEntry));
        } else {
            std::cerr << "got unknown test suite: " << arg << std::endl; 
        }
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return 0;
}
