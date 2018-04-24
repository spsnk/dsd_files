#include <iostream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <vector>
#include <map>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "archivo.h"

using namespace std;

map < string, size_t> letters;

int
parse ( string filename )
{
  cout << "F: " << filename << endl;
  return 0;
}

int
main ( int argc, char *argv[] )
{
  if(argc < 3)
  {
    cout << "Missing arguments" << endl;
    return 1;
  }

  int threads_number = atoi (argv[1]);
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
      string filename ( dit->d_name );
      threads.push_back( thread( parse, filename));
      //cout << "File: " << dit->d_name << endl;
    }
  }
  for (thread& th : threads) 
  {
    th.join();
  }
  closedir(dip);
}

