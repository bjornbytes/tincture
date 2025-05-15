#include <tint/tint.h>
#include <string.h>

extern "C" {

bool spirv_to_wgsl(const uint32_t* bytes, uint32_t wordCount, char** result) {
  std::vector<uint32_t> input(bytes, bytes + wordCount);

  tint::spirv::reader::Options readerOptions = {};
  tint::Program program = tint::spirv::reader::Read(input, readerOptions);

  if (!program.IsValid()) {
    *result = strdup(program.Diagnostics().Str().c_str());
    return false;
  }

  tint::wgsl::writer::Options writerOptions = {};
  tint::Result<tint::wgsl::writer::Output> output = tint::wgsl::writer::Generate(program, writerOptions);

  *result = strdup(output->wgsl.c_str());
  return true;
}

}
