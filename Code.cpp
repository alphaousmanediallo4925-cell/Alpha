#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    //+++++++++++  STRJUCTURE DU COMPTE ++++++++++++
typedef struct{
    int num;
    char nom[50];
    char prenom[50];
    float solde;
    char dateCreation[20];  
} Client;

Client banque[1000];
int total = 0;
    //++++++++++  PROTOTYPES DES FONCTIONS ++++++++++++
void titre();
void menu();
int trouverClient(int numero);
void ajouterClient();
void faireDepot();
void faireRetrait();
void transfertMontant();
void supprimerCompte();
void voirSolde();
void afficherClients();
void sauvegarder();
void charger();
void attendre();
void interfaceGraphique();
    // FONCTIONS PRINCIPALES
int main(){
    charger();
    menu();
    return 0;
}
    // FONCTION TITRE
void titre(){
    system("cls"); // Windows
    printf("================================================\n");
    printf("          APPLICATION DE GESTION BANCAIRE        \n");
    printf("================================================\n");
    printf("             PROJET EN LANGAGE C                \n");
    printf("================================================\n\n");
}
    // FONCTION INTERFACE GRAPHIQUE
void interfaceGraphique(){
    printf("\n");
    printf("==================================================\n");
    printf("  [1] Ajouter  |  [2] Depot         |  [3] Retrait\n");
    printf("  [4] Solde    |  [5] Liste         |  [6] Save\n");
    printf("  [7] Charger  |  [8] Transfert\n");
    printf("  [9] Supprimer|  [0] Quitter\n");
    printf("==================================================\n");
}
    // FONCTION ATTENDRE
void attendre(){
    printf("\nAppuie sur ENTREE pour continuer...");
    getchar();
    getchar();
}
    // FONCTION MENU
void menu(){
    int option;

    do{
        titre();
        interfaceGraphique();
        printf("==================================================\n");
        printf("      CHER CLIENT BIENVENUE DANS NOTRE SERVICE    \n");
        printf("==================================================\n");
        printf("\n Veuillez choisir une option : ");
        scanf("%d", &option);

        switch (option){
            case 1: ajouterClient(); break;
            case 2: faireDepot(); break;
            case 3: faireRetrait(); break;
            case 4: voirSolde(); break;
            case 5: afficherClients(); break;
            case 6: sauvegarder(); break;
            case 7: charger(); break;
            case 8: transfertMontant(); break;
            case 9: supprimerCompte(); break;
            case 0:sauvegarder();
                printf("========================================================\n");
                printf("    CHER CLIENT; Mercie pour votre visite à bientôt     \n");
                printf("========================================================\n");
                break;
            default:
                printf("\n L'option choisie est incorrect !");
                attendre();
        }

    } while (option != 0);
}
    // FONCTION TROUVER CLIENT 
int trouverClient(int numero){
    for (int i = 0; i < total; i++){
        if (banque[i].num == numero)
            return i;
    }
    return -1;
}
    // FONCTION AJOIUTER CLIENT 
void ajouterClient(){
    int numero;

    titre();

    if (total >= 1000){
        printf("Désolé ! la banque est pleine !");
        attendre();
        return;
    }

    printf("Entrez le numero du compte : ");
    scanf("%d", &numero);

    if (trouverClient(numero) != -1){
        printf(" Ce numero existe deja !");
        attendre();
        return;
    }

    banque[total].num = numero;

    // AJOUT DU NOM
    printf("Entrez votre nom : ");
    scanf("%s", banque[total].nom);

    // AJOUT DU PRENOM 
    printf("Entrez votre prenom : ");
    getchar();
    fgets(banque[total].prenom, 50, stdin);
    banque[total].prenom[strcspn(banque[total].prenom, "\n")] = 0;

    // AJOUT DE LA DATE DE CREATION
    printf("Entrez la date de creation : ");
    scanf("%s", banque[total].dateCreation);

    banque[total].solde = 0;
    total++;
	printf("\n=======================================================================\n");
    			printf("Votre compte a été ajouté avec succès !\n");
    printf("\n=======================================================================\n");
    attendre();
}
    // FONCTION DEPOT 
void faireDepot(){
    int numero, pos;
    float montant;

    titre();
    printf("Entrez le numero du compte : ");
    scanf("%d", &numero);

    pos = trouverClient(numero);

    if (pos == -1){
        printf("Le compte est introuvable !");
        attendre();
        return;
    }

    printf("Entrez le montant à déposer (MAD) : ");
    scanf("%f", &montant);

    if (montant <= 0){
        printf("le montant entré est incorrect !");
        attendre();
        return;
    }

    banque[pos].solde += montant;

    printf("Depot reussi ! Votre nouveau solde est de : %.2f MAD", banque[pos].solde);
    attendre();
}
    // FONCTION RETRAIT
void faireRetrait(){
    int numero, pos;
    float montant;

    titre();
    printf("Entrez le numero du compte : ");
    scanf("%d", &numero);

    pos = trouverClient(numero);

    if (pos == -1){
        printf("Le compte est introuvable !");
        attendre();
        return;
    }

    printf("Entrez le montant à retirer (MAD) : ");
    scanf("%f", &montant);

    if (montant <= 0 || banque[pos].solde < montant){
        printf("Erreur le montant est incorrect !");
        attendre();
        return;
    }

    banque[pos].solde -= montant;

    printf("Retrait reussi ! Votre nouveau solde est de : %.2f MAD", banque[pos].solde);
    attendre();
}
    // FONCTION TRANSFERT D'ARGENT 
void transfertMontant(){
    int source, destination;
    int pos1, pos2;
    float montant;

    titre();

    printf("Entrez le numero de compte de l'expediteur : ");
    scanf("%d", &source);

    printf("Entrez le numero de compte du destinateur : ");
    scanf("%d", &destination);

    pos1 = trouverClient(source);
    pos2 = trouverClient(destination);

    if (pos1 == -1 || pos2 == -1){
        printf("Le compte est invalide !");
        attendre();
        return;
    }

    printf("Entrez le montant à transferer (MAD) : ");
    scanf("%f", &montant);

    if (montant <= 0 || banque[pos1].solde < montant){
        printf("Le montant entré est incorrect !");
        attendre();
        return;
    }

    banque[pos1].solde -= montant;
    banque[pos2].solde += montant;

    printf("Transfert reussi !");
    attendre();
}
    // FONCTION SUPPRIMER COMPTE
void supprimerCompte(){
    int numero, pos;

    titre();
    printf("Entrez le numero du compte à supprimer : ");
    scanf("%d", &numero);

    pos = trouverClient(numero);

    if (pos == -1){
        printf("Le compte est introuvable !");
        attendre();
        return;
    }

    for (int i = pos; i < total - 1; i++){
        banque[i] = banque[i + 1];
    }

    total--;

    printf("Le compte a été supprimé !");
    attendre();
}
    // FONCTION SOLDE
void voirSolde(){
    int numero, pos;

    titre();

    printf("Entrez le numero du compte : ");
    scanf("%d", &numero);

    pos = trouverClient(numero);

    if (pos == -1){
        printf("Le compte est introuvable !");
        attendre();
        return;
    }

    printf("\nSolde actuel : %.2f MAD\n", banque[pos].solde);
    attendre();
}
    // FONCTION AFFICHER CLIENT 
void afficherClients(){
    titre();

    if (total == 0){
        printf("Il n' y a Aucun compte dans la banque !");
        attendre();
        return;
    }

    printf("====================================================================================================\n");
    printf("| %-15s | %-15s | %-20s | %-15s | %-15s |\n",
           "NUM COMPTE", "NOM", "PRENOM", "SOLDE (MAD)", "DATE CREATION");
    printf("====================================================================================================\n");

    for (int i = 0; i < total; i++){
        printf("| %-15d | %-15s | %-20s | %-15.2f | %-15s |\n",
               banque[i].num,
               banque[i].nom,
               banque[i].prenom,
               banque[i].solde,
               banque[i].dateCreation);
    }

    printf("====================================================================================================\n");

    attendre();
}
    // FONCTION SAUVEGARDER
void sauvegarder(){
    FILE *f = fopen("banque C.txt", "w");

    if (f == NULL)
        return;

    fwrite(&total, sizeof(int), 1, f);
    fwrite(banque, sizeof(Client), total, f);

    fclose(f);
}
    // FONCTION CHARGER
void charger(){
    FILE *f = fopen("banque C.txt", "r");

    if (f == NULL){
        total = 0;
        return;
    }

    fread(&total, sizeof(int), 1, f);
    fread(banque, sizeof(Client), total, f);

    fclose(f);
}