#include "archivo.h"

Archivo::Archivo (std::string filename):
  nombreArchivo(filename)
{
  fd = open(filename.c_str(), O_RDONLY);
  num_bytes = 0;
  contenido = NULL;
}

Archivo::Archivo (std::string filename,int banderas, mode_t modo):
  nombreArchivo(filename)
{
  fd = open(filename.c_str(), banderas, modo);
  num_bytes = 0;
  contenido = NULL;
}

Archivo::~Archivo()
{
  close(fd);
  free(contenido);
}

size_t
Archivo::lee ( size_t nbytes)
{
  size_t bytes_read;
  contenido = (char *) realloc ( contenido, num_bytes + nbytes );
  bytes_read = read(fd, contenido+num_bytes, nbytes);
  num_bytes += bytes_read;
  return bytes_read;
}

size_t
Archivo::escribe (void *buffer, size_t nbytes)
{
  size_t bytes_written;
  bytes_written = write(fd, buffer, nbytes);
  return bytes_written;
}

size_t
Archivo::obtieneNum_bytes()
{
  return num_bytes;
}

const char *
Archivo::get_contenido()
{
  return contenido;
}

