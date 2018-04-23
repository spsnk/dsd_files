#include <iostream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "archivo.h"

using namespace std;

int
parse ( string &filename )
{
  
}

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
  std::vector<std::thread> threads;

  if ( (dip = opendir( argv[2]) ) == NULL )
  {
    return 2;
  }

  cout << "Directory open: '" << argv[2] << "'" << endl;

  while ( (dit = readdir(dip) ) != NULL )
  { 
    if( strstr (dit->d_name, ".txt") )
    {
      file_number++;
      cout << "File: " << dit->d_name << endl;
    }
  }

  closedir(dip);
}

