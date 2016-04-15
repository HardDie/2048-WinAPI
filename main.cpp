#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include <cstdlib>

using namespace std;
bool k = false;
unsigned long int score(0);

class cell
{
private:
	int a;
public:
	cell(void)
	{
		a = 0;
	};
	void next_step(void)
	{
		if (a != 11)
			a++;
	}
	void null_cell(void)
	{
		a = 0;
	}
	int get_value(void)
	{
		return a;
	}
	int get_score(void)
	{
		switch(a)
		{
		case 0:
			return 0;
			break;
		case 1:
			return 2;
			break;
		case 2:
			return 4;
			break;
		case 3:
			return 8;
			break;
		case 4:
			return 16;
			break;
		case 5:
			return 32;
			break;
		case 6:
			return 64;
			break;
		case 7:
			return 128;
			break;
		case 8:
			return 256;
			break;
		case 9:
			return 512;
			break;
		case 10:
			return 1024;
			break;
		case 11:
			return 2048;
			break;
		}
	}
	void set_value(int x)
	{
		if (x >=0 && x<=11)
			a = x;
	}
	~cell(void){};
};

class square
{
private:
	cell table[4][4];
public:
	square(void)
	{
		/*table[0][0].set_value(1);
		table[0][1].set_value(2);
		table[0][2].set_value(3);
		table[0][3].set_value(4);
		table[1][0].set_value(5);
		table[1][1].set_value(6);
		table[1][2].set_value(7);
		table[1][3].set_value(8);
		table[2][0].set_value(9);
		table[2][1].set_value(10);
		table[2][2].set_value(11);*/
	};
	void output_gametable(void)
	{
		//system("cls");
		//cout << "---------------------\n";
		//for (int i = 0; i < 4; i++)
		//{
		//	cout << "*    *    *    *    *\n";
		//	cout << "*    *    *    *    *\n";
		//	cout << "*    *    *    *    *\n";
		//	cout << "---------------------\n";
		//}

		//hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		//for (int i = 0; i < 4; i++)
		//	for (int j = 0; j < 4; j++)
		//	{
		//		cPos.Y = 2 + 4*i; // координата консоли по У
		//		cPos.X = 1 + 5*j;  // координата консоли по Х  
		//		SetConsoleCursorPosition(hCon, cPos); // Установка курсора в положение (x,y)
		//		cout << table[i][j].get_number();
		//	}

			
	}
	bool spawn(void)
	{
		srand(time(NULL));
		int k(0);
		bool win(false);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (table[i][j].get_value() == 0)
					k++;
			}
		if (k == 0)
			return false;

		int c = rand()%500 + 1;

		while (true)
		{
			int a, b;
			a = rand()%4; b = rand()%4;
			if (table[a][b].get_value() == 0)
			{
				if (c == 500)
					table[a][b].set_value(2);
				else
					table[a][b].next_step();
				break;
			}
		}
		return true;
	};
	bool step_right()
	{
		int temp,k;
		bool G(false);
		for (int i = 0; i < 4; i++)
			do
			{
				temp = 0;
				for (int j = 0; j < 3; j++)
					if (table[i][j].get_value() && !table[i][j+1].get_value())
					{
						k = table[i][j].get_value();
						table[i][j].set_value(table[i][j+1].get_value());
						table[i][j+1].set_value(k);
						temp++;
					}
				if (temp)
					G = true;
			}while(temp);
		if (G)
			return true;
		else return false;
	}
	bool merger_right()
	{
		bool G(false);
		for (int i = 0; i < 4; i++)
			for (int j = 3; j > 0; j--)
				if(table[i][j].get_value() == table[i][j-1].get_value() && table[i][j].get_value() != 0)
				{
					G = true;
					score += table[i][j].get_score()+table[i][j-1].get_score();
					table[i][j].next_step();
					table[i][j-1].set_value(0);
				}
		if(G)
			return true;
		else return false;
	}
	bool step_left()
	{
		int temp,k;
		bool G(false);
		for (int i = 0; i < 4; i++)
			do
			{
				temp = 0;
				for (int j = 0; j < 3; j++)
					if (!table[i][j].get_value() && table[i][j+1].get_value())
					{
						k = table[i][j].get_value();
						table[i][j].set_value(table[i][j+1].get_value());
						table[i][j+1].set_value(k);
						temp++;
					}
				if (temp)
					G = true;
			}while(temp);
		if (G)
			return true;
		else return false;
	}
	bool merger_left()
	{
		bool G(false);
		for (int i = 0; i < 4; i++)
			for (int j = 1; j < 4; j++)
				if(table[i][j].get_value() == table[i][j-1].get_value() && table[i][j].get_value() != 0)
				{
					G = true;
					score += table[i][j].get_score()+table[i][j-1].get_score();
					table[i][j-1].next_step();
					table[i][j].set_value(0);
				}
		if(G)
			return true;
		else return false;
	}
	bool step_down()
	{
		int temp,k;
		bool G(false);
		for (int i = 0; i < 4; i++)
			do
			{
				temp = 0;
				for (int j = 0; j < 3; j++)
					if (table[j][i].get_value() && !table[j+1][i].get_value())
					{
						k = table[j][i].get_value();
						table[j][i].set_value(table[j+1][i].get_value());
						table[j+1][i].set_value(k);
						temp++;
					}
				if (temp)
					G = true;
			}while(temp);
		if (G)
			return true;
		else return false;
	}
	bool merger_down()
	{
		bool G(false);
		for (int i = 0; i < 4; i++)
			for (int j = 3; j > 0; j--)
				if(table[j][i].get_value() == table[j-1][i].get_value() && table[j][i].get_value() != 0)
				{
					G = true;
					score += table[j][i].get_score()+table[j-1][i].get_score();
					table[j][i].next_step();
					table[j-1][i].set_value(0);
				}
		if(G)
			return true;
		else return false;
	}
	bool step_up()
	{
		int temp,k;
		bool G(false);
		for (int i = 0; i < 4; i++)
			do
			{
				temp = 0;
				for (int j = 0; j < 3; j++)
					if (!table[j][i].get_value() && table[j+1][i].get_value())
					{
						k = table[j][i].get_value();
						table[j][i].set_value(table[j+1][i].get_value());
						table[j+1][i].set_value(k);
						temp++;
					}
				if (temp)
					G = true;
			}while(temp);
		if (G)
			return true;
		else return false;
	}
	bool merger_up()
	{
		bool G(false);
		for (int i = 0; i < 4; i++)
			for (int j = 1; j < 4; j++)
				if(table[j][i].get_value() == table[j-1][i].get_value() && table[j][i].get_value() != 0)
				{
					G = true;
					score += table[j][j].get_score()+table[j-1][j].get_score();
					table[j-1][i].next_step();
					table[j][i].set_value(0);
				}
		if(G)
			return true;
		else return false;
	}
	cell get_element(int a, int b)
	{
		return table[a][b];
	}
	~square(void){};
};
square game;
inline void step(const char& p)
{
	bool a,b;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (game.get_element(i,j).get_value() == 11)
			{
				k = true;
				return;
			}
		}
	if (p == 'd' || p == 'D' || p == 'в' || p == 'В')
	{
			a = game.step_right();
			b = game.merger_right();
			game.step_right();
			if (a || b) game.spawn();
	}
	if (p == 'a' || p == 'A' || p == 'ф' || p == 'Ф')
	{
			a = game.step_left();
			b = game.merger_left();
			game.step_left();
			if (a || b) game.spawn();
	}
	if (p == 's' || p == 'S' || p == 'ы' || p == 'Ы')
	{
			a = game.step_down();
			b = game.merger_down();
			game.step_down();
			if (a || b) game.spawn();
	}
	if (p == 'w' || p == 'W' || p == 'ц' || p == 'Ц')
	{
			a = game.step_up();
			b = game.merger_up();
			game.step_up();
			if (a || b) game.spawn();
	}
}

inline void Paint_GameTable(HDC, int, int);



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	game.spawn();
	game.spawn();

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	if(!RegisterClass(&wc))
		return 0;
	hWnd = CreateWindow(WinName, _T("2048!"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 610, 640, HWND_DESKTOP, NULL, This, NULL);
	ShowWindow(hWnd, mode);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static char p;
	static int sx,sy;
	TCHAR s[10];
	static HFONT newFont = CreateFont(20, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0 ,0 , _T("Arial"));
	static HFONT newFont2 = CreateFont(40, 20, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0 ,0 , _T("Arial"));
	switch(message)
	{
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_CHAR:
		p = (TCHAR)wParam;
		step(p);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		if (k)
		{
			SelectObject(hdc, newFont2);
			Paint_GameTable(hdc, sx, sy);
			SelectObject(hdc, newFont);
			wsprintf(s, "%d", score);
			TextOut(hdc, 10, 50, "Score: ", 7);
			TextOut(hdc, 70, 50, s, _tcslen(s));
			TextOut(hdc, 60, 540, "Congratulations!!! You win!!! Now you must suck my DICK!!!", 58);
		}
		else
		{
			SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			/*COLORREF WINAPI SetTextColor(hdc, RGB(0,0,0));*/
			SelectObject(hdc, newFont2);
			Paint_GameTable(hdc, sx, sy);
			SelectObject(hdc, newFont);
			wsprintf(s, "%d", score);
			TextOut(hdc, 10, 50, "Score: ", 7);
			TextOut(hdc, 70, 50, s, _tcslen(s));
		}
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

inline void OutNumber(HDC hdc, int x, int y, int n)
{
	switch(n)
	{
		case 0:
			break;
		case 1:
			TextOut(hdc,x+40,y+30,"2",1);
			break;
		case 2:
			TextOut(hdc,x+40,y+30,"4",1);
			break;
		case 3:
			TextOut(hdc,x+40,y+30,"8",1);
			break;
		case 4:
			TextOut(hdc,x+28,y+30,"16",2);
			break;
		case 5:
			TextOut(hdc,x+28,y+30,"32",2);
			break;
		case 6:
			TextOut(hdc,x+28,y+30,"64",2);
			break;
		case 7:
			TextOut(hdc,x+18,y+30,"128",3);
			break;
		case 8:
			TextOut(hdc,x+18,y+30,"256",3);
			break;
		case 9:
			TextOut(hdc,x+17,y+30,"512",3);
			break;
		case 10:
			TextOut(hdc,x+8,y+30,"1024",4);
			break;
		case 11:
			TextOut(hdc,x+8,y+30,"2048",4);
			break;
	}

}
inline void SetColor(HDC hdc, int N)
{
	static HBRUSH hbrush1 = CreateSolidBrush(RGB(23,186,186));		// 23,186,186  - 2
	static HBRUSH hbrush2 = CreateSolidBrush(RGB(43,181,94));		// 43,181,94   - 4
	static HBRUSH hbrush3 = CreateSolidBrush(RGB(151,191,80));		// 151,191,80  - 8
	static HBRUSH hbrush4 = CreateSolidBrush(RGB(201,200,75));		// 201,200,75  - 16
	static HBRUSH hbrush5 = CreateSolidBrush(RGB(216,163,49));		// 216,163,49  - 32
	static HBRUSH hbrush6 = CreateSolidBrush(RGB(219,112,54));		// 219,112,54  - 64
	static HBRUSH hbrush7 = CreateSolidBrush(RGB(209,84,78));		// 209,84,78   - 128
	static HBRUSH hbrush8 = CreateSolidBrush(RGB(200,98,141));		// 200,98,141  - 256
	static HBRUSH hbrush9 = CreateSolidBrush(RGB(186,92,178));		// 186,92,178  - 512
	static HBRUSH hbrush10 = CreateSolidBrush(RGB(154,108,221));	// 154,108,221 - 1024
	static HBRUSH hbrush11 = CreateSolidBrush(RGB(75,150,219));	// 75,150,219  - 2048
	switch(N)
	{
	case 0:
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		break;
	case 1:
		SelectObject(hdc, hbrush1);
		break;
	case 2:
		SelectObject(hdc, hbrush2);
		break;
	case 3:
		SelectObject(hdc, hbrush3);
		break;
	case 4:
		SelectObject(hdc, hbrush4);
		break;
	case 5:
		SelectObject(hdc, hbrush5);
		break;
	case 6:
		SelectObject(hdc, hbrush6);
		break;
	case 7:
		SelectObject(hdc, hbrush7);
		break;
	case 8:
		SelectObject(hdc, hbrush8);
		break;
	case 9:
		SelectObject(hdc, hbrush9);
		break;
	case 10:
		SelectObject(hdc, hbrush10);
		break;
	case 11:
		SelectObject(hdc, hbrush11);
		break;
	}
}
inline void Paint_GameTable(HDC hdc, int sx, int sy)
{
	static HBRUSH hbrush = CreateSolidBrush(RGB(220,210,189));
	SelectObject(hdc, hbrush);
	Rectangle(hdc,0,0,sx,sy);
	SetBkMode(hdc, TRANSPARENT);
	// First string
	SetColor(hdc, (int)game.get_element(0,0).get_value()); Rectangle(hdc,100,100,200,200);
	SetColor(hdc, (int)game.get_element(0,1).get_value()); Rectangle(hdc,199,100,300,200);
	SetColor(hdc, (int)game.get_element(0,2).get_value()); Rectangle(hdc,299,100,400,200);
	SetColor(hdc, (int)game.get_element(0,3).get_value()); Rectangle(hdc,399,100,500,200);
	// Second string
	SetColor(hdc, game.get_element(1,0).get_value()); Rectangle(hdc,100,199,200,300);
	SetColor(hdc, game.get_element(1,1).get_value()); Rectangle(hdc,199,199,300,300);
	SetColor(hdc, game.get_element(1,2).get_value()); Rectangle(hdc,299,199,400,300);
	SetColor(hdc, game.get_element(1,3).get_value()); Rectangle(hdc,399,199,500,300);
	// Third string
	SetColor(hdc, game.get_element(2,0).get_value()); Rectangle(hdc,100,299,200,400);
	SetColor(hdc, game.get_element(2,1).get_value()); Rectangle(hdc,199,299,300,400);
	SetColor(hdc, game.get_element(2,2).get_value()); Rectangle(hdc,299,299,400,400);
	SetColor(hdc, game.get_element(2,3).get_value()); Rectangle(hdc,399,299,500,400);
	// Fourth string
	SetColor(hdc, game.get_element(3,0).get_value()); Rectangle(hdc,100,399,200,500);
	SetColor(hdc, game.get_element(3,1).get_value()); Rectangle(hdc,199,399,300,500);
	SetColor(hdc, game.get_element(3,2).get_value()); Rectangle(hdc,299,399,400,500);
	SetColor(hdc, game.get_element(3,3).get_value()); Rectangle(hdc,399,399,500,500);

	// First string
	OutNumber(hdc,100,100, game.get_element(0,0).get_value());
	OutNumber(hdc,199,100, game.get_element(0,1).get_value());
	OutNumber(hdc,299,100, game.get_element(0,2).get_value());
	OutNumber(hdc,399,100, game.get_element(0,3).get_value());
	// Second string
	OutNumber(hdc,100,199, game.get_element(1,0).get_value());
	OutNumber(hdc,199,199, game.get_element(1,1).get_value());
	OutNumber(hdc,299,199, game.get_element(1,2).get_value());
	OutNumber(hdc,399,199, game.get_element(1,3).get_value());
	// Third string
	OutNumber(hdc,100,299, game.get_element(2,0).get_value());
	OutNumber(hdc,199,299, game.get_element(2,1).get_value());
	OutNumber(hdc,299,299, game.get_element(2,2).get_value());
	OutNumber(hdc,399,299, game.get_element(2,3).get_value());
	// Fourth string
	OutNumber(hdc,100,399, game.get_element(3,0).get_value());
	OutNumber(hdc,199,399, game.get_element(3,1).get_value());
	OutNumber(hdc,299,399, game.get_element(3,2).get_value());
	OutNumber(hdc,399,399, game.get_element(3,3).get_value());
}