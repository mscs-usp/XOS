//  Copyright (c) 2005-2007 Andre Merzky (andre@merzky.net)
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <saga.hpp>

saga::file  write_file(saga::directory dir,char *name, int size) {
  char*  something="****************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************";

  saga::file file;

  file=dir.open(name,saga::file::Write);
  for (int s;size>0;size-=1024) {
    s=1024;
    if (size<1024) {
      s=size;
    }
     file.write(something,1);
  }
  file.close();

  return file;
}



///////////////////////////////////////////////////////////////////////////////
int main (int argc, char* argv[])
{
  
  printf ("\n\n\n cleaning Working directory....\n");
  system("rm -rf /tmp/SAGA");
  
   // creation of SAGA dir
  printf ("\n\n\n creating directory tree....\n");
  saga::directory dir("any://localhost/tmp/SAGA/",saga::file::ReadWrite|saga::file::Create|saga::file::CreateParents);
  saga::directory dir1k("any://localhost/tmp/SAGA/sup1k",
			saga::file::ReadWrite|saga::file::Create|saga::file::CreateParents);
  saga::directory dir1M("any://localhost/tmp/SAGA/sup1k/sup1M",
			saga::file::ReadWrite|saga::file::Create|saga::file::CreateParents);
  saga::directory dir5M("any://localhost/tmp/SAGA/sup1k/sup1M/sup5M",
			saga::file::ReadWrite|saga::file::Create|saga::file::CreateParents);

  system("ls -Rl /tmp/SAGA");

  // create file of different size
  printf ("\n\n\n creating files....\n");
  saga::file file=write_file(dir,"es.txt",5);
  write_file(dir1k,"es1k.txt",1024);
  write_file(dir1M,"es1M.txt",1024000);
  write_file(dir5M,"es5M.txt",1024000*5);
  write_file(dir5M,"es100M.txt",1024000*100);
  system("ls -Rl /tmp/SAGA");

  

  //copy it
  printf ("\n\n\n copying file SAGA/es.txt to SAGA/as.txt....\n");
  file.copy("/tmp/SAGA/as.txt");
  system("ls -Rl /tmp/SAGA");

  // rename it
  printf ("\n\n\n renaming file SAGA/es.txt in SAGA/es2.txt....\n");
  file.move("/tmp/SAGA/es2.txt");
  system("ls -Rl /tmp/SAGA");

  // erase copy
  printf ("\n\n\n deleting file SAGA/as.txt ....\n");
  saga::file file2("/tmp/SAGA/as.txt");
  file2.remove();
  system("ls -Rl /tmp/SAGA");

  return 0;
}



