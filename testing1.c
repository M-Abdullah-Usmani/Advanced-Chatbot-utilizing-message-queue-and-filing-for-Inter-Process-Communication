#include "functions.h"
#define MAXSIZE 27

struct mesg_buffer {
    long mesg_type;
    char mesg_text[50];
} message;

double averagepipe=0,averagequeue=0;

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
int ret=mkfifo("myfifo1",0666);
char sh[]="--";
*shm='-';
*(shm+1)='-';
key_t key1;
int msgid;  
key1 = ftok("progfile", 65);
msgid = msgget(key1, 0666 | IPC_CREAT);
double t1,t2,ff,countpipe=0,countqueue=0,sumpipe=0,sumqueue=0;
char str2[10]={'\0'};
FILE *fptr;
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
	if(*(shm+1)=='!')
	{	
		system("reset");
		system("clear");
		return;
	}	
	if(*(shm+1)=='*') //TO INDICATE THAT OTHER IS TYPING
	{
		if(counter==0)
		printf("\033[22;0H\033[30m\033[47mOther is typing...\033[23;%dH",i+7);
		counter=1;
	}
	else
	{
		if(*(shm+1)=='~') // IF OTHER IS NOT TYPING ANYMORE
		{printf("\033[0m\033[22;0H\033[K\033[23;%dH",i+7); //CLEAR "OTHER IS TYPING.." MESSAGE
		*(shm+1)='-';
		counter=0;}
		else if(*(shm+1)=='^') //IF OTHER HAS SENT A MESSAGE TO US
		{
			printf("\033[0m\033[22;0H\033[K\033[23;%dH",i+7);
			wait(1);
			if(signal==0) 
			{
				fd=open("myfifo",O_RDONLY);
				read(fd,str1,sizeof(str1));
				t1=omp_get_wtime();
				close(fd);
			}
			else if (signal==1)
			{
				message.mesg_type = 0;
				msgrcv(msgid, &message, sizeof(message), 1, 0);
				t1=omp_get_wtime();
				strcpy(str1,message.mesg_text);
			}ff=0;
			fptr = fopen("temp.txt","r");
 			fscanf(fptr,"%s",str2);
 			fclose(fptr);
			ff=atof(str2);
			if(t1>0 && ff>0 && t1>=ff)
			{
				if(t1<1)
				{
					t1-=ff;
					if(signal==0)
					{	
						countpipe++;
						sumpipe+=t1;
						averagepipe=sumpipe/countpipe;
					}
					else if (signal==1)
					{
						countqueue++;
						sumqueue+=t1;
						averagequeue=sumqueue/countqueue;
					}
				}
			}
			for (int lp=0;lp<sizeof(str2);lp++)
			str2[lp]='\0';
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
				for(int ss=0;ss<sizeof(str1);ss++)
					str1[ss]='\0';
				counter=0;
				*(shm+1)='-';
		}
	}

	tempflag=0;
	if(kbhit()) 	//search for a keypress
	{
		c=fgetc(stdin); 	//save the character on the pressed key
		while(u_kbhit()) 	// in case pressed key in held down
			getch();
			*shm='+';
		if(c==127) 	// to see if pressed key==backspace
		{
			if(i>0) 	//if we already 1 or more character types
			{
				printf("\b\033[47m \b"); //delete the previous typed character from screen
				i--;
				str[i]='\0'; //delete the previous typed character from string
			}
			if(i<=0)
			{*shm='~';
			continue;}
		}
		else if (c==27) // if pressed key==ESC
		{
			*shm='!';
			system("reset");
			system("clear");
			msgctl(msgid, IPC_RMID, NULL);
			return;		
		}
		else if (c==13 || c==10)  // if pressed key==Enter
		{
			enterkey(&mecount,str,50);
				i=0;
				*shm='^';
				if (signal==0)
				{
					fd=open("myfifo1",O_WRONLY);
					write (fd,str,sizeof(str));
					t1=omp_get_wtime();
					close(fd);
				}
				else if (signal==1)
				{
					message.mesg_type = 1;
					strcpy(message.mesg_text,str);
					msgsnd(msgid, &message, sizeof(message), 0);
					t1=omp_get_wtime();
				}
				ff=0;
				fptr = fopen("temp.txt","r");
 				 fscanf(fptr,"%s",str2);
 				 fclose(fptr);
				 ff=atof(str2);
	  			 if(t1>0 && ff>0 && t1>ff)
			 	 {
					t1-=ff;
					if(t1<1)
					{
						if(signal==0)
						{
							countpipe++;
							 sumpipe+=t1;
							  averagepipe=sumpipe/countpipe;
						}
						else if (signal==1)
						{
							countqueue++;
							 sumqueue+=t1;
							 averagequeue=sumqueue/countqueue;
						}
					}
				}
				for (int lp=0;lp<sizeof(str2);lp++)
				str2[lp]='\0';
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
						*shm='!';
						msgctl(msgid, IPC_RMID, NULL);
						return;
					}
					else if (c==13 || c==10)  // if pressed key==Enter
					{
						enterkey(&mecount,str,50);
						i=0;
						if(mecount>=22)
						counter=0;
						tempflag=1; //to indicate that enter has been pressed
						*shm='^';
						if(signal==0)
						{
							fd=open("myfifo1",O_WRONLY);
							write (fd,str,sizeof(str));
							t1=omp_get_wtime();
							close(fd);
						}
						else if (signal==1)
						{
							strcpy(message.mesg_text,str);
							msgsnd(msgid, &message, sizeof(message), 0);
							t1=omp_get_wtime();
						}
						ff=0;
						fptr = fopen("temp.txt","r");
 						 fscanf(fptr,"%s",str2);
 						 fclose(fptr);
						 ff=atof(str2);
	  					 if(t1>0 && ff>0 && t1>ff)
			 			 {
							t1-=ff;
							if(t1<1)
							{
								if(signal==0)
								{
									countpipe++;
									 sumpipe+=t1;
									  averagepipe=sumpipe/countpipe;
								}
								else if (signal==1)
								{
									countqueue++;
									 sumqueue+=t1;
									 averagequeue=sumqueue/countqueue;
								}
							}
						}
						for (int lp=0;lp<sizeof(str2);lp++)
						str2[lp]='\0';
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
printf("This is the chatbot game\n\nFirstly Filing will be used for communications\n\nPlease open another terminal to run the other process");
getch();
Chatbot1(0);
sleep(3);
system("clear");
Chatbot1(1);
printf("\t\tThe Average of IPC using filing:%f\n\t\tThe Average of IPC using message_queue: %f",averagepipe,averagequeue);
if(averagepipe<averagequeue)
printf("\n\n\n\n\tIn this particular scenario, filings gave better performance\n");
else if(averagepipe>averagequeue)
printf("\n\n\n\n\tIn this particular scenario, message_queue gave better performance\n");
else
printf("\n\n\n\n\tIn this particular scenario, both approaches gave equal performance\n");
getch();
}
