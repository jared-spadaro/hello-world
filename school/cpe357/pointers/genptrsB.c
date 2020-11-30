int SameId(void *p1, void *p2) {
   return ((Person *)p1)->id == ((Person *)p2)->id;
}
