#include <windows.h>
#include <commdlg.h>
#include <fstream>
#include <string>
#include <tchar.h>
#include <sstream>
#include <windef.h>
#include <bits/stdc++.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
// 窗口过程函数声明
// 全局变量
RECT rect1,rect2;
int ky_dn=-1,press=-1,printlast;
bool REDRAW;
std::vector <std::string> GeneratedMMDZ; 
std::vector <std::string> _v1,_v2,_v3,_v4; 
std::vector <std::string> v1,v2,v3,v4;
std::map<std::string,bool> mp;
int n_1,n_2,n_3,n_4;
int sum,r,slp,tt,tt1;
std::string GenerateMMDZ() {//By mmdz & HuChai
	//v1是人物，v2是地点，v3是事件,v4是时间 
//	return "生成失败"; 
	std::string v_1,v_2,v_3,v_4,v_1_2;
	int MMDZ=0;
	if(!v1.size()||!v2.size()||!v3.size()||!v4.size()) return "生成失败";
	v_1=v1[rand()%v1.size()];v_1_2=v1[rand()%v1.size()];
	v_2=v2[rand()%v2.size()];
	v_3=v3[rand()%v3.size()];
	v_4=v4[rand()%v4.size()];
	while(v_1==v_1_2&&v1.size()>1)	v_1=v1[rand()%v1.size()];
	std::string mmdz=v_4+"，"+v_1+"和"+v_1_2+"在"+v_2+v_3;
	while(mp.count(mmdz))	
	{
		v_1=v1[rand()%v1.size()];v_1_2=v1[rand()%v1.size()];
		v_2=v2[rand()%v2.size()];
		v_3=v3[rand()%v3.size()];
		v_4=v4[rand()%v4.size()];
		while(v_1==v_1_2&&v1.size()>1)	v_1=v1[rand()%v1.size()];
		mmdz=v_4+"，"+v_1+"和"+v_1_2+"在"+v_2+v_3;
		MMDZ++;
		if(MMDZ>100) return "生成失败";
	}
	mp[mmdz]=1;
	return mmdz;
}
void INIT(std::string x) {
	_v1.clear(); _v2.clear(); _v3.clear(); _v4.clear();
    v1.clear(); v2.clear(); v3.clear(); v4.clear();
    n_1 = n_2 = n_3 = n_4 = 0;
	int __t=0,_last=0; 
	std::string _q="";
	r=0,sum=0;
	for(int i=0;i<x.size();i++) {
		if(i==x.size()-1||x[i]==10) {
			_q=x.substr(_last,i-_last);
			_last=i+1;
			if(__t==0) {
				for(int j=0;j<_q.size();j++) {
					if(_q[j]>='0'&&_q[j]<='9') {
						sum=sum*10+_q[j]-'0';
					}
					if(j==_q.size()-1||((_q[j]>='0'&&_q[j]<='9')&&!(_q[j+1]>='0'&&_q[j+1]<='9')))  {
						++r;
						if(r==1) n_1=sum;
						else if(r==2) n_2=sum;
						else if(r==3) n_3=sum;
						else n_4=sum;
						sum=0;
					}
				}
//				注意不要用sscanf,否则会导致崩溃 
//				sscanf(_q.c_str(),"%lld%lld%lld%lld",&n_1,&n_2,&n_3,&n_4);
			} else if(__t>=1&&__t<=n_1) {
				_v1.push_back(_q);
			} else if(__t>=n_1+1&&__t<=n_1+n_2) {
				_v2.push_back(_q);
			} else if(__t>=n_1+n_2+1&&__t<=n_1+n_2+n_3) {
				_v3.push_back(_q);
			} else if(__t>=n_1+n_2+n_3+1&&__t<=n_1+n_2+n_3+n_4) {
				_v4.push_back(_q);
			} else {
				for(int j=0;j<n_1;j++) if(_q[j]=='1') v1.push_back(_v1[j]);
				for(int j=0;j<n_2;j++) if(_q[n_1+j]=='1') v2.push_back(_v2[j]);
				for(int j=0;j<n_3;j++) if(_q[n_1+n_2+j]=='1') v3.push_back(_v3[j]);
				for(int j=0;j<n_4;j++) if(_q[n_1+n_2+n_3+j]=='1') v4.push_back(_v4[j]);
			}
			__t++;
		}
	}
	return;
}
int checkButton() {
	if(KEY_DOWN(VK_NUMPAD0)||KEY_DOWN(0x30)) return 0;
	if(KEY_DOWN(VK_NUMPAD1)||KEY_DOWN(0x31)) return 1;
	if(KEY_DOWN(VK_NUMPAD2)||KEY_DOWN(0x32)) return 2;
	if(KEY_DOWN(VK_NUMPAD3)||KEY_DOWN(0x33)) return 3;
	if(KEY_DOWN(VK_NUMPAD4)||KEY_DOWN(0x34)) return 4;
	if(KEY_DOWN(VK_NUMPAD5)||KEY_DOWN(0x35)) return 5;
	if(KEY_DOWN(VK_NUMPAD6)||KEY_DOWN(0x36)) return 6;
	if(KEY_DOWN(VK_NUMPAD7)||KEY_DOWN(0x37)) return 7;
	if(KEY_DOWN(VK_NUMPAD8)||KEY_DOWN(0x38)) return 8;
	if(KEY_DOWN(VK_NUMPAD9)||KEY_DOWN(0x39)) return 9;
	if(KEY_DOWN(VK_BACK)) return 10;
	if(KEY_DOWN(VK_UP)) return 11;
	if(KEY_DOWN(VK_DOWN)) return 12;
	return -1;
}
std::string x1;
HWND g_hEdit; // 输入框句柄
HWND g_hDlg;  // 对话框句柄
bool TIMES,SPEED,PRINT,f1,f2,f3,OPF;
int g1,g2,g3,ts=20,sd=20,nts,nsd,k;
std::string ITS(int x) {
	if(x==0) return "0";
	std::string ans="";
	while(x>0) {
		ans=char((x%10)+'0')+ans;
		x/=10;
	}
	return ans;
}
std::string ITS1(int x) {
	if(x==0) return "";
	std::string ans="";
	while(x>0) {
		ans=char((x%10)+'0')+ans;
		x/=10;
	}
	return ans;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 注册窗口类
    const char CLASS_NAME[] = "Sample Window Class";
//    mp[0]=mp[1]=mp[2]=mp[3]=mp[4]=mp[5]=mp[6]=mp[7]=mp[8]=mp[9]=mp[10]=-2e9;
    rect1.left=10;
	rect1.top=50;
	rect1.right=280;
	rect1.bottom=100;
	rect2.left=10;
	rect2.top=50;
	rect2.right=600;
	rect2.bottom=800;
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    
    RegisterClass(&wc);
    
    // 创建窗口
    HWND hwnd = CreateWindow(
        CLASS_NAME,
        "狗屁不通生成器-HuChai-v1.0.0",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1000, 650,
        NULL, NULL, hInstance, NULL
    );
    
    if (hwnd == NULL) {
        return 0;
    }
    
    // 创建“导入文件”按钮
    CreateWindow(
        "BUTTON", "导入配置",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        0,0,120,30,
//        150, 100, 100, 30,
        hwnd, (HMENU)1, hInstance, NULL
    );
    CreateWindow(
            "BUTTON", "输出句数",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            140 ,0, 120, 30,
            hwnd, (HMENU)2, GetModuleHandle(NULL), NULL
    );
    CreateWindow(
            "BUTTON", "设置速度",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            280 ,0, 120, 30,
            hwnd, (HMENU)3, GetModuleHandle(NULL), NULL
    );
    CreateWindow(
            "BUTTON", "开始输出",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            420 ,0, 120, 30,
            hwnd, (HMENU)8, GetModuleHandle(NULL), NULL
    );
    HWND hwnd1,hwnd2,hwnd3,hwnd4,hwnd5;
    ShowWindow(hwnd, nCmdShow);
    
    // 消息循环
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
    	int ckb=checkButton();
    	if(ckb!=ky_dn) {
    		press=ckb;
    		ky_dn=ckb;
    	}
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if(TIMES) {
        	if(f1==0) {
        		hwnd1=CreateWindow(
          	 		"BUTTON", "确定",
           	 		WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
            		300 ,60, 80, 30,
            		hwnd, (HMENU)4, GetModuleHandle(NULL), NULL
   				);
   				hwnd2=CreateWindow(
          	 		"BUTTON", "取消",
           	 		WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
            		420 ,60, 80, 30,
            		hwnd, (HMENU)5, GetModuleHandle(NULL), NULL
   				);
   				f1=1;
   				ShowWindow(hwnd1, nCmdShow);
   				ShowWindow(hwnd2, nCmdShow);
   				
        	}
        }
        if(!TIMES&&f1==1) {
        	DestroyWindow(hwnd1);
        	DestroyWindow(hwnd2);
			f1=0;
        }
        
        if(SPEED) {
        	if(f2==0) {
        		hwnd3=CreateWindow(
          	 		"BUTTON", "确定",
           	 		WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
            		300 ,60, 80, 30,
            		hwnd, (HMENU)6, GetModuleHandle(NULL), NULL
   				);
   				hwnd4=CreateWindow(
          	 		"BUTTON", "取消",
           	 		WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
            		420 ,60, 80, 30,
            		hwnd, (HMENU)7, GetModuleHandle(NULL), NULL
   				);
   				f2=1;
   				ShowWindow(hwnd3, nCmdShow);
   				ShowWindow(hwnd4, nCmdShow);
        	}
        }
        if(PRINT) {
        	if(f3==0) {
        		hwnd5=CreateWindow(
          	 		"BUTTON", "退出",
           	 		WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
            		300 ,270, 80, 30,
            		hwnd, (HMENU)9, GetModuleHandle(NULL), NULL
   				);
   				f3=1;
   				ShowWindow(hwnd5,nCmdShow);
			}
			int xt=clock();
			if(xt-printlast>=slp&&tt<ts) {
				g3=0;
				printlast=xt;
				tt++;
				if(tt>=10) tt1++;
				InvalidateRect(hwnd,&rect2,true); UpdateWindow(hwnd);
			} 
		}
		if(!PRINT&&f3==1) {
			DestroyWindow(hwnd5);
			f3=0; 
			InvalidateRect(hwnd,&rect2,true); UpdateWindow(hwnd);
		} 
        if(!SPEED&&f2==1) {
        	DestroyWindow(hwnd3);
        	DestroyWindow(hwnd4);
			f2=0;
        }
        if(TIMES) {
			if(press>=0&&press<=9) {
				if(nts>0||(nts==0&&press!=0)) {
					if(nts*10+press<=1000) nts=nts*10+press;
					else MessageBox(hwnd,"数字过大","Error",MB_OK | MB_ICONERROR);
				}
				REDRAW=1;
				press=-1;
				InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
			} else if(press==10){
				if(nts>0) {
					nts=nts/10;
				}
				REDRAW=1;
				press=-1;
				InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
			}
        }
        else if(SPEED) {
			if(press>=0&&press<=9) {
				if(nsd>0||(nsd==0&&press!=0)) {
					if(nsd*10+press<=1000) nsd=nsd*10+press;
					else MessageBox(hwnd,"数字过大","Error",MB_OK | MB_ICONERROR);
				}
				REDRAW=1;
				press=-1;
				InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
			} else if(press==10){
				if(nsd>0) {
					nsd=nsd/10;
				}
				REDRAW=1;
				press=-1;
				InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
			}
        }
	}
    return 0;
}

// 窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) { // 按钮 ID 为 1
                // 打开文件对话框
                OPENFILENAME ofn = { 0 };
                char szFile[260] = { 0 }; // 文件路径缓冲区
                
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = "配置文件 (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                
                if (GetOpenFileName(&ofn)) {
                    // 读取文件内容
                    std::ifstream file(szFile);
                    if (file.is_open()) {
                    	OPF=1;
                    	InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
                        std::stringstream buffer;
                        buffer << file.rdbuf();
                        std::string content = buffer.str();
                        file.close();
                        INIT(content); 
                        // 显示文件内容（使用消息框）
                    } else {
                        MessageBox(hwnd, "打开配置失败!", "Error", MB_OK | MB_ICONERROR);
                    }
                }
            } else if (LOWORD(wParam) == 2) { // “输入数字”按钮
            	if(SPEED||PRINT) MessageBox(hwnd, "请先关闭已经打开的功能!", "Error", MB_OK | MB_ICONERROR);
            	else if(TIMES) MessageBox(hwnd, "已打开!", "Error", MB_OK | MB_ICONERROR);
            	else {
            		TIMES=1;
            		nts=0;
            	} 
            } else if(LOWORD(wParam)==4&&TIMES) {
            	if(nts>=1&&nts<=1000) ts=nts;
            	else MessageBox(hwnd,"无效,次数须在1~1000之间","Error",MB_OK | MB_ICONERROR);
            	TIMES=0;
            } else if(LOWORD(wParam)==5&&TIMES) {
            	TIMES=0;
            } else if (LOWORD(wParam) == 3) { // “设置速度”按钮
            	if(TIMES||PRINT) MessageBox(hwnd, "请先关闭已经打开的功能!", "Error", MB_OK | MB_ICONERROR);
            	else if(SPEED) MessageBox(hwnd, "已打开!", "Error", MB_OK | MB_ICONERROR);
            	else {
            		SPEED=1;
            		nsd=0;
            	}
            } else if(LOWORD(wParam)==6&&SPEED) {
            	if(nsd>=1&&nsd<=1000) sd=nsd;
            	else MessageBox(hwnd,"无效,次数须在1~1000之间","Error",MB_OK | MB_ICONERROR);
            	SPEED=0;
            } else if(LOWORD(wParam)==7&&SPEED) {
            	SPEED=0;
            } else if(LOWORD(wParam)==8) {//开始输出 
            	tt=0;
            	tt1=0;
            	slp=20+1000/sqrt(sd*1.0);
//            	MessageBox(hwnd,ITS(slp).c_str(),"Error",MB_OK | MB_ICONERROR);
            	if(TIMES||SPEED) MessageBox(hwnd,"请先关闭已经打开的功能!","Error",MB_OK | MB_ICONERROR);
            	else if(PRINT) MessageBox(hwnd, "已打开!", "Error", MB_OK | MB_ICONERROR);
            	else if(!OPF) MessageBox(hwnd, "未导入配置文件!", "Error", MB_OK | MB_ICONERROR);
            	else {
            		PRINT=1,GeneratedMMDZ.clear();
            		srand(time(0));
            		while(GeneratedMMDZ.size()<ts) {
						GeneratedMMDZ.push_back(GenerateMMDZ());
					}
				}
//            	InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
            } else if(LOWORD(wParam)==9&&PRINT) {
            	PRINT=0;
//            	InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
            }
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
            
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            if((!TIMES)&&(!SPEED)&&(!PRINT)) {
            	x1="次数:"+ITS(ts)+" 速度:"+ITS(sd)+" 配置"+(OPF?"已":"未")+"导入";
            	const char* cstr = x1.c_str();
            	if(k) g1=0;
            	k=0;
            	if(g1==10) g1=0;
				if(g1==0) {
					InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
				}
				g1++;
				TextOut(hdc, 10, 70, TEXT(cstr), lstrlen(TEXT(cstr)));
			}
			else if((!PRINT)&&(SPEED||TIMES)) {
				x1="改成:"+ITS1(TIMES?nts:nsd);
				if(k==0||k==2) {
					InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
					g2=0;
				}
				k=1;
				if(REDRAW) {
					InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
					REDRAW=0;
				}
				const char* cstr = x1.c_str();
				if(g2==10) g2=0;
				if(g2==0) {
					InvalidateRect(hwnd,&rect1,true); UpdateWindow(hwnd);
				}
				g2++;
				TextOut(hdc, 10, 70, TEXT(cstr), lstrlen(TEXT(cstr)));
			} else if(PRINT) {
				if(k==0||k==1) {
					g3=0;
				}
				
//				MessageBox(hwnd, ITS(k).c_str(), "Error", MB_OK | MB_ICONERROR);
				k=2;
				if(g3==10) g3=0;
				if(g3==0) {
					InvalidateRect(hwnd,&rect2,true); UpdateWindow(hwnd);
				}
				g3++;
				
//				MessageBox(hwnd, cstr1, "Error", MB_OK | MB_ICONERROR);
//				TextOut(hdc, 10, 70, TEXT("mmdz"), lstrlen(TEXT("mmdz")));
				for(int i=tt1;i<=tt1+9;i++) {
					if(i<GeneratedMMDZ.size()) TextOut(hdc, 10, 70+20*(i-tt1), TEXT(GeneratedMMDZ[i].c_str()), lstrlen(TEXT(GeneratedMMDZ[i].c_str())));
				}
//				if(GeneratedMMDZ.size()) TextOut(hdc, 10, 70, TEXT(cstr1), lstrlen(TEXT(cstr1)));
			}
            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
