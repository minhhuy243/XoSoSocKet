// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "resource.h"
#include "afxsock.h"
#include "math.h"
#include "Tokenizer.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object
using namespace std;
CWinApp theApp;

struct Name
{
	string User;
	string Pass;
};
struct KQSX
{
	string ngay;
	string GiaiDB;
	string GiaiNhat;
	string GiaiNhi;
	string GiaiBa;
	string GiaiTu;
	string GiaiNam;
	string GiaiSau;
	string GiaiBay;
	string GiaiTam;
};

vector<string> Tokenizer::Split(const string& s, const char delim)
{
	vector<string> result;

	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
	{
		result.push_back(item);
	}

	return result;
}
string Parse(string s)
{
	vector<string> parts = Tokenizer::Split(s, '	');
	string a;
	a = parts[1];
	return a;
}
string  TimKQSX(string TenTinhThanh, string ngay)
{
	KQSX *a = new KQSX[2];

	ifstream f;

	if (TenTinhThanh == "PhuYen")
		f.open("PhuYen.txt");
	if (TenTinhThanh == "BinhDuong")
		f.open("BinhDuong.txt");
	if (TenTinhThanh == "BinhPhuoc")
		f.open("BinhPhuoc.txt");
	if (TenTinhThanh == "BinhThuan")
		f.open("BinhThuan.txt");
	if (TenTinhThanh == "DongNai")
		f.open("DongNai.txt");
	if (TenTinhThanh == "LongAn")
		f.open("LongAn.txt");
	if (TenTinhThanh == "MienBac")
		f.open("MienBac.txt");
	if (TenTinhThanh == "NinhThuan")
		f.open("NinhThuan.txt");
	if (TenTinhThanh == "QuangNgai")
		f.open("QuangNgai.txt");
	if (TenTinhThanh == "TpHCM")
		f.open("TpHCM.txt");
	if (TenTinhThanh == "VungTau")
		f.open("VungTau.txt");
	for (int i = 0; i < 2; i++)
	{
		getline(f, a[i].ngay);
		getline(f, a[i].GiaiDB);
		getline(f, a[i].GiaiNhat);
		getline(f, a[i].GiaiNhi);
		getline(f, a[i].GiaiBa);
		getline(f, a[i].GiaiTu);
		getline(f, a[i].GiaiNam);
		getline(f, a[i].GiaiSau);
		getline(f, a[i].GiaiBay);
		getline(f, a[i].GiaiTam);
	}
	for (int i = 0; i < 2; i++)
	{
		if (a[i].ngay == ngay)
		{
			return (a[i].ngay+ "\n"+a[i].GiaiDB+"\n"+a[i].GiaiNhat+"\n"+a[i].GiaiNhi+"\n"+a[i].GiaiBa+"\n"+a[i].GiaiTu+"\n"+a[i].GiaiNam+"\n"+a[i].GiaiSau+"\n"+a[i].GiaiBay+"\n"+a[i].GiaiTam+"\n");
		}
	}
	return ("Ket qua mo thuong khong co");
}

string KiemTraVeSo(string TenTinhThanh, string Ve, string ngay)
{
	string GiaiTrung = "Chuc ban may mam lan sau";
	ifstream f;

	KQSX *a = new KQSX[10];

	if (TenTinhThanh == "PhuYen")
		f.open("PhuYen.txt");
	if (TenTinhThanh == "BinhDuong")
		f.open("BinhDuong.txt");
	if (TenTinhThanh == "BinhPhuoc")
		f.open("BinhPhuoc.txt");
	if (TenTinhThanh == "BinhThuan")
		f.open("BinhThuan.txt");
	if (TenTinhThanh == "DongNai")
		f.open("DongNai.txt");
	if (TenTinhThanh == "LongAn")
		f.open("LongAn.txt");
	if (TenTinhThanh == "MienBac")
		f.open("MienBac.txt");
	if (TenTinhThanh == "NinhThuan")
		f.open("NinhThuan.txt");
	if (TenTinhThanh == "QuangNgai")
		f.open("QuangNgai.txt");
	if (TenTinhThanh == "TpHCM")
		f.open("TpHCM.txt");
	if (TenTinhThanh == "VungTau")
		f.open("VungTau.txt");
	for (int i = 0; i < 10; i++)
	{
		getline(f, a[i].ngay);
		getline(f, a[i].GiaiDB);
		a[i].GiaiDB = Parse(a[i].GiaiDB);
		getline(f, a[i].GiaiNhat);
		a[i].GiaiNhat = Parse(a[i].GiaiNhat);
		getline(f, a[i].GiaiNhi);
		a[i].GiaiNhi = Parse(a[i].GiaiNhi);
		getline(f, a[i].GiaiBa);
		a[i].GiaiBa = Parse(a[i].GiaiBa);
		getline(f, a[i].GiaiTu);
		a[i].GiaiTu = Parse(a[i].GiaiTu);
		getline(f, a[i].GiaiNam);
		a[i].GiaiNam = Parse(a[i].GiaiNam);
		getline(f, a[i].GiaiSau);
		a[i].GiaiSau = Parse(a[i].GiaiSau);
		getline(f, a[i].GiaiBay);
		a[i].GiaiBay = Parse(a[i].GiaiBay);
		getline(f, a[i].GiaiTam);
		a[i].GiaiTam = Parse(a[i].GiaiTam);
	}
	for (int i = 0; i < 10; i++)
	{
		if (a[i].ngay == ngay)
		{
			if (Ve == a[i].GiaiDB)
				GiaiTrung = "Woah! chuc mung ban da trung giai Dat Biet tri gia 1,5ty vnd";
			else
			{
				if ((stoi(Ve) % 100000) == stoi(a[i].GiaiNhat))
					GiaiTrung = "GiaiNhat";
				else
				{

					if ((stoi(Ve) % 100000) == stoi(a[i].GiaiNhi))
						GiaiTrung = "GiaiNhi";
					else
					{
						vector<string> parts = Tokenizer::Split(a[i].GiaiBa, '-');
						if ((stoi(Ve) % 100000) == stoi(parts[0]) || (stoi(Ve) % 100000) == stoi(parts[1]))
							GiaiTrung = "GiaiBa";
						else
						{
							vector<string> parts = Tokenizer::Split(a[i].GiaiTu, '-');
							if ((stoi(Ve) % 100000) == stoi(parts[0]) || (stoi(Ve) % 100000) == stoi(parts[1]) || (stoi(Ve) % 100000) == stoi(parts[2]) || (stoi(Ve) % 100000) == stoi(parts[3]) || (stoi(Ve) % 100000) == stoi(parts[4]) || (stoi(Ve) % 100000) == stoi(parts[5]) || (stoi(Ve) % 100000) == stoi(parts[6]))
								GiaiTrung = "GiaiTu";
							else
							{
								if (stoi(Ve) % 10000 == stoi(a[i].GiaiNam))
									GiaiTrung = "GiaiNam";
								else
								{
									vector<string> parts1 = Tokenizer::Split(a[i].GiaiSau, '-');
									if (stoi(Ve) % 10000 == stoi(parts1[0]) || stoi(Ve) % 10000 == stoi(parts1[1]) || stoi(Ve) % 10000 == stoi(parts1[2]))
										GiaiTrung = "GiaiSau";
									else
									{
										if (stoi(Ve) % 1000 == stoi(a[i].GiaiBay))
											GiaiTrung = "GiaiBay";
										else
										{
											if (stoi(Ve) % 100 == stoi(a[i].GiaiTam))
												GiaiTrung = "GiaiTam";
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return GiaiTrung;
}

int SaveUser(string user, string pass)
{
	ifstream f;
	f.open("TaiKhoan.txt");

	int n, k;
	string m, s;
	Name a[30];
	f >> n;
	for (int i = 0; i < 30; i++)
	{
		a[i].User = "";
		a[i].Pass = "";
	}
	k =-1;
	for (int i = 0; i < n; i++)
	{
		f >> m;
		f >> s;
		a[i].User = m;
		a[i].Pass = s;
		if (user == a[i].User)
		{
			k = 0;
			return 0;
		}
	}
	

	if (k == -1)
	{
		n++;
		a[n - 1].User = user;
		a[n - 1].Pass = pass;
		remove("TaiKhoan.txt"); // xoa file 
		ofstream f1;
		f1.open("TaiKhoan.txt"); // tao lai file moi cung ten
		f1 << n;
		f1 << endl;
		// ghi lai danh sach user bao gom ca user vua moi tao
		for (int i = 0; i < n; i++)
		{
			f1 << a[i].User;
			f1 << " ";
			f1 << a[i].Pass;
			f1 << endl;
		}
	}
	return 1;

}
bool SearchUSer(string user, string pass)
{
	ifstream f;
	f.open("TaiKhoan.txt");

	int n, k;
	string m, s;
	Name a[50];
	while (!f)
	{
		
		cout << "tep tin khong ton tai";
		return false;
	}

	f >> n;
	for (int i = 0; i < 50; i++)
	{
		a[i].User = "NULL";
	}
	for (int i = 0; i < n; i++)
	{
		f >> m;
		f >> s;
		a[i].User = m;
		a[i].Pass = s;
	}
	k = -1;
	for (int i = 0; i < n; i++)
	{
		if ( a[i].User==user && a[i].Pass == pass )
		{
			k = 0;
			return true;
		}
	}
	return false;
}
bool SearchTinhThanh(string TinhThanh)
{
	ifstream f;
	f.open("DanhSach.txt");
	string a[11];
	int n, k;
	string m, s;
	while (!f)
	{
		cout << "tep tin khong ton tai";
		return false;
	}
	for(int i = 0; i<11; i++)
	{
		f >> a[i];
	}
	for (int i = 0; i < 11; i++)
	{
		if ( a[i] == TinhThanh )
		{
			k = 0;
			return true;
		}
	}
	return false;
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
		CSocket server;
		unsigned int port = 1234;
		int i;
		AfxSocketInit(NULL);

		server.Create(port);
		server.Listen(5);

		//Nhap so luong client
		printf("\n Nhap so luong Client: ");
		int num_client;
		scanf_s("%d",&num_client);
		if(num_client <=0 || num_client >=10)
		{
			cout<<"Vui long nhap dung so luong"<<endl;
			goto EXIT;
			
		}
		printf("\n Dang lang nghe ket noi tu Client...\n");

		//Tao mang chua cac socket client
		CSocket* sockClients = new CSocket[50];
		for(i=0 ; i<num_client; i++)
		{
			server.Accept(sockClients[i]);
			printf("Da tiep nhan client %d/%d\n",i+1,num_client);
			//Bao cho client biet minh la client thu may
			sockClients[i].Send((char*)&i,sizeof(int),0);
		
			int k,x;
			char* User;
			int lenU;
			char* Pass;
			int lenP;
			int j = i;
			// k là giá trị choose

			sockClients[i].Receive((char*)&k,sizeof(k),0);
			if(k == 1)
			{
DangKi:
				sockClients[j].Listen(5);
				// ---------------------------------------
				// my code
				// nhận User đã kiểm tra đúng

				sockClients[j].Receive(&lenU,sizeof(int),0);
				User = new char[lenU];
				sockClients[i].Receive(User,lenU,0);
				User[lenU] = '\0';
				// nhận pass
				sockClients[j].Receive(&lenP,sizeof(int),0);
				Pass = new char[lenP];
				sockClients[j].Receive(Pass,lenP,0);
				Pass[lenP] = '\0';
				int k;
				if(SaveUser(User,Pass) == 0)
				{
					x = 0;
					cout<<"   Dang ki khong thanh cong. Tai khoan da duoc dang ki"<<endl;				
					sockClients[j].Send((char*)&x,sizeof(int),0);
					goto DangKi;
				}
				else
				{
					x = 1;
					k = 2;				
					cout << "   Dang ki thanh cong" << endl;
					sockClients[j].Send((char*)&x,sizeof(int),0);
					goto DangNhap;
				}
			}
			// 2 là đăng nhập
			if( k == 2)
			{
DangNhap:
				sockClients[j].Receive(&lenU,sizeof(int),0);
				User = new char[lenU];
				sockClients[j].Receive(User,lenU,0);
				User[lenU] = '\0';

				sockClients[j].Receive(&lenP,sizeof(int),0);
				Pass = new char[lenP];
				sockClients[j].Receive(Pass,lenP,0);
				Pass[lenP] = '\0';
				// dang nhập thành công
				if(SearchUSer(User,Pass) == true)
				{
					int p = 1;
					sockClients[j].Send((char*)&p,sizeof(p),0);
					// nhận truy vấn ngày của client gởi cho
					char* day;
					int len_day;
					sockClients[j].Receive((char*)&len_day,sizeof(int),0);
					day = new char[len_day];
					sockClients[j].Receive(day,len_day,0);
					day[len_day] = '\0';
					// day là để truy vấn xem hôm đó có kqxs của tỉnh nào
					
					// nhận truy vấn h
					int x; // x = h

					sockClients[j].Receive((char*)&x,sizeof(x),0);
					if( x == 1) // x = h = 1
					{
						// gởi hướng dẫn truy vấn 2 & 3 và tỉnh thành xs trong ngày
						char truyvan23[] = "1. <DS> : de nhan cac tinh thanh co kqxs\n2. <TenTinhThanh> <Ngay Can Tra Cuu> : xem kqxs cua ngay can tran cuu \n3. <TenTinhThanh> <SoVe> <NgayCanTraCuu>: de tra cuu giai thuong\n4. <EXIT>: De thoat";
						int tv23 = strlen(truyvan23);
						sockClients[j].Send((char*)&tv23,sizeof(int),0);
						sockClients[j].Send(truyvan23,sizeof(truyvan23),0);
TruyVan:
						// nhận kết quả truy vấn
						int kq; // kq = kqtv
						sockClients[j].Receive((char*)&kq,sizeof(kq),0);
						// kq = 1: xuất danh sách tỉnh thành có kqxs ra
						if(kq == 1)
						{
							ifstream ff;
							ff.open("DanhSach.txt");
							string ds1[11];
							for(int i=0; i<11; i++)
							{
								ff>>ds1[i];
								int len_t = strlen(ds1[i].c_str());
								sockClients[j].Send((char*)&len_t,sizeof(int),0);
								sockClients[j].Send(ds1[i].c_str(),len_t,0);
							}
							goto TruyVan;
						}
						// truy van 2 <TenTinhThanh>
						if(kq==2)
						{
							char* Tentinhthanh;
							int len_ten;
							char* Ngay;
							int len_ngay;

							sockClients[j].Receive((char*)&len_ten,sizeof(int),0);
							Tentinhthanh = new char[len_ten];
							sockClients[j].Receive(Tentinhthanh,len_ten,0);
							Tentinhthanh[len_ten] = '\0';
							
							sockClients[j].Receive((char*)&len_ngay,sizeof(int),0);
							Ngay = new char[len_ngay];
							sockClients[j].Receive(Ngay,len_ngay,0);
							Ngay[len_ngay] = '\0';

							string TraCuu= TimKQSX(Tentinhthanh,Ngay);
							int len_tracuu=strlen(TraCuu.c_str());
							// tra ket qua
							sockClients[j].Send((char*)&len_tracuu,sizeof(int),0);
							sockClients[j].Send(TraCuu.c_str(),len_tracuu,0);
							goto TruyVan;
						}
						// nhận truy vấn 3 từ client
						if(kq == 3)
						{
							char* Tentinhthanh;
							int len_ten;
							char* Sove;
							int len_sove;
							char* Ngay;
							int len_ngay;
							// nhận từ client
							sockClients[j].Receive((char*)&len_ten,sizeof(int),0);
							Tentinhthanh = new char[len_ten];
							sockClients[j].Receive(Tentinhthanh,len_ten,0);
							Tentinhthanh[len_ten] = '\0';

							
							sockClients[j].Receive((char*)&len_sove,sizeof(int),0);
							Sove = new char[len_sove];
							sockClients[j].Receive(Sove,len_sove,0);
							Sove[len_sove] = '\0';
							
							sockClients[j].Receive((char*)&len_ngay,sizeof(int),0);
							Ngay = new char[len_ngay];
							sockClients[j].Receive(Ngay,len_ngay,0);
							Ngay[len_ngay] = '\0';

							string KiemTra = KiemTraVeSo(Tentinhthanh,Sove,Ngay);
							int len_ktra = strlen(KiemTra.c_str());
							// gởi kết quả của hàm KIểmTraVeSo cho client
							sockClients[j].Send((char*)&len_ktra,sizeof(int),0);
							sockClients[j].Send(KiemTra.c_str(),len_ktra,0);

							goto TruyVan;
						}
						// nhận truy vấn 4 từ client

					}


				}
				// đăng nhập thất bại
				else
				{
					int p = 0;
					sockClients[j].Send((char*)&p,sizeof(p),0);
					goto DangNhap;
				}
			}

				
			


			// ---------------------------------------
		
		// ngắt kết nối
		sockClients[i].Close();
		}
EXIT:
		
		cout<<"Exit..."<<endl;

		
		getchar();
	}
	
	getchar();
	return nRetCode;
}
