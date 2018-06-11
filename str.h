
#ifndef KAYNAK_STR_H_
#define KAYNAK_STR_H_
#include<cstdio>
#include<string>
#include<vector>
using namespace std;
class str
{
private:
	static string BUFFER;
	static vector<string> PARAMS;
	static short indx1,indx2;
	static bool sp_oncesi;
public:
	static string* kucult(string *metin)
	{
		for(int i = 0;i<metin->size();i++)
		{
			(*metin)[i] = tolower((*metin)[i]);
		}
		return metin;
	}

	static bool numkont(const string *);
	static bool bos_mu(const string *);
	static bool kod_dosyasi_mi(const string *);
	static bool	hepsi_num(const string *);
	static const string *utf8(string *);

	static vector<string> is_func_strutc(string *);
};



#endif /* KAYNAK_STR_H_ */
