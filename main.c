#include "function.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int choice;          // Khai bao bien choice
    int choiceCategory;   // Khai bao bien choiceCategory

    do {
        lobbyMenu(choice);
        scanf("%d", &choice);
        switch(choice){
            case 1:
                do {
                    // Lua chon 
                    danhmucMenu(choiceCategory); 
                    scanf("%d", &choiceCategory);
                    switch(choiceCategory){
                        case 1:
                            viewCategory();
                            break;
                        case 2:
                            addCategory();
                            break;
                        case 3:
                            editCategory(); 
                            break;
                        case 4:
                            deleteCategory();
                            break;
                    }
                } while(choiceCategory != 6);
                break;
            case 2:
                break;    
        }
    } while(choice != 3);
    return 0;
}

