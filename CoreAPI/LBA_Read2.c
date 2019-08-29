#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/fs.h>
//#include "common.h"

typedef unsigned long long int var64;


int getSectorSize(int handle)
{
        int sectorSize = 0;

        //get the physical sector size of the disk
        if (ioctl(handle, BLKSSZGET, &sectorSize)) {

                printf("getSectorSize: Reading physical sector size failed.\n");

                sectorSize = 512;
        }

        return sectorSize;
}



var64 readLBA(int handle, var64 lba, void* buf, var64 bytes)
{
        int ret = 0;
        int sectorSize = getSectorSize(handle);
        var64 offset = lba * sectorSize;

        printf("readFromLBA: entered.\n");

        lseek64(handle, offset, SEEK_SET);
        ret = read(handle, buf, bytes);
        if(ret != bytes) {

              printf("read LBA: read failed.\n");

                return -1;
        }

        printf("read LBA: retvalr: %lld.\n", ret);
        return ret;
}

int main(int argc, char **argv)
{
  int sectorSize, fd;
  char buff[100];
  printf("Calling getSectorSize\n");

  fd = open(argv[1], O_RDONLY);

  if(fd == -1)
  {
    printf("open  failed");
    exit(1);
  }
  sectorSize = getSectorSize(fd);
  printf("Sector size = %u\n", sectorSize);
  memset(buff, 0, sizeof(buff)); 
  readLBA(fd, 1, buff, 2); // if i put the 2nd arg as -12378 gives same answer
}


