#include<stdio.h>
#include<ctype.h>
//#include<stdlib.h>
typedef struct{
	int word;
	int line;
	int cha;
}numbers;

numbers wc(FILE *f){
	//numbers n=malloc(sizeof(numbers));
	int in_word=0;
	char c;
	int line=0;
	int word=0;
	int cha=0;
	while((c=fgetc(f))!=EOF){
		if(c=='\n')line++;
		if(isspace(c)){
		in_word=0;
		}else if(!in_word){
		word++;
		in_word=1;

		}
		
cha++;

	}


	printf("\t%d\t %d\t %d\t ",line,word,cha);
return (numbers){.line=line,.word=word,.cha=cha};
}
int main(int argc,char **argv){
numbers n={
.line=0,
.word=0,
.cha=0
},s;

	if(argc<2){
	n=wc(stdin);

	printf("\n");
	}else{
		for(int i=1;i<argc;i++){
	FILE *f=fopen(argv[i],"r");
	s=wc(f);
	n.line+=s.line;
	n.word+=s.word;
	n.cha+=s.cha;
	printf("%s",argv[i]);

	printf("\n");
		}
	printf("\t%d\t %d\t %d\t total\n",n.line,n.word,n.cha);
	}


return 0;

}
