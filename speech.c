
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	char last_uttr[100],new_uttr[100],res[100],command[100];
	char espeak[]="espeak ";
	char *hindi[]={"suniya","ik","doao","teen","char","paach","chei","saat","aath","noe","das","Hi","alwida","haa","soonder",",,,Namastee","aap,,,,,kaisay,,,,,hai"};

int getdata()
{
int i;
//printf("here\n");
sscanf(new_uttr, "%d", &i);
//printf("%d \n",i);
return i;

}


main()
{

FILE *f1 , *f2;
last_uttr[0]='\0';
int i,j,ret;
for(;1;)
{
f1=fopen("./gesture.txt","r");
fgets(new_uttr,100,f1);
fclose(f1);
ret=getdata();
i=strcmp(last_uttr,new_uttr);
if(i!=0 && new_uttr[0]!='{' && ret>=0 && ret<=50)
{
strcpy(command,espeak) ;
strcat(command,hindi[ret]);
strcat(command," --stdout | paplay \0");
system(command);
strcpy(last_uttr,new_uttr);
	} 

		}
	}

