/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   log.h
 * Author: ethan
 *
 * Created on February 1, 2017, 1:34 PM
 */

#ifndef LOG_H
#define LOG_H

#include "Exception.h"
#include "Lock.h"
#include <sys/types.h>
#include <unistd.h>
#include <map>


//this log class will generate some log files everyday
//each day we get a debug20170201.log , Info20170201.log, etc
//the regulation of filename is using the prefix of LogLevle and plus the date of that day
//the extension of all logs file is .log
//and the log library is thread safety and well interfaced.

//singleton pattern
class Log
{
public:
    enum LogLevel {
        LogDebug = 0,
        LogInfo,
        LogWarnning,
        LogFatal,
    };
private:
    static constexpr Log* _instance = nullptr;
private:
    static const std::string _debug;
    static const std::string _info ;
    static const std::string _warn;
    static const std::string _fatal;
    static const std::string _other;
private:
    std::string _fileDir = "";
    std::string _processId;
    Lock* _lock = nullptr;
    std::map<std::string,FILE*>  _mapFile;
    
public:
    Log(const std::string & nfileDir,
            Lock* nplock )throw(FileNotExistingException&,FileNotEditableException&) :
        _fileDir(nfileDir),
        _lock(nplock) {     
            _processId = "" + getpid();
            if(!access(_fileDir.c_str(), F_OK ))
                throw FileNotExistingException(_fileDir);
            if(!access(_fileDir.c_str(), W_OK ))
                throw FileNotEditableException(_fileDir);
        }
    ~Log(){
        for(auto & kv :_mapFile )
            fclose(kv.second);
    }
    
    static inline const std::string& LogLevelToString(const LogLevel & nLogLevel) 
    {
        switch(nLogLevel){
            case LogDebug : return _debug;
            case LogInfo : return _info;
            case LogWarnning : return _warn;
            case LogFatal : return _fatal;
            default : return _other;
        }
    }
   
    void write(const LogLevel& nLogLevel,
        const char *format,
        va_list args) noexcept;
   
    
};


#endif /* LOG_H */

