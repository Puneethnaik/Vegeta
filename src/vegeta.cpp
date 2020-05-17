
#include "vegeta_log.h"



int main(int argc, char **argv) {
    // FileLogHandler *logHandler;

    // logHandler = init_log_file();

    // // printf("fileloghandler address is %d", logHandler->fd);
    // logHandler->close_log();
    SyslogHandler *sysLogHandler;
    sysLogHandler = init_log_syslog();
    sysLogHandler->close_log();
    return VEGETA_OK;
}