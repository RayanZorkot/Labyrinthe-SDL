#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constant.h"

/////////////////////////////Fonction pour afficher les Murs qui representent des "0"//////////////////////////////////////////
  void AfficherMur (SDL_Renderer* afficheur , SDL_Texture*  textuMure, char* table[] )
    {
        int i , j ;
        SDL_Rect Rect_destinataire;
        SDL_Rect Rect_source;
        Rect_source.w = TAILLE_CARREAU_LARGEUR;
        Rect_destinataire.w = TAILLE_CARREAU_LARGEUR;
        Rect_source.h = TAILLE_CARREAU_HAUTEUR;
        Rect_destinataire.h = TAILLE_CARREAU_HAUTEUR;

        for (i = 0 ; i < NB_CARREAU_LARGEUR ; i++)
        {
            for (j= 0 ; j <NB_CARREAU_HAUTEUR ; j++)
            {
                Rect_destinataire.x = i * TAILLE_CARREAU_LARGEUR;
                Rect_destinataire.y = j* TAILLE_CARREAU_HAUTEUR;

                  Rect_source.x = (table[j][i] - '0') * TAILLE_CARREAU_LARGEUR; //mure
                Rect_source.y = 0 ;
                SDL_RenderCopy(afficheur , textuMure , &Rect_source , &Rect_destinataire);

                }
            }
        }

        //////////////Fonction pour afficher le sol , qui correspondent aux 1////////////////////////////////////
 void AfficherSol (SDL_Renderer* renderer, SDL_Texture* textureSol, char* table[] )
{
    SDL_Rect Rect_source;
    SDL_Rect Rect_destinataire;
    Rect_source.w = TAILLE_CARREAU_LARGEUR;
    Rect_source.h = TAILLE_CARREAU_HAUTEUR;
    Rect_destinataire.w = TAILLE_CARREAU_LARGEUR;
    Rect_destinataire.h = TAILLE_CARREAU_HAUTEUR;

    for (int i = 0; i < NB_CARREAU_LARGEUR; i++)
    {
        for (int j = 0; j < NB_CARREAU_HAUTEUR; j++)
        {
            Rect_destinataire.x = i * TAILLE_CARREAU_LARGEUR;
            Rect_destinataire.y = j * TAILLE_CARREAU_HAUTEUR;
                  Rect_source.x = (table[j][i] - '1') * TAILLE_CARREAU_LARGEUR; //Sol
                Rect_source.y = 0 ;
                SDL_RenderCopy(renderer , textureSol , &Rect_source , &Rect_destinataire);



        }
    }
}

int main(int argc, char* argv[])
{
      SDL_Window *ecran = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture  *textujoueur = NULL;
    SDL_Surface  *joueur = NULL;
    SDL_Surface  *mur = NULL, *case_vide = NULL;
    SDL_Texture  *textureMure = NULL, *textureCase_vide = NULL;
    SDL_Rect positionPerso;
    joueur = IMG_Load("luffy.png"); //image du personnage
   ////////////////////////////////////////////Position x et y du personnage///////////////////////
    positionPerso.x = 1;
    positionPerso.y = 1;


    SDL_Event event;
    SDL_bool continuer = SDL_TRUE; /////////Ici le bool sera utiliser dans le while

     ecran = SDL_CreateWindow("LabyrintheSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_ECRAN , HAUTEUR_ECRAN , 0); //creation de la fenetre SDL
    if (ecran == NULL)
    {
        fprintf (stderr, "Erreur venant de SDL_Createtexture : %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }


     renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED); //Affichage de la fenetre
    if (renderer == NULL)
    {
        fprintf (stderr, "Erreur Createrenderer : %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    mur = IMG_Load("mur.jpg");//image du mur
    if (mur == NULL)
    {
        fprintf (stderr, "%s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    case_vide = IMG_Load("sol.jpg");//image du sol
    if (case_vide == NULL)
    {
        fprintf (stderr, "%s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    textureCase_vide = SDL_CreateTextureFromSurface(renderer, case_vide);
    if (textureCase_vide == NULL)
    {
        fprintf (stderr, "%s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

textureMure = SDL_CreateTextureFromSurface(renderer, mur);
    if (textureMure == NULL)
    {
        fprintf (stderr, "%s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    textujoueur = SDL_CreateTextureFromSurface(renderer, joueur);

    SDL_Rect rect;
    rect.x = TAILLE_CARREAU_LARGEUR * positionPerso.x; //utiliser pour deplacer le perso de haut en bas
    rect.y = TAILLE_CARREAU_HAUTEUR * positionPerso.y; //utiliser pour deplacer le perso de gauche a droite
    rect.w = 34;
    rect.h = 34; //dimmension du perso

    SDL_RenderCopy(renderer, textujoueur, NULL, &rect);

    SDL_RenderPresent(renderer);

    while (continuer)

    {


    SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT)
        {
            continuer = SDL_FALSE;
        }

        if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_RIGHT && table[positionPerso.y][positionPerso.x + 1] != '0')   //Ici on utlilise des if pour le deplacemencent et la collision du perso , nous pouvions egalement utiliser un switch
            {
                positionPerso.x++;
            }

             if(event.key.keysym.sym == SDLK_LEFT && table[positionPerso.y][positionPerso.x - 1] != '0')
            {
                positionPerso.x--;
            }

             if(event.key.keysym.sym == SDLK_UP && table[positionPerso.y - 1][positionPerso.x] != '0')
            {
                positionPerso.y--;
            }

             if(event.key.keysym.sym == SDLK_DOWN && table[positionPerso.y + 1][positionPerso.x] != '0')
            {
                positionPerso.y++;
            }
        }
        rect.x = positionPerso.x * TAILLE_CARREAU_LARGEUR;
        rect.y = positionPerso.y * TAILLE_CARREAU_HAUTEUR;

        SDL_RenderClear(renderer);
        AfficherMur(renderer, textureMure, table);
        AfficherSol(renderer, textureCase_vide, table);

        SDL_RenderCopy(renderer, textujoueur, NULL, &rect );

    SDL_RenderPresent(renderer);

    }


    SDL_Delay(0);

//liberation de la memoire ////////////////////////////////////////
    SDL_FreeSurface(mur);
    SDL_FreeSurface(case_vide);
    SDL_FreeSurface(joueur);
    SDL_DestroyTexture(textureMure);
    SDL_DestroyTexture(textureCase_vide);
    SDL_DestroyTexture(textujoueur);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ecran);
    SDL_Quit();
    return 0;
}
