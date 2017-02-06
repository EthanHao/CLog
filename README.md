# CLog
A very useful, and thread-safety log library based on linux. Using c++ 11 to implement.

# How to use
```c++
CLOG::Log::GetInstance()->Init("/home/ethan/log");
for (int i = 0; i < 10; i++)
     CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogDebug, "try to output debug %d", i);
for (int i = 0; i < 10; i++)
     CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogInfo, "try to output info %d", i);
for (int i = 0; i < 10; i++)
     CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogWarnning, "try to output warning %d", i);
for (int i = 0; i < 10; i++)
     CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogFatal, "try to output fatal %d", i)
```
