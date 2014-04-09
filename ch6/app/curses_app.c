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
static char current_cd[MAX_STRING] = "\0";
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
				choice = getchoice("Options:",current_cd[0] ? extended_menu : main_menu);
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
		


int getchoice(char *greet,char *choices[])
{
		static int selected_row = 0;
		int max_row = 0;
		int start_screenrow = MESSAGE_LINE,start_screencol = 10;
		char **option;
		int selected;
		int key = 0;

		option = choices;
		while(*option){
				max_row++;
				option++;
		}

		/* protect against menu getting shorted when CD deleted */
		if(selected_row >= max_row)
				selected_row = 0;

		clear_all_screen();
		mvprintw(start_screenrow - 2,start_screencol,greet);

		keypad(stdscr,TRUE);
		cbreak();
		noecho();

		key = 0;
		while(key != 'q' && key != KEY_ENTER && key != '\n'){
				if(key == KEY_UP){
						if(selected_row == 0)
								selected_row = max_row - 1;
						else
								selected_row--;
				}
				if(key ==KEY_DOWN){
						if(selected_row == (max_row - 1))
								selected_row = 0;
						else
								selected_row++;
				}
				selected = *choices[selected_row];
				draw_menu(choices,selected_row,start_screenrow,start_screencol);
				key = getch();
		}

		keypad(stdscr,FALSE);
		nocbreak();
		echo();

		if(key == 'q')
				selected = 'q';
		return(selected);

}

void draw_menu(char *options[],int current_highlight,int start_row,int start_col)
{
		int current_row = 0;
		char **option_ptr;
		char *txt_ptr;

		option_ptr = options;
		while(*option_ptr){
				if(current_row == current_highlight)
						attron(A_STANDOUT);
				txt_ptr = options[current_row];
				//why ++? mark
//				txt_ptr++;
				mvprintw(start_row + current_row,start_col,"%s",txt_ptr);
				if(current_row == current_highlight)
						attroff(A_STANDOUT);
				current_row++;
				option_ptr++;
		}

		mvprintw(start_row + current_row + 3,start_col,"Move highlight and then press Return ");

		refresh();
}


void clear_all_screen()
{
		clear();
		mvprintw(2,Q_LINE,"%s","CD Datebase Application");
		if(current_cd[0]){
				mvprintw(ERROR_LINE,0,"Current CD: %s: %s\n",current_cat,current_cd);
		}
		refresh();

}


void add_record()
{
		char catalog_number[MAX_STRING];
		char cd_title[MAX_STRING];
		char cd_type[MAX_STRING];
		char cd_artist[MAX_STRING];
		char cd_entry[MAX_STRING];

		int screenrow = MESSAGE_LINE;
		int screencol = 10;

		clear_all_screen();
		mvprintw(screenrow,screencol,"Enter new CD detail");
		screenrow += 2;

		mvprintw(screenrow,screencol,"Catalog Number: ");
		get_string(catalog_number);
		screenrow ++;

		mvprintw(screenrow,screencol,"		CD Title: ");
		get_string(cd_title);
		screenrow++;

		mvprintw(screenrow,screencol,"		 CD type: ");
		get_string(cd_type);
		screenrow++;

		mvprintw(screenrow,screencol,"		  Artist: ");
		get_string(cd_artist);
		screenrow++;

		mvprintw(15,5,"About to add this new entry:");
		sprintf(cd_entry,"%s,%s,%s,%s",catalog_number,cd_title,cd_type,cd_artist);
		mvprintw(17,5,"%s",cd_entry);
		refresh();

		move(PROMPT_LINE,0);
		if(get_confirm()){
				insert_title(cd_entry);
				strcpy(current_cd,cd_title);
				strcpy(current_cat,catalog_number);
		}
}


void get_return()
{
		int ch;
		mvprintw(23,0,"%s"," Press return ");
		refresh();
		while((ch = getchar()) != '\n' && ch != EOF)
				;
}

int get_confirm()
{
		int confirmed = 0;
		char first_char = 'N';

		mvprintw(Q_LINE,5,"Are you sure? ");
		clrtoeol();
		refresh();

		cbreak();
		first_char = getch();
		if(first_char == 'Y' || first_char == 'y')
				confirmed = 1;
		nocbreak();

		if(!confirmed){
				mvprintw(Q_LINE,1,"		Cancelled");
				clrtoeol();
				refresh();
				sleep(1);
		}
		return confirmed;
}


void insert_title(char *cdtitle)
{
		FILE *fp = fopen(title_file,"a");
		if(!fp)
				mvprintw(ERROR_LINE,0,"cannot open CD titles database");
		else
		{
				fprintf(fp,"%s\n",cdtitle);
				fclose(fp);
		}
}

void get_string(char *string)
{
		int len;

		wgetnstr(stdscr,string,MAX_STRING);
		len = strlen(string);
		if(len > 0 && string[len-1] == '\n')
				string[len - 1] ='\0';
}


void count_cds(void)
{
		FILE *titles_fp,*tracks_fp;
		char entry[MAX_ENTRY];
		int titles = 0;
		int tracks = 0;

		titles_fp = fopen(title_file,"r");
		if(titles_fp){
				while(fgets(entry,MAX_ENTRY,titles_fp))
						titles++;
				fclose(titles_fp);
		}
		tracks_fp = fopen(tracks_file,"r");
		if(tracks_fp){
				while(fgets(entry,MAX_ENTRY,tracks_fp))
						tracks++;
				fclose(tracks_fp);
		}
		mvprintw(ERROR_LINE,0,"Database contains %d titles,with a total of %d tracks.",titles,tracks);
		get_return();
				
}

void find_cd(void)
{
		char match[MAX_STRING],entry[MAX_STRING];
		FILE *titles_fp;
		int count = 0;
		char *found,*title,*catalog;

		mvprintw(Q_LINE,0,"Enter a string to search for in CD titles: ");
		get_string(match);

		titles_fp = fopen(title_file,"r");
		if(titles_fp)
		{
				//To review
				while(fgets(entry,MAX_ENTRY,titles_fp)){
						/* Skip past catalog number */
						catalog = entry;
						if(found = strstr(catalog,",")){
								*found = 0;
								title = found + 1;

		/* Zap the next comma in the entry to reduce it to title only */
								if(found = strstr(title,",")){
										*found = '\0';
										if(found = strstr(title,match)){
												count++;
												strcpy(current_cd,title);
												strcpy(current_cat,catalog);
										}
								}
						}
				}
				fclose(titles_fp);
		}
		if(count != 1){
				if(count == 0)
						mvprintw(ERROR_LINE,0,"Sorry,no matching CD found.");
				if(count > 1)
						mvprintw(ERROR_LINE,0,"Sorry,match is ambigous:%d CDs found. ",count);
				current_cd[0] = '\0';
				get_return();
		}
}

void list_tracks(void)
{

}

void remove_tracks(void)
{
		FILE *tracks_fp,*temp_fp;
		char entry[MAX_ENTRY + 1];
		int cat_length;

		if(current_cd[0] == '\0')
				return;

		cat_length = strlen(current_cat);
		if(tracks_fp == (FILE *)NULL)
				return;
		temp_fp = fopen(temp_file,"w");

}

void remove_cd(void)
{
}
void update_cd(void)
{
}
