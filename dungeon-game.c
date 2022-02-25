// Written by Tunahan DANIŞ(B1905.010027)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getinput(); // Declaring all the functions
void commandgo(char *obj);
void commandlook(char *obj);
void takeitem(char *obj);
void checkinv();
void killguard();
void skull();
static int executecommand();
char input[100];
int playerlocation=1,k=0,m=0;

struct items
{
	const char *usertag;
	const char *description;
	struct items *location;
	bool inventory;
	bool permission;
};
struct items locsnitems[12] // Items and locations have various uses in this game, some doesn't have specific attributes. Such as rocky place having no 'location' since it's already a location
{
	{"player",NULL,&locsnitems[playerlocation],false,NULL},
	{NULL,"an empty room with literally nothing but a door that leads to north, most likely to another room(type 'go north')",NULL,false,NULL},
	{"north","a room with lots of ivies, trees and many other plants. Feels like you are in the middle of a dangerous forest.\nThere is a door that leads to west.",NULL,false,NULL},
	{"west","a room full of rocks. There is a ladder you can 'go up' with.",NULL,false,NULL},
	{"up","a room that looks like an arena. There is a door that leads to south.",NULL,false,NULL},
	{"south","a room full of ice and snow. You are freezing right now. There is a door that leads to east.",false,NULL},
	{"east","a room with no light except a sparkling skull. This skull is bigger and far more horrifying than all the others.\nThis may be due to the lack of light or the skull itself.(type 'skull')",NULL,false,NULL},
	{"violet","a stone that sparkles with beautiful violet rays.",&locsnitems[3],false,false},
	{"red","a stone that sparkles with beautiful red rays.",&locsnitems[2],false,false},
	{"blue","a stone that sparkles with beautiful blue rays.",&locsnitems[5],false,false},
	{"sword","a rusty sword",&locsnitems[2],false,NULL},
	{"guard","a scary looking guard who protects the entrance to the south.",&locsnitems[4],false,NULL}
};
int main()
{
	printf("Welcome to a dungeon game with low budget and programming skills.\nYou can type 'look around' at every stage of the game in order to receive info about environment and what to do next.");
	getinput();
	while(executecommand())  // This loop executes getinput and executecommand forever until user enters 'quit' , stated below.
	{
		getinput();
	}
	return 0;
}
void getinput() // This function is the only source for getting input from user
{
	printf("\n--> ");
	char *p=input;
	gets(p);
}
static int executecommand() // This function calls almost all the other functions with command from user
{
	if(strcmp(input,"quit")==0)
	{
		return 0;
	}
	char *verb=strtok(input," ");
	char *obj=strtok(NULL," ");
	if(verb != NULL)
	{
		if(strcmp(verb,"go")==0)
		{
			if(obj!=NULL)
			{
				commandgo(obj);
				if(m==1) puts("Done.");
				else if(m==0) printf("I don't know that direction.");
				m=0;
			}
			else printf("go 'where'?");
		}
		else if(strcmp(verb,"look")==0)
		{
			if(obj!=NULL)
			{
				if(strcmp(obj,"around")!=0) printf("I don't know how to look there.");
				commandlook(obj);
			}
			else printf("look 'where'?");
		}
		else if(strcmp(verb,"take")==0)
		{
			if(obj!=NULL)
			{
				takeitem(obj);
			    if(k==0) printf("There is no '%s' to take.",obj);
				else if(k==1) printf("Done(you can see your items by typing 'inventory')");
				k=0;
			}
			else printf("take 'what'?");
		}
		else if(strcmp(verb,"inventory")==0) checkinv();
		else if(strcmp(verb,"kill")==0) killguard();
		else if(strcmp(verb,"skull")==0) skull();
	}
	return 1;
}
void commandgo(char *obj)
{
	if(strcmp(obj,locsnitems[2].usertag)==0)
	{
		playerlocation=2;
		m=1;
	}
	else if(strcmp(obj,locsnitems[3].usertag)==0)
	{
		playerlocation=3;
		m=1;
	}
	else if(strcmp(obj,locsnitems[4].usertag)==0)
	{
		playerlocation=4;
		m=1;
	}
	else if(strcmp(obj,locsnitems[5].usertag)==0 && locsnitems[11].location == NULL)
	{
		playerlocation=5;
		m=1;
	}
	else if(strcmp(obj,locsnitems[5].usertag)==0 && locsnitems[11].location != NULL)
	{
		printf("There is a guard that holds the entrance to the south. You can kill him with a sword(type kill)");
		m=2;
	}
	else if(strcmp(obj,locsnitems[6].usertag)==0)
	{
		playerlocation=6;
		m=1;
	}
	else if(strcmp(obj,locsnitems[7].usertag)==0)
	{
		playerlocation=7;
		m=1;
	}
}
void commandlook(char *obj)
{
	if(strcmp(obj,"around")==0) printf("It is %s",locsnitems[playerlocation].description);
	if(playerlocation==2 && locsnitems[10].inventory==false && strcmp(obj,"around")==0) printf("\nAlso lays a sword you could barely see inside the bushes(type 'take sword')");
	if(playerlocation==2 && locsnitems[8].inventory==false && strcmp(obj,"around")==0) printf("\nThere is also a skull with a sparkling red stone behind its teeth. You could speak with skull to get it(type 'skull')");
	if(playerlocation==3 && locsnitems[7].inventory==false && strcmp(obj,"around")==0) printf("\nThere is also a sparkling violet stone in skull. You could try to speak with skull to get it(type 'skull')");
	if(playerlocation==5 && locsnitems[9].inventory==false && strcmp(obj,"around")==0) printf("\nThere is also a skull with a sparkling blue stone behind its teeth.\nYou could speak with skull to get it(type 'skull')");
}
void takeitem(char *obj)
{
	if(strcmp(obj,locsnitems[7].usertag)==0 && playerlocation==3 && locsnitems[7].permission == true)
	{
		k=1;
		locsnitems[7].inventory=true;
	}
    else if(strcmp(obj,locsnitems[7].usertag)==0 && playerlocation==3 && locsnitems[7].permission == false)
	{
		printf("Speak with the skull to get the stone(type 'skull')");
		k=2;
	}
	if(strcmp(obj,locsnitems[8].usertag)==0 && playerlocation==2 && locsnitems[8].permission == true)
	{
		k=1;
		locsnitems[8].inventory=true;
	}
	else if(strcmp(obj,locsnitems[8].usertag)==0 && playerlocation==2 && locsnitems[8].permission == false)
	{
		printf("Speak with the skull to get the stone(type 'skull')");
		k=2;
	}
	if(strcmp(obj,locsnitems[9].usertag)==0 && playerlocation==5 && locsnitems[9].permission == true)
	{
		k=1;
		locsnitems[9].inventory=true;
	}
	else if(strcmp(obj,locsnitems[9].usertag)==0 && playerlocation==5 && locsnitems[9].permission == false)
	{
		printf("Speak with the skull to get the stone(type 'skull')");
		k=2;
	}
	if(strcmp(obj,locsnitems[10].usertag)==0 && playerlocation==2)
	{
		k=1;
		locsnitems[10].inventory=true;
	}
}
void checkinv()
{
	printf("You see:\n");
	for(int i=7;i<11;i++)
	{
		if(locsnitems[i].inventory==true)
		{
			printf("%s\n",locsnitems[i].description);
		}
	}
}
void killguard()
{
	if(locsnitems[10].inventory==true && playerlocation==4)
	{
		printf("You challenged the guard to fight you and he gladly accepted it.\nSwords slashed, blood splattered and you finally won after a dangerous battle. Entrance to the south is now open.");
		locsnitems[11].location=NULL;
	}
	else if(locsnitems[10].inventory==true && playerlocation!=4) printf("There is noone to kill.");
	else if(locsnitems[10].inventory==false && playerlocation==4) printf("You need a sword."); 
}
void skull()
{
	char ans1[10],ans2[10],ans3[10],ans4[10];
	if(playerlocation==2)
	{
		printf("WELCOME MORTAL. IN ORDER FOR YOU TO ESCAPE THIS DUNGEON, YOU MUST COLLECT ALL THREE STONES AND REACH THE FINAL STAGE.\nI HAVE THE FIRST STONE, RED. BEAUTIFUL INDEED, BUT YOU MUST EARN IT WITH YOUR KNOWLEDGE.\n");
		printf("YOU KNOW THE SAYING 'NOTHING TRAVELS FASTER THAN LIGHT'. WHAT ACTUALLY TRAVELS BUT DOES NOT CONTRADICT THIS SAYING?\n-> "); gets(ans1);
		if(strcmp(ans1,"space")==0)
		{
			printf("CORRECT, YOU MAY TAKE THE STONE.\nThe skull's mouth suddenly opens and you could clearly see the magical stone(type 'take red'. Then 'go west')");
			printf("\n*Don't forget to take the sword if you haven't*");
			locsnitems[8].permission=true;
		}
		else
		{
			while(true)
			{
				printf("TRY AGAIN.\n-> "); gets(ans1);
				if(strcmp(ans1,"space")==0)
				{
					printf("CORRECT, YOU MAY TAKE THE STONE.\nThe skull's mouth suddenly opens and you could clearly see the magical stone(type 'take red'. Then 'go west')");
			        locsnitems[8].permission=true;
			        printf("\n*Don't forget to take the sword if you haven't*");
			        break;
				}
			}
		}
    }
	if(playerlocation==3)
	{
		printf("I AM A GOD, A PLANET, AND ABLE TO MEASURE HEAT. WHAT AM I?\n-> "); gets(ans2);
		if(strcmp(ans2,"mercury")==0)
		{
			printf("CORRECT, YOU MAY TAKE THE STONE.\nThe skull's mouth suddenly opens and you could clearly see the magical 'violet' stone.");
			locsnitems[7].permission=true;
		}
		else
		{
			while(true)
			{
				printf("TRY AGAIN.\n-> "); gets(ans2);
				if(strcmp(ans2,"mercury")==0)
				{
					printf("CORRECT, YOU MAY TAKE THE STONE.\nThe skull's mouth suddenly opens and you could clearly see the magical 'violet' stone.");
			        locsnitems[7].permission=true;
			        break;
				}
			}
		}
	}
	if(playerlocation==5)
	{
		printf("SHOULD YOU START PLAYING LEAGUE OF LEGENDS?\n-> "); gets(ans3);
		if(strcmp(ans3,"no")==0)
		{
			printf("CORRECT, YOU MAY TAKE THE STONE.\nThe skull's mouth suddenly opens and you could clearly see the magical 'blue' stone.");
			locsnitems[9].permission=true;
		}
		else
		{
			while(true)
			{
				printf("TRY AGAIN.\n-> "); gets(ans3);
				if(strcmp(ans3,"no")==0)
				{
					printf("CORRECT, YOU MAY TAKE THE STONE.\nThe skull's mouth suddenly opens and you could clearly see the magical 'blue' stone.");
					locsnitems[9].permission=true;
				}
			}
		}
	}
	if(playerlocation==6)
	{
		printf("YOU'VE COME AT LAST. THIS IS YOUR FINAL CHALLENGE. NOW, GIVE ME THE MOST POWERFUL STONE YOU HAVE.\nBEWARE THOUGH, YOU HAVE ONLY ONE CHANCE. IF YOU FAIL, YOU SHALL DIE(give 'red/violet/blue')\n-> "); gets(ans4);
		if(strcmp(ans4,"give violet")==0)
		{
			printf("\nSEEMS YOU ARE WORTHY OF LIVING. YOU MAY GO NOW.\nA wall magically appears near you and you finally see the sunlight.\n\nGAME OVER");
			exit (EXIT_FAILURE);
		}
		else
		{
			printf("\nHOW UNFORTUNATE.\nYou suddenly hear the sound of a blade from total darkness.\n\nGAME OVER");
			exit (EXIT_FAILURE);
		}
	}
}
