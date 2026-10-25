#ifndef INGEST_H
#define INGEST_H

# define INGEST_PORT 5140
# define INGEST_MAX  1400

int		ingest_open(void);
void	ingest_handle(int fd);
void	ingest_close(int fd);

#endif