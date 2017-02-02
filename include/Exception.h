/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.h
 * Author: ethan
 *
 * Created on February 1, 2017, 9:25 AM
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>

class FileException : public std::exception
{
public:
  FileException(const std::string& nfilepath):_filepath(nfilepath){}
  
  std::string filePath() const {return _filepath;}
  // overriden what() method from exception class
  const char* what() const throw() { 
      std::string ret = "Open File " + _filepath ;
      return ret.c_str();
  }
 
 private:
  const std::string _filepath; 
};

class FileNotExistingException : public FileException
{
  public:
   FileNotExistingException(const std::string& nfilepath):FileException(nfilepath){}
  // overriden what() method from exception class
  const char* what() const throw() { 
      std::string ret =  "File Not Existing " + filePath() ;
      return ret.c_str();
  }
};


class FileNotEditableException : public FileException
{
  public:
   FileNotEditableException(const std::string& nfilepath):FileException(nfilepath){}
  // overriden what() method from exception class
  const char* what() const throw() { 
      std::string ret =  "File Not Editable " + filePath() ;
      return ret.c_str();
  }
};

#endif /* EXCEPTION_H */

