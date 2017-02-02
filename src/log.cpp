/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../include/log.h"

const std::string Log::_debug = "debug";
const std::string Log::_info = "info";
const std::string Log::_warn = "warn";
const std::string Log::_fatal = "fatal";
const std::string Log::_other = "other";


 void Log::write(const LogLevel& nLogLevel,
        const char *format,
        va_list args) noexcept {
        //get date
        time_t lnow;
	lnow = time(&lnow);
	struct tm lvtm; 
        localtime_r(&lnow, &lvtm);
        
        //check file existing
        const std::string & lPrefixString = LogLevelToString(nLogLevel);
        
        //construct the fileName
        
        //get the associated file handle of the filename
        
        //if not ,then create this file and close the yesterday file.
        
        //write the base information
        
        //write the parameter information
        
        //write the '\n'
        
        //done
        
}