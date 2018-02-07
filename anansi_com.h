#ifndef ANANSI_COM_H
#define ANANSI_COM_H

#define COM1    0x3F8
#define COM2    0x2F8
#define COM3    0x3E8
#define COM4    0x2E8

void
anansi_com_write(int port, const char *str);

#endif /* ANANSI_COM_H */
