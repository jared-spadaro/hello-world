int *Insert(int *blk, int *toInsert, int dim1, int dim2, int offset) {
   int *temp = blk;
   blk = calloc(sizeof(int), dim1 + dim2);
   memmove(blk, temp, offset * sizeof(int));
   memmove(blk + offset, toInsert, dim2 * sizeof(int));
   memmove(blk + offset + dim2, temp + offset, (dim1 - offset) * sizeof(int));

   free(temp);
   return blk;
}
