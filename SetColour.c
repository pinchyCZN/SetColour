//#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>

#define _MAX_COLORS_ 40
int MAX_COLORS=_MAX_COLORS_;
char ini_file[MAX_PATH]={0};

char *col_names[]={
"COLOR_SCROLLBAR",
"COLOR_BACKGROUND",
"COLOR_ACTIVECAPTION",
"COLOR_INACTIVECAPTION",
"COLOR_MENU",
"COLOR_WINDOW",
"COLOR_WINDOWFRAME",
"COLOR_MENUTEXT",
"COLOR_WINDOWTEXT",
"COLOR_CAPTIONTEXT",
"COLOR_ACTIVEBORDER",
"COLOR_INACTIVEBORDER",
"COLOR_APPWORKSPACE",
"COLOR_HIGHLIGHT",
"COLOR_HIGHLIGHTTEXT",
"COLOR_BTNFACE",
"COLOR_BTNSHADOW",
"COLOR_GRAYTEXT",
"COLOR_BTNTEXT",
"COLOR_INACTIVECAPTIONTEXT",
"COLOR_BTNHIGHLIGHT",
"COLOR_3DDKSHADOW",
"COLOR_3DLIGHT",
"COLOR_INFOTEXT",
"COLOR_INFOBK",
"UNKNOWN_COLOR",
"COLOR_HOTLIGHT",
"COLOR_GRADIENTACTIVECAPTION",
"COLOR_GRADIENTINACTIVECAPTION"
};

//  A B G R
int def_colors[_MAX_COLORS_]={
	0x00FF3838,
	0x00000000,
	0x00480000,
	0x00480000,
	0x00700000,
	0x00000000,
	0x00000000,
	0x0000FF00,
	0x0000FF00,
	0x0000FF00,
	0x006F0000,
	0x006F0000,
	0x00480000,
	0x00800000,
	0x0000FF00,
	0x00700000,
	0x00480000,
	0x00480000,
	0x0000FF00,
	0x00008000,
	0x00FF3838,
	0x00000000,
	0x00303030,
	0x00000000,
	0x00E1FFFF,
	0x00B8B4B8,
	0x00FF0000,
	0x00480000,
	0x00480000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000
};
int def_contrast[_MAX_COLORS_]={
//classic desktop
	0x00C8D0D4,
	0x00A56E3A,
	0x006A240A,
	0x00808080,
	0x00C8D0D4,
	0x00FFFFFF,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00FFFFFF,
	0x00C8D0D4,
	0x00C8D0D4,
	0x00808080,
	0x006A240A,
	0x00FFFFFF,
	0x00C8D0D4,
	0x00808080,
	0x00808080,
	0x00000000,
	0x00C8D0D4,
	0x00FFFFFF,
	0x00404040,
	0x00C8D0D4,
	0x00000000,
	0x00E1FFFF,
	0x00B5B5B5,
	0x00800000,
	0x00F0CAA6,
	0x00C0C0C0,
	0x006A240A,
	0x00C8D0D4,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
};
int alt_contrast[_MAX_COLORS_]={
//aqua
	0x00D8E0C8,
	0x00474E2C,
	0x00800000,
	0x00889048,
	0x00B8C088,
	0x00D8E0C8,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00FFFFFF,
	0x00B8C088,
	0x00B8C088,
	0x00848D4B,
	0x00800000,
	0x00FFFFFF,
	0x00B8C088,
	0x00889048,
	0x00889048,
	0x00000000,
	0x00C0C0C0,
	0x00D8E0C8,
	0x00000000,
	0x00B8C088,
	0x00000000,
	0x00D8E0C8,
	0x00C0C0C0,
	0x00800000,
	0x00C0B418,
	0x00D8CC78,
	0x00000000,
	0x00B8C088,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000
};

int set_ini_path()
{
	char path[MAX_PATH]={0};
	char drive[_MAX_DRIVE]={0};
	char dir[_MAX_DIR]={0};
	char fname[_MAX_PATH]={0};
	GetModuleFileName(NULL,path,sizeof(path));
	_splitpath(path,drive,dir,fname,NULL);
	_snprintf(ini_file,sizeof(ini_file),"%s%s%s%s",drive,dir,fname,".INI");
	ini_file[sizeof(ini_file)-1]=0;
	return 0;
}
int get_ini_value(char *section,char *key,int *val)
{
	char str[255];
	int result=0;
	if(ini_file[0]!=0){
		str[0]=0;
		result=GetPrivateProfileString(section,key,"",str,sizeof(str),ini_file);
		if(str[0]!=0)
			*val=atoi(str);
	}
	return result>0;
}
int save_colors(int custom_num)
{
	int i;
	char section[80]={0};
	_snprintf(section,sizeof(section),"%s%i","CUSTOM",custom_num);
	for(i=0;i<MAX_COLORS;i++){
		char key[40]={0};
		char val[40]={0};
		int c;
		_snprintf(key,sizeof(key),"C%02i",i);
		c=GetSysColor(i);
		_snprintf(val,sizeof(val),"0x%08X",c);
		if(ini_file[0]!=0){
			char *k=key;
			if(i<(sizeof(col_names)/sizeof(char*)))
				k=col_names[i];
			WritePrivateProfileString(section,k,val,ini_file);
		}
	}
	return i;
}
int load_colors(int custom_num)
{
	int i,*color_array,*index;
	char section[80]={0};
	color_array=malloc(sizeof(int)*MAX_COLORS);
	index=malloc(sizeof(int)*MAX_COLORS);
	if(color_array!=0 && index!=0){
		memset(color_array,0,MAX_COLORS*sizeof(int));
		memset(index,0,MAX_COLORS*sizeof(int));
		_snprintf(section,sizeof(section),"%s%i","CUSTOM",custom_num);
		for(i=0;i<MAX_COLORS;i++){
			char key[40]={0};

			color_array[i]=GetSysColor(i);
			index[i]=i;

			_snprintf(key,sizeof(key),"C%02i",i);
			if(ini_file[0]!=0){
				char val[40]={0};
				char *k=key;
				if(i<(sizeof(col_names)/sizeof(char*)))
					k=col_names[i];
				GetPrivateProfileString(section,k,"",val,sizeof(val),ini_file);
				if(val[0]!=0){
					val[sizeof(val)-1]=0;
					color_array[i]=strtoul(val,NULL,0);
				}
			}
		}
		SetSysColors(MAX_COLORS,index,color_array);
		if(color_array)
			free(color_array);
		if(index)
			free(index);
	}
	return i;
}
int get_custom_num(int *c,int argc,char *argv[])
{
	int i;
	for(i=1;i<argc;i++){
		char *s=0;
		if(strstr(argv[i],"-custom=")){
			s=strstr(argv[i],"=");
			if(s){
				s++;
				*c=atoi(s);
				break;
			}
		}
	}
	return 0;
}
int have_arg(const char *ARG,int argc,char *argv[])
{
	int i,result=FALSE;
	for(i=1;i<argc;i++){
		char *s=0;
		if(strstr(argv[i],ARG)){
			result=TRUE;
			break;
		}
	}
	return result;
}
int print_cmd()
{
	printf("hold shift or control to load alt contrast scheme\n");
	printf("l,r,u,d or middle button overrides to classic color\n");
	printf("cmd line options: -save -custom={num}\n");
	printf("                  -? -h -help\n");
	printf("ini section\n[KEYS]\ndelay=1\nspeed=23\n\n");
	return 0;
}
int load_default()
{
	int i;
	int temp[_MAX_COLORS_],index[_MAX_COLORS_];

	for(i=0;i<_MAX_COLORS_;i++){
		index[i]=i;
	}
	for(i=0;i<_MAX_COLORS_;i++){
		temp[i]=GetSysColor(i);
	}

	if(0==memcmp(temp,def_colors,_MAX_COLORS_*4)){
		int load_alt=FALSE;
		if(GetAsyncKeyState(VK_CONTROL)&0x8000)
			load_alt=TRUE;
		if(GetAsyncKeyState(VK_SHIFT)&0x8000)
			load_alt=TRUE;
		if(GetAsyncKeyState(VK_MBUTTON)&0x8000)
			load_alt=FALSE;
		if(GetAsyncKeyState(VK_UP)&0x8000)
			load_alt=FALSE;
		if(GetAsyncKeyState(VK_DOWN)&0x8000)
			load_alt=FALSE;
		if(GetAsyncKeyState(VK_LEFT)&0x8000)
			load_alt=FALSE;
		if(GetAsyncKeyState(VK_RIGHT)&0x8000)
			load_alt=FALSE;

		if(load_alt)
			SetSysColors(_MAX_COLORS_,index,alt_contrast);
		else
			SetSysColors(_MAX_COLORS_,index,def_contrast);
	}
	else
		SetSysColors(_MAX_COLORS_,index,def_colors);
	return 0;
}
int set_keys()
{
	int delay=1;
	int speed=23;
	get_ini_value("KEYS","DELAY",&delay);
	get_ini_value("KEYS","SPEED",&speed);
	SystemParametersInfo( SPI_SETKEYBOARDDELAY, delay, NULL, 0 );
	SystemParametersInfo( SPI_SETKEYBOARDSPEED, speed, NULL, 0 );
	return 0;
}
int dump_colors()
{
	int i;
	for(i=0;i<_MAX_COLORS_;i++){
		int c=GetSysColor(i);
		printf("0x%08X,\n",c);
	}
	return 0;
}
/*
int dump_file(char *n)
{
	char nout[MAX_PATH]={0};
	FILE *f,*fout;

	f=fopen(n,"rb");
	_snprintf(nout,sizeof(nout),"%s_out.txt",n);
	fout=fopen(nout,"wb+");
	if(f){
		int i;
		for(i=0;i<40;i++){
			int buf[1]={0};
			char str[40]={0};
			fread(buf,1,4,f);
			_snprintf(str,sizeof(str),"0x%08X,\n",buf[0]);
			if(fout)
				fprintf(fout,"%s",str);
		}
	}
	if(f)
		fclose(f);
	if(fout)
		fclose(fout);
}
*/
int main(int argc,char *argv[])
{
	int custom=-1;
	
	print_cmd();
	if(have_arg("-?",argc,argv)
		|| have_arg("-h",argc,argv)
		|| have_arg("-help",argc,argv)){
		exit(0);
	}
	set_ini_path();
	printf("ini file:%s\n",ini_file);
	get_custom_num(&custom,argc,argv);
	if(have_arg("-save",argc,argv)){
		if(custom<0)
			custom=0;
		printf("saving colors to CUSTOM%i\n",custom);
		save_colors(custom);
		exit(0);
	}
	else if(have_arg("-dump",argc,argv)){
		printf("dumping colors:\n");
		dump_colors();
		exit(0);
	}
	set_keys();
	if(custom<0){
		printf("loading default colors\n");
		load_default();
		exit(0);
	}
	else{
		printf("loading custom %i\n",custom);
		load_colors(custom);
	}
}



