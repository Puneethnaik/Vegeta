#include "vegeta_log.h"
#include "os/unix/unix_misc.h"

vegeta_function_status FileLogHandler::connect(std::string file_name, std::string location) {
    /*
        * connect is a function that connects a file descriptor
        * to a log file whose location can be specified.
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
    this->fd = open(file_absolute_path.c_str(), O_WRONLY|O_APPEND);
    if(this->fd < 0) {
        //create the file
        this->fd = open(file_absolute_path.c_str(), O_WRONLY|O_APPEND|O_CREAT);
        if(this->fd < 0) {
            return VEGETA_ERROR;
        }
    }
    this->file_name = file_name;
    this->location = location;
    return VEGETA_OK;
}

vegeta_function_status FileLogHandler:: write_log(vegeta_log_message log_message) {
    if(write(this->fd, log_message.message.c_str(), log_message.message.length()) != log_message.message.length()) {
        return VEGETA_ERROR;
    }
    return VEGETA_OK;
}

vegeta_function_status init_log() {
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
    if(fileLogHandler->connect(vegeta_file_log_info.file_name, vegeta_file_log_info.location) != VEGETA_OK) {
        return VEGETA_ERROR;
    }
    vegeta_log_message log_message;
    log_message.level = VEGETA_LOG_INFO;
    log_message.message = "Initialising Vegeta Logging System With File";
    fileLogHandler->write_log(log_message);
}