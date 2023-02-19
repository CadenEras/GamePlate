#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHOICE_LEN 10

// Structure pour stocker les choix de symbole des joueurs
typedef struct {
    char symbol[MAX_CHOICE_LEN];
    bool is_chosen;
} PlayerChoice;

int main() {
    // Définition des symboles de pion
    const char* symbols[] = {"Cercle", "Triangle", "Croix"};
    const int num_symbols = sizeof(symbols) / sizeof(symbols[0]);

    // Initialisation de la structure pour les choix de symbole
    PlayerChoice player_x, player_o;
    memset(&player_x, 0, sizeof(player_x));
    memset(&player_o, 0, sizeof(player_o));

    // Boucle de sélection de symboles pour le joueur X
    printf("Joueur X, choisissez votre symbole parmi %s, %s et %s : ",
           symbols[0], symbols[1], symbols[2]);
    while (true) {
        char choice[MAX_CHOICE_LEN];
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("Erreur: Impossible de lire l'entrée utilisateur.\n");
            return 1;
        }
        choice[strcspn(choice, "\r\n")] = 0;  // Supprime les sauts de ligne

        // Vérifie si le choix est valide
        bool is_valid_choice = false;
        for (int i = 0; i < num_symbols; i++) {
            if (strcasecmp(choice, symbols[i]) == 0) {
                is_valid_choice = true;
                break;
            }
        }
        if (!is_valid_choice) {
            printf("Erreur: Choix invalide. Choisissez parmi %s, %s et %s : ",
                   symbols[0], symbols[1], symbols[2]);
            continue;
        }

        // Vérifie si le symbole est déjà choisi
        if (!player_o.is_chosen || strcasecmp(choice, player_o.symbol) != 0) {
            strncpy(player_x.symbol, choice, MAX_CHOICE_LEN);
            player_x.is_chosen = true;
            break;
        } else {
            printf("Erreur: Ce symbole est déjà choisi par l'autre joueur. Choisissez autre chose.\n");
        }
    }

    // Boucle de sélection de symboles pour le joueur O
    printf("Joueur O, choisissez votre symbole parmi %s, %s et %s : ",
           symbols[0], symbols[1], symbols[2]);
    while (true) {
        char choice[MAX_CHOICE_LEN];
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("Erreur: Impossible de lire l'entrée utilisateur.\n");
            return 1;
        }
        choice[strcspn(choice, "\r\n")] = 0;  // Supprime les sauts de ligne

        // Vérifie si le choix est valide
        bool is_valid_choice = false;
        for (int i = 0; i < num_symbols; i++) {
            if (strcasecmp(choice, symbols[i]) == 0) {
                is_valid_choice = true;
                break;
            }
        }
       if (!is_valid_choice) {
            printf("Erreur: Choix invalide. Choisissez parmi %s, %s et %s : ",
                   symbols[0], symbols[1], symbols[2]);
            continue;
        }

        // Vérifie si le symbole est déjà choisi
        if (!player_x.is_chosen || strcasecmp(choice, player_x.symbol) != 0) {
            strncpy(player_o.symbol, choice, MAX_CHOICE_LEN);
            player_o.is_chosen = true;
            break;
        } else {
            printf("Erreur: Ce symbole est déjà choisi par l'autre joueur. Choisissez autre chose.\n");
        }
    }

return 0;

}