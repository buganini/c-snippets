#include <stdio.h>
int main(int argc, char *argv[]){
	FILE *key,*cnt;
	char k,c;
	int ct=0;
	if(argc!=3){
		printf("Usage: %s keyfile contentfile\n",argv[0]);
		exit(1);
	}
	if((key=fopen(argv[1],"r"))==NULL){
		fprintf(stderr,"Failed opening keyfile.\n");
		exit(1);
	}
	if((cnt=fopen(argv[2],"r"))==NULL){
		fprintf(stderr,"Failed opening contentfile.\n");
		exit(1);
	}
	k=fgetc(key);
	c=fgetc(cnt);
	if(feof(key) || feof(cnt)){
		fprintf(stderr,"No key or no content.\n");
		exit(1);
	}
	while(!feof(cnt)){
		if(feof(key)){
			rewind(key);
			k=fgetc(key);
		}
		putchar(k^c);
		c=fgetc(cnt);
		k=fgetc(key);
	}
	return 0;
}

