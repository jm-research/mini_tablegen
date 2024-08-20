#ifndef MINI_TABLEGEN_PARSER_H
#define MINI_TABLEGEN_PARSER_H

namespace llvm {
class SourceMgr;
}

namespace mini_tablegen {

using namespace llvm;

class RecordKeeper;

/// Parse the TableGen file defined within the main buffer of the given
/// SourceMgr. On success, populates the provided RecordKeeper with the parsed
/// records and returns false. On failure, returns true.
///
/// NOTE: TableGen currently relies on global state within a given parser
///       invocation, so this function is not thread-safe.
bool TableGenParseFile(SourceMgr &InputSrcMgr, RecordKeeper &Records);

} // namespace mini_tablegen

#endif // MINI_TABLEGEN_PARSER_H