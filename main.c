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
        printf("\n%d ",arc->sommetS);
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
        Newarc->sommetS=s2;
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
        Newarc->sommetS=s2;
        Newarc->valeur=poids;
        Newarc->arc_suivant=NULL;

        if(temp->sommetS>s2)
        {

            Newarc->arc_suivant=temp->arc_suivant;

            Newarc->sommetS=temp->sommetS;
            Newarc->sommetS=s2;
            Newarc->valeur=poids;
            temp->arc_suivant=Newarc;

            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerAreteV2(pArc* Arc,int s1,int s2, int poids,int indice)
{
    pArc Newarc=(pArc)malloc(sizeof(struct Arc));
    Newarc->sommetS=s2;
    Newarc->sommetP=s1;
    Newarc->valeur=poids;
    Newarc->arc_suivant=NULL;
    Arc[indice]=Newarc;

    return Arc;


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

            if(sommet[arc->sommetS]->m==0){
                //si la distance à partir du sommet actuel est plus petite que celle déjà établie et que ce sommet n'est pas marqué,on remplace cette dernière
                if(sommet[arc->sommetS]->distance>sommetTemp->distance+arc->valeur){
                    sommet[arc->sommetS]->distance=sommetTemp->distance+arc->valeur;
                    sommet[arc->sommetS]->pred=sommetTemp->valeur;
                }

            }
            //on charche l'arc possèdant le poids le plus petit
            if(arc->valeur<dmin && sommet[arc->sommetS]->m == 0){//si on trouve une valeur plus petite que celle établie, on la remplace
                dmin=arc->valeur; // on définit la valeur du chemin le plus court trouvé
                sommet[arc->sommetS]->m=1;
                Sd=arc->sommetS; // on définit le sommet au bout du chemin le plus court trouvé
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
void Prim(pSommet* sommet){

}


void Tri_Selection(Graphe* graphe, pArc* Arc){
    int min;
    int indice_min;
    pArc ArcTemp;
    for(int i=0;i<graphe->taille;i++){
        min = Arc[i]->valeur;
        for(int j=i+1;j<graphe->taille;j++){
            pArc arc=Arc[j];
            //printf("\n%d",j);
            //printf("\nmin : %d, arc->valeur : %d",min,arc->valeur);
            if(min>arc->valeur){
                min=arc->valeur;
                indice_min=j;
            }
        }

        ArcTemp=Arc[i];
        Arc[i]=Arc[indice_min];
        Arc[indice_min]=ArcTemp;

        printf(" %d ,",Arc[i]->valeur);
    }
}

void Kruskal(Graphe* graphe,pSommet* sommet, pArc* Arc){
    int poidsTot=0;

    Tri_Selection(graphe, Arc);
    for(int i=0; i <graphe->ordre;i++){
         printf(" %d - %d |",sommet[Arc[i]->sommetP]->pd,sommet[Arc[i]->sommetS]->pd);
        printf("Sommet %d : %d \n ",sommet[i]->valeur,sommet[i]->pd);

    }
    for(int i=0; i <graphe->taille;i++){
        if(sommet[Arc[i]->sommetS]->pd != sommet[Arc[i]->sommetP]->pd){
            for(int j=0; j <graphe->ordre;j++){

                if(sommet[j]->pd==sommet[Arc[i]->sommetS]->pd || sommet[j]->pd==sommet[Arc[i]->sommetP]->pd){
                    sommet[j]->pd=sommet[Arc[i]->sommetS]->pd;
                }
            }
            sommet[Arc[i]->sommetP]->pd = sommet[Arc[i]->sommetS]->pd;
            poidsTot=poidsTot+Arc[i]->valeur;
            for(int j=0; j <graphe->ordre;j++){

                if(sommet[j]->pd==sommet[Arc[i]->sommetS]->pd){
                    sommet[j]->pd=sommet[Arc[i]->sommetS]->pd;
                }
                printf("Sommet %d : %d \n ",sommet[j]->valeur,sommet[j]->pd);

            }
            printf("\n (%d) ---- %d ---- (%d)",sommet[Arc[i]->sommetP]->valeur,Arc[i]->valeur,sommet[Arc[i]->sommetS]->valeur);
            printf("\n");

            printf("\n");
        }

    }
}
// créer le graphe
Graphe* CreerGraphe(int ordre,int taille)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    Newgraphe->pArc = (pArc*)malloc(taille*sizeof(pArc));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->pd=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }

    for(int i=0; i<taille; i++)
    {

        Newgraphe->pArc[i]=(pArc)malloc(sizeof(struct Arc));

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
    fscanf(ifs,"%d",&taille);
    graphe=CreerGraphe(ordre,taille); // créer le graphe d'ordre sommets
    graphe->orientation=0;
    graphe->ordre=ordre;
    graphe->taille=taille;

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
        graphe->pArc=CreerAreteV2(graphe->pArc, s1, s2, poids,i);


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
    Kruskal(g, g->pSommet,g->pArc);






    return 0;
}
