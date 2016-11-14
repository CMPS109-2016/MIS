#ifndef IDATAHANDLER_H_
#define IDATAHANDLER_H_

class IDataHandler {
  virtual bool IsNumeric() const = 0;
  virtual bool IsReal() const = 0;
  virtual bool IsChar() const = 0;
  virtual bool IsString() const = 0;
  virtual bool IsNumber() const = 0;
  virtual bool IsCharSequence() const = 0;

  virtual long GetAsReal() const = 0;
  virtual double GetAsNumeric() const = 0;
  virtual char GetAsChar() const = 0;
  virtual char *GetAsString() const = 0;

};

#endif
