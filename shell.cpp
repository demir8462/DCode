#include "DCode.h"
#include<array>
#include<vector>
#include <iostream>
#include<ctime>
#include<string>
#include<iomanip>
#include<algorithm>
#include "str.h"

using namespace std;
const char* terminal::surum = "1.0";
const string* terminal::kadi = nullptr;
const array<array<string,3>,terminal::KOMUT_SAYISI> terminal::komutlar = {"Yardým","Komut Yardimi","Yardým \"Yardým\"","Yükle","Komut Dosyasýný Programa Dahil Eder","Yükle \"deðiþkenler.txt\"","Söyle","Ekrana Parametre Yazar","Söyle \"Merhaba Dünya !\"","Çýk","Terminali Kapar","Çýkýþ","Ata","Deðiþken Atar","Ata D \"Mesajým \" mesaj_degiskeni","Sistem","Ýþletim Sistemi Komut Ýþlemcisine Komut Ýþletir","Sistem \"echo merhaba\"","Listele","Dizi Elemanlarýný Gösterir","Listele \"Deðiþkenler\"","Sabit","Sabit Deðerli Deðiþkenler Oluþturur","Sabit NAME \"Ornek\"","Kucuk_h","Stringi Küçük Harf Dizisine Dönüþtürür","Kucuk_h\"KuCuLt\"","Tip","Deðiþken Hakkýda Bilgi Verir","Tip ABC_DEGISKENÝ","Sil","Deðiþkeni Tanýmsýz Yapar","Sil USER_DEGISKENÝ","SetCWD","Çalýþma Dizinini Deðiþtirir","SetCWD C:\\\\","WinP","Windows Popup Servisi","WinP \"Merhaba !\"","MD5","Dosya Yada Metnin Hash Kodu(MD5)","MD5 \"Dosya.txt\" veya \"Merhaba\"","SHA256","Dosya Yada Metnin Hash Kodu(SHA256)","SHA256 \"Dosya.txt\" veya \"Merhaba\"","Bekle","Sonraki Komut Satýrýna Geçmeden Bekler","Bekle 10"};
const vector<array<string,2>> terminal::FONKSIYONLAR = {{"Saat","void"}};
const char *terminal::getSurum()
{
	return surum;
}
terminal::terminal(const char *username)
{
	SetConsoleTitleA("DCode - 1.0");
	cout <<setw(62)<< "###     DCode Aktif Shell     ###"<<endl;
	cout <<setw(48)<< "V 1.0"<<endl;
	this->kadi = new string(username);
	this->komut = new string;
	this->parametre = new string;
	this->metin = new string;
	this->deg = new string;
	this->_e_d_isim = new string;
	this->CWD_PTR = new string();
}
void terminal::get_m_User(bool x)
{
	if(!x)
	{
		while(1)
		{
			cout << *this->kadi << "-->";
			getline(cin,*metin);
			str::utf8(metin);
			if(metin->size() != 0)
				break;
		}
	}else
	{
		str::utf8(metin);
	}
}
void terminal::bekle(unsigned long ms)
{
	static unsigned long bas;
	bas = clock();
	while(true)
		if(ms <= clock()-bas)
			break;
}
DCode::DCode(const char *username)
:terminal(username)
{
	cout << "DCode'e Hoþ Geldin "<< username<<"!"<<endl;
	this->degler->setDegisken("surum",this->getSurum(),"sistem_sabit");
	this->degler->setDegisken("kullanici",username,"sistem_sabit");
	this->degler->setDegisken("Coder","Ali Demir","sistem_sabit");
	this->degler->setDegisken("NULL","NULL","sistem_sabit");
	this->HASH_PTR = nullptr;
	this->dosya = nullptr;
	this->kod_dosya = new ifstream;
}
terminal::~terminal()
{
	cout << "Hoþçakal "<<*kadi << " !"<<endl;
	delete deg;
	delete komut;
	delete metin;
	delete parametre;
	delete CWD_PTR;
}
DCode::~DCode()
{
	cout << "System Closing..."<<endl;
	delete degler;
	delete HASH_PTR;
	delete dosya;
}
int DCode::baslat()
{
	const long bas = time(0);
	kod_islet();
	return time(0)-bas;
}
void DCode::kod_islet(bool x)
{
	while(this->devam)
	{
		*this->_e_d_isim = "";
		*parametre = "";
		*komut = "";
		*deg = "";
		this->ilk_d = true;
		this->alindi_kmt = false;
		try
		{
			get_m_User(x);
			for(int i = 0;i<metin->size();i++)
			{
				if(!this->alindi_kmt && (*metin)[i] == ' ') // komut Ã¶ncesi boÅŸluk atla
					continue;
				else if(!this->alindi_kmt && (*metin)[i] != ' ') // komutu al
				{
					for(int i2=i;i2<this->metin->size();i2++)
					{
						if((*metin)[i2] == ' ')
						{
							i = i2;
							break;
						}else if(i2 == metin->size()-1 && (*metin)[i2] != ' ')
						{
							*(this->komut) += (*metin)[i2];
							i = i2;
							break;
						}
						*(this->komut) += (*metin)[i2];
					}
					this->alindi_kmt = true;
				}else if(this->alindi_kmt && (*metin)[i] == '"')
				{
					for(int i2 = i+1,degil_sayici = 0;i2<this->metin->size();i2++)
					{
						if((*metin)[i2] == '"' && ((*metin)[i2-1] != '\\' || degil_sayici % 2 == 0))
						{
							i = i2;
							break;
						}
						if((*metin)[i2] == '\\' && (degil_sayici+1) % 2 == 0)
						{
							++degil_sayici;
							*(this->parametre) += (*metin)[i2];
						}else if((*metin)[i2] == '\\' && (degil_sayici+1) % 2 == 1)
						{
							++degil_sayici;
							continue;
						}else
						{
							*(this->parametre) += (*metin)[i2];
							degil_sayici = 0;
						}
					}
				}else if(this->alindi_kmt && (*metin)[i] != '"' && (*metin)[i] != ' ')
				{
					*deg = "";
					for(int i2 = i;i2<this->metin->size();i2++)
					{
						if((*metin)[i2] == ' ' || (*metin)[i2] == '"')
						{
							i = i2;
							break;
						}else if(i2 == metin->size()-1)
						{
							*this->deg += (*this->metin)[i2];
							i = i2;
							break;
						}
						*(this->deg) += (*metin)[i2];
					}
					if(this->ilk_d && (*this->komut == "Ata" || *this->komut == "Sabit"|| *this->komut == "Sil" ))
					{
						if(!str::numkont(this->deg))
							throw invalid_argument("Deðiþken Ýsminde Hata");
						*this->_e_d_isim = *this->deg;
						this->ilk_d = false;
					}else if(str::numkont(this->deg) && !this->degler->degiskenVarmi(*this->deg) && (*this->komut != "Ata" && *this->komut != "Sabit" ) && str::is_func_strutc(this->deg).empty())
					{
						throw invalid_argument("Bilinmeyen Deðiþken("+*this->deg+")");
					}else
					{
						if(!str::numkont(this->deg))
						{
							*(this->parametre) += *this->deg;
						}else
						{
							if(!str::is_func_strutc(this->deg).empty())
							{
							//	*(this->parametre) += fonksiyon_isletici(str::is_func_strutc(this->deg));
							}else
							{
								*(this->parametre) += *degler->getDegisken(*(this->deg))[1];
							}
						}
					}
				}
			}
			this->islemci();
		}catch(runtime_error &hata)
		{
			cout << "DCode-->"<<hata.what()<<endl;
		}catch(invalid_argument &hata)
		{
			cout << "DCode-->"<< hata.what()<<endl;
		}
		if(x)
			break;
	}
}
bool DCode::islemci()
{
	static short ii = 0;
	ii = 0;
	this->KOMUT = KOMUTLAR::NULL_CMD;
	for(const array<string,3> &i : komutlar)
	{
		if(i[0] == *this->komut)
		{
			this->KOMUT = static_cast<KOMUTLAR>(ii);
		}
		++ii;
	}
	switch(this->KOMUT)
	{
	case KOMUTLAR::YARDIM:
		this->kodvarmi = false;
		if(this->kodvarmi && !this->parametre->empty())
		{
			for(const array<string,3> &i : komutlar)
			{
				if(i[0] == *this->parametre)
				{
					this->kodvarmi = true;
					cout << "Komut Adý : "<<*this->parametre<<endl;
					cout << "Kullanýmý : "<<i[1]<<endl;
					cout << "Örnek Kod : "<<i[2]<<endl;
				}
			}
		}
		else if(!this->kodvarmi && !this->parametre->empty())
		{
			throw invalid_argument("Yardým Ýstediðiniz Komut("+*this->parametre+") Bulunmamakta");
		}else if(!this->kodvarmi && this->parametre->empty())
		{
			this->komut_dizisi();
		}
		break;
	case KOMUTLAR::YUKLE:
		if(this->kod_dosya->is_open())
			this->kod_dosya->close();
		if(!str::kod_dosyasi_mi(parametre))
			*(this->parametre) += ".dt";
		this->kod_dosya->open(*(this->parametre));
		if(!kod_dosya->is_open())
			throw invalid_argument("Yüklenecek Kod Dosyasý Bulunamadý !");
		else
		{
			while(getline(*kod_dosya,*metin))
			{
				if(str::bos_mu(metin) && metin->size() == 0)
					continue;
				kod_islet(true);
			}
			kod_islet();
			this->dosya->close();
			
		}
		break;
	case KOMUTLAR::SOYLE:
		cout << *this->parametre<<endl;
		break;
	case KOMUTLAR::CIK:
		this->devam = false;
		break;
	case KOMUTLAR::ATA:
		this->degler->setDegisken(*this->_e_d_isim,*this->parametre,"d_b");
		cout << *this->_e_d_isim << " = \""<<*this->parametre<<"\""<<endl;
		break;
	case KOMUTLAR::SYSTEM:
		system(this->parametre->c_str());
		break;
	case KOMUTLAR::LISTELE:
		this->degler->listele(*this->parametre);
		break;
	case KOMUTLAR::SABIT:
		this->degler->setDegisken(*this->_e_d_isim,*this->parametre,"sabit");
		cout <<"[SABIT]"<<*this->_e_d_isim << " = \""<<*this->parametre<<"\""<<endl;
		break;
	case KOMUTLAR::KUCULT:
		cout << *str::kucult(this->parametre)<<endl;
		break;
	case KOMUTLAR::TIP:
		if(!degler->degiskenVarmi(*this->parametre))
		{
			throw invalid_argument("Tip Bilgisi Ýçin Bilinmeyen Deðiþken("+*this->parametre+")");
		}else
		{
			cout << "{D_ISIM : " << *this->parametre << ",Tip: " << *degler->getDegisken(*this->parametre)[2]<<"}"<<endl;
		}
		break;
	case KOMUTLAR::SIL:
		if(!str::bos_mu(this->parametre) || str::bos_mu(this->_e_d_isim))
		{
			throw runtime_error("Yazým Hatasý !");
		}else
		{
			this->degler->unset(this->_e_d_isim->c_str());
			cout << "[NULL]" << *this->_e_d_isim << " = NULL"<<endl;
		}
		break;
	case KOMUTLAR::SETCWD:
		if(!this->calisma_alani(this->parametre))
		{
			throw invalid_argument("Çalýþma Dizini Ayarlanamadý !");
		}
		break;
	case KOMUTLAR::WIN_POPUP:
		if(this->parametre->empty())
		{
			throw invalid_argument("Bu Komut Parametre Olmadan Kullanýlamaz !");
		}else
		{
			MessageBox(0,this->parametre->c_str(),"DCode",MB_ICONINFORMATION);
		}
		break;
	case KOMUTLAR::MD5:
		this->HASH_PTR = new md5wrapper();
		this->dosya = new ifstream(*this->parametre);
		if(this->dosya->is_open())
		{
			this->dosya->close();
			cout << "MD5(DOSYA) : " << HASH_PTR->getHashFromFile(*this->parametre)<<endl;
			delete this->HASH_PTR;
			this->HASH_PTR = nullptr;
		}else
		{
			cout << "MD5(GÝRDÝ) : " << HASH_PTR->getHashFromString(*this->parametre)<<endl;
			delete this->HASH_PTR;
			this->HASH_PTR = nullptr;
		}
		break;
	case KOMUTLAR::SHA256:
		this->HASH_PTR = new sha256wrapper();
		this->dosya = new ifstream(*this->parametre);
		if(this->dosya->is_open())
		{
			this->dosya->close();
			cout << "SHA256(DOSYA) : " << HASH_PTR->getHashFromFile(*this->parametre)<<endl;
			delete this->HASH_PTR;
			this->HASH_PTR = nullptr;
		}else
		{
			cout << "SHA256(GÝRDÝ) : " << HASH_PTR->getHashFromString(*this->parametre)<<endl;
			delete this->HASH_PTR;
			this->HASH_PTR = nullptr;
		}
		break;
	case KOMUTLAR::BEKLE:
		if(!str::hepsi_num(this->parametre))
			throw invalid_argument("Ms Ýnt Tipinde Belirtilmelidir");
		this->bekle(stoi(*this->parametre));
		break;
	default:
		throw invalid_argument("Böyle Bir Komut Yok , Kullanýlabilir Komutlar Ýçin : Yardým");
		break;
	}
	return false;
}
void DCode::komut_dizisi()
{
		cout << "\nListe Þablonu : {\"Komut\",\"Açýklama\",\"Örnek\"}"<<endl;
		for(const array<string,3>  &k_l : this->komutlar)
		{
			cout << "{"<<k_l[0]<<","<<k_l[1]<<","<<k_l[2]<<"}"<<endl;
		}
		cout << endl;
}
bool terminal::calisma_alani(string *dizin)
{
	if(SetCurrentDirectory(dizin->c_str()))
	{
		*this->CWD_PTR = *dizin;
		return true;
	}
	return false;
}
void terminal::konsol_gizle(short CS_MODE)
{
	switch(CS_MODE)
	{
		case SW_HIDE:
			ShowWindow(GetConsoleWindow(),SW_HIDE);
			break;
		case SW_SHOW:
			ShowWindow(GetConsoleWindow(),SW_SHOW);
			break;
		default:
			throw invalid_argument("Bu Özellik Þu Anda Kullanýlamýyor!");
			break;
	}
}

const char * DCode::fonksiyon_isletici(const vector<string> &dizi)
{
	
}
const vector<array<string,2>> &terminal::get_functions()
{
	return FONKSIYONLAR;
}

