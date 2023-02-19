#include <stdio.h>         // Inclut la bibliothèque d'entrée/sortie standard
#include <stdlib.h>        // Inclut la bibliothèque de fonctions de base
#include <string.h>        // Inclut la bibliothèque de fonctions de chaînes de caractères
#include <errno.h>         // Inclut la bibliothèque de gestion d'erreur
#include <ctype.h>         // Inclut la bibliothèque de fonctions de caractères
#include <stdbool.h>       // Inclut la bibliothèque de type booléen
#include <ini.h>           // Inclut la bibliothèque pour lire les fichiers de configuration .ini

#define MAX_CHOICE_LEN 10  // Définit la longueur maximale des choix de symbole

// Structure pour stocker les choix de symbole des joueurs
typedef struct {
    char symbol[MAX_CHOICE_LEN];  // Chaîne de caractères pour le symbole
    bool is_chosen;               // Booléen pour savoir si le symbole est déjà choisi ou non
} PlayerChoice;

// Callback function pour traiter les entrées de configuration .ini
static int config_handler(void *user, const char *section, const char *name, const char *value) {
    PlayerChoice *player_x = (PlayerChoice*) user;  // Cast le pointeur utilisateur vers PlayerChoice

    if (strcmp(section, "joueur_x") == 0) {  // Si la section est "joueur_x"
        if (strcmp(name, "1") == 0) {       // Si le nom est "1"
            strncpy(player_x->symbol, value, MAX_CHOICE_LEN);  // Copie la valeur dans player_x->symbol
            player_x->is_chosen = false;     // Marque le symbole comme non choisi
        }
    }

    return 1;  // Indique qu'il n'y a pas d'erreur
}

int main() {
    // Initialisation de la structure pour les choix de symbole
    PlayerChoice player_x, player_o;
    memset(&player_x, 0, sizeof(player_x));  // Initialise player_x avec des zéros
    memset(&player_o, 0, sizeof(player_o));  // Initialise player_o avec des zéros

    // Chargement du fichier de configuration .ini
    if (ini_parse("config.ini", config_handler, &player_x) < 0) {  // Parse le fichier config.ini avec config_handler
        printf("Erreur: Impossible de charger le fichier de configuration.\n");
        return 1;
    }

    // Demande au joueur X de choisir son symbole
    printf("Joueur X, choisissez votre symbole parmi %s, %s et %s : ",
           "Cercle", "Triangle", "Croix");
    while (true) {
        char choice[MAX_CHOICE_LEN];  // Initialise le tableau de caractères pour stocker le choix
        if (fgets(choice, sizeof(choice), stdin) == NULL) {  // Lit l'entrée utilisateur et la stocke dans choice
            printf("Erreur: Impossible de lire l'entrée utilisateur.\n");
            return 1;
        }
    }

}
    

