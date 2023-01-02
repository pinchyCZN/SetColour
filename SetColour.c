//#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include "resource.h"
#pragma warning( disable : 4996)

#define MAX_COLORS 41
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
"UNKNOWN_COLOR_25",
"COLOR_HOTLIGHT",
"COLOR_GRADIENTACTIVECAPTION",
"COLOR_GRADIENTINACTIVECAPTION",
"COLOR_MENUHILIGHT",
"COLOR_MENUBAR",
"UNKNOWN_COLOR_31",
"UNKNOWN_COLOR_32",
"UNKNOWN_COLOR_33",
"UNKNOWN_COLOR_34",
"UNKNOWN_COLOR_35",
"UNKNOWN_COLOR_36",
"UNKNOWN_COLOR_37",
"UNKNOWN_COLOR_38",
"UNKNOWN_COLOR_39",
"UNKNOWN_COLOR_40"
};

//  A B G R
int def_colors[MAX_COLORS]={
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
	0x00B02000,
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
	0x00F00000,
	0x00700000,
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
int def_contrast[MAX_COLORS]={
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
	0x00000000,
};
int alt_contrast[MAX_COLORS]={
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
	0x00000000,
	0x00000000,
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
		if(0==strcmp(argv[i],ARG)){
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
	printf("cmd line options:\n");
	printf("[-custom={num}]\n");
	printf("[-load]\n");
	printf("[-load1|2|3]\n");
	printf("[-save]\n");
	printf("[-dump]\n");
	printf("[-keys] #SPI_SETKEYBOARDDELAY=1, SPI_SETKEYBOARDSPEED=23\n");
	printf("[-?|-h|-help]\n");
	return 0;
}
int load_default()
{
	int i;
	int temp[MAX_COLORS],index[MAX_COLORS];

	for(i=0;i<MAX_COLORS;i++){
		index[i]=i;
	}
	for(i=0;i<MAX_COLORS;i++){
		temp[i]=GetSysColor(i);
	}

	if(0==memcmp(temp,def_colors,MAX_COLORS*sizeof(int))){
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
			SetSysColors(MAX_COLORS,index,alt_contrast);
		else
			SetSysColors(MAX_COLORS,index,def_contrast);
	}
	else
		SetSysColors(MAX_COLORS,index,def_colors);
	return 0;
}
void load_set(const int set)
{
	int i,index[MAX_COLORS];
	for(i=0;i<MAX_COLORS;i++){
		index[i]=i;
	}
	if(1==set){
		SetSysColors(MAX_COLORS,index,def_colors);
	}else if(2==set){
		SetSysColors(MAX_COLORS,index,def_contrast);
	}else if(3==set){
		SetSysColors(MAX_COLORS,index,alt_contrast);
	}
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
	for(i=0;i<MAX_COLORS;i++){
		int c=GetSysColor(i);
		const char *name=col_names[i];
		printf("0x%08X, // %s\n",c,name);
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
HWND WINAPI GetConsoleWindow(void);

typedef struct{
	HWND hcolor;
	HWND hedit;
	HWND hbutton;
	DWORD color;
}CONTROL;

CONTROL g_controls[MAX_COLORS]={0};
DWORD g_original[MAX_COLORS]={0};
int g_live_update=0;

void save_original()
{
	int i;
	for(i=0;i<MAX_COLORS;i++){
		g_original[i]=GetSysColor(i);
	}
}
void restore_color_list()
{
	int i;
	for(i=0;i<MAX_COLORS;i++){
		g_controls[i].color=g_original[i];
	}
}

void get_color_values()
{
	int i;
	for(i=0;i<MAX_COLORS;i++){
		g_controls[i].color=GetSysColor(i);
	}
}
void set_color_hex_values()
{
	int i;
	for(i=0;i<MAX_COLORS;i++){
		HWND hedit=g_controls[i].hedit;
		if(hedit){
			char tmp[40]={0};
			COLORREF c=g_controls[i].color;
			_snprintf(tmp,sizeof(tmp),"%08X",c);
			SetWindowText(hedit,tmp);
		}
	}
}
void invalidate_color_buttons()
{
	int i;
	for(i=0;i<MAX_COLORS;i++){
		HWND hcolor=g_controls[i].hcolor;
		if(hcolor){
			InvalidateRect(hcolor,0,0);
		}
	}
}
void set_windows_colors()
{
	int i;
	int array[MAX_COLORS];
	COLORREF colors[MAX_COLORS];
	for(i=0;i<MAX_COLORS;i++){
		colors[i]=g_controls[i].color;
		array[i]=i;
	}
	SetSysColors(MAX_COLORS,array,colors);
}
void adjust_number(char *str,const int str_size,const int index,const int amount)
{
	DWORD orig,val;
	int shift=7-index;
	int tmp=1<<(shift*4);
	if(index<2 || index>7){
		return;
	}
	orig=val=strtoul(str,NULL,16);
	if(amount<0){
		tmp=-tmp;
	}else if(0==amount){
		tmp=0;
	}
	val+=tmp;
	tmp=0xFF<<((shift/2)*8);
	val&=tmp;
	orig&=~tmp;
	val=orig|val;
	_snprintf(str,str_size,"%08X",val);
}
void move_next_control(const HWND hwnd,const int dir)
{
	int i;
	for(i=0;i<MAX_COLORS;i++){
		HWND hedit=g_controls[i].hedit;
		if(hwnd==hedit){
			DWORD x=0,y=0;
			int index=i+dir;
			if(index==MAX_COLORS){
				index=0;
			}else if(index<0){
				index=MAX_COLORS-1;
			}
			hedit=g_controls[index].hedit;
			SendMessage(hwnd,EM_GETSEL,(WPARAM)&x,(LPARAM)&y);
			SetFocus(hedit);
			SendMessage(hedit,EM_SETSEL,(WPARAM)x,(LPARAM)y);
			break;
		}
	}
}
void set_color_value(const HWND hedit,const DWORD color)
{
	int i;
	for(i=0;i<MAX_COLORS;i++){
		HWND h=g_controls[i].hedit;
		if(h==hedit){
			g_controls[i].color=color;
			InvalidateRect(g_controls[i].hcolor,0,0);
			break;
		}
	}
}
void normalize_color_val(const HWND hedit)
{
	int i;
	for(i=0;i<MAX_COLORS;i++){
		HWND h=g_controls[i].hedit;
		if(h==hedit){
			char tmp[20]={0};
			DWORD x=0,y=0;
			DWORD c;
			SendMessage(hedit,EM_GETSEL,(WPARAM)&x,(LPARAM)&y);
			GetWindowText(hedit,tmp,sizeof(tmp));
			g_controls[i].color=c=strtoul(tmp,0,16);
			_snprintf(tmp,sizeof(tmp),"%08X",c);
			SetWindowText(hedit,tmp);
			SendMessage(hedit,EM_SETSEL,(WPARAM)x,(LPARAM)y);
			InvalidateRect(g_controls[i].hcolor,0,0);
			break;
		}
	}

}
void update_system_colors(const HWND hedit,const int update_all)
{
	int i;
	int counter=0;
	COLORREF colors[MAX_COLORS]={0};
	int array[MAX_COLORS]={0};
	if(!g_live_update){
		return;
	}
	for(i=0;i<MAX_COLORS;i++){
		if(update_all){
			array[counter]=i;
			colors[counter]=g_controls[i].color;
			counter++;
		}else{
			HWND h=g_controls[i].hedit;
			if(h==hedit){
				array[counter]=i;
				colors[counter]=g_controls[i].color;
				counter++;
				break;
			}
		}
	}
	SetSysColors(counter,array,colors);
}
static WNDPROC g_old_win_proc=0;
LRESULT CALLBACK subclass_proc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	LRESULT result=0;
	switch(msg){
	case WM_GETDLGCODE:
		break;
	case WM_KEYDOWN:
		{
			//intf("msg=%i (%08X) %08X %08X\n",msg,msg,wparam,lparam);
		}
		{
			int vkey=(int)wparam;
			if(VK_UP==vkey || VK_DOWN==vkey){
				char tmp[40]={0};
				DWORD x=0,y=0;
				if(0x8000&GetKeyState(VK_CONTROL)){
					move_next_control(hwnd,VK_UP==vkey?-1:1);
					return result;
				}
				GetWindowText(hwnd,tmp,sizeof(tmp));
				SendMessage(hwnd,EM_GETSEL,(WPARAM)&x,(LPARAM)&y);
				adjust_number(tmp,sizeof(tmp),x,VK_UP==vkey?1:-1);
				SetWindowText(hwnd,tmp);
				SendMessage(hwnd,EM_SETSEL,(WPARAM)x,(LPARAM)y);
				x=strtoul(tmp,0,16);
				set_color_value(hwnd,x);
				update_system_colors(hwnd,0);
				return result;
			}
			else if(VK_PRIOR==vkey || VK_NEXT==vkey){
				move_next_control(hwnd,VK_PRIOR==vkey?-1:1);
				return result;
			}
			else if(VK_F1==vkey){
				int check;
				HWND hparent=GetParent(hwnd);
				check=SendDlgItemMessage(hparent,IDC_LIVE,BM_GETCHECK,0,0);
				check=BST_CHECKED==check?BST_UNCHECKED:BST_CHECKED;
				SendDlgItemMessage(hparent,IDC_LIVE,BM_SETCHECK,check,0);
				g_live_update=BST_CHECKED==check?1:0;
				printf("live=%i\n",g_live_update);
				return result;
			}
			else if(VK_F5==vkey){
				DWORD x=0,y=0;
				SendMessage(hwnd,EM_GETSEL,(WPARAM)&x,(LPARAM)&y);
				get_color_values();
				set_color_hex_values();
				invalidate_color_buttons();
				SendMessage(hwnd,EM_SETSEL,(WPARAM)x,(LPARAM)y);
				update_system_colors(hwnd,1);
			}else if((vkey>='0' && vkey<='9') || (vkey>='A' && vkey<='F')){
				DWORD x=0,y=0;
				SendMessage(hwnd,EM_GETSEL,(WPARAM)&x,(LPARAM)&y);
				if(x>=2 && x<=7){
					char tmp[4]={0};
					y=x+1;
					SendMessage(hwnd,EM_SETSEL,(WPARAM)x,(LPARAM)y);
					tmp[0]=vkey;
					SendMessage(hwnd,EM_REPLACESEL,(WPARAM)0,(LPARAM)tmp);
					normalize_color_val(hwnd);
					update_system_colors(hwnd,0);
				}else if(x<=2){
					x++;
					SendMessage(hwnd,EM_SETSEL,(WPARAM)x,(LPARAM)x);
				}
			}else if((vkey<=VK_SPACE)||(vkey>=VK_SELECT && vkey<=0x6F)){
				DWORD x=0,y=0;
				SendMessage(hwnd,EM_GETSEL,(WPARAM)&x,(LPARAM)&y);
				if(x<2){
					x++;
					SendMessage(hwnd,EM_SETSEL,(WPARAM)x,(LPARAM)x);
				}
				return result;
			}
		}
		break;
	}
	result=CallWindowProc(g_old_win_proc,hwnd,msg,wparam,lparam);
	return result;
}


void construct_window(HWND hwnd)
{
	int i;
	const int TOTAL=MAX_COLORS;
	HINSTANCE hinst=(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
	HDC hdc=GetDC(hwnd);
	RECT crect={0};
	int y=0;
	HGDIOBJ hobj=GetStockObject(SYSTEM_FIXED_FONT);
	SelectObject(hdc,hobj);
	get_color_values();
	for(i=0;i<TOTAL;i++){
		char tmp[80]={0};
		SIZE text_size={0};
		int w,h;
		int x;
		HWND htmp;
		RECT rect={0};
		_snprintf(tmp,sizeof(tmp),"0134");
		GetTextExtentPoint32(hdc,tmp,strlen(tmp),&text_size);
		w=text_size.cx+5;
		h=text_size.cy+5;
		x=3;
		// COLOR SQUARE
		htmp=CreateWindow("BUTTON","",WS_VISIBLE|WS_CHILD|BS_OWNERDRAW,x,y,w,h,hwnd,NULL,hinst,NULL);
		g_controls[i].hcolor=htmp;
		GetWindowRect(htmp,&rect);
		x+=rect.right-rect.left+1;

		_snprintf(tmp,sizeof(tmp),"%08X",g_controls[i].color);
		GetTextExtentPoint32(hdc,tmp,strlen(tmp),&text_size);
		w=text_size.cx+5;
		h=text_size.cy+5;
		htmp=CreateWindow("EDIT",tmp,WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_LEFT,x,y,w,h,hwnd,NULL,hinst,NULL);
		SendMessage(htmp,WM_SETFONT,(WPARAM)hobj,0);
		SendMessage(htmp,EM_LIMITTEXT,8,0);

		g_old_win_proc=(WNDPROC)SetWindowLong(htmp,GWL_WNDPROC,(LONG)subclass_proc);
		GetWindowRect(htmp,&rect);
		g_controls[i].hedit=htmp;

		_snprintf(tmp,sizeof(tmp),"%i=%s",i,col_names[i]);
		GetTextExtentPoint32(hdc,tmp,strlen(tmp),&text_size);
		w=text_size.cx+8;
		h=text_size.cy+5;
		x+=rect.right-rect.left+5;
		htmp=CreateWindow("BUTTON",tmp,WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_LEFT,x,y,w,h,hwnd,NULL,hinst,NULL);
		SendMessage(htmp,WM_SETFONT,(WPARAM)hobj,0);
		g_controls[i].hbutton=htmp;
		GetWindowRect(htmp,&rect);
		y+=rect.bottom-rect.top;
	}
	GetClientRect(hwnd,&crect);
	if(crect.bottom<y){
		int delta=y-crect.bottom+10;
		RECT wrect={0};
		int w,h;
		GetWindowRect(hwnd,&wrect);
		w=wrect.right-wrect.left;
		h=wrect.bottom-wrect.top;
		SetWindowPos(hwnd,NULL,wrect.left,wrect.top,w,h+delta,SWP_NOZORDER);
	}
	ReleaseDC(hwnd,hdc);
}

void move_console(HWND hwnd)
{
	HWND hcon=GetConsoleWindow();
	RECT wrect,crect;
	GetWindowRect(hwnd,&wrect);
	GetWindowRect(hcon,&crect);
	SetWindowPos(hcon,0,wrect.right,crect.top,0,0,SWP_NOSIZE|SWP_SHOWWINDOW|SWP_NOZORDER|SWP_NOACTIVATE);
}

int CALLBACK  dlg(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	switch(msg){
	case WM_INITDIALOG:
		{
			save_original();
			construct_window(hwnd);
			move_console(hwnd);
			SetWindowText(GetDlgItem(hwnd,IDC_CUSTOM),"0");
			SetFocus(g_controls[0].hedit);
		}
		break;
	case WM_GETDLGCODE:
		break;
	case WM_SIZE:
		break;
	case WM_SIZING:
		break;
	case WM_DRAWITEM:
		{
			DRAWITEMSTRUCT *di=(LPDRAWITEMSTRUCT)lparam;
			RECT rect={0};
			HRGN hreg;
			COLORREF c=0;
			HBRUSH hbr=0;
			int i;
			HDC hdc=di->hDC;

			for(i=0;i<MAX_COLORS;i++){
				if(g_controls[i].hcolor==di->hwndItem){
					c=g_controls[i].color;
					break;
				}
			}
			GetClientRect(di->hwndItem,&rect);
	        hreg = CreateRectRgnIndirect(&rect);
			hbr = CreateSolidBrush(c);
			FillRgn(hdc, hreg, hbr);
			DeleteObject(hreg);
			DeleteObject(hbr);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wparam)){
		case IDCANCEL:
			EndDialog(hwnd,0);
			break;
		case IDOK:
			set_windows_colors();
			break;
		case IDC_RELOAD:
			if(HIWORD(wparam)==BN_CLICKED){
				get_color_values();
				set_color_hex_values();
				invalidate_color_buttons();
			}
			break;
		case IDC_REVERT:
			if(HIWORD(wparam)==BN_CLICKED){
				restore_color_list();
				set_color_hex_values();
				invalidate_color_buttons();
				set_windows_colors();
			}
			break;
		case IDC_LIVE:
			if(HIWORD(wparam)==BN_CLICKED){
				DWORD val;
				HWND hcheck=(HWND)lparam;
				val=SendMessage(hcheck,BM_GETCHECK,0,0);
				g_live_update=0;
				if(BST_CHECKED==val){
					g_live_update=1;
				}
				printf("live=%i\n",g_live_update);
			}
			break;
		case IDC_SAVE:
			if(HIWORD(wparam)==BN_CLICKED){
				char tmp[40]={0};
				int num;
				GetDlgItemText(hwnd,IDC_CUSTOM,tmp,sizeof(tmp));
				set_windows_colors();
				num=strtoul(tmp,0,10);
				save_colors(num);
			}
			break;
		case IDC_LOAD1:
		case IDC_LOAD2:
		case IDC_LOAD3:
			if(HIWORD(wparam)==BN_CLICKED){
				int i;
				for(i=0;i<MAX_COLORS;i++){
					int *ptr=def_colors;
					if(IDC_LOAD2==LOWORD(wparam)){
						ptr=def_contrast;
					}else if(IDC_LOAD3==LOWORD(wparam)){
						ptr=alt_contrast;
					}
					g_controls[i].color=ptr[i];
				}
				set_color_hex_values();
				set_windows_colors();
				invalidate_color_buttons();
			}
			break;
		}
		break;
	}
	return 0;
}


void show_gui()
{
	DialogBoxParam(0,(LPSTR)IDD_DIALOG1,0,dlg,(LPARAM)0);
	exit(0);
}

int main(int argc,char *argv[])
{
	int custom=-1;
	
	print_cmd();
	if(have_arg("-?",argc,argv)
		|| have_arg("-h",argc,argv)
		|| have_arg("-help",argc,argv)
		|| (1==argc)){
		exit(0);
	}
	set_ini_path();
	printf("ini file:%s\n",ini_file);
	if(have_arg("-gui",argc,argv)){
		show_gui();
		exit(0);
	}
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
	if(have_arg("-load1",argc,argv)){
		printf("loading set 1\n");
		load_set(1);
		exit(0);
	}
	else if(have_arg("-load2",argc,argv)){
		printf("loading set 2\n");
		load_set(2);
		exit(0);
	}
	else if(have_arg("-load3",argc,argv)){
		printf("loading set 3\n");
		load_set(3);
		exit(0);
	}
	else if(have_arg("-load",argc,argv)){
		if(custom < 0){
			printf("loading default colors\n");
			load_default();
			exit(0);
		}
		else{
			printf("loading custom %i\n",custom);
			load_colors(custom);
		}
	}
	if(have_arg("-keys",argc,argv)){
		set_keys();
	}
}



