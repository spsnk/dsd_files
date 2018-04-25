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
parse ( vector<string> files , int n)
{
  for(string filename : files )
  {
    cout << "Thread " << n << " Processing file :" << filename << '\n' << flush;
    
  }
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

  int thread_number = atoi (argv[1]);
  int file_number = 0;
  DIR * dip;
  struct dirent *dit;
  bool is_dir;
  std::vector<std::thread> threads;
  threads.reserve(thread_number);
  std::vector<std::string> files;

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
      files.push_back(string ( dit->d_name ));
    }
  }
  int th = 1;
  for (int i = 0, j = 0; j < thread_number; j++, i+= file_number/thread_number)
  {
    int temp;
    if( j == thread_number - 1)
    {
      temp = file_number;
    }
    else
    {
      temp = i + file_number/thread_number;
    }
    threads.push_back( thread( parse, vector<string> (files.begin()+i, files.begin()+temp) , th++ ));
  }
  
  for (thread& th : threads) 
  {
    th.join();
  }
  closedir(dip);
}

