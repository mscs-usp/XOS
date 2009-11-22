#!/usr/bin/env python

from os import system

from saga import (buffer, url)
from saga.file import (file, directory,
                       Write, ReadWrite, Create, CreateParents)

def write_file(dir, name, size):
    something = buffer(1024)
    something.data = "*" * 1024

    file1 = dir.open(url(name), Write)

    while size > 0:
        if size < 1024:
            s = size
        else:
            s = 1024

        file1.write(something, 1)

        size -= 1024

    file1.close()
    return file1

if __name__ == "__main__":
    print "\n\n\n cleaning Working directory...."
    system("rm -rf /tmp/SAGA");

    # creation of SAGA dir
    print "\n\n\n creating directory tree...."
    dir = directory(url("any://localhost/tmp/SAGA/"),
                    ReadWrite | Create | CreateParents)
    dir1k = directory(url("any://localhost/tmp/SAGA/sup1k"),
                      ReadWrite | Create | CreateParents)
    dir1M = directory(url("any://localhost/tmp/SAGA/sup1k/sup1M"),
                      ReadWrite | Create | CreateParents)
    dir5M =  directory(url("any://localhost/tmp/SAGA/sup1k/sup1M/sup5M"),
                       ReadWrite | Create | CreateParents)
    system("ls -Rl /tmp/SAGA")

    # create file of different size
    print "\n\n\n creating files...."
    file1 = write_file(dir, "es.txt", 5)
    write_file(dir1k, "es1k.txt", 1024)
    write_file(dir1M, "es1M.txt", 1024000)
    write_file(dir5M, "es5M.txt", 1024000*5)
    write_file(dir5M, "es100M.txt", 1024000*100)
    system("ls -Rl /tmp/SAGA")

    # copy it
    print "\n\n\n copying file SAGA/es.txt to SAGA/as.txt...."
    file1 = dir.open(url("es.txt"), Write)
    file1.copy(url("/tmp/SAGA/as.txt"))
    system("ls -Rl /tmp/SAGA")

    # rename it
    print "\n\n\n renaming file SAGA/es.txt in SAGA/es2.txt....\n"
    file1.move(url("/tmp/SAGA/es2.txt"))
    system("ls -Rl /tmp/SAGA")

    # erase copy
    print "\n\n\n deleting file SAGA/as.txt ....\n"
    file2 = file(url("/tmp/SAGA/as.txt"))
    file2.remove()
    system("ls -Rl /tmp/SAGA")
