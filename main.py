import pygame
import random
import math
import sys
from menu import menu

# Initialisation de Pygame
pygame.init()

# Paramètres du jeu
largeur_fenetre = 800
hauteur_fenetre = 600
taille_case = 50
nombre_colonnes = largeur_fenetre // taille_case
nombre_lignes = hauteur_fenetre // taille_case

# Couleurs
blanc = (255, 255, 255)
noir = (0, 0, 0)
rouge = (255, 0, 0)

# Création de la fenêtre du jeu
fenetre = pygame.display.set_mode((largeur_fenetre, hauteur_fenetre))
pygame.display.set_caption("Rogue-like en Python")

# Police pour le texte
police = pygame.font.SysFont(None, 36)

class Viseur:
    def __init__(self):
        self.x = 0
        self.y = 0

# Classe pour représenter un tir
class Tir:
    def __init__(self, x, y, direction, vitesse=10.0):
        self.x = x
        self.y = y
        self.direction = direction
        self.vitesse = vitesse

    def deplacer(self):
        self.x += math.cos(self.direction) * self.vitesse
        self.y += math.sin(self.direction) * self.vitesse

# Classe pour représenter le joueur
class Joueur:
    def __init__(self, vitesse_tir_joueur=10.0, delai_tir_joueur=450):
        self.x = random.randint(0, nombre_colonnes - 1)
        self.y = random.randint(0, nombre_lignes - 1)
        self.dx = 0
        self.dy = 0
        self.vitesse = 0.22
        self.vie = 100
        self.tirs = []
        self.vitesse_tir_joueur = vitesse_tir_joueur
        self.temps_dernier_tir = pygame.time.get_ticks()
        self.delai_tir_joueur = delai_tir_joueur 

    def deplacer(self):
        self.x += self.dx * self.vitesse
        self.y += self.dy * self.vitesse
        self.x = max(0, min(self.x, nombre_colonnes - 1))
        self.y = max(0, min(self.y, nombre_lignes - 1))

    def perdre_vie(self, points):
        self.vie -= points
        self.vie = max(0, self.vie)

# Classe pour représenter un ennemi
class Ennemi:
    def __init__(self, vitesse_tir_ennemi=2.0):
        self.x = random.randint(0, nombre_colonnes - 1)
        self.y = random.randint(0, nombre_lignes - 1)
        self.tirs = []
        self.temps_dernier_tir = pygame.time.get_ticks()
        self.vitesse_tir_ennemi = vitesse_tir_ennemi
        self.vie = 100

    def perdre_vie(self, points):
        self.vie -= points
        print("vie -> ", self.vie)
        if self.vie <= 0:
            self.vie = 0

    def suivre_joueur(self, joueur):
        dx = joueur.x - self.x
        dy = joueur.y - self.y
        distance = math.sqrt(dx**2 + dy**2)

        if distance > 0:
            vitesse = 0.05
            self.x += (dx / distance) * vitesse
            self.y += (dy / distance) * vitesse

    def gestion_collision_ennemis(self, autres_ennemis):
        for autre_ennemi in autres_ennemis:
            if autre_ennemi != self:
                distance = math.sqrt((self.x - autre_ennemi.x)**2 + (self.y - autre_ennemi.y)**2)
                if distance < 1:
                    angle = math.atan2(self.y - autre_ennemi.y, self.x - autre_ennemi.x)
                    self.x += math.cos(angle) * (1 - distance)
                    self.y += math.sin(angle) * (1 - distance)

    def tirer(self, joueur):
        now = pygame.time.get_ticks()
        temps_ecoule = now - self.temps_dernier_tir
        delai_tir = 1000

        if temps_ecoule > delai_tir:
            angle = math.atan2(joueur.y - self.y, joueur.x - self.x)
            tir = Tir(self.x, self.y, angle, vitesse=self.vitesse_tir_ennemi)
            self.tirs.append(tir)
            self.temps_dernier_tir = now

    def deplacer_tirs(self):
        for tir in self.tirs:
            tir.deplacer()

# Fonction pour dessiner les entités (joueur, ennemis, tirs)
def dessiner_entites(joueur, ennemis):
    fenetre.fill(blanc)

    pygame.draw.rect(fenetre, noir, (joueur.x * taille_case, joueur.y * taille_case, taille_case, taille_case))

    for tir in joueur.tirs:
        pygame.draw.circle(fenetre, noir, (int(tir.x), int(tir.y)), 5)

    for ennemi in ennemis:
        pygame.draw.rect(fenetre, rouge, (ennemi.x * taille_case, ennemi.y * taille_case, taille_case, taille_case))
        
        # Dessiner le point de vie au-dessus de l'ennemi
        texte_vie_ennemi = police.render(str(ennemi.vie), True, noir)
        fenetre.blit(texte_vie_ennemi, (ennemi.x * taille_case, ennemi.y * taille_case - 20))

        for tir in ennemi.tirs:
            pygame.draw.circle(fenetre, rouge, (int(tir.x * taille_case), int(tir.y * taille_case)), 5)

# Fonction pour gérer les collisions entre les tirs et le joueur
def gestion_collisions(joueur, ennemis):
    tirs_joueur_a_retirer = []
    ennemis_a_retirer = []
    tirs_ennemis_a_retirer = [] 

    for tir in joueur.tirs:
        for ennemi in ennemis:
            tir_x = int(tir.x // taille_case)
            tir_y = int(tir.y // taille_case)
            
            distance = math.sqrt((ennemi.x - tir_x)**2 + (ennemi.y - tir_y)**2)
            if distance < 1:
                print("Balle touche un ennemi!")
                ennemi.perdre_vie(10)
                tirs_joueur_a_retirer.append(tir)
                if ennemi.vie == 0:
                    print("Ennemi éliminé!")
                    ennemis_a_retirer.append(ennemi)

    for ennemi in ennemis:
        for tir in ennemi.tirs:
            distance = math.sqrt((joueur.x - tir.x)**2 + (joueur.y - tir.y)**2)
            if distance < 1:
                print("Balle ennemie touche le joueur!")
                joueur.perdre_vie(5)
                tirs_ennemis_a_retirer.append(tir)

    joueur.tirs = [tir for tir in joueur.tirs if tir not in tirs_joueur_a_retirer]
    for ennemi in ennemis:
        ennemi.tirs = [tir for tir in ennemi.tirs if tir not in tirs_ennemis_a_retirer]
    for ennemi in ennemis_a_retirer:
        ennemis.remove(ennemi)

def mapOne():
    joueur = Joueur(vitesse_tir_joueur=10.0)  # Vous pouvez ajuster cette valeur selon vos besoins
    nombre_ennemis = 5
    ennemis = [Ennemi(vitesse_tir_ennemi=0.1) for _ in range(nombre_ennemis)]  # Vous pouvez ajuster cette valeur selon vos besoins
    viseur = Viseur()  
    continuer = True
    clock = pygame.time.Clock()

    while continuer:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                continuer = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    joueur.dy = -1
                elif event.key == pygame.K_DOWN:
                    joueur.dy = 1
                elif event.key == pygame.K_LEFT:
                    joueur.dx = -1
                elif event.key == pygame.K_RIGHT:
                    joueur.dx = 1
            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                    joueur.dy = 0
                elif event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                    joueur.dx = 0
            elif event.type == pygame.MOUSEMOTION:
                viseur.x, viseur.y = event.pos  # Mettre à jour la position du viseur

            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1:  # Vérifiez si c'est un clic gauche
                    now = pygame.time.get_ticks()
                    temps_ecoule = now - joueur.temps_dernier_tir
                    if temps_ecoule > joueur.delai_tir_joueur:
                        angle = math.atan2(viseur.y - joueur.y * taille_case, viseur.x - joueur.x * taille_case)
                        tir = Tir(joueur.x * taille_case, joueur.y * taille_case, angle, vitesse=joueur.vitesse_tir_joueur)
                        joueur.tirs.append(tir)
                        joueur.temps_dernier_tir = now

        for tir in joueur.tirs:
            tir.deplacer()

        for ennemi in ennemis:
            ennemi.suivre_joueur(joueur)
            ennemi.gestion_collision_ennemis(ennemis)
            ennemi.tirer(joueur)
            ennemi.deplacer_tirs()

        joueur.deplacer()
        gestion_collisions(joueur, ennemis)
        dessiner_entites(joueur, ennemis)

        pygame.draw.circle(fenetre, noir, (int(viseur.x), int(viseur.y)), 5)

        texte_vie = police.render(f"Vie : {joueur.vie}", True, noir)
        fenetre.blit(texte_vie, (10, 10))

        pygame.display.flip()
        clock.tick(60)

# Fonction principale du jeu
def jouer():
    etat_jeu = "menu"

    while True:
        if etat_jeu == "menu":
            etat_jeu = menu(fenetre)
        elif etat_jeu == "play":
            etat_jeu = mapOne()
            etat_jeu = "menu"

# Appel de la fonction principale
jouer()
