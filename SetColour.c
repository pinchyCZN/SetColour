#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <stdio.h>


extern int colour[];
extern int contrast[];

//#define SAVE_COLOURS
//#define GETCOLOUR
//#define TEST

int main()
{
	int i;
	int temp[40],index[40];
	int nKBDelay=1;
	int nKBSpeed=23;

	SystemParametersInfo( SPI_SETKEYBOARDDELAY, nKBDelay, NULL, 0 );
	SystemParametersInfo( SPI_SETKEYBOARDSPEED, nKBSpeed, NULL, 0 );

#ifdef SAVE_COLOURS
#include "text.h"
	FILE *stream;
 	memset(temp,0,sizeof(temp));
	for (i=0;i<40;i++)
	temp[i]=GetSysColor(i);


	#ifdef GETCOLOUR
	stream=fopen("colours.bin","w+b");
	#else
	stream=fopen("contrast.bin","w+b");
	#endif
	fwrite(temp,4*40,1,stream);
	fclose(stream);

	#ifdef GETCOLOUR
	stream=fopen("colours.txt","w+b");
	for (i=0;i<40;i++)
	{
		fprintf(stream,"%s%08X"," DD $",temp[i]);
		fprintf(stream," %s%i",";",i);
		if (i<29)
		fprintf(stream," %s\n",text[i]);
		else
		fprintf(stream," %s\n","UNKNOWN_COLOR");


	}
	#endif

#else
	
	for (i=0;i<40;i++)
	 index[i]=i;	

	for (i=0;i<40;i++)
	temp[i]=GetSysColor(i);

	i=memcmp(temp,colour,40*4);
#ifndef TEST
	if (i==0) //we have colour ,set contrast
	SetSysColors(40,index,contrast);
	else
#endif
	SetSysColors(40,index,colour);
#endif

	return 0;
}



