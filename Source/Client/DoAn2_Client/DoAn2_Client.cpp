// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "resource.h"
#include "afxsock.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

bool CheckEmail(char* user)
{
	int len = strlen(user);
	char* email = "moc.liamg@";
	int len_E = strlen(email);
	if(_strnicmp(_strrev(user),email,len_E) == 0)
		return true;
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
		CSocket client;
		char sAdd[1000];
		unsigned int port = 1234; //Cung port voi server
		AfxSocketInit(NULL);

		//1. Tao socket
		client.Create();

		// Nhap dic chi IP cua server
		printf("\n Nhap dia chi IP cua server: ");
		cin>>(sAdd);
				
		char* UserName1;
		int lenUser1;
		char* Password1;
		int lenPass1;

		char* UserName;
		int lenUser;
		char* Password;
		int lenPass;

		if (client.Connect(CA2W(sAdd),port))
		{
			printf("\n Client da ket noi toi server");
			//Nhan tu server, cho biet day la client thu may
			int id;
			client.Receive((char*)&id,sizeof(id),0);
			printf(" \nDay la client thu %d\n",id+1);
			//------------------------------------------
			// sẽ có bảng menu để client chọn
MENU:
			cout<<"         MENU\n"<<endl<<"1.Tao tai khoan"<<endl;
			cout<<"2.Dang Nhap"<<endl<<"3.Exit"<<endl;
			int choose;
			cout<<"Choose: ";
			cin>>choose;
			client.Send((char*)&choose,sizeof(choose),0);
			if(choose == 1)
				goto DangKi;
			else if(choose == 2)
				goto DangNhap;
				else
					goto Exit;
			// gởi cho server biết client thực hiện thao tác gì
// k = 1
DangKi:
			cout<<"         Dang ki tai khoan"<<endl;
			UserName = new char[50];
			Password = new char[50];
			
			cout<<"User: ";
			cin>>UserName;
			lenUser = strlen(UserName);
			if(!CheckEmail(UserName))
			{
				cout<<"User bat buoc la 1 dia chi gmail"<<endl;
				goto DangKi;
			}
			client.Send(&lenUser,sizeof(int),0);
			client.Send(_strrev(UserName),lenUser,0);

			cout<<"Pass: ";
			cin>>Password;
			lenPass = strlen(Password);
			client.Send(&lenPass,sizeof(int),0);
			client.Send((Password),lenPass,0);
			// a là x bên server
			int a;
			client.Receive((char*)&a,sizeof(a),0);
			if (a == 0)
			{
				cout << "Tai khoan da ton tai. Hay dang ki tai khoan khac" << endl;
				goto DangKi;
			}
			else
			{
				goto DangNhap;
			}

// k = 2
DangNhap:
			UserName1 = new char[50];
			Password1 = new char[50];
			
			cout<<"       DANG NHAP"<<endl;
			cout<<"UserName: ";
			cin>>UserName1;
			lenUser1 = strlen(UserName1);

			cout<<"PassWord: ";
			cin>>Password1;
			lenPass1 = strlen(Password1);
			
			client.Send(&lenUser1,sizeof(lenUser1),0);
			client.Send(UserName1,lenUser1,0);
			client.Send(&lenPass1,sizeof(lenPass1),0);
			client.Send(Password1,lenPass1,0);

			int temp;
			client.Receive((char*)&temp,sizeof(int),0);
			// temp là p
			if(temp == 1)
			{
				char* temp1 = new char[1];
				cout<<"Chuc mung ban da dang nhap thanh cong!"<<endl;				
TruyVan:
				int len_day;
				char* day = new char[5];
				cout<<"Hom ngay ngay(dd/mm): ";
				cin>>day;
				len_day = strlen(day);
				day = new char[len_day];
				day[len_day] = '\0';
				// gởi ngày cho server
				client.Send(&len_day,sizeof(int),0);
				client.Send(day,len_day,0);


				cout<<"'h' de duoc huong dan"<<endl<<"chon: ";
				cin>>temp1;
				if(strcmp(temp1,"h")==0)
				{
					int h = 1;
					client.Send((char*)&h,sizeof(h),0);
					char *tv23;
					int Tv23;
					// Nhận truyvan23 từ server;
					client.Receive((char*)&Tv23,sizeof(Tv23),0);
					tv23 = new char[Tv23];
					client.Receive(tv23,strlen(tv23),0);
					tv23[Tv23] = '\0';
					
					// truy vấn DS
DSTV:
					cout<<tv23<<endl;
					int kqtv;
					cout<<"Chon: ";
					cin>>kqtv;
					// gởi kết quả truy vấn cho Server
					client.Send((char*)&kqtv,sizeof(kqtv),0);
					// truy vấn 1: xem danh sách các tỉnh mở thưởng
					if( kqtv == 1)
					{
						//string ds[11];
						char *p = new char[10];
						cout<<"Danh sach cac tinh thanh mo thuong kqxs:"<<endl;
						for(int i=0; i<11; i++)
						{
							int len_t;
							client.Receive((char*)&len_t,sizeof(int),0);
							client.Receive(p,len_t,0);
							p[len_t] = '\0';
							cout<<p<<endl;
						}
						goto DSTV;
					}
					// truy vấn 2: <tênTỉnhThành>
					if(kqtv==2)
					{
						char* Tentinhthanh = new char[10];
						char* Sove = new char[10];
						char* Ngay = new char[5];

						cout<<"<TenTinhThanh(viet Hoa dau chu cai)>: ";
						cin>>Tentinhthanh;
				
						int len_ten = strlen(Tentinhthanh);
					
						cout<<"<Ngay>: ";
						cin>>Ngay;
						int len_ngay = strlen(Ngay);

						// gui yeu cau cho sv
						client.Send((char*)&len_ten,sizeof(int),0);
						client.Send(Tentinhthanh,len_ten,0);
						
						client.Send((char*)&len_ngay,sizeof(int),0);
						client.Send(Ngay,len_ngay,0);
						// nhan ket qua
						char* ketqua;
						int len_kq;
						client.Receive((char*)&len_kq,sizeof(int),0);
						ketqua = new char(len_kq);
						client.Receive(ketqua,len_kq,0);
						ketqua[len_kq] = '\0';
						cout<<ketqua<<endl;
						goto DSTV;
					}
					// truy vấn 3 : <tenTinhThanh> <soVe> <Ngay>
					if(kqtv == 3)
					{
						char* Tentinhthanh = new char[10];
						char* Sove = new char[10];
						char* Ngay = new char[5];
						cout<<"<TenTinhThanh(viet Hoa dau chu cai)>: ";
						cin>>Tentinhthanh;
						int len_ten = strlen(Tentinhthanh);
						cout<<"<Sove>: ";
						cin>>Sove;
						int len_sove = strlen(Sove);
						cout<<"<Ngay>: ";
						cin>>Ngay;
						int len_ngay = strlen(Ngay);
						// gởi cho server:
						client.Send((char*)&len_ten,sizeof(int),0);
						client.Send(Tentinhthanh,len_ten,0);

						client.Send((char*)&len_sove,sizeof(int),0);
						client.Send(Sove,len_sove,0);
						
						client.Send((char*)&len_ngay,sizeof(int),0);
						client.Send(Ngay,len_ngay,0);
						// nhận kết quả truy vấn
						char* ketqua;
						int len_kq;
						client.Receive((char*)&len_kq,sizeof(int),0);
						ketqua = new char(len_kq);
						client.Receive(ketqua,len_kq,0);
						ketqua[len_kq] = '\0';
						cout<<ketqua<<endl;

						goto DSTV;
					}
					// truy vấn 4: <exit>
					if(kqtv==4)
					{
						goto Exit;
					}

				}
				else
				{
					cout<<"Truy van sai"<<endl;
					goto TruyVan;
				}
			}
			else // temp =2
			{
				cout<<"Sai ten dang nhap hoac mat khau"<<endl;
				goto DangNhap;
			}


			//-----------------------------------------
			client.Close();
		}
		else
			printf("Khong connect duoc toi server....");
Exit:
		cout<<"Exit..."<<endl;
	}
	getchar();
	return nRetCode;
}
