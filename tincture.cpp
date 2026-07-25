#include <tint/tint.h>
#include "src/tint/lang/core/ir/module.h"
#include "src/tint/lang/wgsl/writer/ir_to_program/ir_to_program.h"
#include <string.h>

extern "C" {

bool spirv_to_wgsl(const uint32_t* bytes, uint32_t wordCount, char** result) {
  std::vector<uint32_t> spirv(bytes, bytes + wordCount);

  tint::Result<tint::core::ir::Module> resultIR = tint::spirv::reader::ReadIR(spirv);

  if (resultIR != tint::Success) {
    *result = strdup(resultIR.Failure().reason.c_str());
    return false;
  }

  tint::core::ir::Module ir = resultIR.Move();

  tint::wgsl::writer::Options writerOptions = {};
  tint::Result<tint::wgsl::writer::Output> resultWGSL = tint::wgsl::writer::WgslFromIR(ir, writerOptions);

  if (resultWGSL != tint::Success) {
    *result = strdup(resultWGSL.Failure().reason.c_str());
    return false;
  }

  tint::wgsl::writer::Output output = resultWGSL.Move();
  *result = strdup(output.wgsl.c_str());
  return true;
}

}
