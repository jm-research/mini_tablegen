#ifndef MINI_TABLEGEN_ERROR_H
#define MINI_TABLEGEN_ERROR_H

#include "mini_tablegen/Record.h"
#include "llvm/Support/SourceMgr.h"

namespace mini_tablegen {

using namespace llvm;

void PrintNote(const Twine &Msg);
void PrintNote(ArrayRef<SMLoc> NoteLoc, const Twine &Msg);

[[noreturn]] void PrintFatalNote(const Twine &Msg);
[[noreturn]] void PrintFatalNote(ArrayRef<SMLoc> ErrorLoc, const Twine &Msg);
[[noreturn]] void PrintFatalNote(const Record *Rec, const Twine &Msg);
[[noreturn]] void PrintFatalNote(const RecordVal *RecVal, const Twine &Msg);

void PrintWarning(const Twine &Msg);
void PrintWarning(ArrayRef<SMLoc> WarningLoc, const Twine &Msg);
void PrintWarning(const char *Loc, const Twine &Msg);

void PrintError(const Twine &Msg);
void PrintError(ArrayRef<SMLoc> ErrorLoc, const Twine &Msg);
void PrintError(const char *Loc, const Twine &Msg);
void PrintError(const Record *Rec, const Twine &Msg);
void PrintError(const RecordVal *RecVal, const Twine &Msg);

[[noreturn]] void PrintFatalError(const Twine &Msg);
[[noreturn]] void PrintFatalError(ArrayRef<SMLoc> ErrorLoc, const Twine &Msg);
[[noreturn]] void PrintFatalError(const Record *Rec, const Twine &Msg);
[[noreturn]] void PrintFatalError(const RecordVal *RecVal, const Twine &Msg);

void CheckAssert(SMLoc Loc, Init *Condition, Init *Message);
void dumpMessage(SMLoc Loc, Init *Message);

extern SourceMgr SrcMgr;
extern unsigned ErrorsPrinted;

} // namespace mini_tablegen

#endif // MINI_TABLEGEN_ERROR_H