#include "str.h"
#include "DCode.h"
#include <string>
#include<iostream>
using namespace std;
vector<string> str::PARAMS = {};
string str::BUFFER = "";
short str::indx1 = 0,str::indx2 = 0;
bool str::sp_oncesi = false;
bool rakammi(const char karakter)
{
	for(int i = 0;i<10;i++)
	{
		if(degisken_saklayici::getRakamlar()[i] == karakter)
		{
			return true;
		}
	}
	return false;
}
bool str::numkont(const string *metin)
{
	if(rakammi((*metin)[0]))
	{
		return false;
	}
	for(int i = 0;i<metin->size();i++)
	{
		if(!rakammi((*metin)[i]))
		{
			return true;
		}
	}
	return false;
}
bool str::bos_mu(const string *metin)
{
	if(metin->empty())
	{
		return true;
	}else
	{
		for(const char i : *metin)
		{
			if(i != ' ')
				return false;
		}
	}
	return true;
}
const string *str::utf8(string *metin)
{
	for(int i = 0;i<metin->size();i++)
	{
		switch((*metin)[i])
		{
			case -121:
				(*metin)[i] = static_cast<char>(-25);
				break;
			case -128:
				(*metin)[i] = static_cast<char>(-57);
				break;
			case -115:
				(*metin)[i] = static_cast<char>(-3);
				break;
			case -104:
				(*metin)[i] = static_cast<char>(-35);
				break;
			case -108:
				(*metin)[i] = static_cast<char>(-10);
				break;
			case -103:
				(*metin)[i] = static_cast<char>(-42);
				break;
			case -97:
				(*metin)[i] = static_cast<char>(-2);
				break;
			case -98:
				(*metin)[i] = static_cast<char>(-34);
				break;
			case -127:
				(*metin)[i] = static_cast<char>(-4);
				break;
			case -102:
				(*metin)[i] = static_cast<char>(-36);
				break;
			case -89:
				(*metin)[i] = static_cast<char>(-16);
				break;
			case -90:
				(*metin)[i] = static_cast<char>(-48);
				break;
			default:
				break;
		}
	}
	return metin;
}
bool str::hepsi_num(const string *str)
{
	for(short i=0;i<str->size();i++)
	{
		if(!rakammi((*str)[i]))
			return false;
	}
	return true;
}
bool str::kod_dosyasi_mi(const string *str)
{
	if(str->size() < 3 || (*str)[str->size()-1] != 't' || (*str)[str->size()-2] != 'd'  || (*str)[str->size()-3] != '.')
		return false;
	else
		return true;
}
vector<string> str::is_func_strutc(string *param)
{
	BUFFER = "";
	PARAMS = {};
	sp_oncesi = false;
	indx1 = 0;
	indx2 = 0;
	if((*param)[0] == '(' || (*param)[0] == ')')
		throw runtime_error("Function Hatasý : Ýlk Karakter ( || )");
	for(int i = 0;i<param->size();i++)
	{
		if((*param)[i] == '(' && indx1 != 0)
		{
			throw runtime_error("Function Hatasý : Hatalý Karakter ( || )");
		}else if((*param)[i] == '(' && indx1 == 0)
		{
			indx1 = i;
			continue;
		}
		if((*param)[i] == ')' && indx2 != 0)
		{
			throw runtime_error("Function Hatasý : Hatalý Karakter ( || )");
		}else if((*param)[i] == ')' && indx2 == 0)
		{
			indx2 = i;
			continue;
		}else
		{
			BUFFER += (*param)[i];
		}
	}
	PARAMS.push_back(BUFFER);
	BUFFER = "";
	for(int i = indx1+1;i<indx2;i++)
	{
		if(!sp_oncesi && (*param)[i] != ',' && (*param)[i] != ' ')
		{	
			BUFFER += (*param)[i];
			sp_oncesi = true;
			continue;
		}else if(sp_oncesi && (*param)[i] == ',')
		{
			PARAMS.push_back(BUFFER);
			BUFFER = "";
			sp_oncesi = false;
			continue;
		}else if(!sp_oncesi &&(*param)[i] == ',')
		{
			throw runtime_error("Function Hatasý : Hatalý Parametre Giriþi");
		}
	}
	if((indx1 == 0 && indx2 != 0)  || (indx1 != 0 && indx2 == 0))
		throw runtime_error("Deðiþken Ýsminde Geçersiz Karakter : ( || )");
	else if(indx1 == 0 && indx2 == 0)
		return {};
	else
	{
		return PARAMS;
	}
}

