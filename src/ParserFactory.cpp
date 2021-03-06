#include "ParserFactory.h"
#include "AddMulParser.h"
#include "SubDivParser.h"
#include "VarParser.h"
#include "LabelParser.h"
#include "SleepParser.h"
#include "JmpParser.h"
#include "AssignParser.h"
#include "OutParser.h"
#include "JmpznzParser.h"
#include "JmpglteParser.h"
#include "GetStrCharParser.h"
#include "SetStrCharParser.h"

std::map<std::string, Parser*> ParserFactory::parsers;
bool ParserFactory::initialized;

ParserFactory::ParserFactory() { Init(); }

void ParserFactory::Init() {
  if (!initialized) {
    initialized = true;
    parsers["ADD"] = new AddMulParser();
    parsers["SUB"] = new SubDivParser();
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
    parsers["MUL"] = new AddMulParser();
    parsers["DIV"] = new SubDivParser();
    parsers["GET_STR_CHAR"] = new GetStrCharParser();
    parsers["SET_STR_CHAR"] = new SetStrCharParser();
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

