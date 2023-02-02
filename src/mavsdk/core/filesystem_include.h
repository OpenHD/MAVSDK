#pragma once

// Fucking hell, we need to get rid of fs for android ndk 22.x
#ifdef USE_FILESYSTEM_ANYWAYS

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "Missing the <filesystem> header."
#endif

#endif //USE_FILESYSTEM_ANYWAYS
