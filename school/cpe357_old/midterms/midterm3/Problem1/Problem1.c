
int getBits (unsigned int from, int at, int count) {
   int countshift = 32 - count;
   from >>= at;
   from <<= countshift;
   from >>= countshift;
   return from;
}

