#include "universal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH_DEFAULT 80

Data_t Local;
_Bool buffered;
short quit_chosen;
short width;

int main()
{
  _Bool on= 1;
  char temp[128];
  char t;

  width= WIDTH_DEFAULT;
  Local.state='i';
  Local.previous='q';
  Local.chosen= 1;
  Local.health= 3;

  while(on)
    {
      next_page();
      
      if(!Local.health)
        Local.state='g';
      else if(Local.Battle.enemies && Local.state!='q')
        Local.state='b';

      switch(Local.state)
        {
        case'i':
          print_intro();
          Local.state='m';
          if(!press_a())
            on=0;
          continue;
        case'm':
          print_menu();
          if(choice(&Local.chosen, 4))
            switch(Local.chosen)
              {
              case 1:
                deleteChoices(&Local.Events);
                readsaves();
                do{
                  next_page();
                  print_Choices(&Local.Events,Local.chosen);
                }while(!choice(&Local.chosen, Local.Events.choices)&& Local.state!='q');
                if(Local.Events.choices && Local.state!='q')
                  {
                    select(&Local.Events, Local.name, Local.chosen);
                    deleteChoices(&Local.Events);
                    load();
                  }
                if(Local.state=='q')
		  {
		    switch_state();
		    deleteChoices(&Local.Events);
		    Local.chosen= 1;
		  }
                continue;
              case 2:
                if(new_name())
                  {
                    Local.state='t';
                    Local.phase='i';
                    strcpy(Local.id,"Start");
                    Local.done= 0;
                    Local.enemy_chosen= 0;
                    Local.item_chosen= 1;
                    Local.use_chosen= 1;
                    Local.health= 3;
                    save();
                  }
                if(!press_a())
		  {
		    Local.state= 'm';
		    Local.previous= 'q';
		  }
                continue;
              case 3:
		while(1)
		  {
		    next_page();
		    print_imp();
		    if(choice(&width, 120))
		      break;
		    if(Local.state=='q')
		      {
			switch_state();
			width= WIDTH_DEFAULT;
			break;
		      }
		  }
                continue;
              case 4:
                next_page();
                deletesaves();
                if(!press_a())
                  switch_state();
                continue;
              }
          else
            continue;
        case't':
          strcpy(temp,Local.id);
	  deleteChoices(&Local.Events);
          readevent(temp, &t);
          if(press_a())
            {
              strcpy(Local.id,temp);
              Local.state= t;
              Local.done= 0;
            }
          continue;
        case'c':
          print_Choices(&Local.Events, Local.chosen);
          if(choice(&Local.chosen, Local.Events.choices))
            {
              select(&Local.Events, Local.id, Local.chosen);
              deleteChoices(&Local.Events);
              Local.state='t';
            }
          continue;
        case'b':
          battle();
          continue;
        case'g':
          print_gameover();
          if(!press_a())
            on=0;
          else
            {
              deleteItems(&Local.Bag);
              Local.state='i';
              Local.chosen= 1;
            }
          continue;
        case'q':
          print_quit(&quit_chosen);
          if(choice(&quit_chosen, 3))
            switch(quit_chosen)
              {
              case 1:
                if(Local.previous!='m')
                  {
                    switch_state();
                    save();
                    switch_state();
                    press_a();
                  }
                continue;
              case 2:
                deleteItems(&Local.Bag);
		deleteEnemies(&Local.Battle);
                Local.chosen= 1;
                Local.state='m';
                Local.previous='q';
                continue;
              case 3:
                on= 0;
                continue;
              }
        }
    }
  next_page();
  return 0;
}
