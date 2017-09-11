#include "Dig_SetMotionName.h"
#include "resource.h"

char *g_SetMotionNAmeBuf;
LRESULT CALLBACK Proc_SetMotionName(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		{
			HWND namebox = GetDlgItem(hDlg, IDC_NAME);
			SetWindowText(namebox, g_SetMotionNAmeBuf);
		}
		return TRUE;
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDOK)
			{
				HWND namebox = GetDlgItem(hDlg, IDC_NAME);
				GetWindowText(namebox, g_SetMotionNAmeBuf,1024);
			}
			if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg,LOWORD(wParam));
				return TRUE;
			}
			break;

		}
	}
	return FALSE;
}

void DoMoal_SetMotionName(HINSTANCE a_hInst, HWND a_hWnd, char *a_buf)
{
	g_SetMotionNAmeBuf = a_buf;
	DialogBox(a_hInst,(LPCTSTR)IDC_NAME, a_hWnd,(DLGPROC)Proc_SetMotionName);
}

void SaveData( Data *a_target, const char *a_filename)
{
	FILE *f;
	SingleFrame *sf;
	int i;
	f = fopen(a_filename,"wt");
	if( f == NULL)
		return;
	fprintf(f,"원본 그림의 이름: %s\n", a_target->m_source_picture.m_name);

	fprintf(f,"동작의 이름 : %s\n", a_target->m_motion_set.m_name);
	fprintf(f,"동작의 길이: %d\n", GetNumberOFFrames(&(a_target->m_motion_set)));

	sf = a_target->m_motion_set.m_frames.m_next;
	i = 0;

	while(sf)
	{
		fprintf(f,"# %d\n",i);
		fprintf(f,"범위 : ( %d, %d) - (%d , %d)\n"
			,sf->m_rect.left
			,sf->m_rect.top
			,sf->m_rect.right
			,sf->m_rect.bottom);
		fprintf(f,"중심위치 : ( %d, %d )\n"
			,sf->m_hotspot.x
			,sf->m_hotspot.y);
		fprintf(f,"지속시간 : %d\n"
			,sf->m_duration);
		i++;
		sf = sf->m_next;
	}
	fclose(f);
}

void LoadData( Data * a_target, const char *a_filename)
{
	FILE * f;
	SingleFrame *sf;
	int i, ni, dummy;
	char buf[1024];

	f = fopen( a_filename, "rt");

	if( f == NULL)
		return;

	fscanf(f,"원본 그림의 이름 : %s\n",buf);
	LoadSourcePicture(&(a_target->m_source_picture),buf);

	fscanf(f,"동작의 이름 : %s\n", a_target->m_motion_set.m_name);
	fscanf(f,"동작의 길이 : %d\n", &ni);

	for( i = 0; i < ni; i++)
	{
		sf = AddSingleFrame(&(a_target->m_motion_set));
		fscanf(f," # %d\n", &dummy);

		fprintf(f,"범위 : ( %d, %d) - (%d , %d)\n"
			,sf->m_rect.left
			,sf->m_rect.top
			,sf->m_rect.right
			,sf->m_rect.bottom);
		fprintf(f,"중심위치 : ( %d, %d )\n"
			,sf->m_hotspot.x
			,sf->m_hotspot.y);
		fprintf(f,"지속시간 : %d\n"
			,sf->m_duration);
	}
	fclose(f);
}

int GetNumberOFFrames( MotionSet * a_target)
{
	SingleFrame * sf = a_target->m_frames.m_next;
	int rv = 0;
	while(sf)
	{
		sf = sf->m_next;
		rv++;
	}
	return rv;
}