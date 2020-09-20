#include <stdio.h>
#include <math.h>
#ifdef FREEBSD
#include <unistd.h>
#endif

float capo=7.0;
int default_length=1;
int fq(char,float);
void play(char *,float);

int main(int ac, char **av){
//HSNU
//play("2E2GDE2C -BGEA4G 2A+2CDE2C ECDE4D 3C-G2E2G3+DC-G+C-2A 3EG2A2G+3ECDE2C 3GGEC-AGA+CD.5C.5DEC2D -3GGEGAGA+CD.5C.5DC-G2A Gx+Cx-A+C-Gx Ax+CxDECx 3D.5C.5DECC-.5A+.5C4E4E 2GEG2D2EC-.5A+.5CDG4E -G2AG+E.5D.5CDE2CC.5C.5CC-BAG+ 2E2GDE2C -BGEA4G 2A+2CDE2C ECDE3D -E3GG2+G2GAAG.5E.5C-A+CDE2C+2C.5C.5C",200);

//mario
play(".5E.5E.5x.5E.5x.5CEGx-Gx+1.5C-.5Gx1.5EAB.5bA.7G+.8E.7GA.5F.5G.5xE.5C.5D-1.5B+1.5C-.5Gx1.5EAB.5bA.7G+.8E.7GA.5F.5G.5xE.5C.5D-1.5Bx+.5G.5g.5Fe.5E.5x-a.5A+.5C.5x-.5A+.5C.5Dx.5G.5g.5Fe.5E.5x+C.5C2Cx-.5G.5g.5Fe.5E.5x-.5a.5A+.5C.5X.5-A+.5C.5Dxe.5x1.5D2C2xx.5G.5g.5Fe.5E.5x-a.5A+.5C.5x-.5A+.5C.5Dx.5G.5g.5Fe.5E.2xx+C.5C2Cx-.5G.5g.5Fe.5E.5x-.5a.5A+.5C.5X.5-A+.5C.5Dxe.5x1.5D2C2x.5CC.5C.5x.5CD.5EC-.5A2G+.5CC.5C.5x.5CDE4x.5CC.5C.5x.5CD.5EC-.5A2G+.5E.5E.5x.5E.5x.5CEGx-Gx+1.5C-.5Gx1.5EAB.5bA.7G+.8E.7GA.5F.5G.5xE.5C.5D-1.5B+1.5C-.5Gx1.5EAB.5bA.7G+.8E.7GA.5F.5G.5xE.5C.5D-1.5B+.5EC-.5Gxa.5A+F.5F-2A.7B+.8A.7A.7A.8G.7F.5EC-.5A2G+.5EC-.5Gxa.5A+F.5F-2A.5B+F.5F.7F.8E.7D2C-2C   -.7G+.8C.7E.7G+.8C.7E2G2E--.7a+.8C.7E.7a+.8C.7e2a2e--.7b+.8D.7F .7b+.8D.7F 2b .7b.8b.7b +8C",200);

//Butterfly 
//play("2EEG3AGA+C-AG4E2DDE2GECDEDC-4A:",150);

//Scotland The Brave
//play("3C-B+2C2D2E2C2E2G+8C2C-2G2E2C4F2A2F2E2G2E2C4D2G2A2G2AGFED3C-B+2C2D2E2C2E2G+8C2C-2G2E2C4F2A2F2E2G2E2C4D2C-2B+4C2E2G+8C2C-2G2E2C4+8C2C-2G2E2C4F2A2F2E2G2E2C4D2C-2B+4C",100);

//lol song
//play("+CxCxCxCxCxCxCxCxDxDxDxDx-8ABxBxBxBxBxBxBxBx2A2G2A2B+8C",100);

//hello, how are you
//play("GA+CC2C2x-A+C3E2GGED4EEDE2DC-3A",200);

//let me think for a while - bass
//play("---CxCx3GC+2C-2B2G2C CxCx3GC+2C-2B2G2C AxAx+3E-A+2A2a2E-2A AxAx+3E-A+2A2a2E-2A FxFx+3C-F+2F2E2C-2F FxFx+3C-F+2F2E-2G2A GxGx+3D-G+2G2g2D-2G GxGx+3D-G+2G2g2D-2G: Cx4C2x2D4G2x -Ax4A2x+2E-4A2x +Dx4D2x2E4A2x Dx4D2x2E4A2x Dx4D2x2E4A2x Dx4D2x2E4A2x Cx4C2x2D4G2x Cx4C2x2D4G2x Cx4C2x2D4G2x -Ax4A2x+2E-4A2x +Dx4D2x2E4A2x Dx4D2x2E4A2x Dx4D2x2E4A2x Dx4D2x2E4A2x Gx4G2x2A4+D1.5x-.5G.5x GxGx+3D-G +EF2E2C-2G FxFx+3C-F FxFx2G+2C -FxFx+3CF 2E2C-2G2F ExEx3BE ExEx2g2B",112.4);
return 0;
}

#ifdef FREEBSD
/* Need ports/audio/beep */
void beep(int p, int t){
	char cmd[50];
	sprintf(cmd,"beep -p %d %d", p, t/10);
	system(cmd);
}
#endif

void play(char *song,float timebase){
	float level=0.0;
	float length=0;
	float isfloat=0;
	char *repeatfrom=song-1;
	float repeatlevel=0;
	char alreadyrepeat=0;
	while(*song!=0){
		putchar(*song);
		if(*song=='+'){
			++level;
		}else if(*song=='-'){
			--level;
		}else if(*song=='X' || *song=='x'){
			if(length==0){
				length=default_length;
			}
#ifdef FREEBSD
			usleep((useconds_t) (timebase*length*1000));
#else
			sleep((int) (timebase*length));
#endif
			length=0;
			isfloat=0;
		}else if(*song>='0' && *song<='9'){
			if(isfloat==0){
				length*=10;
				length+=(*song-'0');
			}else{
				length+=((*song-'0')/pow(10,isfloat));
				++isfloat;
			}
		}else if(*song=='.'){
			isfloat=1;
		}else if(*song=='|'){
			repeatfrom=song;
			repeatlevel=level;
		}else if(*song==':'){
			if(alreadyrepeat==0){
				song=repeatfrom;
				level=repeatlevel;
				alreadyrepeat=1;
			}else{
				alreadyrepeat=0;
			}
		}else if(*song!=' ' && *song!='\n'){
			if(length==0){
				length=default_length;
			}
#ifdef FREEBSD
			beep(fq(*song,level),(int) (timebase*length));
#else
			beep(fq(*song,level),(int) (timebase*length));
#endif
			length=0;
			isfloat=0;
		}
		++song;
	}
}

int fq(char c,float lv){
	float freq[256];
	freq['C']=261.6255653;
	freq['d']=277.1826309;
	freq['D']=293.6647679;
	freq['e']=311.1269837;
	freq['f']=freq['E']=329.6275569;
	freq['F']=349.2282314;
	freq['g']=369.9944227;
	freq['G']=391.9954359;
	freq['a']=415.3046975;
	freq['A']=440.0;
	freq['b']=466.1637615;
	freq['c']=freq['B']=493.8833012;
return (int) (freq[c]*pow(1.059463,capo)*pow(2.0,lv));
}
