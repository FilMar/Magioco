#include "var.h"

void addAction(Enemy_t* Enemy, char* text, char type, short value);
void addEnemy(char* name, short health, short defence);
void addItem(Item_List* List, char* name, char type, int usev, unsigned short trwv, unsigned short defv, int uses);
Item_t* searchItem(char* id, Item_List* List);
