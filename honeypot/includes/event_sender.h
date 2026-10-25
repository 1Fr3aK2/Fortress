#ifndef EVENT_SENDER_H
# define EVENT_SENDER_H

# include <stddef.h>

# define EVENT_SINK_HOST "logger"
# define EVENT_SINK_PORT "5140"
# define EVENT_MAX       1400

int	event_send(const char *buf, size_t len);

#endif