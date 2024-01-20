import pygame
import csv

pygame.init()

largeur_fenetre = 800
hauteur_fenetre = 600

def charger_carte(nom_fichier):
    with open(nom_fichier, 'r') as fichier_csv:
        lecteur_csv = csv.reader(fichier_csv)
        carte = [ligne for ligne in lecteur_csv]
    return carte

def afficher_carte(carte_sol, carte_obstacles, carte_elements):
    for y, ligne in enumerate(carte_sol):
        for x, case in enumerate(ligne):
            # Dessiner une case pour le sol
            pygame.draw.rect(ecran, (100, 100, 100), (x * 32, y * 32, 32, 32))

    for y, ligne in enumerate(carte_obstacles):
        for x, case in enumerate(ligne):
            # Dessiner une case pour les obstacles (par exemple, rouge pour simplifier)
            pygame.draw.rect(ecran, (255, 0, 0), (x * 32, y * 32, 32, 32))

    for y, ligne in enumerate(carte_elements):
        for x, case in enumerate(ligne):
            # Dessiner une case pour les autres éléments (par exemple, bleu pour simplifier)
            pygame.draw.rect(ecran, (0, 0, 255), (x * 32, y * 32, 32, 32))

ecran = pygame.display.set_mode((largeur_fenetre, hauteur_fenetre))
pygame.display.set_caption("Chargement de carte depuis des fichiers CSV")

# Charger les cartes à partir des fichiers CSV
nom_fichier_sol = 'bob.csv'
nom_fichier_obstacles = 'bob2.csv'
nom_fichier_elements = 'bob3.csv'

carte_sol = charger_carte(nom_fichier_sol)
carte_obstacles = charger_carte(nom_fichier_obstacles)
carte_elements = charger_carte(nom_fichier_elements)

continuer = True
while continuer:
    for evenement in pygame.event.get():
        if evenement.type == pygame.QUIT:
            continuer = False

    ecran.fill((0, 0, 0))

    afficher_carte(carte_sol, carte_obstacles, carte_elements)

    pygame.display.flip()

pygame.quit()
