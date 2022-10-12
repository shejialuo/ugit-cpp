/**
 * @file err.hpp
 * @author shejialuo
 * @brief exit status code wrap
 *
 */

#ifndef _UGIT_CPP_DATA_ERR_HPP_
#define _UGIT_CPP_DATA_ERR_HPP_

namespace ugit {
enum class Error {
  CraeteFileError = 1,
  FileNotExist,
  OpenFileError,
  TypeNotEqual,
};
};  // namespace ugit

#endif  // _UGIT_CPP_DATA_ERR_HPP_
