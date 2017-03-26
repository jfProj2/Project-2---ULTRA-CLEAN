/**
PROJECT 2
**************

File: methods3.h

Date: 3/27/2017

Authors: Ryan Joiner (810638856)
         Emma Fick   (810609119)

Prof. Michael Cotterell
**************

<NEED DESCRIPTION>

This is the supporting method file for Project2.

<NEED DESCRIPTION>
**/

#ifndef METHODS3_H
#define METHODS3_H

//########
//INCLUDES
//########
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <curses.h>
#include <ncurses.h>
#include <menu.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <form.h>

#include "methods_main.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

//##########
//PROTOTYPES
//##########
using namespace std;

int show_menu_window(int menu_h, int menu_w, int menu_y, int menu_x);
int show_error_window(int code, int err_h, int err_w, int err_y, int err_x);
string show_open_window(int open_h, int open_w, int open_y, int open_x);
int show_save_window(int save_h, int save_w, int save_y, int save_x);

//###################
//METHOD DESCRIPTIONS
//###################

//NEEDS JAVADOC
int show_menu_window(int menu_h, int menu_w, int menu_y, int menu_x){
  WINDOW *menu_win;
  WINDOW *menu_subwin;
  MENU *main_menu;
  ITEM **items;
  initscr();
  const char * choices[] = {"Open","Save","Save As", "Exit"};
  int n_choices = ARRAY_SIZE(choices);
  items = (ITEM**)calloc(n_choices+1, sizeof(ITEM*));
  for(int i = 0; i < n_choices; i++){
    items[i] = new_item(choices[i], NULL);
  }
  items[n_choices] = (ITEM*)NULL;
  main_menu = new_menu((ITEM**)items);
  menu_win = newwin(menu_h, menu_w, menu_y, menu_x);
  menu_subwin = derwin(menu_win, (menu_h/2), (menu_w/2), (menu_h*0.4), (menu_w/3));
  keypad(menu_win, true);
  set_menu_win(main_menu, menu_win);
  set_menu_sub(main_menu, menu_subwin);
  set_menu_mark(main_menu, "* ");
  box(menu_win, 0, 0);
  wrefresh(menu_win);
  cbreak();
  post_menu(main_menu);
  wrefresh(menu_win);

  int key = 1;
  int choice = 0;
  bool selected = false;

  while(key != KEY_F(1) && !selected){
    key = wgetch(menu_win);
    switch(key){
    case KEY_DOWN:
      menu_driver(main_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(main_menu, REQ_UP_ITEM);
      break;
    case 10:
      //MORE TO DO HERE
      //menu_driver(main_menu,REQ_TOGGLE_ITEM);
      // cur_item= current_item(main_menu);
      selected = true;
      break;
    }
    wrefresh(menu_win);
  }

  if(selected){
    ITEM *cur_item = current_item(main_menu);
    const char * it = item_name((const ITEM*)cur_item);
    if(strcmp(it,"Open") == 0){
      choice = 1;
    } else if (strcmp(it,"Save") == 0){
      choice = 2;
    } else if (strcmp(it,"Save As") == 0){
      choice = 3;
    } else if (strcmp(it,"Exit") == 0){
      choice = 4;
    }
  }

  unpost_menu(main_menu);
  for(int i=0; i < n_choices; i++){
    free_item(items[i]);
  }

  wborder(menu_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(menu_win);
  //mvprintw(2, (menu_w/2)-4, NULL);
  wrefresh(menu_win);
  free_menu(main_menu);
  wrefresh(menu_win);
  delwin(menu_subwin);
  delwin(menu_win);
  // endwin();
  return choice; //USER EXITS MENU (F1 Pressed)
}


//NEEDS CLEANING
//NEEDS JAVADOC
int show_error_window(int code, int err_h, int err_w, int err_y, int err_x){
  WINDOW *error_win;
  WINDOW *error_subwin;
  MENU *error_menu;
  ITEM **items;
  initscr();
  const char * choices[] = {"Yes", "No"};
  int n_choices = ARRAY_SIZE(choices);
  items = (ITEM**)calloc(n_choices+1, sizeof(ITEM*));
  for(int i = 0; i < n_choices; i++){
    items[i] = new_item(choices[i], NULL);
  }
  items[n_choices] = (ITEM*)NULL;
  error_menu = new_menu((ITEM**)items);
  error_win = newwin(err_h, err_w, err_y, err_x);
  error_subwin = derwin(error_win, (err_h/2), (err_w/2), (err_h*0.4), (err_w/3));
  keypad(error_win, true);


  set_menu_win(error_menu, error_win);
  set_menu_sub(error_menu, error_subwin);
  set_menu_mark(error_menu, "* ");
  box(error_win, 0, 0);
  wrefresh(error_win);
  cbreak();
  post_menu(error_menu);
  wrefresh(error_win);

  int key = 1;
  int choice = 0;
  bool selected = false;

  while(key != KEY_F(1) && !selected){
    key = wgetch(error_win);
    switch(key){
    case KEY_DOWN:
      menu_driver(error_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(error_menu, REQ_UP_ITEM);
      break;
    case 10:
      //MORE TO DO HERE?
      selected = true;
      break;
    }
    wrefresh(error_win);
  }

  if(selected){
    ITEM *cur_item = current_item(error_menu);
    const char * it = item_name((const ITEM*)cur_item);
    if(strcmp(it,"Open") == 0){
      choice = 1;
    } else if (strcmp(it,"Save") == 0){
      choice = 2;
    } else if (strcmp(it,"Save As") == 0){
      choice = 3;
    } else if (strcmp(it,"Exit") == 0){
      choice = 4;
    }
  }

  unpost_menu(error_menu);
  for(int i=0; i < n_choices; i++){
    free_item(items[i]);
  }

  wborder(error_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(error_win);
  //mvprintw(2, (menu_w/2)-4, NULL);
  wrefresh(error_win);
  free_menu(error_menu);
  wrefresh(error_win);
  delwin(error_subwin);
  delwin(error_win);
  // endwin();
  return choice; //USER EXITS MENU (F1 Pressed)
}

//NEEDS CLEANING
//NEEDS JAVADOC
string show_open_window(int open_h, int open_w, int open_y, int open_x){
  WINDOW *open_win;
  WINDOW *open_subwin;
  //forms stuff
  FORM *form;
  string filename = "";
  FIELD *field[2];

  initscr();
  cbreak();
  keypad(stdscr, true);
 

  field[0] = new_field(1, open_w/2, 0, 0, 0, 0);
  field[1] = NULL;
  set_field_back(field[0], A_UNDERLINE);

  form = new_form(field);
  //scale?
  
  open_win = newwin(open_h, open_w, open_y, open_x);
  open_subwin = derwin(open_win, (open_h/2), (open_w/2), (open_h*.4), (open_w/4));
  
  keypad(open_win, true);
  

  set_form_win(form, open_win);
  set_form_sub(form, open_subwin);
  box(open_win, 0, 0);
  // box(form, 0, 0);
  post_form(form);
  mvwprintw(open_win, 1, open_w/2 -9, "Enter File to Open");
  mvwprintw(open_win, 2, open_w/2 -7, "And Press Enter");
  
  wrefresh(open_win);
  refresh();
  
  int ch;
  bool selected = false;
  while((ch = wgetch(open_win)) != KEY_F(1) && !selected){
    if(ch >= 32 && ch < 127){
      form_driver(form, ch);
      filename += ch;
    }
    else if(ch == 10){
      selected = true;
    }
  }

  // wrefresh(open_win);
  unpost_form(form);
  free_form(form);
  free_field(field[0]);
  free_field(field[1]);
  delwin(open_win);
  delwin(open_subwin);
  //endwin();
  wborder(open_win,' ',' ',' ',' ',' ',' ',' ',' ');
  clear();
  return filename; //USER EXITS MENU (F1 Pressed)
}

//NEEDS CLEANING
//NEEDS JAVADOC

int show_save_window(int save_h, int save_w, int save_y, int save_x){
  WINDOW *save_win;
  WINDOW *save_subwin;
  MENU *save_menu;
  ITEM **items;
  initscr();
  const char * choices[] = {"Yes", "No", "Cancel"};
  int n_choices = ARRAY_SIZE(choices);
  items = (ITEM**)calloc(n_choices+1, sizeof(ITEM*));
  for(int i = 0; i < n_choices; i++){
    items[i] = new_item(choices[i], NULL);
  }
  items[n_choices] = (ITEM*)NULL;
  save_menu = new_menu((ITEM**)items);
  save_win = newwin(save_h, save_w, save_y, save_x);
  mvwprintw(save_win, 1, (save_w/2 - 9),"Do you wish to save?");
  save_subwin = derwin(save_win, (save_h/2), (save_w/2), (save_h*0.4), (save_w/3));
  keypad(save_win, true);

  set_menu_win(save_menu, save_win);
  set_menu_sub(save_menu, save_subwin);
  set_menu_mark(save_menu, "* ");
  
  // mvwprintw(save_win, 1, open_w/2 -9, "Enter File to Open");
  box(save_win, 0, 0);
  wrefresh(save_win);
  refresh();
  cbreak();
  post_menu(save_menu);
  wrefresh(save_win);

  int key = 1;
  int choice = 0;
  bool selected = false;

  while(!selected){
    key = wgetch(save_win);
    switch(key){
    case KEY_DOWN:
      menu_driver(save_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(save_menu, REQ_UP_ITEM);
      break;
    case 10:
      //MORE TO DO HERE?
      selected = true;
      break;
    }
    wrefresh(save_win);
  }

  if(selected){
    ITEM *cur_item = current_item(save_menu);
    const char * it = item_name((const ITEM*)cur_item);
    if(strcmp(it,"No") == 0){
      choice = 0;
    } else if (strcmp(it,"Yes") == 0){
      choice = 1;
    } else if (strcmp(it,"Cancel") == 0){
      choice = 2;
    }
  }

  unpost_menu(save_menu);
  for(int i=0; i < n_choices; i++){
    free_item(items[i]);
  }

  wborder(save_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  mvwprintw(save_win, save_y+10, save_x+10,"");
  wrefresh(save_win);
  //mvprintw(2, (menu_w/2)-4, NULL);
  wrefresh(save_win);
  free_menu(save_menu);
  wrefresh(save_win);
  wclear(save_win);
  wclear(save_subwin);
  refresh();
  delwin(save_subwin);
  delwin(save_win);
  // endwin();
  wclear();
  return choice; //USER EXITS MENU (F1 Pressed)
}


#endif



/**OLD OPEN
//NEEDS CLEANING
//NEEDS JAVADOC
int show_open_window(int open_h, int open_w, int open_y, int open_x){
  WINDOW *open_win;
  WINDOW *open_subwin;
  MENU *open_menu;
  ITEM **items;

  //forms stuff
  FORM *form;
  FIELD *field[1];
  field[0] = new_field(1, open_w/2, 0, 0, 0, 0);
  form = new_form(field);
  post_form(form);
  refresh();
  
  //</> forms stuff
  
  initscr();
  const char * choices[] = {"Open"};
  int n_choices = ARRAY_SIZE(choices);
  items = (ITEM**)calloc(n_choices+1, sizeof(ITEM*));
  for(int i = 0; i < n_choices; i++){
    items[i] = new_item(choices[i], NULL);
  }
  items[n_choices] = (ITEM*)NULL;
  open_menu = new_menu((ITEM**)items);
  open_win = newwin(open_h, open_w, open_y, open_x);
  open_subwin = derwin(open_win, (open_h/2), (open_w/2), (open_h*0.4), (open_w/3));
  keypad(open_win, true);
  set_menu_win(open_menu, open_win);
  set_menu_sub(open_menu, open_subwin);
  set_menu_mark(open_menu, "* ");
  box(open_win, 0, 0);
  wrefresh(open_win);
  cbreak();
  post_menu(open_menu);
  wrefresh(open_win);

  int key = 1;
  int choice = 0;
  bool selected = false;

  while(!selected){
    key = wgetch(open_win);
    switch(key){
    case KEY_DOWN:
      menu_driver(open_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(open_menu, REQ_UP_ITEM);
      break;
    case 10:
      //MORE TO DO HERE?
      selected = true;
      break;
    }
    wrefresh(open_win);
  }
  if(selected){
    ITEM *cur_item = current_item(open_menu);
    const char * it = item_name((const ITEM*)cur_item);
    if(strcmp(it,"Open") == 0){
      choice = 1;
    }
  }

  unpost_menu(open_menu);
  for(int i=0; i < n_choices; i++){
    free_item(items[i]);
  }

  // wborder(open_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(open_win);
  //mvprintw(2, (menu_w/2)-4, NULL);
  wrefresh(open_win);
  unpost_form(form);
  free_form(form);
  free_field(field[0]);
  free_menu(open_menu);
  wrefresh(open_win);
  delwin(open_subwin);
  delwin(open_win);
  // endwin();
  return choice; //USER EXITS MENU (F1 Pressed)
}

//NEEDS CLEANING
//NEEDS JAVADOC
*/
