#ifndef __Doveccl_Cryption_H__
#define __Doveccl_Cryption_H__

#include <cstdio>
#include <random>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

/**
  * ASCII:
  * 0 - 31 & 127  =>   control character
  * 32            =>   ' '
  * 48 - 57       =>   '0' - '9'
  * 65 - 90       =>   'A' - 'Z'
  * 97 - 122      =>   'a' - 'z'
  * others        =>   punctuation & operation symbol
  */

namespace DCrypto {

	#define random(x) (rand() % (x))

	#define MAX_EXTEND 94

	typedef unsigned char UINT8;

	const UINT8 enc_bin[] = {1, 2, 4, 8, 16, 32, 64, 128};
	const UINT8 // opnions for enc_seed
		enc_low = 1,
		enc_upp = 2,
		enc_num = 4,
		enc_pun = 8,
		enc_ord = 16,
		enc_swa = 32,
		enc_flo = 64,
		enc_non = 128;

	const UINT8 enc_clr = 0x0F;

	/*
		enc_seed is an int-master way of encryption
		this algorithm provides adjustive ways to encrypt
		for example:

			a master number
		0   0   0   0   0   0   0   0
		non flo swa ord pun num upp low

		non: no use without flo
			just a flag while do flower process
		flo: flower the UINT8 use the seed itself
			a position is 1 means reserving
			this position of the code
		swa: swap two parts of UINT8
			and reverse the last part
			0100         1101 -> 1011       0100
			 |            |
			first part   last part
		ord: order for swa & flo
			0: flo first, swa second
			1: swa first, flo second
			ord is useful while only flo & swa are used
			or it will be a flag like non
		pun: add punctuation & operation symbol to mapping
		num: add numbers to mapping
		upp: add uppercase to mapping
		low: add lowcase to mapping (use automatically)
	*/

	UINT8 enc_a = 'a', enc_b = 'b';
	UINT8 enc_map[MAX_EXTEND];

	int enc_init_map(UINT8 seed)
	{
		int len=0;

		for (UINT8 i = 'a'; i <= 'z';i++)
			enc_map[len++] = i;

		if (seed & enc_upp)
			for (UINT8 i = 'A'; i <= 'Z'; i++)
				enc_map[len++] = i;

		if (seed & enc_num)
			for (UINT8 i = '0'; i <= '9'; i++)
				enc_map[len++] = i;

		if (seed & enc_pun)
		{
			for (UINT8 i = 33; i <= 47; i++)
				enc_map[len++] = i;
			for (UINT8 i = 58; i <= 64; i++)
				enc_map[len++] = i;
			for (UINT8 i = 91; i <= 96; i++)
				enc_map[len++] = i;
			for (UINT8 i = 123; i <= 126; i++)
				enc_map[len++] = i;
		}

		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(enc_map, enc_map + len, g);

		#ifdef __dc_debug 
			puts("\n----- Debug enc_map -----");
			printf("map length : %d\n", len);
			for (int i = 0; i < len ; i++)
				printf("%d:%c\t", i, enc_map[i]);
			puts("\n----- Debug enc_map -----\n");
		#endif

		return len;
	}

	int enc_init_fill(UINT8 *ret, int src_len, int map_len)
	{
		int last = map_len - src_len % map_len;

		for (int i = 0; i < last; i++)
			ret[i] = random(256);
		ret[last - 1] = last;

		#ifdef __dc_debug
			puts("\n----- Debug init_fill -----");
			printf("Adding the ramdom chars : %u\n", last);
			for (int i = 0; i < last; i++)
				printf("%u\t", ret[i]);
			puts("\n----- Debug init_fill -----\n");
		#endif

		return last + src_len;
	}

	#define __enc_swap(uchar, b) \
		do{	\
			UINT8 temp = 0; \
			for (int p = 0; p < 4; p++) \
				if (b[p] & uchar) \
					temp |= b[7 - p]; \
			for (int p = 4; p < 8; p++) \
				if (b[p] & uchar) \
					temp |= b[p - 4]; \
			uchar = temp; \
		}while(0)

	void enc_swap(UINT8 *s, int len)
	{
		#ifdef __dc_debug
			puts("\n----- Debug swap -----");
		#endif

		for (int i = 0; i < len; i += 2)
		{
			#ifdef __dc_debug
				printf("position: %d      %u -> ", i, s[i]);
			#endif

			__enc_swap(s[i], enc_bin);

			#ifdef __dc_debug
				printf("%u\n", s[i]);
			#endif
		}

		#ifdef __dc_debug
			puts("\n----- Debug swap -----\n");
		#endif
	}

	void enc_flower(UINT8 *s, int len, UINT8 veins)
	{
		#ifdef __dc_debug
			puts("\n----- Debug flower -----");
		#endif

		for (int i = 0; i < len; i += 2)
		{
			#ifdef __dc_debug
				printf("position: %d      %u -> ", i, s[i]);
			#endif

			s[i] ^= veins;

			#ifdef __dc_debug
				printf("%u\n", s[i]);
			#endif
		}

		#ifdef __dc_debug
			puts("\n----- Debug flower -----\n");
		#endif
	}

	#define __enc_rand_map(uchar, t) \
		do{ \
			if (uchar < mod_cmp) \
				uchar = enc_map[uchar + 16 * random(t + 1)]; \
			else uchar = enc_map[uchar + 16 * random(t)]; \
		}while(0)

	void enc_mapping(UINT8 *s, int len, int map_len)
	{
		#define b enc_bin

		#ifdef __dc_debug
			puts("\n----- Debug mapping -----");
			puts("\n   -- Debug divide --   ");
		#endif

		for (int i = 0; i < len; i += 2)
		{
			#ifdef __dc_debug
				printf("position: %d      %u -> ", i, s[i]);
			#endif

			for (int p = 0; p < 4; p++)
				if (s[i] & b[p + 4])
					s[i + 1] |= b[p];

			s[i] &= enc_clr;

			#ifdef __dc_debug
				printf("%u & %u\n", s[i], s[i + 1]);
			#endif
		}

		#ifdef __dc_debug
			puts("\n   -- Debug divide --   \n");
			puts("\n   -- Debug rand-map --   ");
		#endif

		int mod_cmp = map_len % 16;
		int times = map_len / 16;
		int unit_len = len / 2 / map_len;

		for (int i = 0; i < len ; i += 2)
		{
			#ifdef __dc_debug
				printf("position: %u      %u -> ", i, s[i]);
			#endif

			if (i / 2 % unit_len)
			{
				__enc_rand_map(s[i], times); 
				__enc_rand_map(s[i + 1], times);
			}
			else
				s[i] += enc_a,
				s[i + 1] += enc_b;

			#ifdef __dc_debug
				printf("%c\n", s[i]);
			#endif
		}

		#ifdef __dc_debug
			puts("\n   -- Debug rand-map --   \n");
			puts("\n----- Debug mapping -----\n");
		#endif
	}

	int dec_get_map_len(UINT8 seed)
	{
		int len = 26;
		if (enc_upp & seed)
			len += 26;
		if (enc_num & seed)
			len += 10;
		if (enc_pun & seed)
			len += 32;

		return len;
	}

	#define __dec_swap(uchar, b) \
		do{	\
			UINT8 temp = 0; \
			for (int p = 0; p < 4; p++) \
				if (b[7 - p] & uchar) \
					temp |= b[p]; \
			for (int p = 4; p < 8; p++) \
				if (b[p - 4] & uchar) \
					temp |= b[p]; \
			uchar = temp; \
		}while(0)

	void dec_map_recovery(UINT8 *s, int len, int map_len, int seed)
	{
		#ifdef __dc_debug
			puts("\n----- Debug map recovery -----");
		#endif

		int unit_len = len / 2 / map_len;
		int cnt_map = 0; 

		for (int i = 0; i < len ; i += 2)	
			if (! (i / 2 % unit_len))
			{
				#ifdef __dc_debug
					printf("key @ %d : %u & %u ", i, s[i], s[i + 1]);
				#endif

				s[i] -= enc_a;
				s[i + 1] -= enc_b;

				for (int p = 0; p < 4; p++)
					if (s[i + 1] & b[p])
						s[i] |= b[p + 4];

				if (enc_flo & seed && enc_swa & seed)
					if (enc_ord & seed)
					{
						s[i] ^= seed;
						__dec_swap(s[i], enc_bin);
					}
					else
					{
						__dec_swap(s[i], enc_bin);
						s[i] ^= seed;
					}
				else if (enc_flo & seed)
					s[i] ^= seed;
				else if (enc_swa & seed)
					__dec_swap(s[i], enc_bin);		

				enc_map[cnt_map++] = s[i];

				#ifdef __dc_debug
					printf("-> %c\n", s[i]);
				#endif
			}

		#ifdef __dc_debug
			puts("\n----- Debug map recovery -----\n");
		#endif
	}

	void dec_unmapping(UINT8 *s, int len, int map_len)
	{
		#define b enc_bin

		#ifdef __dc_debug
			puts("\n----- Debug unmapping -----");
		#endif

		int unit_len = len / 2 / map_len;
		int half_map[128];
		int cnt_map = 0;

		for (int i = 0; i< map_len; i++)
			half_map[enc_map[i]] = i;

		for (int i = 0; i < len ; i += 2)
			if (i / 2 % unit_len)
			{
				#ifdef __dc_debug
					printf("word @ %d : %u & %u ", i, s[i], s[i + 1]);
				#endif

				s[i] = half_map[s[i]] % 16;
				s[i + 1] = half_map[s[i + 1]] % 16;

				for (int p = 0; p < 4; p++)
					if (s[i + 1] & b[p])
						s[i] |= b[p + 4];

				#ifdef __dc_debug
					printf("-> %u\n", s[i]);
				#endif
			}

		int dec_cnt = 0;
		for (int i = 0; i < len ; i += 2)
			s[dec_cnt++] = s[i];

		#ifdef __dc_debug
			puts("\n----- Debug unmapping -----\n");
		#endif
	}

	void dec_swap(UINT8 *s, int len, int map_len)
	{
		#ifdef __dc_debug
			puts("\n----- Debug unswap -----");
		#endif

		int unit_len = len / map_len;

		for (int i = 0; i < len; i++)
			if (i % unit_len)
			{
				#ifdef __dc_debug
					printf("position: %d      %u -> ", i, s[i]);
				#endif

				__dec_swap(s[i], enc_bin);

				#ifdef __dc_debug
					printf("%u\n", s[i]);
				#endif
			}

		#ifdef __dc_debug
			puts("\n----- Debug unswap -----\n");
		#endif
	}

	void dec_flower(UINT8 *s, int len, UINT8 veins, int map_len)
	{
		#ifdef __dc_debug
			puts("\n----- Debug unflower -----");
		#endif

		int unit_len = len / map_len;

		for (int i = 0; i < len; i++)
			if (i % unit_len)
			{
				#ifdef __dc_debug
					printf("position: %d      %u -> ", i, s[i]);
				#endif

				s[i] ^= veins;

				#ifdef __dc_debug
					printf("%u\n", s[i]);
				#endif
			}

		#ifdef __dc_debug
			puts("\n----- Debug unflower -----\n");
		#endif
	}

	void dec_select(UINT8 *s, int len, int map_len)
	{
		int unit_len = len / map_len;
		int src_suffix = 0;

		for (int i = 0; i < len; i++)
			if (i % unit_len)
				s[src_suffix++] = s[i];

		int src_len = src_suffix - s[src_suffix - 1];
		s[src_len] = 0;
	}

	char *dc_encrypt(const char *src_code, UINT8 enc_seed)
	{
		int src_len = strlen(src_code);
		int src_max_extend_len = src_len + 2 * MAX_EXTEND;

		UINT8 *src = new UINT8[src_max_extend_len];
		UINT8 *enc = new UINT8[2 * src_max_extend_len];
		memset(enc, 0, 2 * src_max_extend_len * sizeof(UINT8));
		memcpy(src, src_code, src_len * sizeof(char));

		srand(time(0));

		int map_len = enc_init_map(enc_seed);
		int len = enc_init_fill(src + src_len, src_len, map_len);

		int unit = len / map_len;
		int cnt_enc = 0, cnt_src = 0;
		for (int i = 0; i < map_len; i++)
		{
			enc[cnt_enc] = enc_map[i];
			cnt_enc += 2;
			for (int j = 0; j < unit; j++)
				enc[cnt_enc] = src[cnt_src++],
				cnt_enc += 2;
		}

		if (enc_flo & enc_seed && enc_swa & enc_seed)
			if (enc_ord & enc_seed)
				enc_swap(enc, cnt_enc),
				enc_flower(enc, cnt_enc, enc_seed);
			else
				enc_flower(enc, cnt_enc, enc_seed),
				enc_swap(enc, cnt_enc);
		else if (enc_flo & enc_seed)
			enc_flower(enc, cnt_enc, enc_seed);
		else if (enc_swa & enc_seed)
			enc_swap(enc, cnt_enc);

		enc_mapping(enc, cnt_enc, map_len);

		return (char *) enc;
	}

	char *dc_decrypt(const char *enc_code, UINT8 enc_seed)
	{
		int map_len = dec_get_map_len(enc_seed);
		int len = strlen(enc_code);
		UINT8 *enc = new UINT8[len];
		memcpy(enc, enc_code, len * sizeof(char));

		dec_map_recovery(enc, len, map_len, enc_seed);
		dec_unmapping(enc, len, map_len);

		len /= 2;

		if (enc_flo & enc_seed && enc_swa & enc_seed)
			if (enc_ord & enc_seed)
				dec_flower(enc, len, enc_seed, map_len),
				dec_swap(enc, len, map_len);
			else
				dec_swap(enc, len, map_len),
				dec_flower(enc, len, enc_seed, map_len);
		else if (enc_flo & enc_seed)
			dec_flower(enc, len, enc_seed, map_len);
		else if (enc_swa & enc_seed)
			dec_swap(enc, len, map_len);

		dec_select(enc, len, map_len);

		return (char *) enc;
	};

} // namespace DCrypto

#endif
