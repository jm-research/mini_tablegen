#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include <iostream>

namespace experimentals {

namespace tgtok {
enum TokKind {
  // Markers
  Eof,
  Error,

  // Tokens with no info.
  minus,     // -
  plus,      // +
  l_square,  // [
  r_square,  // ]
  l_brace,   // {
  r_brace,   // }
  l_paren,   // (
  r_paren,   // )
  less,      // <
  greater,   // >
  colon,     // :
  semi,      // ;
  comma,     // ,
  dot,       // .
  equal,     // =
  question,  // ?
  paste,     // #
  dotdotdot, // ...

  // Boolean literals.
  TrueVal,
  FalseVal,

  // Integer value.
  IntVal,

  // Binary constant.  Note that these are sized according to the number of
  // bits given.
  BinaryIntVal,

  // Preprocessing tokens for internal usage by the lexer.
  // They are never returned as a result of Lex().
  Ifdef,
  Ifndef,
  Else,
  Endif,
  Define,

  // Reserved keywords. ('ElseKW' is named to distinguish it from the
  // existing 'Else' that means the preprocessor #else.)
  Bit,
  Bits,
  Code,
  Dag,
  ElseKW,
  FalseKW,
  Field,
  In,
  Include,
  Int,
  List,
  String,
  Then,
  TrueKW,

  // Object start tokens.
  OBJECT_START_FIRST,
  Assert = OBJECT_START_FIRST,
  Class,
  Def,
  Defm,
  Defset,
  Deftype,
  Defvar,
  Dump,
  Foreach,
  If,
  Let,
  MultiClass,
  OBJECT_START_LAST = MultiClass,

  // Bang operators.
  BANG_OPERATOR_FIRST,
  XConcat = BANG_OPERATOR_FIRST,
  XADD,
  XSUB,
  XMUL,
  XDIV,
  XNOT,
  XLOG2,
  XAND,
  XOR,
  XXOR,
  XSRA,
  XSRL,
  XSHL,
  XListConcat,
  XListSplat,
  XStrConcat,
  XInterleave,
  XSubstr,
  XFind,
  XCast,
  XSubst,
  XForEach,
  XFilter,
  XFoldl,
  XHead,
  XTail,
  XSize,
  XEmpty,
  XIf,
  XCond,
  XEq,
  XIsA,
  XDag,
  XNe,
  XLe,
  XLt,
  XGe,
  XGt,
  XSetDagOp,
  XGetDagOp,
  XExists,
  XListRemove,
  XToLower,
  XToUpper,
  XRange,
  XGetDagArg,
  XGetDagName,
  XSetDagArg,
  XSetDagName,
  XRepr,
  BANG_OPERATOR_LAST = XRepr,

  // String valued tokens.
  STRING_VALUE_FIRST,
  Id = STRING_VALUE_FIRST,
  StrVal,
  VarName,
  CodeFragment,
  STRING_VALUE_LAST = CodeFragment,
};

/// isBangOperator - Return true if this is a bang operator.
static inline bool isBangOperator(tgtok::TokKind Kind) {
  return tgtok::BANG_OPERATOR_FIRST <= Kind && Kind <= BANG_OPERATOR_LAST;
}

/// isObjectStart - Return true if this is a valid first token for a statement.
static inline bool isObjectStart(tgtok::TokKind Kind) {
  return tgtok::OBJECT_START_FIRST <= Kind && Kind <= OBJECT_START_LAST;
}

/// isStringValue - Return true if this is a string value.
static inline bool isStringValue(tgtok::TokKind Kind) {
  return tgtok::STRING_VALUE_FIRST <= Kind && Kind <= STRING_VALUE_LAST;
}
} // namespace tgtok

} // namespace experimentals

using namespace experimentals;

static llvm::SourceMgr SrcMgr;

static llvm::StringRef SrcString = R"(
class test<code C> {
  code Code = C;
}

def foo : test<[{ hello world! }]>;
)";

static std::unique_ptr<llvm::MemoryBuffer> buffer =
    llvm::MemoryBuffer::getMemBufferCopy(SrcString, "<string>");

int main() {
  SrcMgr.AddNewSourceBuffer(std::move(buffer), llvm::SMLoc());

  for (unsigned i = 0, e = SrcMgr.getNumBuffers(); i != e; ++i) {
    const llvm::MemoryBuffer *buffer = SrcMgr.getMemoryBuffer(i + 1);
    llvm::StringRef bufferContents = buffer->getBuffer();

    std::cout << bufferContents.str() << std::endl;
  }
}