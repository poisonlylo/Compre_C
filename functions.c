#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>
#include "functions.h"

void afficherAide() {
    printf("ziptool - Outil de manipulation de fichiers ZIP\n");
    printf("Utilisation : ziptool [OPTIONS]\n");
    printf("Options :\n");
    printf("  -h, --help                    Afficher cette aide\n");
    printf("  -o, --open ZIP_FILE           Ouvrir un fichier ZIP pour le parcourir\n");
    printf("  -b, --bruteforce              Tenter de forcer le mot de passe\n");
    printf("  -d, --dictionary FILE         Tenter de forcer le mot de passe avec un dictionnaire\n");
    printf("  -p, --password PASSWORD       Utiliser ce mot de passe\n");
    printf("  -e, --extract FILE ZIP_FILE   Extraire ce fichier du fichier ZIP\n");
    printf("  -i, --add FILE ZIP_FILE       Ajouter un fichier au fichier ZIP\n");
}

void ouvrirFichierZip(const char *nomFichierZip) {
    struct zip *zip = zip_open(nomFichierZip, ZIP_RDONLY, NULL);
    if (zip == NULL) {
        printf("Échec lors de l'ouverture du fichier ZIP : %s\n", nomFichierZip);
        return;
    }

    int nbFichiers = zip_get_num_entries(zip, 0);
    printf("Fichiers dans le ZIP : %d\n", nbFichiers);

    for (int i = 0; i < nbFichiers; i++) {
        const char *nomFichier = zip_get_name(zip, i, 0);
        printf("- %s\n", nomFichier);
    }

    zip_close(zip);
}

void bruteforcerMotDePasse() {
    printf("Tentative de force du mot de passe...\n");
    // TODO: Implémenter la logique de bruteforce
}

void bruteforcerAvecDictionnaire(const char *fichierDictionnaire) {
    printf("Tentative de force du mot de passe avec le dictionnaire : %s\n", fichierDictionnaire);
    // TODO: Implémenter la logique de bruteforce avec le dictionnaire
}

void extraireFichierDuZip(const char *nomFichierZip, const char *fichierAExtraire) {
 // extraire un fichier depuis un fichier zip ezn utilisant la librairie libzip
    struct zip *zip = zip_open(nomFichierZip, ZIP_RDONLY, NULL);
    if (zip == NULL) {
        printf("Échec lors de l'ouverture du fichier ZIP : %s\n", nomFichierZip);
        return;
    }

    struct zip_stat stat;
    zip_stat_init(&stat);
    int resultat = zip_stat(zip, fichierAExtraire, 0, &stat);
    if (resultat < 0) {
        printf("Échec lors de la récupération des informations du fichier : %s\n", fichierAExtraire);
        zip_close(zip);
        return;
    }

    char *contenu = malloc(stat.size);
    if (contenu == NULL) {
        printf("Échec lors de l'allocation de mémoire pour le fichier : %s\n", fichierAExtraire);
        zip_close(zip);
        return;
    }

    struct zip_file *fichier = zip_fopen(zip, fichierAExtraire, 0);
    if (fichier == NULL) {
        printf("Échec lors de l'ouverture du fichier : %s\n", fichierAExtraire);
        free(contenu);
        zip_close(zip);
        return;
    }

    resultat = zip_fread(fichier, contenu, stat.size);
    if (resultat < 0) {
        printf("Échec lors de la lecture du fichier : %s\n", fichierAExtraire);
        free(contenu);
        zip_fclose(fichier);
        zip_close(zip);
        return;
    }

    const char *nomFichier = strrchr(fichierAExtraire, '/');
    if (nomFichier == NULL) {
        nomFichier = fichierAExtraire;
    } else {
        nomFichier++;
    }

    FILE *fichierSortie = fopen(nomFichier, "wb");
    if (fichierSortie == NULL) {
        printf("Échec lors de l'ouverture du fichier de sortie : %s\n", nomFichier);
        free(contenu);
        zip_fclose(fichier);
        zip_close(zip);
        return;
    }

    resultat = fwrite(contenu, stat.size, 1, fichierSortie);
    if (resultat < 0) {
        printf("Échec lors de l'écriture du fichier de) sortie : %s\n", nomFichier);
}}

void ajouterFichierAuZip(const char *nomFichierZip, const char *fichierAajouter) {
    struct zip *zip = zip_open(nomFichierZip, ZIP_CREATE, NULL);
    if (zip == NULL) {
        printf("Échec lors de la création du fichier ZIP : %s\n", nomFichierZip);
        return;
    }

    struct zip_source *source = zip_source_file(zip, fichierAajouter, 0, 0);
    if (source == NULL) {
        printf("Échec lors de l'ajout du fichier : %s au fichier ZIP\n", fichierAajouter);
        zip_close(zip);
        return;
    }

    const char *nomFichier = strrchr(fichierAajouter, '/');
    if (nomFichier == NULL) {
        nomFichier = fichierAajouter;
    } else {
        nomFichier++;
    }

    int resultat = zip_file_add(zip, nomFichier, source, ZIP_FL_OVERWRITE);
    if (resultat < 0) {
        printf("Échec lors de l'ajout du fichier : %s au fichier ZIP\n", fichierAajouter);
    } else {
        printf("Fichier : %s ajouté au ZIP : %s\n", fichierAajouter, nomFichierZip);
    }

    zip_close(zip);
}