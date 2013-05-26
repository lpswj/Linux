/*
 *CD Datebase Application
 2013-05-26
 * */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#define MAX_STRING (80)			/* Longest allowed response */
#define MAX_ENTRY (1024)		/* Longest allowed database entry */

#define MESSAGE_LINE 6			/* Misc.message go here */
#define ERROR_LINE 22			/* The line to use for errors */
#define Q_LINE 20				/* Line for Questions */
#define PROMPT_LINE 18			/* Line for prompting on */

/*
 *The variable current_cd is used to store the CD title we are working with.
 *current_cat will be used to record the catalog number of the current cd.
 */
static char current_cd[MAX_STRING] = '\0';
static char current_cat[MAX_STRING];

/*
 * File names.
 */
const char *title_file = "title.cdb";
const char *tracks_file = "tracks.cdb";
const char *temp_file = "cdb.tmp";

/* Prototypes for local functions */
void clear_all_screen(void);
void get_return(void);
int get_confirm(void);
int getchoice(char *greet,char *choices[]);
void draw_menu(char *options[],int highlight,int start_row,int start_col);
void insert_title(char *cdtitle);
void get_string(char *string);
void add_record(void);
void count_cds(void);
void find_cd(void);
void list_tracks(void);
void remove_tracks(void);
void remove_cd(void);
void update_cd(void);

/*
 *	Menu structures
 */
char *main_menu[] =
{
		"add new CD",
		"find CD",
		"count CDs and tracks in the catalog",
		"quit",
		0,
};

char *extended_menu[] =
{
		"add new CD",
		"find CD",
		"count CDs and tracks in the catalog",
		"list tracks on current CD",
		"remove current CD",
		"update track information",
		"quit",
		0,
};

int main()
{
		int choice;

		initscr();

		do{
				choice = getchoice("Options:",current_cd[0] ? extended_menu:main_menu);
				switch(choice){
						case 'q':
								break;
						case 'a':
								add_record();
								break;
						case 'c':
								count_cds();
								break;
						case 'f':
								find_cd();
								break;
						case 'l':
								list_tracks();
								break;
						case 'r':
								remove_cd();
								break;
						case 'u':
								update_cd();
								break;
							}
		}while(choice != 'q');
		
		endwin();
		exit(EXIT_SUCCESS);
}
		



