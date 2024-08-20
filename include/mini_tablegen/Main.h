#ifndef MINI_TABLEGEN_MAIN_H
#define MINI_TABLEGEN_MAIN_H

#include <functional>

namespace llvm {
class raw_ostream;
} // namespace llvm

namespace mini_tablegen {

using namespace llvm;

class RecordKeeper;

/// Perform the action using Records, and write output to OS.
/// Returns true on error, false otherwise.
using TableGenMainFn = bool(raw_ostream &OS, RecordKeeper &Records);

int TableGenMain(const char *argv0,
                 std::function<TableGenMainFn> MainFn = nullptr);

} // namespace mini_tablegen

#endif // MINI_TABLEGEN_MAIN_H