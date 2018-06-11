#include "DCode.h"
#include <vector>
#include <array>
#include<iostream>
#include<string>
#include<stdexcept>
#include <iomanip>
#include<clocale>
using namespace std;
vector<array<string*,3>> degisken_saklayici::liste (0);
const char* degisken_saklayici::RAKAMLAR  = new char[10]{'0','1','2','3','4','5','6','7','8','9'};
array<string*,3> degisken_saklayici::getDegisken(string isim)
{
	for(int i = 0;this->liste.size();i++)
	{
		if(*(this->liste[i][0]) == isim)
		{
			return this->liste[i];
		}
	}
	return this->liste.at(3);
}
bool degisken_saklayici::degiskenVarmi(string isim)
{
	for(int i =0;i<this->liste.size();i++)
	{
		if(*this->liste[i][0] == isim)
			return true;
	}
	return false;
}
void degisken_saklayici::setDegisken(string isim,string deger,string tip)
{
	if(!degiskenVarmi(isim))
	{
		this->liste.push_back({new string(isim),new string(deger),new string(tip)});
	}else if(*getDegisken(isim)[2] == "sabit" || *getDegisken(isim)[2] == "sistem_sabit" && degiskenVarmi(isim))
	{
		throw runtime_error("Sabit Deðer Deðiþtirilemez !");
	}else
	{
		for(int i = 0;i<this->liste.size();i++)
		{
			if(*(this->liste.at(i)[0]) == isim)
			{
				this->liste[i][1] = new string(deger);
				this->liste[i][2] = new string(deger);
				break;
			}
		}
	}
}
void degisken_saklayici::listele(const string dizi_adi)
{
	if(dizi_adi == "D_DEÐÝÞKENLER")
	{
		for(array<string*,3> &d_l: this->liste)
		{
			if(d_l[0] == nullptr)
			{
				continue;
			}
			cout << "{"<<*d_l[0]<<","<<*d_l[1]<<","<<*d_l[2]<<"}"<<endl;
		}
	}else if(dizi_adi == "D_FONKSÝYONLAR")
	{
		for(const array<string,2> &d_l: terminal::get_functions())
		{
			cout << "{"<<d_l[0]<<","<<d_l[1]<<"}"<<endl;
		}
	}
}
bool degisken_saklayici::unset(const char* name)
{
	if(!degiskenVarmi(name))
	{
		throw invalid_argument("Tanýmsýz Deðiþken Silinemez");
	}else if(*getDegisken(name)[2] == "sistem_sabit" )
	{
		throw runtime_error("Sistem Sabiti Silinemez !");
	}else
	{
		for(int i = 0;i<this->liste.size();i++)
		{
			if(*(this->liste.at(i)[0]) == name)
			{
				this->liste.erase(this->liste.begin()+i);
				return true;
			}
		}
	}
	return false;
}
int main()
{
	MoveWindow(GetConsoleWindow(),200,200,700,400,0);
	setlocale(LC_ALL,"Turkish");
	DCode *term = new DCode(getenv("USERNAME"));
	term->baslat();
	delete term;
}
