#ifndef OPERATION_H_
#define OPERATION_H_
#include <iostream>
#include <vector>
#include "Token.h"

class Operation {
  protected:
    int min_params;
    int max_params;
    std::vector<Token> params;
  public:
    virtual void Init()=0;
    virtual Operation* Clone()=0;
    virtual void Execute()=0;
    virtual bool HasValidType()=0;
    virtual bool HasValidParams() {
      if (params.size() < min_params || params.size() > max_params) {
        std::cerr << "got " << params.size() << " expected " << min_params << "-" << max_params << ": ";
        return false;
      }
      if (!HasValidType()) {
        std::cerr << "invalid type: ";
        return false;
      }
      return true;
    }
    virtual void SetParams(std::vector<Token> &param_tok) {
      for (auto it = param_tok.begin(); it != param_tok.end(); ++it) {
        params.push_back(*it);
      }
    }
    int GetMinParams() { return min_params; }
    int GetMaxParams() { return max_params; }
};

class AddOperation : public Operation {
  public:
    AddOperation() { Init(); }
    virtual void Init() {
      min_params = 3;
      max_params = 13;
    }

    virtual Operation* Clone() {
      AddOperation *o = new AddOperation();
      o->Init();
      return o;
    }

    virtual bool HasValidType() {
      int i = 1;
      for (auto it = params.begin(); it != params.end(); ++it, ++i) {
        if (i == 1) {
          if (!it->IsVariable()) return false;
          if (!it->IsNumber()) return false;
        } else {
          if (!it->IsNumber()) return false;
        }
        ++i;
      }
      return true;
    }

    virtual void Execute() {
      // TODO
      std::cout << "this is an add operation" << std::endl;
      double sum = 0.0;
      Token *dest_tok = &params.front();
      for (auto it = params.begin(); it != params.end(); ++it) {
        if (it == params.begin()) continue;

        if (it->IsNumeric()) sum += it->GetAsNumeric();
        if (it->IsReal()) sum += it->GetAsReal();
      }
      Data *data;
      if (dest_tok->IsNumeric()) data = new Data((double)sum);
      if (dest_tok->IsReal()) data = new Data((long)sum);
      dest_tok->SetVariableData(*data);
      std::cout << dest_tok->GetAsNumeric() << std::endl;
    }
};

class SubOperation : public Operation {
  public:
    SubOperation() { Init(); }
    virtual void Init() {
    }

    virtual bool HasValidType() {
      int i = 1;
      for (auto it = params.begin(); it != params.end(); ++it, ++i) {
        if (i == 1) {
          if (!it->IsVariable()) return false;
          if (!it->IsNumber()) return false;
        } else {
          if (!it->IsNumber()) return false;
        }
        ++i;
      }
      return true;
    }

    virtual Operation* Clone() {
      SubOperation *o = new SubOperation();
      o->Init();
      return o;
    }
    virtual void Execute() {
      std::cout << "this is a sub operation" << std::endl;
    }
};

#endif
