#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

bool spirv_to_wgsl(const uint32_t* spirv, size_t wordCount, char** result);
