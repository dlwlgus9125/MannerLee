#ifndef __DLG_SETMOTIONNAME_H__
#define __DLG_SETMOTIONNAME_H__

#include <Windows.h>
#include "data.h"
#include "ToolFuncTions.h"

LRESULT CALLBACK Proc_SetMotionName(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void DoMoal_SetMotionName(HINSTANCE a_hinst, HWND a_hWnd, char *a_buf);
int GetNumberOFFrames( MotionSet * a_target);

#endif // __DLG_SETMOTIONNAME_H__