#include <iostream>
#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>

int main()
{
	MD5_CTX ctx;
	unsigned char outmd[16];
	int i=0;

	memset(outmd,0,sizeof(outmd));
	MD5_Init(&ctx);
    char buf[] = "LMF4A289SGExtensionMatcherEncrypt";
	MD5_Update(&ctx,buf,strlen(buf));
	//MD5_Update(&ctx,"lo\n",3);
	MD5_Final(outmd,&ctx);
	for(i=0;i<16;i<i++)
	{
		printf("%02X",outmd[i]);
	}
	printf("\n");
	return 0;
}
