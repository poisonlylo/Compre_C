#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        afficherAide();
        return 0;
    }

    const char *nomFichierZip = NULL;
    const char *fichierAajouter = NULL;
    const char *motDePasse = NULL;
    const char *fichierDictionnaire = NULL;
    const char *fichierAExtraire = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            afficherAide();
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--open") == 0) {
            if (i + 1 < argc) {
                nomFichierZip = argv[i + 1];
                ouvrirFichierZip(nomFichierZip);
            } else {
                printf("Aucun fichier ZIP spécifié\n");
                return 1;
            }
            i++;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--bruteforce") == 0) {
            bruteforcerMotDePasse();
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dictionary") == 0) {
            if (i + 1 < argc) {
                fichierDictionnaire = argv[i + 1];
                bruteforcerAvecDictionnaire(fichierDictionnaire);
            } else {
                printf("Aucun fichier dictionnaire spécifié\n");
                return 1;
            }
            i++;
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--password") == 0) {
            if (i + 1 < argc) {
                motDePasse = argv[i + 1];
            } else {
                printf("Aucun mot de passe spécifié\n");
                return 1;
            }
            i++;
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--add") == 0) {
            if (i + 2 < argc) {
                fichierAajouter = argv[i + 1];
                nomFichierZip = argv[i + 2];
                ajouterFichierAuZip(nomFichierZip, fichierAajouter);
            } else {
                printf("Arguments manquants pour l'ajout de fichier\n");
                return 1;
            }
            i += 2;
        } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--extract") == 0) {
            if (i + 2 < argc) {
                fichierAExtraire = argv[i + 1];
                nomFichierZip = argv[i + 2];
                extraireFichierDuZip(nomFichierZip, fichierAExtraire);
            } else {
                printf("Aucun fichier ou fichier ZIP spécifié\n");
                return 1;
            }
            i += 2;
        } else {
            printf("Option inconnue : %s\n", argv[i]);
            return 1;
        }
    }

    return 0;
}
