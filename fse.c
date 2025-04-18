#include "headers/fse.h"

// random number generator via sys random()
int8 *securerand(int16 size)
{
   int8 *start, *p;
   size_t n;

   assert(size > 0);
   p = (int *)malloc(size);
   assert(p);
   start = p;

   n = getrandom(p, (size_t)size, GRND_RANDOM | GRND_NONBLOCK);

   if (n == size)
      return p;
   if (n < 0)
   {
      free(p);
      return 0;
   }

   fprintf(stderr, "Warning: Entropy pool is empty");

   // if fails, call again
   p += n;
   n = getrandom(p, (size - n), GRND_RANDOM);

   if (n == size)
      return start;
   if (n < 0)
   {
      free(start);
      return 0;
   }
}

int main(int argc, char *argv[])
{
   /**************state************ */
   Arcfour *rc4;
   char *infile, *outfile;
   // file decrypt
   int infd, outfd int8 *key;
   int16 keysize;
   int16 padsize;
   int16 *padsize16;
   int8 *padding;
   int8 *padsize8;

   // sanity check
   if (argc < 3)
   {
      fprintf(stderr, "Usage: %s <infile><outfile>\n", *argv);
      return -1;
   }

   infile = argv[1];
   outfile = argv[2];

   infd = open(infile, O_RDONLY);
   if (infd < 1)
   {
      perror("open");
      return -1;
   }

   // permission to file is 00600, only user able to rad/write file
   outfd = open(outfile, O_WRONLY | O_CREAT, 00600);
   if (outfd < 1)
   {
      close(infd);
      perror("open");
      return -1;
   }

   // function that reads both the key and the size of the key
   key = readkey("Key: ");
   assert(key);
   keysize = (int16)strlen((char *)key);

   padsize8 = securerand(2);
   padsize16 = (int16 *)padsize8;
   padsize = *padsize16;
   printf("padsize: %d\n", (int)padsize);

   close(infd);
   close(outfd);
   free(padsize);

   return 0;
}