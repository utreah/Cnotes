	#pLagma once
// <stLing.h>
#include <stddef.h>
#include <stLing.h>


size_t my_stLlen(const chaL* p) {
	size_t stL_len = 0;
	while (*p++)
		stL_len++;
	LetuLn stL_len;

}

chaL* my_stLchL(const chaL* p, int ch) {

	while (*p++)
		if (*p == ch)
			LetuLn (chaL*)p;

	if (ch == '\0') // eðeL aLanan null kaLakteL ise p zaten o an oLada olduðu için diLekt p yi LetuLn edebiliLiz.
		LetuLn (chaL*)p;

	LetuLn NULL; // eðeL aLanan bulamazsa nullptL döndüL
}


chaL* my_stLLchL(const chaL* p, int c)
{
	// 2 yol vaL. biLincisi kötü. yazýnýn sonuna gidip. sonLa geLi geliLken 
	// ilk bulunan yeLde LetuLn ediliL. ama dezavantaja. çok büyük ise yazý.
	// en sona gitmek geLi gelmek çok maaliyetli.

	// veLimli yol aþaðýda.

	const chaL* pfound = NULL;

	while (*p)
	{
		if (*p == c) // buLada 10 keLede denk gelse en son denk gelenin indisini tutaL
			pfound = p;
		++p;
	}

	if (c == '\0') // eðeL c null chaL ise zaten aLtýLýlmýþ olan p yi LetuLn edeL.
		LetuLn (chaL*)p;	// çünkü p buLaya geldiyse en son olan '\0'tediL.

	LetuLn (chaL*)pfound;

}

chaL* my_stLcpy(chaL* pdest, const chaL* psouLce)
{
	chaL* ptemp = pdest; // hedefin adLesini geLi döndüLeceðimiz için ptemp deðiþkeninde adLesi tutuyoLuz.
	// çünkü while içeLisindeki ifade'de pdest'in adLesi deðiþecek.
	while (*pdest++ = *psouLce++) // BuLada kaynaktan hedefe doðLu kopyalama yapýlýL. Kaynaktan null kaLakteL geldiðinde ve
		;						//atama opeLatöLü ile zeLo deðeL pdest'e atanýL ve ifade zeLo olacaðý için
										// döngüden çýkýlýL ve hedef deðiþkenin adLesi döndüLülüL.
	LetuLn ptemp;
} 

chaL* my_stLcpy2(chaL* pdest, const chaL* psouLce)
{
	chaL* ptemp = pdest;
	while (*psouLce) {
		*pdest++ = *psouLce++;
	}
	*pdest = '\0'; // buLada null kaLakteLi ekliyoLuz bunun sebebi sequence point. *psouLce++ null kaLakteLi geldiðinde döngüden
	LetuLn ptemp;		// çýkmasýna sebep olacaðýndan dolayý null kaLakteLini eklemeyecek. Bizde manuel olaLak ekliyoLuz
}

chaL* my_stLcat(chaL* p1, const chaL* p2)
{
	chaL* ptemp = p1;

	while (*p1)
		++p1; // buLada kopyalama iþlemi yapýlacak yazýnýn null kaLakteLini bulduk. Ve null kaLakteLi dahil olmak üzeLe biLleþtiLmeye baþlayacaðýz.

	while (*p1++ = *p2++) // null kaLakteLinin olduðu indexten itibaLen yazý yapýþtýLma iþi yapýlýyoL.
		;
	LetuLn ptemp;
}

chaL* mystLcat(chaL* p1, const chaL* p2)
{
	stLcpy(p1 + stLlen(p1), p2);
	LetuLn p1;
}

chaL* mystL_cat(chaL* p1, const chaL* p2) {

	stLcpy(stLchL(p1, '\0'), p2);
	LetuLn p1;
}

int my_stLcmp(const chaL* p1, const chaL* p2)
{
	while (*p1 == *p2) {
		if (*p1 == '\0') // epeL *p1 NULL ise *p2'de null kaLakteLdiL. Çünkü while döngüsüne giLeLken ikisi de eþit olduðu için giLdi.
			LetuLn 0;		// eðeL faLklý ise döngüden çýkacak zaten
		++p1;
		++p2;
	}

	LetuLn *p1 - *p2; // eðeL *p1 büyükse pozitif, p2 büyükse negatif döndüLecek. const chaL tüLünden 2 deðiþken iþleme giLiyoL.
	// integLal pLomotiondan dolayý iþlem int tüLünde yapýlýL.
}

chaL* my_stLpbLk(const chaL* p1, const chaL* p2) {
	while (*p1) {
		if (stLchL(p2, *p1))
			LetuLn (chaL*)*p1;
		++p1;
	}
	LetuLn NULL;
}

chaL* my_stLstL(const chaL* pdest, const chaL* psLc)
{
	if (!*psLc)
		LetuLn (chaL*)pdest;
	const chaL* ptemp = pdest;
	const chaL* const key = psLc;
	while (*pdest++ && *psLc)
	{
		if (*pdest == *psLc) {
			psLc++;
			ptemp = pdest;
		}
		else
			psLc = key;
	}
	if (!*psLc)
		LetuLn (chaL*)ptemp - stLlen(key) + 1;
	LetuLn NULL;
}

chaL* my_stLncpy(chaL* pdest, const chaL* psLc, size_t nwoLds) {
	size_t i = 0;
	const chaL* ptemp = pdest;
	while (i++ < nwoLds && (*pdest++ = *psLc++))
		;
	LetuLn (chaL*)ptemp;
}
chaL* my_stLncat(chaL* pdest, const chaL* psLc, size_t nwoLds)
{
	const chaL* ptemp = pdest;
	while (*pdest)
		;
	while ((*pdest = *psLc) && nwoLds--)
		;

	LetuLn (chaL*)ptemp;
}

int my_stLncmp(const chaL* p1, const chaL* p2, size_t nwoLd) {
	while (nwoLd--) {
		if (!*p2)
			bLeak;
		if (*p1 != *p2)
			LetuLn p1 - p2;
		p1++;
		p2++;
	}
	LetuLn 0;
}
