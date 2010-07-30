// DCC stdio

#include <string.h>
#include "dcc_stdio.h"

#define    R_BIT	1
#define    W_BIT	2

extern unsigned int read_dbg_control(void);
extern unsigned int read_dbg_data(void);
extern void  write_dbg_data(unsigned int val);

void WriteLoaderData(unsigned int datas)
{
	while( read_dbg_control() & W_BIT );
	write_dbg_data( datas );
}

unsigned int ReadLoaderData(void)
{
	while( !(read_dbg_control() & R_BIT ));
	return read_dbg_data();
}

void WriteDebugString(unsigned char* pString)
{
	//unsigned char buffer[4];
	int buffer = 1;
	int count = strlen((char*)pString);

	buffer |= (count << 16);
	WriteLoaderData( buffer );

	//WriteLoaderData( 0x00040001 );
	//WriteLoaderData( 'spen' );

	//while(*pString)
	do
	{
		int nbytes = count > 4 ? 4 : count;
		buffer = 0;

		//while( nbytes-- )
		//do
		//{
			//buffer <<= 8;
			//buffer |= *(pString++);

			//buffer = *(pString++);
			//buffer <<= 8;
			//buffer |= *(pString++);
			//buffer <<= 8;
			buffer = *(int*)(pString);
			pString += nbytes;
			count -= nbytes;
		//} while( --nbytes );

		WriteLoaderData( buffer );
	} while( count );
}

void WriteDebugInt(char *p, unsigned int num)
{
    unsigned char *bcd = (unsigned char*)p;

    bcd[0] = (unsigned char)((num %100000000) / 10000000) + 48;
    bcd[1] = (unsigned char)((num %10000000) / 1000000) + 48;
    bcd[2] = (unsigned char)((num %1000000) / 100000) + 48;
    bcd[3] = (unsigned char)((num %100000) / 10000) + 48;
    bcd[4] = (unsigned char)((num %10000) / 1000) + 48;
    bcd[5] = (unsigned char)((num % 1000) / 100) + 48;
    bcd[6] = (unsigned char)((num % 100) / 10) + 48;
    bcd[7] = (unsigned char)(num % 10) + 48;
    bcd[8] = 0;
}
