#ifndef HEADERLER_DCode_H_
#define HEADERLER_DCode_H_
#include<vector>
#include<array>
#include<string>
#include<clocale>
#include<climits>
#include<windows.h>
#include<fstream>
#include "hashlib/hashlibpp.h"
using namespace std;
/*
	-Çalýþma konumu deðiþtirme ekle
	-Dosya silme ekle
	-dosya listeleme ekle
*/
class degisken_saklayici final
{
private:
	static vector<array<string*,3>> liste;
	static const char* RAKAMLAR;
	static vector<string> PARAMS;
public:
	void listele(const string);
	bool unset(const char *);
	array<string*,3> getDegisken(string);
	void setDegisken(string,string,string);
	bool degiskenVarmi(string);
	static const char *getRakamlar()
	{
		return degisken_saklayici::RAKAMLAR;
	}
};
class terminal
{
private:
	static const char *surum;
	static const string *kadi;
protected:
	string *CWD_PTR;
	bool alindi_kmt,devam = true,ilk_d = false;
	string *metin,*komut,*parametre,*deg,*_e_d_isim;
	void get_m_User(bool x = false);
	bool calisma_alani(string *);
	static const short KOMUT_SAYISI = 16;
	static const array<array<string,3>,KOMUT_SAYISI> komutlar;
	static const vector<array<string,2>> FONKSIYONLAR;
	enum class KOMUTLAR {YARDIM,YUKLE,SOYLE,CIK,ATA,SYSTEM,LISTELE,SABIT,KUCULT,TIP,SIL,SETCWD,WIN_POPUP,MD5,SHA256,BEKLE,NULL_CMD};
	void konsol_gizle(short = 5);
	void bekle(unsigned long);
public:
	explicit terminal(const char *);
	virtual ~terminal();
	static const char *getSurum();
	static const vector<array<string,2>>& get_functions();
};
class DCode final : private terminal
{
private:
	bool kodvarmi;
	degisken_saklayici *degler = new degisken_saklayici;
	ifstream *kod_dosya;
	KOMUTLAR KOMUT = KOMUTLAR::NULL_CMD;
	bool islemci();
	const char * fonksiyon_isletici(const vector<string> &);
	hashwrapper *HASH_PTR;
	void komut_dizisi();
	ifstream *dosya;
	void kod_islet(bool x = false);
public:
	explicit DCode(const char*);
	int baslat();
	virtual ~DCode();
};
#endif /* HEADERLER_DCode_H_ */
// CopyRight Ali Demir
// Since 2016
