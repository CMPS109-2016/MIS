#include "ParserFactory.h"

std::map<std::string, Parser*> ParserFactory::parsers;
bool ParserFactory::initialized;

ParserFactory::ParserFactory() { Init(); }

void ParserFactory::Init() {
  if (!initialized) {
    initialized = true;
    parsers["ADD"] = new AddParser();
    parsers["SUB"] = new SubParser();
    parsers["VAR"] = new VarParser();
    parsers["LABEL"] = new LabelParser();
    parsers["SLEEP"] = new SleepParser();
    parsers["JMP"] = new JmpParser();
    parsers["ASSIGN"] = new AssignParser();
    parsers["OUT"] = new OutParser();
    parsers["JMPZ"] = new JmpznzParser();
    parsers["JMPNZ"] = new JmpznzParser();
    parsers["JMPGT"] = new JmpglteParser();
    parsers["JMPGTE"] = new JmpglteParser();
    parsers["JMPLT"] = new JmpglteParser();
    parsers["JMPLTE"] = new JmpglteParser();
    parsers["MUL"] = new AddParser();
    parsers["DIV"] = new SubParser();
  }
}

bool ParserFactory::HasParser(const std::string &str) const {
  if (parsers.find(str) == parsers.end()) return false;
  return true;
}

Parser* ParserFactory::GetParser(const std::string &str) const {
  if (HasParser(str)) {
    return parsers[str]->Clone();
  }
  return nullptr;
}

ParserFactory::~ParserFactory() {
  if (initialized) {
    initialized = false;
    for (auto it = parsers.begin(); it != parsers.end(); ++it) {
      delete it->second;
    }
  }
};

