/*
 * Created by Fabiano Tassotti <fabianotassotti@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 */

#include <stdio.h>

#include <string.h>

//This is the conversion struct.
struct toascii {
  char * string;
  size_t strleng;
  size_t asciileng;
  char * ascii;
};

//This takes two characters and converts to an integer.
int ahex2int(char a, char b) {
  a = (a <= '9') ? a - '0' : (a & 0x7) + 9;
  b = (b <= '9') ? b - '0' : (b & 0x7) + 9;
  return (a << 4) + b;
}

//this splits a hex string, order and send two caracters to ahex2int and then returns an ASCII string.
static char * strtoascii(char str[], size_t sz) {
  static char hex[16];
  char * ascii;
  int j = 0;

  printf("The string size is: %d\n", sz);

  for (int i = 0; i <= sz; i++) {
    (i % 2 == 0) ? hex[j] = (char) ahex2int(str[i], str[i + 1]): j++;
  };

  return ascii = hex;
}

//Write one file with the ASCII string
int fwwrite(char * input, char * output, size_t sz) {
  FILE * fp;

  fp = fopen(output, "wb");
  fwrite(input, 1, sz, fp);

  fclose(fp);
}

//Here all run
int main() {
  struct toascii magic;
  magic.string = "d80db2a1d80db2a1d80db2a1d80db2a1d80db2a1";
  magic.strleng = strlen(magic.string);
  magic.ascii = strtoascii(magic.string, magic.strleng);
  magic.asciileng = magic.strleng / 2;

  fwwrite(magic.ascii, "file.bin", magic.asciileng);

  return (0);
}