#include "mbed.h"
#include <ctype.h>
InterruptIn button1(p7);
InterruptIn button2(p8);
DigitalOut outbytes[10]={p21,p22,p23,p24,p25,p26,p27,p28,p29,p30};
DigitalOut outbytes2[10]={p20,p19,p18,p17,p16,p15,p14,p13,p12,p11};
DigitalOut mining(LED1);

/*
 * Set these constants to the values of the pins connected to the SureElectronics Module
 * For mbed, use WR=p7, DATA=p5, cs1=p17, cs2=p18, cs3=p19, cs4=p20
 */
void stop_mining(){
    printf("TOP");
}
void start_mining(){
    printf("ART");
}
int main() {
    mining=0;
    button2.rise(&stop_mining); 
    button1.rise(&start_mining); 
    for(int i=0; i<10; i++)
        outbytes[i]=0;
    char buf[20];
    char temp[4]= {'0'};
    temp[3]='\0';
    char speed[6]= {'0'};
    speed[5]='\0';
    // int matrix[16][8];
    double fspeed=0;
    int ispeed=0;
    int itemp=0;
    while(1) {
        scanf("%s", buf);
        if(buf[0]=='B' && buf[1]=='T') {
            for(int i=2; i<6; i++) {
                if(isdigit(buf[i]))
                    temp[i-2]=buf[i];
                else if(buf[i]=='S') {
                    temp[i-2]='\0';
                    mining=1;
                    for(int j=++i; j<i+6; j++) {
                        if(buf[j]=='.' || isdigit(buf[j]))
                            speed[j-i]=buf[j];
                        else {
                            speed[j-i]='\0';
                            break;
                        }
                    }
                    break;
                } else {
                    mining=0;
                    temp[i-2]='\0';
                    break;
                }
            }
        }
        fspeed=atof(speed);
        itemp=atoi(temp);
        //speed Range: 2.05-2.15
        //temp Range: 35-75
        itemp=(itemp-35)/5;
        for(int i=0; i<10; i++) {
            if(i<=itemp)
                outbytes[i]=1;
            else
                outbytes[i]=0;
        }
        ispeed=(int)((fspeed-2.05)*100);
        if(mining==1)
            for(int i=0; i<10; i++) {
                if(i<=ispeed)
                    outbytes2[i]=1;
                else
                    outbytes2[i]=0;
            }
        else
            for(int i=0; i<10; i++) {
                    outbytes2[i]=0;
            }
        //printf(buf);      
    }
}
