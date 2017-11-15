#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include "tool_regex.h"

int regex(const char* string,const char* regex,char** value)
{
	int ret = 0;
	int error = 0;
	char errBuff[256];
	regex_t preg;
	int cflags = 0;
	size_t nmatch = 10;
	regmatch_t pmatch[nmatch];
	// Compilation de l'expression reguliere
	printf("string : %s, regex : %s\n",string,regex);
	if ( (error = regcomp(&preg, regex, cflags)) != 0 )
	{
		regerror(error,&preg,errBuff,sizeof(errBuff));
		printf("Compilation errBuff : %s\n",errBuff);
		ret = -1;
	}
	if ( ret != -1 )
	{
		if ( (error = regexec(&preg, string, sizeof(nmatch),pmatch,0)) != 0 )
		{
			regerror(error,&preg,errBuff,sizeof(errBuff));
			printf("Resultat de l'execution : %s\n",errBuff);
			ret = -1;
		}
	}

	regfree(&preg);
	return ret;
}
