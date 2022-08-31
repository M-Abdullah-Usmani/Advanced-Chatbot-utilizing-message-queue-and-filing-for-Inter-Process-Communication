struct mesg_buffer {
    long mesg_type;
    char mesg_text[50];
} message;
  
/*int main()
{
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
  
    // display the message
    printf("Data Received is : %s \n", 
                    message.mesg_text);

    msgctl(msgid, IPC_RMID, NULL);
  
    return 0;
}*/
#include "functions.h"
#define MAXSIZE 27
void enterkey(int * mecount,char str[],int line)
{
int ll;
int strlength=strlen(str);
			if(strlength<25)
			{
				if(*mecount<22) // if we haven't reached the bottom of screen
				{
					printf("\033[%d;%dH\033[0m\033[30;43mYOU:\033[0m\033[32m %s",*mecount,line,str);
					printf("\033[30m\033[23;0H\033[K\r\033[42mTYPE:\033[47m");
					*mecount=*mecount+1;
				}
				else  //if we have reached the bottom of the screen
				{
					printf("\033[0m\033[%d;0H\033[K\r\033[0m\033[%d;%dH\033[30;43mYOU:",*mecount,*mecount,line);
					printf("\033[0m\033[32m %s\033[0m\033[23;0H\033[K\n\n\033[23;0H\033[K\r\033[30m\033[42mTYPE:\033[47m",str);
				}
			}
			else
			{
				int doo=0;
				if(*mecount<22)
				{
					printf("\033[%d;%dH\033[0m\033[30;43mYOU:\033[0m\033[32m ",*mecount,line);
					*mecount=*mecount+1;
				}
				else
				{
					printf("\033[0m\033[%d;0H\033[K\033[%d;%dH\033[30;43mYOU:\033[0m\033[32m ",*mecount,*mecount,line);
					doo=1;
				}
				ll=0;
				for( ll=0;ll<strlength;ll++)
				{
					if(ll<23)
					printf("%c",str[ll]);
					else break;
				}
				if(*mecount<22)
				{
					printf("\033[0m\033[%d;0H\033[K\r\033[0m\033[%d;%dH    \033[0m\033[32m ",*mecount,*mecount,line);
					*mecount=*mecount+1;
				}
				else 
				{
 					if(doo==0)
					printf("\033[0m\033[%d;0H\033[K\033[%d;%dH    \033[0m\033[32m ",*mecount,*mecount,line);
					else
					printf("\033[0m\033[%d;0H\033[K\033[%d;%dH    \033[0m\033[32m ",*mecount+1,*mecount+1,line);
				}
				for( ll;ll<strlength;ll++)
				{
					printf("%c",str[ll]);
				}
				if(*mecount>=22)
				{
					if(doo==0)
					printf("\033[0m\033[23;0H\033[K\n\n\033[23;0H\r\033[30m\033[42mTYPE:\033[47m ");
					if(doo==1)
					printf("\033[0m\033[24;0H\n\n\033[23;0H\r\033[30m\033[42mTYPE:\033[47m ");
				}
				else
				printf("\033[30m\033[23;0H\033[K\r\033[42mTYPE:\033[47m ");
			}				
				for(int l=0;l<69;l++)
					printf(" "); //printing white background
				printf("\033[44m -> \033[47m"); 
				printf("\033[23;7H");
}
void Chatbot1(int signal)
{
int shmid;
key_t key;
char *shm, *s;
fflush(stdin);
key = 2211;
fflush(stdin);

if((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)
die("shmget");
if((shm = shmat(shmid, NULL, 0)) == (char*) -1)
die("shmat");
int fd,fd1;
int ret=mkfifo("myfifo",0666);
key_t key1;
int msgid;  
key1 = ftok("progfile", 65);
msgid = msgget(key1, 0666 | IPC_CREAT);
FILE *fptr;
double t1;


char str[50]={'\0'},str1[50]={'\0'};
system("clear"); //clear screen
printf("\033[23;0H\033[30m\033[42mTYPE:\033[47m "); //move to 2nd-last line,set background=green,print "TYPE" in black and set background=white
for(int l=0;l<69;l++)
printf(" "); //printing white background
printf("\033[44m -> \033[47m"); 
printf("\033[23;7H");
int i=0,mecount=1,tempflag=0,ll=0,counter=0,dp=0;
char c;
while(1)
{
	if(*shm=='!')
	{system("reset");
system("clear");
return;}	
	tempflag=1;
	if(*shm=='+')
	{
		if(counter==0)
		printf("\033[22;0H\033[30m\033[47mOther is typing...\033[23;%dH",i+7);
		counter=1;
	}
	else
	{
		if(*shm=='~')
		{printf("\033[0m\033[22;0H\033[K\033[23;%dH",i+7);
			counter=0;
			*shm='-';
		}	
		else if(*shm=='^')
		{
			printf("\033[0m\033[22;0H\033[K\033[23;%dH",i+7);
			wait(1);
			if(signal==0)
			{
				fd1=open("myfifo1",O_RDONLY);
				read(fd1,str1,sizeof(str1));
				t1=omp_get_wtime();
				close(fd1);
			}
			else if (signal==1)
			{
				message.mesg_type = 0;
				msgrcv(msgid, &message, sizeof(message), 1, 0);
				t1=omp_get_wtime();
				strcpy(str1,message.mesg_text);
			}
			//t1*=60;
			fptr = fopen("temp.txt","w");
 			fprintf(fptr,"%f",t1);
 			fclose(fptr);
		
			int strlength=strlen(str1);
			if(strlength<25)
			{
				if(mecount<22) // if we haven't reached the bottom of screen
				{
					printf("\033[%d;0H\033[0m\033[30;44mOTHER:\033[0m\033[36m %s",mecount,str1);
					printf("\033[30m\033[23;0H\033[K\r\033[42mTYPE:\033[47m");
					if(i>0)
					printf(" %s",str);
					mecount++;
				}
				else  //if we have reached the bottom of the screen
				{
					printf("\033[0m\033[%d;0H\033[K\r\033[0m\033[%d;0H\033[30;44mOTHER:",mecount,mecount);
					printf("\033[0m\033[36m %s\033[0m\033[23;0H\033[K\n\n\033[23;0H\033[K\r\033[30m\033[42mTYPE:\033[47m",str1);
if(i>0)
					printf(" %s",str);
				}
			}
			else
			{
				int doo=0;
				if(mecount<22)
				{
					printf("\033[%d;0H\033[0m\033[30;44mOTHER:\033[0m\033[36m ",mecount);
					mecount++;
				}
				else
				{
					printf("\033[0m\033[%d;0H\033[K\033[%d;0H\033[30;44mOTHER:\033[0m\033[36m ",mecount,mecount);
					doo=1;
				}
				ll=0;
				for( ll=0;ll<strlength;ll++)
				{
					if(ll<23)
					printf("%c",str1[ll]);
					else break;
				}
				if(mecount<22)
				{
					printf("\033[0m\033[%d;0H\033[K\r\033[0m\033[%d;0H      \033[0m\033[36m ",mecount,mecount);
					mecount++;
				}
				else 
				{
 					if(doo==0)
					printf("\033[0m\033[%d;0H\033[K\033[%d;0H      \033[0m\033[36m ",mecount,mecount);
					else
					printf("\033[0m\033[%d;0H\033[K\033[%d;0H      \033[0m\033[36m ",mecount+1,mecount+1);
				}
				for( ll;ll<strlength;ll++)
				{
					printf("%c",str1[ll]);
				}
				if(mecount>=22)
				{
					if(doo==0)
					printf("\033[0m\033[23;0H\033[K\n\n\033[23;0H\r\033[30m\033[42mTYPE:\033[47m ");
					if(doo==1)
					printf("\033[0m\033[24;0H\n\n\033[23;0H\r\033[30m\033[42mTYPE:\033[47m ");
				}
				else
				printf("\033[30m\033[23;0H\033[K\r\033[42mTYPE:\033[47m ");
				if(i>0)
					printf(" %s",str);
			}					
				for(int l=0;l<69-i;l++)
					printf(" "); //printing white background
				printf("\033[44m -> \033[47m"); 
				printf("\033[23;%dH",i+7);
				for(int ss=0;ss<strlength;ss++)
					str1[ss]='\0';
				//i=0;
			counter=0;
			*shm='-';
		}
	}
	
	if(kbhit() ) 	//search for a keypress
	{
		
		c=fgetc(stdin); 	//save the character on the pressed key
		while(u_kbhit()) 	// in case pressed key in held down
			getch();
		*(shm+1)='*';
		if(c==127) 	// to see if pressed key==backspace
		{
			if(i>0) 	//if we already 1 or more character types
			{
				printf("\b\033[47m \b"); //delete the previous typed character from screen
				i--;
				str[i]='\0'; //delete the previous typed character from string
			}
			if(i<=0)
			{*(shm+1)='~';
				//dp=1;
			continue;}
		}
		else if (c==27) // if pressed key==ESC
		{
			*(shm+1)='!';
			system("reset");
			system("clear");
			msgctl(msgid, IPC_RMID, NULL);
			return;		
		}
		else if (c==13 || c==10)  // if pressed key==Enter
		{
			enterkey(&mecount,str,50);
				i=0;
				*(shm+1)='^';
				counter=0;
				if(signal==0)
				{
					fd=open("myfifo",O_WRONLY);
					write (fd,str,sizeof(str));
					t1=omp_get_wtime();
					close(fd);
				}
				else if (signal==1)
				{
					message.mesg_type = 1;
					strcpy(message.mesg_text,str);
					t1=omp_get_wtime();
					msgsnd(msgid, &message, sizeof(message), 0);
				}
				//t1*=60;
				fptr = fopen("temp.txt","w");
 				fprintf(fptr,"%f",t1);
 				fclose(fptr);
				for(int ss=0;ss<sizeof(str);ss++)
				str[ss]='\0';
				continue;
		}
		else // is pressed key==of our use
		{
			printf("\033[30m\033[47m%c",c);//print entered character on screen in black with white background
			str[i]=c; // place it in string
			i++; //increment entered character counter
			if(i==30) //if size limit of entered string is reached
			{
				printf("\033[s\033[23;67H\033[0;31;47;5;4mToo much\033[u");//print "too much" in red
				while(1)
				{
					c=getch(); // catch typed character
					if (c==127) // if typed characte is backspace
					{
						printf("\033[s\033[23;67H         \033[u\b\033[47m \b");//delete previoustypedletter fromscreen
						i--;
						str[i]='\0';//delete the previous typed character from string
						break;
					}
					if (c==27) // if pressed key==ESC
					{
						*(shm+1)='!';
						 msgctl(msgid, IPC_RMID, NULL);
						return;
					}
					else if (c==13 || c==10)  // if pressed key==Enter
					{
						enterkey(&mecount,str,50);
						i=0;
						tempflag=1; //to indicate that enter has been pressed
						*(shm+1)='^';
						if(mecount>=22)
						counter=0;
						if(signal==0)
						{	
							fd=open("myfifo",O_WRONLY);
							write (fd,str,sizeof(str));
							t1=omp_get_wtime();
							close(fd);
						}
						else if (signal==1)
						{
							message.mesg_type = 1;
							strcpy(message.mesg_text,str);
							t1=omp_get_wtime();
							msgsnd(msgid, &message, sizeof(message), 0);
						}
						fptr = fopen("temp.txt","w");
 						fprintf(fptr,"%f",t1);
 						fclose(fptr);
						for(int ss=0;ss<sizeof(str);ss++)
							str[ss]='\0';
						break;
					}
				}

				if(tempflag==1)
				continue;
			}
		}
	}
}
}
int main()
{
system("clear");

Chatbot1(0);
sleep(4);
Chatbot1(1);
}
