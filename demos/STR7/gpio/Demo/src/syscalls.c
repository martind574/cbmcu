
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

int _write_r(void *reent, int fd, char *ptr, size_t len)
{
	return len;
}

void exit(int n)
{
	while(1);
}

register char *stack_ptr asm ("sp");
caddr_t _sbrk_r(void *reent, size_t incr)
{
	extern char end asm ("end");		// Defined by the linker
	//extern char end asm ("__heap_start__");		// Defined by the linker
	static char *heap_end;
	char *prev_heap_end;

	if( heap_end == NULL )
		heap_end = &end;
	prev_heap_end = heap_end;

	if(( heap_end + incr ) > stack_ptr )
	{
		/* Some of the libstdc++-v3 tests rely upon detecting
		out of memory errors, so do not abort here.  */
		//write( 1, "sbrk: Heap and stack collision\n", 32 );
		//abort();
		exit(1);
		//errno = ENOMEM;
		return (caddr_t) -1;
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}
