#include <stdio.h>
#include "Graphe.h"
#include <stdbool.h>
#include "math.h"
/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num)
{

    printf(" sommet %d :\n",num);

    pArc arc=sommet[num]->arc;

    while(arc!=NULL)
    {
        printf("\n%d ",arc->sommet);
        printf("%d ",arc->valeur);
        arc=arc->arc_suivant;
    }

}

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2, int poids)
{

    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->valeur=poids;
        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;

        return sommet;
    }

    else
    {

        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->valeur=poids;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {

            Newarc->arc_suivant=temp->arc_suivant;

            Newarc->sommet=temp->sommet;
            Newarc->sommet=s2;
            Newarc->valeur=poids;
            temp->arc_suivant=Newarc;

            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}
void Dijkstra(Graphe* graphe, pSommet* sommet,int D){
    int dmin;
    int chemin=0;
    bool tous_marques=false;
    int Sd;
    pSommet sommetTemp;
    for(int i=0;i<graphe->ordre;i++){

        sommet[i]->distance =pow(2,29)-1;// on définit la valeur binaire max, c'est l'équivalent de l'infini
        sommet[i]->m = 0; // les sommets ne sont pas encore marqués
    }
    sommet[D]->distance=0; // la distance de l'origine par rapport à elle même est égale à 0
    sommet[D]->pred=D;// on définit son prédécésseur comme étant lui même
    sommetTemp=sommet[D];// on définit un sommet temporaire qui nous permet d'effectuer notre parcours sans modifier les valeurs du tableau de sommets

    while (tous_marques==false){ // tant que nous n'avons pas marqué tous les sommets

        dmin=pow(2,29)-1;// on définit la valeur binaire max, c'est l'équivalent de l'infini
        tous_marques=true;
        for(int i=0;i<graphe->ordre;i++){
            if(sommet[i]->m==0){
                tous_marques=false; // on vérirfie ques les sommets ne sont pas tous marqués
            }
        }
        pArc arc=sommetTemp->arc;

        while(arc!=NULL)
        {

            if(sommet[arc->sommet]->m==0){
                //si la distance à partir du sommet actuel est plus petite que celle déjà établie et que ce sommet n'est pas marqué,on remplace cette dernière
                if(sommet[arc->sommet]->distance>sommetTemp->distance+arc->valeur){
                    sommet[arc->sommet]->distance=sommetTemp->distance+arc->valeur;
                    sommet[arc->sommet]->pred=sommetTemp->valeur;
                }

            }
            //on charche l'arc possèdant le poids le plus petit
            if(arc->valeur<dmin && sommet[arc->sommet]->m == 0){//si on trouve une valeur plus petite que celle établie, on la remplace
                dmin=arc->valeur; // on définit la valeur du chemin le plus court trouvé
                sommet[arc->sommet]->m=1;
                Sd=arc->sommet; // on définit le sommet au bout du chemin le plus court trouvé
                chemin=arc->valeur; // on définit le chemin le plus court trouvé
            }
                arc=arc->arc_suivant; // On change d'arc adjacent
        }


        if(sommetTemp->distance+dmin<=sommet[Sd]->distance){
            sommet[Sd]->distance=chemin+sommetTemp->distance;
            sommet[Sd]->pred=sommetTemp->valeur;
            sommet[Sd]->m=1;
        }

        sommetTemp=sommet[Sd]; // on change de sommet de départ

    }
    printf("=-=-=-= Depart : Sommet %d =-=-=-=",D);
    for(int i=0;i<graphe->ordre;i++){ // on affiche les caractéristiques du parcours
        printf("\n  =+= Arrivee Sommet %d =+= Poids : %d =+= \n", sommet[i]->valeur, sommet[i]->distance);
        sommetTemp=sommet[i];


        while(sommetTemp->valeur!=D){
            printf("%d <--- ",sommetTemp->valeur);
            sommetTemp=sommet[sommetTemp->pred];

        }


    }
}
// créer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}


/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1) et liste des arcs */
Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, orientation, ordre, s1, s2, poids;

    printf("%sTRUC", nomFichier);

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs,"%d",&ordre);

    graphe=CreerGraphe(ordre); // créer le graphe d'ordre sommets

    fscanf(ifs,"%d",&taille);

    graphe->orientation=0;
    graphe->ordre=ordre;

    for(int w=0; w<ordre; w++)
    {
        fscanf(ifs,"%d",&s1);
    }

    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    {
        fscanf(ifs,"%d%d%d",&s1,&s2,&poids);
        //printf("\n%d %d %d",s1,s2,poids);

        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2, poids);

        if(!orientation)
            graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, poids);
    }

    return graphe;
}


/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("graphe\n");

    if(graphe->orientation)
        printf("oriente\n");
    else
        printf("non oriente\n");

    printf("ordre = %d\n",graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}


int main()
{
    Graphe * g;

    char nom_fichier[50];

    printf("entrer le nom du fichier du labyrinthe:");
    gets(nom_fichier);

    g = lire_graphe(nom_fichier);

    ///graphe_afficher(g);

    int depart;
    int fin;


    printf("\ndepart : \n");
    scanf("%d", &depart);


    Dijkstra(g ,g->pSommet,depart);



    return 0;
}