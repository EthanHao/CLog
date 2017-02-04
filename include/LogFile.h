/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LogFile.h
 * Author: ethan
 *
 * Created on February 3, 2017, 6:51 PM
 */

#ifndef LOGFILE_H
#define LOGFILE_H


#include "Exception.h"
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <tuple>
#include <mutex>
namespace CLOG {

    //this log class will generate some log files everyday
    //each day we get a debug20170201.log , Info20170201.log, etc
    //the regulation of filename is using the prefix of LogLevle and plus the date of that day
    //the extension of all logs file is .log
    //and the log library is thread safety and well interfaced.

    //singleton pattern

    class LogFile {
    public:

        enum LogLevel {
            LogDebug = 0,
            LogInfo = 1,
            LogWarnning = 2,
            LogFatal = 3,
        };
  

    private:
        static const std::string _debug;
        static const std::string _info;
        static const std::string _warn;
        static const std::string _fatal;
        static const std::string _other;
        
    private:
        std::string _fileDir = "";
        std::string _processId;
        LogLevel _logLevel = LogDebug;
        std::string _prefixFileName = "";
        std::string _currentFilePath = "";
        struct tm _currentTM;
        FILE *  _fileHandle = nullptr;
        std::mutex _mutex;

    public:

         //can not be constructed outside explicitly
        LogFile(const std::string& nsDir,const LogLevel& nLogLevel) 
                throw (FileNotExistingException&,
                FileNotEditableException&,
                std::invalid_argument&)
        {
            if (nsDir.empty())
                throw std::invalid_argument("Directory is null");
            
            _logLevel = nLogLevel;
            _processId = "" + getpid();
            _prefixFileName = LogLevelToString(_logLevel);
            if (!access(_fileDir.c_str(), F_OK))
                throw FileNotExistingException(_fileDir);
            
            if (!access(_fileDir.c_str(), W_OK))
                throw FileNotEditableException(_fileDir);
        }

        //can not be copy constructed
        LogFile(const LogFile&) = delete;
        //can not be copy assigned
        LogFile& operator=(const LogFile&) = delete;

        //No move constructor
        LogFile(LogFile&&) = delete;

        //No Move assignment
        LogFile& operator=(LogFile&&) = delete;
        
        virtual ~LogFile() {
            //Never throw a exception outside
            //Lock
            std::lock_guard<std::mutex> llock(_mutex);

            //Close the file handle
            if (_fileHandle)
                fclose(_fileHandle);

        }

       
        //Initialize this log with a existing directory path,
        //this must be called before you want to log something
        void Init(const std::string& nsDir)
        throw (FileNotExistingException&,
                FileNotEditableException&,
                std::invalid_argument&) {
            if (nsDir.empty())
                throw std::invalid_argument("Directory is null");
            _processId = "" + getpid();
            if (!access(_fileDir.c_str(), F_OK))
                throw FileNotExistingException(_fileDir);
            if (!access(_fileDir.c_str(), W_OK))
                throw FileNotEditableException(_fileDir);
        }

        //Convert the debug level to a prefix string of the log file name
        //this function will be called very frequently. so use "inline" keyword and return a const string reference
        static inline const std::string& LogLevelToString(const LogLevel & nLogLevel) {
            switch (nLogLevel) {
                case LogDebug: return _debug;
                case LogInfo: return _info;
                case LogWarnning: return _warn;
                case LogFatal: return _fatal;
                default: return _other;
            }
        }

    
        void write( const char *format,
                va_list args) throw(FileOpenFailedException&,FileWriteFailedException&,std::invalid_argument);


    };

}


#endif /* LOGFILE_H */

