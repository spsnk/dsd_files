#ifndef __ARCHIVO_H__
#define __ARCHIVO_H__

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>

class Archivo
{
private:
  std::string nombreArchivo;
  int fd;
  char *contenido;
  size_t num_bytes;
public:
  Archivo(std::string filename);
  Archivo(std::string filename, int banderas, mode_t modo);
  size_t lee(size_t nbytes);
  size_t escribe(void *buffer, size_t nbytes);
  size_t obtieneNum_bytes();
  const char *get_contenido();
  ~Archivo();
};

#endif
