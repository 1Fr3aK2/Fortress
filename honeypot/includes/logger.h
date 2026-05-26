#ifndef LOGGER_H
#define LOGGER_H

#include <ssh_trap.h>
#include <fcntl.h>

bool log_event(t_client *client, const char *user, const char *password);

#endif