#ifndef MINI_TABLEGEN_TABLEGENBACKEND_H
#define MINI_TABLEGEN_TABLEGENBACKEND_H

#include "mini_tablegen/Record.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ManagedStatic.h"

namespace llvm {
class raw_ostream;
}

namespace mini_tablegen {

using namespace llvm;

class RecordKeeper;

namespace TableGen::Emitter {
using FnT = void (*)(RecordKeeper &Records, raw_ostream &OS);

struct OptCreatorT {
  static void *call();
};

extern ManagedStatic<cl::opt<FnT>, OptCreatorT> Action;

struct Opt {
  Opt(StringRef Name, FnT CB, StringRef Desc, bool ByDefault = false) {
    if (ByDefault)
      Action->setInitialValue(CB);
    Action->getParser().addLiteralOption(Name, CB, Desc);
  }
};

template <class EmitterC> class OptClass : Opt {
  static void run(RecordKeeper &RK, raw_ostream &OS) { EmitterC(RK).run(OS); }

public:
  OptClass(StringRef Name, StringRef Desc) : Opt(Name, run, Desc) {}
};

} // namespace TableGen::Emitter

/// emitSourceFileHeader - Output an LLVM style file header to the specified
/// raw_ostream.
void emitSourceFileHeader(StringRef Desc, raw_ostream &OS,
                          const RecordKeeper &Record = RecordKeeper());

} // namespace mini_tablegen

#endif // MINI_TABLEGEN_TABLEGENBACKEND_H