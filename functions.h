#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void afficherAide();
void ouvrirFichierZip(const char *nomFichierZip);
void bruteforcerMotDePasse();
void bruteforcerAvecDictionnaire(const char *fichierDictionnaire);
void extraireFichierDuZip(const char *nomFichierZip, const char *fichierAExtraire);
void ajouterFichierAuZip(const char *nomFichierZip, const char *fichierAajouter);

#endif  // FUNCTIONS_H


