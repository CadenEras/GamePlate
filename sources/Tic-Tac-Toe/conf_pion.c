#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char pion[10];
} configuration;




static int configuration_handler(){

    printf("Configuration du pion\n");
    configuration config = {"croix"}; // configuration par défaut

    // if (ini_parse("config.ini", configuration_handler, &config) < 0) {
    //     printf("Erreur : impossible de lire le fichier de configuration\n");
    //     return 1;
    // }

    if ("choix du triangle" == 0) ") {
        // dessiner un triangle


        
    } else if (strcmp(config.figure, "rond") == 0) {
        printf("Le joueur a choisi le rond\n");
        // dessiner un cercle plein
    } else if (strcmp(config.figure, "croix") == 0) {
        printf("Le joueur a choisi la croix\n");
        // dessiner une croix
    } else {
        printf("Erreur : figure inconnue dans le fichier de configuration\n");
        return 1;
    }
}