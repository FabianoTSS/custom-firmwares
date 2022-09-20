/*
 * Copyright (C) 2022 Vasilis Tsiligiannis <fabianotassotti@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 */
/*
1-read a file
2-write a string on the top of the file
3-create a md5sum 
4-write the sum on the top of the file

#Need a program to receive args - OK
#Need a program to read
#Need a program to write
#Need a program to get md5sum
#Need a program to call another programs and execute all of the procedures
*/

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <libgen.h>

#include <getopt.h>

#include <errno.h>

#include <sys/stat.h>

#include <endian.h>

#define FALSE 0
#define TRUE 1

struct header {
  char * magic;
}
__attribute__((packed));

struct finfo {
  char * name;
  off_t size;
};

struct buf {
  char * start;
  size_t size;
};

static char * progname;
static int force_be = FALSE;

static void usage(int status) {
  FILE * stream = (status != EXIT_SUCCESS) ? stderr : stdout;

  fprintf(stream, "Usage: %s [OPTIONS...]\n", progname);
  fprintf(stream,
    "\n"
    "Options:\n"
    "  -m <magic>      set magic to the router model\n"
    "  -i <file>       read input from file <file>\n"
    "  -o <file>       write output to file <file>\n");

  exit(status);
}

/*
static int strtou32(char * arg, unsigned int * val) {
  char * endptr = NULL;

  errno = 0;
  * val = strtoul(arg, & endptr, 0);
  if (errno || (endptr == arg) || ( * endptr && (endptr != NULL))) {
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}*/
/*
static unsigned short fwcsum(struct buf * buf) {
  int i;
    unsigned short ret = 0;

    for (i = 0; i < buf->size / 2; i++) {
	if (force_be == FALSE)
	    ret -= ((unsigned short *) buf->start)[i];
	else
	    ret -= HOST_TO_BE16(((unsigned short *) buf->start)[i]);
    }
    
    return ret;
}
*/
//finfo->name receives the directory and file to read
static int fwread(struct finfo * finfo, struct buf * buf) {
  FILE * f;

  f = fopen(finfo -> name, "r");
  if (!f) {
    fprintf(stderr, "could not open \"%s\" for reading\n", finfo -> name);
    usage(EXIT_FAILURE);
  }

  buf -> size = fread(buf -> start, 1, finfo -> size, f);
  if (buf -> size != finfo -> size) {
    fprintf(stderr, "unable to read from file \"%s\"\n", finfo -> name);
    usage(EXIT_FAILURE);
  }

  fclose(f);

  return EXIT_SUCCESS;
}

//finfo->name receives the directory and file to read
static int fwwrite(struct finfo * finfo, struct buf * buf) {
  FILE * f;

  f = fopen(finfo -> name, "w");
  if (!f) {
    fprintf(stderr, "could not open \"%s\" for writing\n", finfo -> name);
    usage(EXIT_FAILURE);
  }

  buf -> size = fwrite(buf -> start, 1, finfo -> size, f);
  if (buf -> size != finfo -> size) {
    fprintf(stderr, "unable to write to file \"%s\"\n", finfo -> name);
    usage(EXIT_FAILURE);
  }

  fclose(f);

  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  struct stat st;
  struct header header;
  struct buf ibuf, obuf;
  struct finfo ifinfo, ofinfo;
  unsigned short csum;
  int c;

  ifinfo.name = ofinfo.name = NULL;
  //header.flash = header.size = header.start = 0;
  progname = basename(argv[0]);

  while ((c = getopt(argc, argv, "i:o:m:")) != -1) {
    switch (c) {
    case 'i':
      printf("Case: i\n");
      printf("Input Dir Is = %s\n", optarg);
      ifinfo.name = optarg;
      break;
    case 'o':
      printf("Case: o\n");
      printf("Output Dir Is = %s\n", optarg);
      ofinfo.name = optarg;
      break;
    case 'm':
      printf("Case: m\n");
      printf("Output Magic Is = %s\n", optarg);

      //optarg = "\xd8\x0d\xb2\xa1";
      //header.magic = optarg;
	    /*if (strlen(optarg) != 16) {
		    fprintf(stderr, "magic must be 8 characters long\n");
		    usage(EXIT_FAILURE);
	    }
	    memcpy(header.magic, optarg, 8);*/
        FILE *fp;
   //char str = hexstring_to_ascii(header.magic);

   fp = fopen( "file.bin" , "wb" );
   //fwrite(header.magic , 1 , sizeof(header.magic) , fp );
   fwrite(optarg, 1 , sizeof(optarg) , fp );

   fclose(fp);

	    break;
    default:
      usage(EXIT_FAILURE);
      break;
    }
  }

  if (ifinfo.name == NULL) {
    fprintf(stderr, "no input file specified\n");
    usage(EXIT_FAILURE);
  }

  if (ofinfo.name == NULL) {
    fprintf(stderr, "no output file specified\n");
    usage(EXIT_FAILURE);
  }

  if (stat(ifinfo.name, & st)) {
    fprintf(stderr, "stat failed on %s\n", ifinfo.name);
    usage(EXIT_FAILURE);
  }

  if (header.magic == NULL) {
    fprintf(stderr, "no magic specified\n");
    usage(EXIT_FAILURE);
  }
  
  printf("This is the string Magic:%c\n\n", header.magic);



  //fwwrite(ifinfo.name, hexstring_to_ascii(header.magic));
  ifinfo.size = st.st_size;
  //printf("%d", ifinfo.size);
}

/*
//This is the caller program
int main(void)
{
    FILE *myfile = fopen("intelbras_ap-300-kernel.bin", "wb");
    putc(0x00, myfile);
    putc(0xA8, myfile);
    putc(0xFE, myfile);
    fclose(myfile);
    //fread(buffer,sizeof(buffer),1,myfile); 
    // read 10 bytes to our buffer

    return 0;
}
int main() {
   // printf() displays the string inside quotation

   printf("Hello, World!");
   return 0;
}*/