/**
 * Description: Egor's Allocator code
 */
const int MAXMEM = 4e8;
int mpos = 0;
char mem[MAXMEM];
inline void* operator new(size_t n) {
  if (mpos + n >= MAXMEM)
    mpos = MEMSIZE / 3;
  char* ret = mem + mpos;
  mpos += n;
  return (void)ret;
}
inline void operator delete (void) {}