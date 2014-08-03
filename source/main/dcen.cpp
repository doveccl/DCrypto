#include "dcen.h"

DCEN d;

int main(int argc, char **argv)
{	
	if (argc == 1)
	{
		puts("Welcome to doveccl's encyption");
		puts("Version : 1.0");
		puts("Author : doveccl");
		putchar('\n');
		puts("使用 : \"E inFileName outFilename seed\" 加密");
		puts("使用 : \"D inFileName outFilename seed\" 解密");
		puts("seed 是 0~127 之间的一个整数，充当密钥");
	}
	else if (argc == 5)
	{
		if (*argv[1] == 'E')
		{
			FILE *in = fopen(argv[2], "rb");
			if (in == 0)
				fprintf(stderr, "文件 %s 不存在", argv[2]);
			else
			{
				fseek(in, 0, SEEK_END);
				int fileLen = ftell(in);
				char src[fileLen + 1024];
				fseek(in, 0, SEEK_SET);
				
				int cnt = 0;
				while(! feof(in))
					src[cnt++] = fgetc(in);
				src[cnt] = 0;
				
				FILE *out = fopen(argv[3], "wb");
				fprintf(out, "%s", d.dc_encrypt(src, atoi(argv[4])));
				
				fclose(out);
				fclose(in);
			}
		}
		else if (*argv[1] == 'D')
		{
			FILE *in = fopen(argv[2], "rb");
			if (in == 0)
				fprintf(stderr, "文件 %s 不存在", argv[2]);
			else
			{
				fseek(in, 0, SEEK_END);
				int fileLen = ftell(in);
				char enc[fileLen + 1024];
				fseek(in, 0, SEEK_SET);
				
				int cnt = 0;
				while(! feof(in))
					enc[cnt++] = fgetc(in);
				enc[cnt] = 0;
				
				FILE *out = fopen(argv[3], "wb");
				fprintf(out, "%s", d.dc_decrypt(enc, atoi(argv[4])));
				
				fclose(out);
				fclose(in);
			}
		}
		else
			fprintf(stderr, "参数错误！");
	}
	else
		fprintf(stderr, "缺少参数！");
}
