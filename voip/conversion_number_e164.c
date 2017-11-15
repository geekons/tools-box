#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include "../utils/tool_regex.h"
#include "../str_manipulations/string_manipulation.h"


int convert_local_caller_number_to_e164(const char* prefix_pstn, const char* prefix_international, const char* code_pays, const char* prefix_national,const char* local_called_number, char *e164NewCalled)
{
	int index;
	char* values[10];
	char* tampon = NULL;
	// Verifie la position du prefix pstn
	char regex_str[100];
	regex_str[0]='\0';
	strcat(regex_str,"^");
	strcat(regex_str,prefix_pstn);
	if ( regex(local_called_number, regex_str, values) == 0 ) 
	{
		index = str_istr(local_called_number,prefix_pstn);
		printf("On retire le prefix pstn, index : %d\n",index);
		tampon = str_sub(local_called_number, index+strlen(prefix_pstn), strlen(local_called_number)-index);	
		printf("tampon : %s\n",tampon);
	}
	regex_str[0]='\0';
	strcat(regex_str,"^");
	strcat(regex_str,prefix_international);
	if ( regex(tampon, regex_str, values) == 0 )
	{
		index = str_istr(tampon,prefix_international);
		printf("On retire le prefix international, index : %d\n",index);
		tampon = str_sub(tampon, index+strlen(prefix_international), strlen(tampon)-index);
		sprintf(e164NewCalled,"+%s",tampon);
		printf("Numero International e164NewCalled: %s\n",e164NewCalled);
	}
	else
	{
		printf("Numero National\n");
		regex_str[0]='\0';
		strcat(regex_str,"^");
		strcat(regex_str,prefix_national);
		if ( regex(tampon, regex_str, values) == 0 ) 
		{
			index = str_istr(tampon,prefix_national);
			printf("On retire le prefix national, index : %d\n",index);
			tampon = str_sub(tampon, index+strlen(prefix_national), strlen(tampon)-index);
			sprintf(e164NewCalled,"+%s%s",code_pays,tampon);
			printf("Numero national e164NewCalled: %s\n",e164NewCalled);
		}
	}

}


int main(int argc,char** argv)
{
	const char* local_called_number = NULL;
	const char* prefix_pstn = NULL;
	const char* prefix_international = NULL;
	const char* code_pays = NULL;
	const char* prefix_national = NULL;
	char e164NewCalled[15];
	e164NewCalled[0]='\0';
	for(int i=0;i<argc;i++)
	{
	printf("argv[%d] : %s\n",i,argv[i]);
	switch (i) 
		{
		case 1:
			local_called_number = strdup(argv[i]);
		break;
		case 2:
			prefix_pstn = strdup(argv[i]);
		break;
		case 3:
			prefix_international = strdup(argv[i]);
		break;
		case 4:
			code_pays = strdup(argv[i]);
		break;
		case 5:
			prefix_national = strdup(argv[i]);
		break;
		default:
		break;
		}
	}
	printf("prefix_pstn: %s, prefix_international: %s, code_pays : %s, prefix_national: %s\n", prefix_pstn, prefix_international, code_pays, prefix_national);
	printf("local_called_number: %s\n\n\n", local_called_number);

	convert_local_caller_number_to_e164(prefix_pstn, prefix_international, code_pays, prefix_national, local_called_number, e164NewCalled);
	printf("e164NewCalled : %s\n",e164NewCalled);
return 0;
}

