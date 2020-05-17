#include "vegeta_log.h"

#include "os/unix/unix_misc.h"

// FileLogHandler implementation
vegeta_function_status FileLogHandler::connect(std::string file_name, std::string location) {
    /*
        * connect is a function that connects a file descriptor
        * to a log file, with the given file name and in the given location
        * 
        * Attributes
        * file_name: string
        *      The name of the file that will be used to log all the information
        * location: string
        *      The location where the file should be created.
        *  
    */
    //O_APPEND is a atomic operation so is concurrent safe
    std::string file_absolute_path;

    file_absolute_path = vegeta_unix::join(location, file_name);
    // file_absolute_path = file_name;
    std::string tmp_log = "Attempting to create or open" + file_absolute_path;
    write(STDERR_FILENO, tmp_log.c_str(), tmp_log.length());
    int log_file_mode = S_IWRITE;
    this->fd = open(file_absolute_path.c_str(), O_WRONLY|O_APPEND|O_CREAT, log_file_mode);
    if(this->fd < 0) {
        //create the file
        return VEGETA_ERROR;
    }
    this->file_name = file_name;
    this->location = location;
    return VEGETA_OK;
}

void FileLogHandler::close_log() {
    close(this->fd);
}

vegeta_function_status FileLogHandler:: write_log(vegeta_log_message log_message) {
    if(write(this->fd, log_message.message.c_str(), log_message.message.length()) != log_message.message.length()) {
        std::string tmp_log = "Write Error";
        write(STDERR_FILENO, tmp_log.c_str(), tmp_log.length());
        return VEGETA_ERROR;
    }
    std::string tmp_log = "Write Success";
    write(STDERR_FILENO, tmp_log.c_str(), tmp_log.length());
    return VEGETA_OK;
}

FileLogHandler* init_log_file() {
    /*
     * Initialise the log functionality of the server.
     * For now only file log handler is supported.
    */
    FileLogHandler *fileLogHandler = new FileLogHandler();
    vegeta_file_log_info vegeta_file_log_info;

    vegeta_file_log_info.file_name = "vegeta_core.log";
    // vegeta_file_log_info.location = "/usr/local/vegeta";
    // /home/puneeth/Desktop/Projects/http-server/bin
    vegeta_file_log_info.location = "/home/puneeth/Desktop/Projects/http-server/bin/";
    fileLogHandler->connect(vegeta_file_log_info.file_name, vegeta_file_log_info.location);
    vegeta_log_message log_message;
    log_message.level = VEGETA_LOG_INFO;
    log_message.message = "Initialising Vegeta Logging System With File";
    fileLogHandler->write_log(log_message);

    return fileLogHandler;
}
//FileLogHandler implementation end

//SysLogHandler implementation
vegeta_function_status SyslogHandler::connect(std::string ident) {
    /*
     *
     * This function connects to syslog server. 
     * Attributes
     * ident: string
     * This is the identifier which will be preponed before every message in syslog
     * 
     * 
    */
   openlog(ident.c_str(), LOG_PID|LOG_CONS, LOG_EMERG|LOG_AUTH|LOG_AUTHPRIV);
}
vegeta_function_status SyslogHandler::write_log(vegeta_log_message log_message) {
    /*
     * This function writes message defined by log_message to syslog
     * Attributes
     * 
     * log_message: vegeta_log_message
     * The log message details to log onto syslog
    */
   switch(log_message.level) {
       case VEGETA_LOG_ERROR: 
       syslog(LOG_EMERG, "%s", log_message.message.c_str());
       break;
   }
   return VEGETA_OK;
}
void SyslogHandler::close_log() {
    closelog();
}

SyslogHandler* init_log_syslog() {
    SyslogHandler* syslogHandler = new SyslogHandler();
    syslogHandler->connect("VEGETA");
    vegeta_log_message log_message;
    log_message.level = VEGETA_LOG_ERROR;
    log_message.message = "Initialising Vegeta Logging System With Syslog";
    syslogHandler->write_log(log_message);
    return syslogHandler;
}
//SysLogHandler implementation end