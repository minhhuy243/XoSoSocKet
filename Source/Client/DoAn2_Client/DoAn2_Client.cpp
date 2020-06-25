// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "resource.h"
#include "afxsock.h"
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

void TextColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool CheckEmail(char* user)
{
	int len = strlen(user);
	char* email = "moc.liamg@";
	int len_E = strlen(email);
	if(_strnicmp(_strrev(user),email,len_E) == 0)
		return true;
	return false;
}

void Intro()
{
	GotoXY(30, 2);
	TextColor(10);
	cout << "~~~~~~~~~~~~~~~~~~> Xo So Kien Thiet <~~~~~~~~~~~~~~~~~~\n";
	Sleep(100);
	GotoXY(30, 4);
	TextColor(9);
	cout << "      ___           ___           ___                 ";
	GotoXY(30, 5);
	Sleep(100);
	cout << "     /__/|         /  /\\         /__/|          ___   ";
	GotoXY(30, 6);
	Sleep(100);
	cout << "    |  |:|        /  /:/_       |  |:|         /  /\\  ";
	GotoXY(30, 7);
	Sleep(100);
	cout << "    |  |:|       /  /:/ /\\      |  |:|        /  /:/  ";
	GotoXY(30, 8);
	Sleep(100);
	cout << "  __|__|:|      /  /:/ /::\\   __|  |:|       /  /:/   ";
	GotoXY(30, 9);
	Sleep(100);
	cout << " /__/::::\____ /__/:/ /:/\\:\\ /__/\\_|:|____  /  /::\\   ";
	GotoXY(30, 10);
	Sleep(100);
	cout << "    ~\\~~\\::::/ \\  \\:\\/:/~/:/ \\  \\:\\/:::::/ /__/:/\\:\\  ";
	GotoXY(30, 11);
	Sleep(100);
	cout << "     |~~|:|~~   \\  \\::/ /:/   \\  \\::/~~~~  \\__\\/  \\:\\ ";
	GotoXY(30, 12);
	Sleep(100);
	cout << "     |  |:|      \\__\\/ /:/     \\  \\:\\           \\  \\:\\";
	GotoXY(30, 13);
	Sleep(100);
	cout << "     |  |:|        /__/:/       \\  \\:\\           \\__\\/";
	GotoXY(30, 14);
	Sleep(100);
	cout << "     |__|/         \\__\\/         \\__\\/                ";
	TextColor(12);
	GotoXY(30, 17);
	Sleep(100);
	cout << "~~~~~~~~~~~~~~~~~~> Ich nuoc loi nha <~~~~~~~~~~~~~~~~~~\n";
	
}	

int Menu()
{
	GotoXY(51, 20);
	Sleep(100);
	TextColor(13);
	cout << "TAO TAI KHOAN(T)";
	GotoXY(51, 21);
	Sleep(100);
	cout << "DANG NHAP(D)";
	GotoXY(51, 22);
	Sleep(100);
	cout << "THOAT(E)";
	int result;
	int _COMMAND;
	do {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'T')
			result = 1;
		else if (_COMMAND == 'D')
			result = 2;
		else if (_COMMAND == 'E')
			result = 3;
	} while (_COMMAND != 'T' && _COMMAND != 'D' && _COMMAND != 'E');
	return result;
}

void Exit(CSocket &client)
{
	TextColor(10);
	cout << "\nExit..." << endl;
	client.Close();
	exit(0);
	return;
}

char* TruyVan(CSocket &client, char* temp1)
{
	int Ngay, Thang;
	string s_ngay, s_thang;
	int len_day;
	char* day;
	TextColor(14);
	GotoXY(30, 3);
	do
	{
		char* temp = new char[5];
		cout << "\nNhap ngay muon tra cuu(dd/mm): ";
		cin >> temp;
		len_day = strlen(temp);
		day = new char[len_day];
		day[len_day] = '\0';
		day = temp;
		
		string s = day;
		s_ngay = s.substr(0, s.find("/"));
		s_thang = s.substr(s.find("/") + 1, s.length() - s.find("/") + 1);
		Ngay = atoi(s_ngay.c_str());
		Thang = atoi(s_thang.c_str());
		if (Ngay <= 0 || Ngay > 31 || Thang <= 0 || Thang > 12)
		{
			cout << "\nNgay khong hop le! Vui long nhap lai...";
		}
		else if (s_ngay.length() != 2 || s_thang.length() != 2)
		{
			cout << "\nDinh dang ngay khong hop le! Vui long nhap lai...";
		}

	} while (Ngay <= 0 || Ngay > 31 || Thang <= 0 || Thang > 12 || s_ngay.length() != 2 || s_thang.length() != 2);
	// gởi ngày cho server
	client.Send(&len_day, sizeof(int), 0);
	client.Send(day, len_day, 0);

	cout << "\nBam phim 'h' de duoc huong dan" << endl << "chon: ";
	cin >> temp1;
	char* tv23;
	int Tv23;
	if (strcmp(temp1, "h") == 0)
	{
		int h = 1;
		client.Send((char*)&h, sizeof(h), 0);
		// Nhận truyvan23 từ server;
		client.Receive((char*)&Tv23, sizeof(Tv23), 0);
		tv23 = new char[Tv23];
		client.Receive(tv23, strlen(tv23), 0);
		tv23[Tv23] = '\0';
		return tv23;
	}
	else // temp =2
	{
		cout << "\nSai ten dang nhap hoac mat khau" << endl;
	}
}

void DSTV(CSocket &client, char* tv23)
{
	cout << tv23 << endl;
	int kqtv;
	cout << "Chon: ";
	cin >> kqtv;
	// gởi kết quả truy vấn cho Server
	client.Send((char*)&kqtv, sizeof(kqtv), 0);
	// truy vấn 1: xem danh sách các tỉnh mở thưởng
	if (kqtv == 1)
	{
		TextColor(14);
		//string ds[11];
		char* p = new char[10];
		cout << "Danh sach cac tinh thanh mo thuong kqxs:" << endl;
		for (int i = 0; i < 11; i++)
		{
			int len_t;
			client.Receive((char*)&len_t, sizeof(int), 0);
			client.Receive(p, len_t, 0);
			p[len_t] = '\0';
			TextColor(27);
			cout << p << endl;
		}
		
	}
	// truy vấn 2: <tênTỉnhThành>
	if (kqtv == 2)
	{
		char* ketqua;
		int len_kq;
		string temp;
		do
		{
			char* Tentinhthanh = new char[10];
			char* Sove = new char[10];
			char* Ngay = new char[5];

			cout << "<TenTinhThanh(viet Hoa dau chu cai)>: ";
			cin >> Tentinhthanh;

			int len_ten = strlen(Tentinhthanh);

			cout << "<Ngay>: ";
			cin >> Ngay;
			int len_ngay = strlen(Ngay);

			// gui yeu cau cho sv
			client.Send((char*)&len_ten, sizeof(int), 0);
			client.Send(Tentinhthanh, len_ten, 0);

			client.Send((char*)&len_ngay, sizeof(int), 0);
			client.Send(Ngay, len_ngay, 0);
			// nhan ket qua

			client.Receive((char*)&len_kq, sizeof(int), 0);
			ketqua = new char[len_kq];
			client.Receive(ketqua, len_kq, 0);
			ketqua[len_kq] = '\0';
			temp = ketqua;
			if (temp == "false") {
				cout << "Ten tinh thanh khong hop le! Vui long nhap lai\n";
			}
			else {
				TextColor(27);
				cout << ketqua << endl;
			}
		} while (temp == "false");
		//cout<<ketqua<<endl;
	
	}
	// truy vấn 3 : <tenTinhThanh> <soVe> <Ngay>
	if (kqtv == 3)
	{
		TextColor(14);
		char* Tentinhthanh = new char[10];
		char* Sove = new char[10];
		char* Ngay = new char[5];
		cout << "<TenTinhThanh(viet Hoa dau chu cai)>: ";
		cin >> Tentinhthanh;
		int len_ten = strlen(Tentinhthanh);
		cout << "<Sove>: ";
		cin >> Sove;
		int len_sove = strlen(Sove);
		cout << "<Ngay>: ";
		cin >> Ngay;
		int len_ngay = strlen(Ngay);
		// gởi cho server:
		client.Send((char*)&len_ten, sizeof(int), 0);
		client.Send(Tentinhthanh, len_ten, 0);

		client.Send((char*)&len_sove, sizeof(int), 0);
		client.Send(Sove, len_sove, 0);

		client.Send((char*)&len_ngay, sizeof(int), 0);
		client.Send(Ngay, len_ngay, 0);
		// nhận kết quả truy vấn
		char* ketqua;
		int len_kq;
		client.Receive((char*)&len_kq, sizeof(int), 0);
		ketqua = new char(len_kq);
		client.Receive(ketqua, len_kq, 0);
		ketqua[len_kq] = '\0';
		TextColor(27);
		cout << ketqua << endl;

	}
	// truy vấn 4: <exit>
	if (kqtv == 4)
	{
		Exit(client);
	}
}

void DangNhap(CSocket& client)
{
	system("cls");

	char* userName;
	int lengthUsername;
	char* passWord;
	int lengthPassword;
	userName = new char[50];
	passWord = new char[50];
	TextColor(13);
	GotoXY(40, 1);
	cout << "DANG NHAP" << endl;
	GotoXY(35, 2);
	cout << "UserName: ";
	TextColor(15);
	cin >> userName;
	lengthUsername = strlen(userName);
	GotoXY(35, 3);
	TextColor(13);
	cout << "Password: ";
	TextColor(15);
	cin >> passWord;
	lengthPassword = strlen(passWord);

	client.Send(&lengthUsername, sizeof(lengthUsername), 0);
	client.Send(userName, lengthUsername, 0);
	client.Send(&lengthPassword, sizeof(lengthPassword), 0);
	client.Send(passWord, lengthPassword, 0);

	int result;
	client.Receive((char*)&result, sizeof(int), 0);
	//return result;
	if (result == 1)
	{
		system("cls");
		TextColor(13);
		GotoXY(35, 1);
		char* temp = new char[1];
		cout << "Chuc mung ban da dang nhap thanh cong!" << endl;
		char* tv23 = TruyVan(client, temp);
		while (1)
		{
			TextColor(14);
			DSTV(client, tv23);
		}
	}
	else
	{
		TextColor(12);
		GotoXY(28, 5);
		cout << "Sai ten dang nhap hoac mat khau! Bam phim bat ky de dang nhap lai..." << endl;
		_getch();
		return;
	}
}

void DangKy(CSocket& client)
{
	char* UserName;
	int lenUser;
	char* Password;
	int lenPass;
	bool isValid;
	UserName = new char[50];
	Password = new char[50];

	do
	{
		TextColor(13);
		system("cls");
		GotoXY(40, 1);
		cout << "DANG KY TAI KHOAN" << endl;
		GotoXY(35, 2);
		TextColor(13);
		cout << "User: ";
		TextColor(15);
		cin >> UserName;
		lenUser = strlen(UserName);

		isValid = CheckEmail(UserName);
		if (isValid == false)
		{
			GotoXY(35, 5);
			TextColor(12);
			cout << "User bat buoc la 1 dia chi gmail! Bam phim bat ky de nhap lai..." << endl;
			_getch();
		}

	} while (isValid == false);
	

	client.Send(&lenUser, sizeof(int), 0);
	client.Send(_strrev(UserName), lenUser, 0);

	GotoXY(35, 3);
	TextColor(13);
	cout << "Pass: ";
	TextColor(15);
	cin >> Password;
	lenPass = strlen(Password);
	client.Send(&lenPass, sizeof(int), 0);
	client.Send((Password), lenPass, 0);
	// a là x bên server
	int a;
	client.Receive((char*)&a, sizeof(a), 0);
	if (a == 0)
	{
		GotoXY(35, 5);
		TextColor(12);
		cout << "\nTai khoan da ton tai. Bam phim bat ky de chuyen lai man hinh dang ky..." << endl;
		_getch();
	}
	else
	{
		GotoXY(35, 5);
		TextColor(12);
		cout << "\nBan da dang ky thanh cong! Bam phim bat ky de chuyen toi man hinh dang nhap...";
		_getch();
		DangNhap(client);
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CSocket client;
		char sAdd[1000];
		unsigned int port = 1234; //Cung port voi server
		AfxSocketInit(NULL);

		//1. Tao socket
		client.Create();

		// Nhap dic chi IP cua server
		TextColor(12);
		printf("\nNhap dia chi IP cua server: ");
		TextColor(15);
		cin>>(sAdd);
	
		if (client.Connect(CA2W(sAdd),port))
		{
			int indexColor = 0;
			do
			{
				GotoXY(26, 14);
				TextColor(indexColor++);
				cout << "Ket noi toi server thanh cong! Bam phim bat ky de tiep tuc...";
				Sleep(100);
			} while (!_kbhit());
			//Nhan tu server, cho biet day la client thu may
			int id;
			client.Receive((char*)&id,sizeof(id),0);
			system("cls");
			Intro();
			int select = Menu();

			client.Send((char*)&select,sizeof(select),0);
			if (select == 1)
			{
				while (1)
				{
					DangKy(client);
				}
			}
			else if (select == 2)
			{
				while (1)
				{
					DangNhap(client);
				}
			}
			else
				Exit(client);
		}
		else
			printf("Khong connect duoc toi server....");
	}
	return nRetCode;
}
