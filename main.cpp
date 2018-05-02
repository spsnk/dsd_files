#include <iostream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <vector>
#include <set>
#include <map>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "archivo.h"

using namespace std;

map < string, size_t> usedwords;

typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;
Comparator compFunctor =
			[](std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)
			{
				return elem1.second > elem2.second;
			};

int
parse ( const char * words, size_t size )
{
  string word;
  string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚñü";
  for ( size_t i = 0; i < size; i++ )
  {
    unsigned char c = words[i];
    switch (c)
    {
      default:
        if ( alphabet.find (c) != string::npos )
        {
          word += c<97?c+32:c;
        }
        break;
      case '\n':
      case ' ':
        if(!word.empty ())
        {
          usedwords [word] = usedwords [word] + 1;
          word.clear();
        }
        break;
      
    }
  }
  return 0;
}

int
process ( vector<string> files , int n)
{
  for(string filename : files )
  {
    cout << "Thread " << n << "->" << filename << '\n' << flush;
    Archivo file (filename);
    while ( file.lee(BUFSIZ) > 0 );
    parse ( file.get_contenido(), file.obtieneNum_bytes() );
  }
  return 0;
}

int
main ( int argc, char *argv[] )
{
  if(argc < 3)
  {
    cout << "Missing arguments\nUsage: main threads folder" << endl;
    return 1;
  }

  int thread_number = atoi (argv[1]);
  int file_number = 0;
  DIR * dip;
  struct dirent *dit;
  std::vector<std::thread> threads;
  threads.reserve(thread_number);
  std::vector<std::string> files;

  if ( (dip = opendir( argv[2] ) ) == NULL )
  {
    return 2;
  }

  cout << "Directory open: '" << argv[2] << "'" << endl;

  while ( (dit = readdir(dip) ) != NULL )
  { 
    if( strstr (dit->d_name, ".txt") )
    {
      file_number++;
      string temp ( argv[2] );
      temp += "/";
      temp +=dit->d_name;
      files.push_back(temp);
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
    threads.push_back( thread( process, vector<string> (files.begin()+i, files.begin()+temp) , th++ ));
  }
  
  for (thread& th : threads) 
  {
    th.join();
  }
  
  std::set<std::pair<std::string, int>, Comparator> setOfWords(usedwords.begin(), usedwords.end(), compFunctor);
  cout << endl << "N°\tPalabra" << endl;
  int i = 1;
  for (const auto& sm_pair : setOfWords)
  {
    if(i > 500)
    {
      break;
    }
    cout << i++ << '\t' << sm_pair.first << '\t' << endl; 
  }
  
  closedir(dip);
}

