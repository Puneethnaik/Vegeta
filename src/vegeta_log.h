#ifndef VEGETA_LOG_H
#define VEGETA_LOG_H

#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <sys/stat.h>

//Syslog Dependency
#include <syslog.h>

#include "vegeta_core.h"

#define vegeta_stdout STDOUT_FILENO
#define vegeta_stderr STDERR_FILENO

//Log Levels
#define VEGETA_LOG_INFO 1
#define VEGETA_LOG_DEBUG 2
#define VEGETA_LOG_ERROR 3

typedef int vegeta_log_level;
// typedef std::string vegeta_log_message;
typedef int vegeta_function_status;

struct vegeta_file_log_info {
    /*
     * Holds information necessary to initialise the logging 
     * systems. Applies for file logging
    */
   std::string file_name;
   std::string location;
};

struct vegeta_log_message {
    vegeta_log_level level;
    std::string message;
};

class BaseLogHandler {
    public:
    virtual vegeta_function_status write_log(vegeta_log_message log_message) = 0;  
    virtual void close_log() = 0;
};

class FileLogHandler : BaseLogHandler {
    //This log handler connects to a file
    //and stores to a file
    //This is the file descriptor of the file that is opened after connect called
    int fd;
    std::string file_name;
    std:: string location;
    public:
    vegeta_function_status connect(std::string, std::string);
    vegeta_function_status write_log(vegeta_log_message);
    void close_log();
};

class SyslogHandler : BaseLogHandler {
    //This log handler connects to syslog protocol
    public:
    vegeta_function_status connect(std::string);
    vegeta_function_status write_log(vegeta_log_message);
    void close_log();
};

SyslogHandler* init_log_syslog();
FileLogHandler* init_log_file();

#endif