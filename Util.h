#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <sstream>


/*
 * Function: remove_trailing_zeroes
 * Description: removes zeroes at end of a string, keeps last zero
 */
static inline std::string &remove_trailing_zeroes(std::string &str) {
  size_t index_cutoff = str.find_last_not_of('0');
  if (index_cutoff == 1) {
    ++index_cutoff;
  }
  ++index_cutoff;
  str = str.erase(index_cutoff, std::string::npos);
  return str;
}

/*
 * Function: cut_quotes
 * Description: Removes first and last char from string
 */
static inline std::string &cut_quotes(std::string &str) {
  str.pop_back();
  str.erase(str.begin());
  return str;
}

/*
 * Function: remove_vector_front
 * Description: removes first element of vector
 */
static inline void remove_vector_front(std::vector<auto> &vec) {
  if (vec.empty()) return;
  vec.erase(vec.begin());
}

/*
 * Function: ltrim
 * Description: trims whitespace from front of string
 */
static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

/*
 * Function: rtrim
 * Description: trims whitespace from end of string
 */
static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

/*
 * Function: trim
 * Description: trims whitespace from string
 */
static inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}

/*
 * Function: str_is_label
 * Description: if string is formatted like lAbEl1
 */
static inline bool str_is_label(const std::string &str) {
  if (str.size() < 1) return false;
  if (!isalpha(str[0])) return false;
  for (size_t i = 0; i < str.size(); ++i) {
    if (!isalnum(str[i])) return false;
  }
  return true;
}

/*
 * Function: isstringchar
 * Description: true if is a representable character like ' ' or '$'
 */
static inline bool isstringchar(char c) {
  if (c >= 32 && c <= 176) return true; /* <! All ascii chars that can be viewed > */
  return false;
}

/*
 * Function: str_is_char
 * Description: if string is formatted like 'c', ' ', or '$'
 */
static inline bool str_is_char(const std::string &str) {
  if (str.size() != 3) return false;
  if (str[0] != '\'') return false;
  if (str[2] != '\'') return false;
  if (!isstringchar(str[1])) return false;
  return true;
}


/*
 * Function: str_is_string
 * Description: if string is formatted like "sTrInG1"
 */
static inline bool str_is_string(const std::string &str) {
  if (str[0] != '\"') return false;
  if (str[str.size()-1] != '\"') return false;
  for (size_t i = 1; i < str.size() - 1; ++i) {
    if (!isstringchar(str[i])) return false;
  }
  return true;
}

/*
 * Function: str_is_real
 * Description: if string is formatted like 54
 */
static inline bool str_is_real(const std::string &str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (!isdigit(str[i])) return false;
  }
  return true;
}

/*
 * Function: str_is_numeric
 * Description: if string is formatted like 12.45
 */
static inline bool str_is_numeric(const std::string &str) {
  int period_count = 0;
  for (size_t i = 0 ; i < str.size(); ++i) {
    if (str[i] == '.') {
      ++period_count;
    } else if (!isdigit(str[i])) {
      return false;
    }
  }
  if (period_count != 1) return false;
  return true;
}

/*
 * Function: str_is_variable
 * Description: if string is formatted like $mYvAr1
 */
static inline bool str_is_variable(const std::string &str) {
  if (str.size() < 2) return false;
  if (str[0] != '$') return false;
  if (!isalpha(str[1])) return false;
  for (size_t i = 2; i < str.size(); ++i) {
    if (!isalnum(str[i] )) return false;
  }
  return true;
}

/*
 * Function: get_opname_line
 * Description: advances is to next line, stores first token into src_str, stores read line into src_line
 */
static inline std::istream &get_opname_line(std::istream &is, std::string &src_str, std::string &src_line) {
  std::getline(is, src_line);
  if (trim(src_line).empty()) {
    src_str = "";
    return is;
  }
  char *cstr = (char*)malloc(sizeof(char) * src_line.length() + 1);
  strcpy(cstr, src_line.c_str());
  char *token = std::strtok(cstr, " \n");
  src_str = std::string(token);
  free(cstr);
  return is;
}

static inline std::string &get_full_string_token(const std::string &str, size_t curr_i, size_t prev_i) {
}

/*
 * Function: valid_string_token
 * Description: checks for occurrence of a quote starting from first index to beginning second index
 */
static inline bool valid_string_token(const std::string &str, size_t curr_i, size_t prev_i) {
  int quote_count = 0;
  if (str[curr_i] != '\"') return false;
  for (int i = curr_i - 1; i >= prev_i; --i) {
    if (quote_count == 1) {
      if (i != prev_i && !iswspace(str[i])) return false;
    }

    if (str[i] == '\"') ++quote_count;

    if (quote_count > 1) return false;
  }
  if (quote_count != 1) return false;

  for (int i = curr_i + 1; i < str.size(); ++i) {
    if (quote_count == 1) {
      if (i != prev_i && !iswspace(str[i])) return false;
    }

    if (str[i] == '\"') ++quote_count;

    if (quote_count > 1) return false;
  }
  return true;
}

/*
 * Function: split_line
 * Description: splits string into tokens delimited by comma and \n, returns vector of the string tokens
 */
static inline std::vector<std::string> split_line(const std::string &str) {
  std::vector<std::string> strings;
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  char *copy = strdup(cstr);

  char delims[] = "\",\n";
  int curr_i = 0;
  char* tok_p = strtok(cstr, delims);
  while (tok_p != NULL) {
    std::string token = std::string(tok_p);
    trim(token);

    if (token.empty()) {
      tok_p = strtok(NULL, delims);
      continue;
    }

    int prev_i = curr_i;
    curr_i = tok_p-cstr+strlen(tok_p);

    if (valid_string_token(str, curr_i, prev_i)) {
      token = "\"" + token + "\"";
    }

    strings.push_back(token);
    tok_p = strtok(NULL, delims);
  }
  delete cstr;
  free(copy);
  return strings;
}

/*
 * Function: remove_opname
 * Description: given a vector of strings, remove the the operation name from first token
 */
static inline std::string remove_opname(std::vector<std::string> &str_toks) {
  std::string &first = str_toks.front();
  int index = first.find(" ");
  std::string opname = first.substr(0, index);
  first = first.substr(index + 1);
  trim(first);
  return opname;
}

/*
 * Function: split_line_getopname
 * Description: splits the string into string tokens, and cuts and stores the operation name
 */
static inline std::vector<std::string> split_line_getopname(const std::string &str, std::string &opname) {
  std::vector<std::string> strings = split_line(str);
  if (strings.empty()) return strings;
  opname = remove_opname(strings); 
  return strings;
}

#endif
