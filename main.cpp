#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "archivo.h"

using namespace std;

int
main ( int argc, char *argv[] )
{
  if(argc < 3)
  {
    cout << "Missing arguments" << endl;
    return 1;
  }

  int threads = atoi (argv[1]);
  int file_number = 0;
  DIR * dip;
  struct dirent *dit;
  bool is_dir;

  if ( (dip = opendir( argv[2]) ) == NULL )
  {
    return 2;
  }

  cout << "Directory open: '" << argv[2] << "'" << endl;

  while ( (dit = readdir(dip) ) != NULL )
  { 
    struct stat stbuf;
    stat(dit->d_name, &stbuf);
    is_dir = S_ISDIR(stbuf.st_mode);

    if(!is_dir)
    {
      file_number++;
      cout << "File: " << dit->d_name << endl;
    }
  }

  closedir(dip);
}

