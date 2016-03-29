#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char last_uttr[100],new_uttr[100],res[100],command[100];
char espeak[]="espeak -p 50 -s 100 -a 20 \"";
char *hindi[]={"su niya","ik","doao","teen","char","paach","chei","saat","aath","noe","das","namaste","alwieda","achaa","haa"};

int getdata()
{
int i;
sscanf(new_uttr, "%d", &i);
return i;

}


main()
{

FILE *f1 , *f2;
last_uttr[0]='\0';
int i,j,ret;
for(;1;)
{
f1=fopen("./result.txt","r");
fgets(new_uttr,100,f1);
fclose(f1);
ret=getdata();
i=strcmp(last_uttr,new_uttr);
if(i!=0 && new_uttr[0]!='{' && ret>=0 && ret<=10)
{
strcpy(command,espeak) ;
strcat(command,hindi[ret]);
strcat(command,"\"\0");
system(command);
strcpy(last_uttr,new_uttr);
} 
}
}

