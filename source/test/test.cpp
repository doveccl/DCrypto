/* debug_mod
#define __dc_debug
*/
#include "dcen.h"

int main()
{
	int res = 0;
	DCEN de;
	freopen("out.txt", "w", stdout);
	UINT8 seed = 0;
	char s[1024];
	srand(time(0));
	int Case = 10000;
	while (Case--)
	{
		seed = random(128);
		for (int i = 0; i < 1024; i++)
			s[i] = random(90) + 33;
		char *aft = de.dc_encrypt(s, seed);
		aft = de.dc_decrypt(aft, seed);
		int sres = strcmp(s, aft);
		if (sres) res = 1;
		printf("case : %d\tres : %d\n", Case, sres);
		puts(s),puts(aft);
	}
	return res;
}
