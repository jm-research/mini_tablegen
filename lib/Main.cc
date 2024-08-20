#include "mini_tablegen/Main.h"
#include "mini_tablegen/Error.h"
#include "mini_tablegen/Record.h"
#include "mini_tablegen/TGLexer.h"
#include "mini_tablegen/TGParser.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <string>
#include <system_error>
#include <utility>

namespace mini_tablegen {

using namespace llvm;

static cl::opt<std::string>
OutputFilename("o", cl::desc("Output filename"), cl::value_desc("filename"),
               cl::init("-"));

static cl::opt<std::string>
DependFilename("d",
               cl::desc("Dependency filename"),
               cl::value_desc("filename"),
               cl::init(""));

static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("<input file>"), cl::init("-"));

static cl::list<std::string>
IncludeDirs("I", cl::desc("Directory of include files"),
            cl::value_desc("directory"), cl::Prefix);

static cl::list<std::string>
MacroNames("D", cl::desc("Name of the macro to be defined"),
            cl::value_desc("macro name"), cl::Prefix);

static cl::opt<bool>
WriteIfChanged("write-if-changed", cl::desc("Only write output if it changed"));

static cl::opt<bool>
TimePhases("time-phases", cl::desc("Time phases of parser and backend"));

static cl::opt<bool> NoWarnOnUnusedTemplateArgs(
    "no-warn-on-unused-template-args",
    cl::desc("Disable unused template argument warnings."));

static int reportError(const char *ProgName, Twine Msg) {
  errs() << ProgName << ": " << Msg;
  errs().flush();
  return 1;
}

int TableGenMain(const char *argv0, std::function<TableGenMainFn> MainFn) {
  RecordKeeper Records;

  if (TimePhases)
    Records.startPhaseTiming();

  // Parse the input file.

  Records.startTimer("Parse, build records");
  ErrorOr<std::unique_ptr<MemoryBuffer>> FileOrErr =
      MemoryBuffer::getFileOrSTDIN(InputFilename, /*IsText=*/true);
  if (std::error_code EC = FileOrErr.getError())
    return reportError(argv0, "Could not open input file '" + InputFilename +
                                  "': " + EC.message() + "\n");

  Records.saveInputFilename(InputFilename);

  // Tell SrcMgr about this buffer, which is what TGParser will pick up.
  SrcMgr.AddNewSourceBuffer(std::move(*FileOrErr), SMLoc());

  // Record the location of the include directory so that the lexer can find
  // it later.
  SrcMgr.setIncludeDirs(IncludeDirs);

  TGParser Parser(SrcMgr, MacroNames, Records, NoWarnOnUnusedTemplateArgs);

  if (Parser.ParseFile())
    return 1;
  Records.stopTimer();

  return 0;
}

} // namespace mini_tablegen