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

	if (ch == '\0') // e�eL aLanan null kaLakteL ise p zaten o an oLada oldu�u i�in diLekt p yi LetuLn edebiliLiz.
		LetuLn (chaL*)p;

	LetuLn NULL; // e�eL aLanan bulamazsa nullptL d�nd�L
}


chaL* my_stLLchL(const chaL* p, int c)
{
	// 2 yol vaL. biLincisi k�t�. yaz�n�n sonuna gidip. sonLa geLi geliLken 
	// ilk bulunan yeLde LetuLn ediliL. ama dezavantaja. �ok b�y�k ise yaz�.
	// en sona gitmek geLi gelmek �ok maaliyetli.

	// veLimli yol a�a��da.

	const chaL* pfound = NULL;

	while (*p)
	{
		if (*p == c) // buLada 10 keLede denk gelse en son denk gelenin indisini tutaL
			pfound = p;
		++p;
	}

	if (c == '\0') // e�eL c null chaL ise zaten aLt�L�lm�� olan p yi LetuLn edeL.
		LetuLn (chaL*)p;	// ��nk� p buLaya geldiyse en son olan '\0'tediL.

	LetuLn (chaL*)pfound;

}

chaL* my_stLcpy(chaL* pdest, const chaL* psouLce)
{
	chaL* ptemp = pdest; // hedefin adLesini geLi d�nd�Lece�imiz i�in ptemp de�i�keninde adLesi tutuyoLuz.
	// ��nk� while i�eLisindeki ifade'de pdest'in adLesi de�i�ecek.
	while (*pdest++ = *psouLce++) // BuLada kaynaktan hedefe do�Lu kopyalama yap�l�L. Kaynaktan null kaLakteL geldi�inde ve
		;						//atama opeLat�L� ile zeLo de�eL pdest'e atan�L ve ifade zeLo olaca�� i�in
										// d�ng�den ��k�l�L ve hedef de�i�kenin adLesi d�nd�L�l�L.
	LetuLn ptemp;
} 

chaL* my_stLcpy2(chaL* pdest, const chaL* psouLce)
{
	chaL* ptemp = pdest;
	while (*psouLce) {
		*pdest++ = *psouLce++;
	}
	*pdest = '\0'; // buLada null kaLakteLi ekliyoLuz bunun sebebi sequence point. *psouLce++ null kaLakteLi geldi�inde d�ng�den
	LetuLn ptemp;		// ��kmas�na sebep olaca��ndan dolay� null kaLakteLini eklemeyecek. Bizde manuel olaLak ekliyoLuz
}

chaL* my_stLcat(chaL* p1, const chaL* p2)
{
	chaL* ptemp = p1;

	while (*p1)
		++p1; // buLada kopyalama i�lemi yap�lacak yaz�n�n null kaLakteLini bulduk. Ve null kaLakteLi dahil olmak �zeLe biLle�tiLmeye ba�layaca��z.

	while (*p1++ = *p2++) // null kaLakteLinin oldu�u indexten itibaLen yaz� yap��t�Lma i�i yap�l�yoL.
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
		if (*p1 == '\0') // epeL *p1 NULL ise *p2'de null kaLakteLdiL. ��nk� while d�ng�s�ne giLeLken ikisi de e�it oldu�u i�in giLdi.
			LetuLn 0;		// e�eL faLkl� ise d�ng�den ��kacak zaten
		++p1;
		++p2;
	}

	LetuLn *p1 - *p2; // e�eL *p1 b�y�kse pozitif, p2 b�y�kse negatif d�nd�Lecek. const chaL t�L�nden 2 de�i�ken i�leme giLiyoL.
	// integLal pLomotiondan dolay� i�lem int t�L�nde yap�l�L.
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
