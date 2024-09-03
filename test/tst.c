#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct date
{
    int jour, mois, annee;
} date;

typedef struct tache
{
    int id;
    char titre[20];
    char desc[255];
    char status[11];
    date deadline;
} tache;
tache t[100];
int ID = 0;
int dim = 0;

void ajouter_tache(tache t[])
{
    int choix2;
    t[dim].id = ID + 1;
    printf("\t\ttitre : ");
    scanf(" %[^\n]", t[dim].titre);
    strupr(t[dim].titre);
    printf("\t\tdescription : ");
    scanf(" %[^\n]", t[dim].desc);
    do
    {
        printf("\t\tStatus du tache :\n \t1- A realiser | 2- En cours | 3- Finalisee  : ");
        scanf("%d", &choix2);

    } while (choix2 <= 0 || choix2 >= 4);
    switch (choix2)
    {
    case 1:
        strcpy(t[dim].status, "A realiser");
        break;
    case 2:
        strcpy(t[dim].status, "En cours");
        break;
    case 3:
        strcpy(t[dim].status, "Finalisee");
        break;
    default:
        printf("valeur invalide.\n");
    }
    do
    {
        printf("\t\tsaisir le deadline :");
        scanf("%d/%d/%d", &t[dim].deadline.jour, &t[dim].deadline.mois, &t[dim].deadline.annee);
    } while (t[dim].deadline.jour <= 0 || t[dim].deadline.jour >= 32 || t[dim].deadline.mois <= 0 || t[dim].deadline.mois >= 13 || t[dim].deadline.annee <= 0);
    dim++;
    ID++;
}

void ajouter_plus(tache t[])
{
    int nbr, p;
    printf("\t\tcombien vous voulez ajouter :");
    scanf("%d", &nbr);
    p = nbr + dim;
    for (int i = dim; i < p; i++)
    {
        ajouter_tache(t);
    }
}

void afficher_tache(tache t[])
{
    printf("\t\t+------------------------------------------------------------------------------+\n");
    printf("\t\t| Id |        Tache         |      Description     | Date limite |    Status   |\n");
    printf("\t\t+------------------------------------------------------------------------------+\n");
    for (int i = 0; i < dim; i++)
    {

        printf("\t\t| %-2d | %-20s | %-20s | %2d-%2d-%4d  | %-11s |\n", t[i].id, t[i].titre, t[i].desc, t[i].deadline.jour, t[i].deadline.mois, t[i].deadline.annee, t[i].status);
    }
    printf("\t\t+------------------------------------------------------------------------------+\n");
}

void tri_alpha(tache t[])
{
    tache r[100], temp;
    for (int i = 0; i < dim; i++)
    {
        r[i] = t[i];
    }
    for (int i = 0; i < dim; i++)
    {
        for (int j = i + 1; j < dim; j++)
        {
            if (strcmp(r[i].titre, r[j].titre) > 0)
            {
                temp = r[i];
                r[i] = r[j];
                r[j] = temp;
            }
        }
    }
    printf("\t\tLes taches triees alphabitique : \n");
    afficher_tache(r);
}

void tri_deadline(tache t[])
{
    int i, j, temp, days;
    ;
    tache temp2;
    tache r[100];
    int table[100];
    for (i = 0; i < 100; i++)
    {
        r[i] = t[i];
    }
    time_t seconds = time(NULL);
    struct tm current_time = *localtime(&seconds);
    int anneeActuelle = current_time.tm_year + 1900;
    int moisActuell = current_time.tm_mon + 1;
    int numJours = current_time.tm_mday;

    for (i = 0; i < dim; i++)
    {
        days = r[i].deadline.annee * 365 + r[i].deadline.mois * 30 + r[i].deadline.jour;
        table[i] = days - (anneeActuelle * 365 + moisActuell * 30 + numJours);
    }
    for (i = 0; i < dim; i++)
    {
        for (j = i + 1; j < dim; j++)
        {
            if (table[i] > table[j])
            {
                temp = table[i];
                table[i] = table[j];
                table[j] = temp;

                temp2 = r[i];
                r[i] = r[j];
                r[j] = temp2;
            }
        }
    }
    printf("\t\tLes taches triees par deadline : \n");
    afficher_tache(r);
}

void tache_moins_trois(tache t[])
{
    int delai, days;
    int c = 0;
    time_t seconds = time(NULL);
    struct tm current_time = *localtime(&seconds);
    int anneeActuelle = current_time.tm_year + 1900;
    int moisActuell = current_time.tm_mon + 1;
    int numJours = current_time.tm_mday;
    for (int i = 0; i < dim; i++)
    {
        days = t[i].deadline.annee * 365 + t[i].deadline.mois * 30 + t[i].deadline.jour;
        delai = days - (anneeActuelle * 365 + moisActuell * 30 + numJours);
        if (delai < 0)
            continue;
        if (delai > 0 && delai < 4)
        {
            c++;
            printf("\t\t| %-2d | %-20s | %-20s | %11s | dans %d jour(s) |\n", t[i].id, t[i].titre, t[i].desc, t[i].status, delai);
        }
    }
    if (c == 0)
        printf("\t\tIl n\'y a pas une tache dont le deadline est 3 jours ou moin.\n");
}

void supprimer_tache(tache t[])
{
    int id, c;
    printf("Saisir id :");
    scanf("%d", &id);
    for (int i = 0; i < dim; i++)
    {
        if (t[i].id == id)
        {
            c++;
            for (int j = i; j < dim - 1; j++)
            {
                t[j] = t[j + 1];
            }
            dim--;
        }
    }
    if (c == 0)
        printf("\t\tIl n\'y a pas de tache avec l\'Id %d\n", id);
    else
        afficher_tache(t);
}

void recherche_id(tache t[])
{
    int number;
    printf("\t\tentrer l'id de la tache : ");
    scanf("%d", &number);
    for (int i = 0; i < dim; i++)
    {
        if (t[i].id == number)
        {
        printf("\t\t| %-2d | %-20s | %-20s | %2d-%2d-%4d  | %-11s |\n", t[i].id, t[i].titre, t[i].desc, t[i].deadline.jour, t[i].deadline.mois, t[i].deadline.annee, t[i].status);
            break;
        }
    }
}

void recherche_titre(tache t[])
{
    char title[20];
    printf("\t\tentrer le titre de la tache : ");
    scanf(" %[^\n]", title);
    strupr(title);
    for (int i = 0; i < dim; i++)
    {
        if (strcmp(t[i].titre,title) == 0)
        {
        printf("\t\t| %-2d | %-20s | %-20s | %2d-%2d-%4d  | %-11s |\n", t[i].id, t[i].titre, t[i].desc, t[i].deadline.jour, t[i].deadline.mois, t[i].deadline.annee, t[i].status);
        }
    }
}

void modifier_desc(tache t[])
{
    int number;
    int c = 0;
    printf("\t\tentrer l'id de la tache : ");
    scanf("%d", &number);
    for (int i = 0; i < dim; i++)
    {
        if (t[i].id == number)
        {c++;
            printf("\t\tentrer nouvelle description");
            scanf(" %[^\n]", t[i].desc);
        }
    }
    if (c==0)printf("\t\tIl n\'y a pas une tache dont l\'id %d", number);
}

void modifier_status(tache t[])
{
    int number, choix2;
    printf("\t\tentrer l'id de la tache : ");
    scanf("%d", &number);
    for (int i = 0; i < dim; i++)
    {
        if(t[i].id==number){
        do
        {
            printf("\t\tStatus du tache :\n \t1- A realiser | 2- En cours | 3- Finalisee  : ");
            scanf("%d", &choix2);

        } while (choix2 <= 0 || choix2 >= 4);
        switch (choix2)
        {
        case 1:
            strcpy(t[i].status, "A realiser");
            break;
        case 2:
            strcpy(t[i].status, "En cours");
            break;
        case 3:
            strcpy(t[i].status, "Finalisee");
            break;
        default:
            printf("valeur invalide.\n");
        }
    }}
}

void modifier_deadline(tache t[])
{
    int number;
    printf("entrer l'id de la tache : ");
    scanf("%d", &number);
    for (int i = 0; i < dim; i++)
    {
        if(t[i].id==number){
        do
        {
            printf("saisir le nouvaux deadline :");
            scanf("%d/%d/%d", &t[i].deadline.jour, &t[i].deadline.mois, &t[i].deadline.annee);
        } while (t[i].deadline.jour <= 0 || t[i].deadline.jour >= 32 || t[i].deadline.mois <= 0 || t[i].deadline.mois >= 13 || t[i].deadline.annee <= 0);
    }}
}
void stats1(tache t[])
{
    int total_taches = 0;
    for (int i = 0; i < dim; i++)
    {
        total_taches++;
    }
    printf("\t\tle nombre total des taches est %d\n", total_taches);
}

void stats2(tache t[])
{
    int complet = 0;
    int incomplets = 0;
    for (int i = 0; i < dim; i++)
    {
        if (strcmp(t[i].status, "Finalisee") == 0)
        {
            complet++;
        }
        else
        {
            incomplets++;
        }
    }
    printf("\t\tle nombre total des taches complets est %d\n", complet);
    printf("\t\tle nombre total des taches incomplets est %d\n", incomplets);
}

void stats3(tache t[])
{
    int delai,days;

    time_t seconds = time(NULL);
    struct tm current_time = *localtime(&seconds);
    int anneeActuelle = current_time.tm_year + 1900;
    int moisActuell = current_time.tm_mon + 1;
    int numJours = current_time.tm_mday;

    for (int i = 0; i < dim; i++)
    {
        days = t[i].deadline.annee * 365 + t[i].deadline.mois * 30 + t[i].deadline.jour;
        delai = days - (anneeActuelle * 365 + moisActuell * 30 + numJours);
    
        if (delai == 0)
        {
            printf("\t\tid:%d  | titre : %s |  Aujourd\'hui\n", t[i].id, t[i].titre);
        }
        else
        {
            printf("\t\tid:%d  | titre : %s | deadline dans %d jour(s)\n", t[i].id, t[i].titre,delai);
        }
    }
}

int menu_affichage()
{
    int choix;
    while (1)
    {
        printf("\t\tMenu affichage :\n");
        printf("\t\t1. afficher les taches \n");
        printf("\t\t2. afficher les taches par alphabet \n");
        printf("\t\t3. afficher les taches par deadline  \n");
        printf("\t\t4. afficher les taches dont le deadline est dans 3 jours  \n");
        printf("\t\t5. retour \n");
        printf("\t\tEnter votre choix (1-5): ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            afficher_tache(t);
            system("pause");
            break;
        case 2:
            tri_alpha(t);
            system("pause");
            break;
        case 3:
            tri_deadline(t);
            system("pause");
            break;
        case 4:
            tache_moins_trois(t);
            system("pause");
            break;
        case 5:
            return 0;
            break;
        default:
            printf("\t\terreur, entrer en entier de 1 a 5.\n");
            return 0;
        }
    }

    return 0;
}

int menu_gestion()
{
    int choix;
    while (1)
    {
        printf("\t\tMenu affichage :\n");
        printf("\t\t1. Modifier la description d\'une tache.\n");
        printf("\t\t2. Modifier le status d\'une tache.\n");
        printf("\t\t3. Modifier le deadline d\'une tache.\n");
        printf("\t\t4. Supprimer une tache.  \n");
        printf("\t\t5. Rechercher une tache par id\n");
        printf("\t\t6. Rechercher une tache par titre\n");
        printf("\t\t7. retour \n");
        printf("\t\tEnter votre choix (1-7): ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            modifier_desc(t);
            break;
        case 2:
            modifier_status(t);
            break;
        case 3:
            modifier_deadline(t);
            break;
        case 4:
            supprimer_tache(t);
            system("pause");
            break;
        case 5:
            recherche_id(t);
            system("pause");
            break;
        case 6:
            recherche_titre(t);
            system("pause");
            break;
        case 7:
            return 0;
            break;
        default:
            printf("\t\terreur, entrer en entier de 1 a 7.\n");
            return 0;
        }
    }

    return 0;
}


int menu_stats()
{
    int choix;
    while (1)
    {
        printf("\t\tMenu stats :\n");
        printf("\t\t1. nombre total des taches\n");
        printf("\t\t2. afficher le nombre total des taches complets et incomplets\n");
        printf("\t\t3. afficher les taches dont le delai est dans 3 jours.\n");
        printf("\t\t4. retour \n");
        printf("\t\tEnter votre choix (1-4): ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            stats1(t);
            system("pause");
            break;
        case 2:
            stats2(t);
            system("pause");
            break;
        case 3:
            stats3(t);
            system("pause");
            break;
        case 4:
            return 0;
            break;
        default:
            printf("\t\terreur, entrer en entier de 1 a 4.\n");
            return 0;
        }
    }

    return 0;
}

int menu()
{
    int choix;
    while (1)
    {
        printf("\t\tMenu:\n");
        printf("\t\t1. ajouter une seul tache \n");
        printf("\t\t2. ajouter plusieur taches \n");
        printf("\t\t3. menu affichage \n");
        printf("\t\t4. menu gestion\n");
        printf("\t\t5. statistiques\n");
        printf("\t\t6. quitter \n");
        printf("\t\tEnter votre choix (1-6): ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            ajouter_tache(t);
            break;
        case 2:
            ajouter_plus(t);
            break;
        case 3:
            menu_affichage();
            break;
        case 4:
            menu_gestion();
            break;
        case 5:
            menu_stats();
            break;
        case 6:
            return 0;
        default:
            printf("\t\terreur, entrer en entier de 1 a 6.\n");
            return 0;
        }
    }

    return 0;
}

int main()
{
    menu();
    return 0;
}