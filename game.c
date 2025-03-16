#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// ~~~ FONT DEFINE ~~~

#define RESET "\033[0m"
#define RED "\033[31m"
#define ORANGE "\033[38;2;255;165;0m"
#define GREEN "\033[32m"
#define ITALIC "\033[3m"
#define BOLD "\033[1m"
#define CYAN "\033[36m"

// ~~~ DIED FUNCTION ~~~

void youDied(){

    printf("\n");
    printf(RED"██╗   ██╗ ██████╗ ██╗   ██╗    ██████╗ ██╗███████╗██████╗ \n");
    printf("╚██╗ ██╔╝██╔═══██╗██║   ██║    ██╔══██╗██║██╔════╝██╔══██╗ \n");
    printf(" ╚████╔╝ ██║   ██║██║   ██║    ██║  ██║██║█████╗  ██║  ██║ \n");
    printf("  ╚██╔╝  ██║   ██║██║   ██║    ██║  ██║██║██╔══╝  ██║  ██║ \n");
    printf("   ██║   ╚██████╔╝╚██████╔╝    ██████╔╝██║███████╗██████╔╝ \n");
    printf("   ╚═╝    ╚═════╝  ╚═════╝     ╚═════╝ ╚═╝╚══════╝╚═════╝  \n\n"RESET);        
    exit(0);                                          
}

// ~~~ SAVE GAME FUNCTION ~~~

void saveGame(char *name, int playerHp, int chapter) {

    FILE *file = fopen("savegame.txt", "w");
    if (file == NULL) {
        printf(RED "System" RESET ": Failed to save the game.\n");
        return;
    }

    fprintf(file, "%s\n", name);
    fprintf(file, "%d\n", playerHp);
    fprintf(file, "%d\n", chapter);

    fclose(file);
    printf(RED "System" RESET ": Game saved successfully.\n");
}

// ~~~ LOAD GAME FUNCTION ~~~

int loadGame(char *name, int *playerHp, int *chapter) {

    FILE *file = fopen("savegame.txt", "r");
    if (file == NULL) {
        printf(RED "System" RESET ": No saved game found.\n");
        return 0;
    }

    fscanf(file, "%s", name);
    fscanf(file, "%d", playerHp);
    fscanf(file, "%d", chapter);

    fclose(file);
    printf(RED "System" RESET ": Game loaded successfully.\n");
    return 1;
}

// ~~~ CLEAN INPUT BUFFER ~~~

void clean_input_buffer() {

    while (getchar() != '\n');
}

// ~~~ CLOSE GAME FUNCTION ~~~

void closegame() {

    printf("\n\033[38;2;255;165;0mStoryteller\033[0m: Maybe next time...Goodbye!\n");
    system("stty -echo");
    printf("\n\033[31mSystem\033[0m: The game will close in 3...\n");
    sleep(1);
    printf("\033[31mSystem\033[0m: The game will close in 2...\n");
    sleep(1);
    printf("\033[31mSystem\033[0m: The game will close in 1...\n");
    sleep(1);
    printf("\n\033[31mSystem\033[0m: !!!\033[31mPROGRAM CLOSED\033[0m!!!\n\n");
    system("stty echo");
    exit(0);
}

// THE BEGINNING			~~~ CHAPTER 1 ~~~

void beginning(char *name) {

    printf("\033[38;2;255;165;0mStoryteller\033[0m: Let's start the adventure, " GREEN "%s" RESET "!\n", name);
    sleep(2);

    printf("\033[38;2;255;165;0mStoryteller\033[0m: As a gift, I will show you a cat.\n\033[38;2;255;165;0mStoryteller\033[0m: Wait a second!\n");
    sleep(2);

    printf(" /\\_/\\\n( o.o )	" ITALIC "MEOWWW" RESET "\n > ^ <\n");
    sleep(2);

    printf("\033[38;2;255;165;0mStoryteller\033[0m: Jokes aside, let's start! But be aware, this will not be easy!\n");
    sleep(3);

    printf(ORANGE "Storyteller" RESET ": Do you see that dungeon in front of you? Enter it, battle awaits you!\n");

    printf("                ________________\n               |                |\n               |   DUNGEON      |\n               |________________|\n 			|\n");

    printf(ITALIC "\n*Enters the dungeon.*\n" RESET);
    sleep(1);
}

// DISPLAY STATS			~~~ CHAPTER 2 ~~~

void displayStatsChapter2(int playerHp, int dragonHp) {

    printf(RED "\nSystem" RESET ":" " PLAYER HP = %d\n" RED "System" RESET ": ""DRAGON HP = %d\n", playerHp, dragonHp);
}

// ENTERING IN DUNGEON				~~~ CHAPTER 2 ~~~

void dungeonstart() {

    printf(ORANGE "\nStoryteller" RESET ": You encounter a dragon...It doesn't seem so friendly.\n");
    sleep(2);
}

// THE BATTLE STARTS				~~~ CHAPTER 2 ~~~

void dungeon_battle_starts(int *playerHp, int dragonHp, char name[15]) {

    printf(ITALIC "\n*Battle starts.*\n" RESET);

    srand(time(NULL));
    int dungeonChoice;
    int dragonAttack, damage;
    int tryagainFirstBattle;

    while (*playerHp > 0 && dragonHp > 0) {
        printf(ITALIC "\nChoose your action!\n" RESET);
        printf(BOLD "\n1. Attack\n2. Defend\n3. Special move\n" RESET);
        printf(GREEN "\n%s: " RESET, name);
        scanf("%d", &dungeonChoice);

        while (getchar() != '\n');

        switch (dungeonChoice) {

            case 1:

                damage = (rand() % 30) + 10;
                dragonHp -= damage;
                printf(ITALIC "\nYou slash the dragon, dealing %d damage to the dragon!\n" RESET, damage);
                break;

            case 2:

                printf(ITALIC "\nYou raised your shield, reducing incoming damage!\n" RESET);
                break;

            case 3:

                damage = (rand() % 60) + 10;
                dragonHp -= damage;
                printf(ITALIC "\nYou unleashed a powerful strike, dealing %d damage to the dragon!\n" RESET, damage);
                break;

            default:

                printf(ITALIC "\nInvalid choice...You hesitate.\n" RESET);
                continue;
        }

        if (dragonHp <= 0) {

            printf(ITALIC "You have slain the dragon!\n\n" RESET);
            break;
        }

        dragonAttack = (rand() % 20) + 10;

        if (dungeonChoice == 2) {
            dragonAttack /= 2;
        }

        *playerHp -= dragonAttack;
        printf(ITALIC "\nThe dragon retaliates, doing %d damage to you!\n" RESET, dragonAttack);
        displayStatsChapter2(*playerHp, dragonHp);
    }

    if (*playerHp <= 0) {
 
        printf(ITALIC "\nYou have been defeated!\n" RESET);
        printf(RED "System" RESET ": Type '1' for 'yes' and '2' for 'no'.\n\n");
        printf(GREEN "%s" RESET ": ", name);

        while (1) {
            
            if (scanf("%d", &tryagainFirstBattle) != 1) {
                while (getchar() != '\n');
                printf("\n\033[31mSystem:\n" RESET "!!!!!\nInvalid option! Try again!\n!!!!!\n");
            } 
           
            else {
           
                if (tryagainFirstBattle == 1) {
                    *playerHp = 100;
                    dragonHp = 120;
                    displayStatsChapter2(*playerHp, dragonHp);
                    dungeon_battle_starts(playerHp, dragonHp, name);
                    break;
                }
            
                else if (tryagainFirstBattle == 2) {
                    closegame();
                } 
            
                else {
                    printf("\n\033[31mSystem:\n" RESET "!!!!!\nInvalid option! Try again!\n!!!!!\n");
                }
            }
        }
    }
}

// ~~~ CHAPTER 3 ~~~

void chapter3beginning(int playerHp, char *name, int skipDialogue) {
    
    if (!skipDialogue) {
    
        printf(ORANGE "Storyteller" RESET ": This is your first victory, be proud, but not too proud, harder battles will come!\n");
        sleep(3);
        printf(ORANGE "Storyteller" RESET ": As you walk further into this dungeon, you will face evil!\n");
        sleep(3);
        printf(ORANGE "Storyteller" RESET ": Wait...the dragon has some last words.\n");
        sleep(3);
        printf(CYAN "Dragon" RESET ": Victory may be yours for now...But this is not the end!\n");
        sleep(3);
        printf(CYAN "Dragon" RESET ": My name is Vyrathis, remember it!\n");
        sleep(3);
        printf(CYAN "Vyrathis" RESET ": Good luck, until the next time...\n");
        sleep(3);
        printf(ORANGE "Storyteller" RESET ": What do you want do now?\n");
        sleep(3);
        printf(ITALIC "\nOptions:\n" RESET);
        printf(BOLD "\n1. Look around\n" RESET);
        printf(BOLD "2. Give up\n" RESET);

        int choice_chapter3_beginning;

        while (1) {
            printf(GREEN "\n%s" RESET ": ", name);

            if (scanf("%d", &choice_chapter3_beginning) == 1) {
            
                switch (choice_chapter3_beginning) {
    
                    case 1:
                        printf(GREEN"\n%s"RESET": Let me take a look quickly.\n", name);
                        sleep(3);
                        printf(ITALIC "* You look around and see a door... What could it hide? *\n" RESET);
                        break;

                    case 2:
                        printf(GREEN"\n%s"RESET": I can't do this anymore.\n", name);
                        sleep(3);
                        closegame();

                    default:
                        printf(RED "\nSystem" RESET ": Invalid choice.\n");
                        continue;
                }
            } 
            
            else {
                printf(RED "\nSystem" RESET ": Invalid choice.\n");
            }
            
            if (choice_chapter3_beginning == 1 || choice_chapter3_beginning == 2) {
                while (getchar() != '\n');
                break;
            }

            while (getchar() != '\n');
        }
        
        sleep(2);
        printf(ORANGE "Storyteller" RESET ": You enter the door. \n");
        sleep(2);
    }

    printf(ORANGE "Storyteller" RESET ": There is a chest right in front of you, it could hide precious items!\n");
    sleep(3);
    printf(ORANGE "Storyteller" RESET ": You opened it and found a healing potion. How lucky!\n");
    sleep(3);

    if(!skipDialogue){

        printf(ORANGE"Storyteller"RESET": Type 'heal' to heal yourself.\n");

        char healC3[20];

        while (1) {
            
            printf(GREEN "%s" RESET ": ", name);
            fgets(healC3, sizeof(healC3), stdin);
            healC3[strcspn(healC3, "\n")] = '\0';

            if (strcmp(healC3, "heal") == 0) {
                playerHp = 100;
                printf(ORANGE "Storyteller" RESET ": Well done! Your HP is now:" BOLD " %d.\n" RESET, playerHp);
                break;
            } 
            
            else {
                printf(RED "\nSystem" RESET ": Invalid choice.\n");
                printf(ORANGE "Storyteller" RESET ": Type 'heal' to heal yourself.\n\n");
            }
        }
    }
    
    else{
        playerHp = 100;
        sleep(2);
        printf(RED"System"RESET": You automatically used the healing potion, your HP is now:"BOLD" %d.\n"RESET, playerHp);
    }
}

void chapter3continue(char *name, int playerHp){

    sleep(4);
    printf(ORANGE"Storyteller"RESET": While healing you look down and see a sword on the floor.\n");
    sleep(3);
    printf(ORANGE"Storyteller"RESET": You decide to pick it up.\n\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣿⡇\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⡿⠋⣻⣿⣿⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⡿⠋⣠⣾⣿⡿⠁⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠋⣠⣾⣿⡿⠋⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣔⣿⡿⠋⣠⣾⣿⡿⠋⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢀⣤⡀⠀⠀⠀⠀⣠⣾⣿⡿⠋⣠⣾⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⢴⣿⡋⣠⡄⠀⠀⢸⣿⡿⠋⣠⣾⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠙⢿⣿⣡⣴⠶⢾⣿⣿⣾⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢹⡟⠀⠀⠀⢹⡏⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⢀⣼⣿⣤⣀⣠⡾⠃⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⢀⣴⣿⣿⠟⠉⠉⠙⢿⣿⡋⢀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⢠⣶⣶⣿⣿⠟⠁⠀⠀⠀⠀⠀⠙⢿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠐⢿⣿⣿⡧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠁⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    sleep(2);

    printf(ORANGE"\nStoryteller"RESET": The sword seems to be a very good weapon for future battles.\n");
    sleep(3);
   
    int swordChoice;

    printf(ORANGE"Storyteller"RESET": Are you going to use it?\n");
    printf(RED"\nSystem"RESET": "ITALIC"Choose your response.\n"RESET);
    printf(BOLD"\n1. Yes, this could help me.\n2. No, I don't need it.\n3."RED" Seppuku(切腹)\n"RESET);
    
    while(1){
        printf(GREEN"\n%s"RESET": ", name);
        if(scanf("%d", &swordChoice) == 1){
          
            if(swordChoice == 1){
                printf(GREEN"\n%s"RESET": Yes, this could help me.\n", name);
                sleep(3);
                printf(ORANGE"Storyteller"RESET": You pick up the sword.\n");
                sleep(2);
                printf(GREEN"%s"RESET": I can feel myself becoming more powerful! The energy of this sword enters my bloodstream!\n", name);
                break;
            }
            else if(swordChoice == 2){
                printf(GREEN"\n%s"RESET": No, I don't need it.\n", name);
                sleep(3);
                printf(ORANGE"Storyteller"RESET": Hmmm...You don't want the sword? Not a good choice in my opinion.\n");
                sleep(5);
                printf(ORANGE"Storyteller"RESET": Oh no! What's this? A stone golem rises from the floor and started attacking you!\n");
                sleep(4);
                printf(ORANGE"Storyteller"RESET": You are getting cornered.\n");
                sleep(4);
                printf(ORANGE"Storyteller"RESET": You tried to attack the golem but without the sword it's hard to deal any damage at all.\n");
                sleep(4);
                printf(ORANGE"Storyteller"RESET": The golem deals the final blow and ends up killing you.\n");
                sleep(4);
                youDied();
            }
            else if(swordChoice == 3){
                printf(GREEN"\n%s"RESET": There is no honor in this place. The reapers are calling my name.\n", name);
                sleep(3);
                printf(ORANGE"Storyteller"RESET": You feel like you've lost your"ITALIC" honor"RESET", you decided to perform the lost art of the samurai fighters, often called a '"RED"seppuku(切腹)"RESET"'.\n");
                sleep(4);
                printf(ORANGE"Storyteller"RESET": Atleast you end your life with honor.\n");
                sleep(4);
                printf(ITALIC"\n* You cut open your abdomen from left to right and bled to death. *\n"RESET);
                sleep(4);
                youDied();
            }
            else{
                printf(RED "\nSystem" RESET ": Invalid choice.\n");
            }
        }
        else{
            printf(RED "\nSystem" RESET ": Invalid choice.\n");
            clean_input_buffer();
        }
    }

}

void chapter3end(char *name, int playerHp){

    char lookChapter3[10];
    sleep(3);
    printf(ORANGE"Storyteller"RESET": After you pick up the sword you decide to look around the room.\n");
    sleep(3);
    printf(ORANGE"Storyteller"RESET": Type 'look' to look around.\n");
    clean_input_buffer();
   
    while(1){
        
        printf(GREEN "%s" RESET ": ", name);
      
        if(fgets(lookChapter3, sizeof(lookChapter3), stdin) != NULL){
            lookChapter3[strcspn(lookChapter3, "\n")] = '\0';
        
            if(strcmp(lookChapter3, "look") == 0){

                printf(ORANGE"Storyteller"RESET": You inspect the room and see a trapdoor.\n");
                sleep(3);
                printf(ITALIC"* Walks to the trapdoor. *\n"RESET);
                sleep(3);
                break;
            }
            else{
                printf(RED"\nSystem"RESET": Invalid choice. Please try again.\n");
                printf(ORANGE"Storyteller"RESET": Type 'look' to look around.\n\n");
            }
        }
        else{
            printf(RED"\nSystem"RESET": Invalid choice. Please try again.\n");
            clean_input_buffer();
        }
    }
}

// MAIN FUNCTION 		~~~ THE MAIN GAME ~~~

int main() {
    
    char name[15];
    int choice;
    int chapter = 1;
    int playerHp = 100;

    // Try to load the game
    
    if (loadGame(name, &playerHp, &chapter)) {
    
        printf(ORANGE "Storyteller" RESET ": Welcome back, " GREEN "%s" RESET "!\n", name);
        sleep(2);
        printf(ORANGE "Storyteller" RESET ": You are currently in chapter %d with"BOLD" %d"RESET" HP.\n", chapter, playerHp);
        sleep(2);
    
        // If the game was saved after chapter 3, continue from there
    
        if (chapter == 3) {
            printf(ORANGE "Storyteller" RESET ": Continuing your adventure...\n");
            sleep(2);

            chapter3beginning(playerHp, name, 1);
            chapter3continue(name, playerHp);
            chapter3end(name, playerHp);
            return 0;
        }
        else if(chapter == 4){
            printf(ORANGE "Storyteller" RESET ": Continuing your adventure...\n");
            return 0;
        }
    } 
    else {
    
        // If no saved game, start a new game
    
        printf(ORANGE "Storyteller" RESET ": Hello warrior!");
        printf("\n\033[38;2;255;165;0mStoryteller\033[0m: What is your name?\n");
        printf("\033[32mWarrior:\033[0m: ");
        scanf("%s", name);
        printf(ORANGE "Storyteller" RESET ": Hello " GREEN "%s" RESET "! Are you ready for an adventure?\n", name);
        printf(ORANGE "Storyteller" RESET ": If so, type \"1\" to continue, otherwise type \"2\" to exit.\n");

        while (1) {
            printf(GREEN "%s: " RESET, name);
            if (scanf("%d", &choice) == 1) {
                if (choice == 1) {
                    printf(GREEN"%s"RESET": I was born ready!\n", name);
                    sleep(2);  
                    break;
                } 
                else if (choice == 2) {
                    printf(GREEN"%s"RESET": Not yet... But I promise I will be back!\n", name);
                    sleep(2);
                    closegame();
                } 
                else {
                    printf(RED "System" RESET ": Invalid option! Try again.\n");
                }
            } 
            else {
                printf(RED "System" RESET ": Invalid option! Try again.\n");
                while (getchar() != '\n');
            }
        }
    }

    // Start the game

    beginning(name);

    // Chapter 2

    dungeonstart();
    
    int dragonHp = 120;
    
    displayStatsChapter2(playerHp, dragonHp);
    sleep(2);
    dungeon_battle_starts(&playerHp, dragonHp, name);

    // Chapter 3

    chapter3beginning(playerHp, name, 0);
    
    // SAVE

    playerHp = 100;
    chapter = 3;

    saveGame(name, playerHp, chapter);

    chapter3continue(name, playerHp);
    chapter3end(name, playerHp);

    // SAVE

    playerHp = 100;
    chapter = 4;

    saveGame(name, playerHp, chapter);

    return 0;
}