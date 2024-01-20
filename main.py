import pygame
import random
import math

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

# Classe pour représenter le joueur
class Joueur:
    def __init__(self):
        self.x = random.randint(0, nombre_colonnes - 1)
        self.y = random.randint(0, nombre_lignes - 1)
        self.dx = 0
        self.dy = 0
        self.vitesse = 0.22
        self.vie = 100

    def deplacer(self):
        self.x += self.dx * self.vitesse
        self.y += self.dy * self.vitesse
        self.x = max(0, min(self.x, nombre_colonnes - 1))
        self.y = max(0, min(self.y, nombre_lignes - 1))

    def perdre_vie(self, points):
        self.vie -= points
        self.vie = max(0, self.vie)

# Classe pour représenter un tir
class Tir:
    def __init__(self, x, y, direction):
        self.x = x
        self.y = y
        self.direction = direction

    def deplacer(self):
        vitesse = 0.1
        self.x += math.cos(self.direction) * vitesse
        self.y += math.sin(self.direction) * vitesse

# Classe pour représenter un ennemi
class Ennemi:
    def __init__(self):
        self.x = random.randint(0, nombre_colonnes - 1)
        self.y = random.randint(0, nombre_lignes - 1)
        self.tirs = []
        self.temps_dernier_tir = pygame.time.get_ticks()

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
            tir = Tir(self.x, self.y, angle)
            self.tirs.append(tir)
            self.temps_dernier_tir = now

    def deplacer_tirs(self):
        for tir in self.tirs:
            tir.deplacer()

# Fonction pour dessiner les entités (joueur, ennemis, tirs)
def dessiner_entites(joueur, ennemis):
    fenetre.fill(blanc)

    pygame.draw.rect(fenetre, noir, (joueur.x * taille_case, joueur.y * taille_case, taille_case, taille_case))

    for ennemi in ennemis:
        pygame.draw.rect(fenetre, rouge, (ennemi.x * taille_case, ennemi.y * taille_case, taille_case, taille_case))
        for tir in ennemi.tirs:
            pygame.draw.circle(fenetre, rouge, (int(tir.x * taille_case), int(tir.y * taille_case)), 5)

# Fonction pour gérer les collisions entre les tirs et le joueur
def gestion_collisions(joueur, ennemis):
    for ennemi in ennemis:
        for tir in ennemi.tirs:
            distance = math.sqrt((joueur.x - tir.x)**2 + (joueur.y - tir.y)**2)
            if distance < 1:
                joueur.perdre_vie(5)
                ennemi.tirs.remove(tir)

# Fonction pour la page de menu
def menu():
    font_menu = pygame.font.SysFont(None, 50)
    titre = font_menu.render("Rogue-like en Python", True, noir)
    play_button = pygame.Rect(300, 250, 200, 50)
    quit_button = pygame.Rect(300, 350, 200, 50)
    play_color = rouge
    quit_color = rouge

    while True:
        fenetre.fill(blanc)
        fenetre.blit(titre, (200, 150))

        pygame.draw.rect(fenetre, play_color, play_button)
        pygame.draw.rect(fenetre, quit_color, quit_button)

        texte_play = font_menu.render("PLAY", True, blanc)
        texte_quit = font_menu.render("QUIT", True, blanc)
        fenetre.blit(texte_play, (play_button.x + 50, play_button.y + 15))
        fenetre.blit(texte_quit, (quit_button.x + 50, quit_button.y + 15))

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if play_button.collidepoint(event.pos):
                    return "play"
                elif quit_button.collidepoint(event.pos):
                    pygame.quit()
                    quit()
            elif event.type == pygame.MOUSEMOTION:
                if play_button.collidepoint(event.pos):
                    play_color = (255, 0, 0)  # Rouge
                else:
                    play_color = (0, 255, 0)  # Vert

                if quit_button.collidepoint(event.pos):
                    quit_color = (255, 0, 0)  # Rouge
                else:
                    quit_color = (0, 255, 0)  # Vert


# Fonction principale du jeu
def jouer():
    etat_jeu = "menu"

    while True:
        if etat_jeu == "menu":
            etat_jeu = menu()
        elif etat_jeu == "play":
            joueur = Joueur()
            nombre_ennemis = 5
            ennemis = [Ennemi() for _ in range(nombre_ennemis)]
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

                for ennemi in ennemis:
                    ennemi.suivre_joueur(joueur)
                    ennemi.gestion_collision_ennemis(ennemis)
                    ennemi.tirer(joueur)
                    ennemi.deplacer_tirs()

                joueur.deplacer()
                gestion_collisions(joueur, ennemis)
                dessiner_entites(joueur, ennemis)

                texte_vie = police.render(f"Vie : {joueur.vie}", True, noir)
                fenetre.blit(texte_vie, (10, 10))

                pygame.display.flip()
                clock.tick(60)

            etat_jeu = "menu"  # Retour au menu après la fin du jeu

# Appel de la fonction principale
jouer()
