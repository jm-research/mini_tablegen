#include "mini_tablegen/Main.h"
#include "mini_tablegen/Record.h"
#include "mini_tablegen/TableGenBackend.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace llvm;
using namespace mini_tablegen;

namespace {

cl::OptionCategory PrintTestOption("Options for test");
cl::opt<int> Test("test", cl::desc("Print input"), cl::value_desc("int input"),
                  cl::cat(PrintTestOption));

void PrintTest(int input, raw_ostream &OS) { OS << input; }

TableGen::Emitter::Opt X[] = {
    {"dump-json", EmitJSON, "Dump all records as machine-readable JSON"},
};

} // namespace

int main(int argc, char **argv) {
  InitLLVM X(argc, argv);
  cl::ParseCommandLineOptions(argc, argv);

  std::string output;
  llvm::raw_string_ostream stream(output);
  PrintTest(Test, stream);
  std::cout << output << std::endl;

  return TableGenMain(argv[0]);
}