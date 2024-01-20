import pygame
import random
import math
from menu import menu

# Initialisation de Pygame
pygame.init()

# Paramètres du jeu
largeur_fenetre = 800
hauteur_fenetre = 600
taille_case = 50
nombre_colonnes = largeur_fenetre // taille_case
nombre_lignes = hauteur_fenetre // taille_case

shoot_sound = pygame.mixer.Sound("song/tir.mp3")  # Replace with the path to your shoot sound file
enemy_died = pygame.mixer.Sound("song/dead.mp3")
player_degat = pygame.mixer.Sound("song/degat.mp3")
player_dead = pygame.mixer.Sound("song/jesuismort.mp3")
new_level = pygame.mixer.Sound("song/level.mp3")
win = pygame.mixer.Sound("song/win.mp3")

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
        self.image = pygame.image.load("original.png")  # Remplacez "path/to/your/crosshair.png" par le chemin de votre image
        self.image = pygame.transform.scale(self.image, (50, 50))  # Ajustez la taille de l'image selon vos besoins
        self.rect = self.image.get_rect()

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
    def __init__(self, vitesse_tir_joueur=100.0, delai_tir_joueur=0):
        self.image_original = pygame.image.load("player.png")
        self.image_original = pygame.transform.scale(self.image_original, (taille_case, taille_case))
        self.image = self.image_original.copy() 
        self.rect = self.image.get_rect()
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
        self.angle = 0  # Nouvelle propriété pour l'angle de rotation
        self.vitesse_rotation = 2

    def deplacer(self):
        self.x += self.dx * self.vitesse
        self.y += self.dy * self.vitesse
        self.x = max(0, min(self.x, nombre_colonnes - 1))
        self.y = max(0, min(self.y, nombre_lignes - 1))

    def tourner(self, angle):
        # Mettre à jour l'angle du joueur
        self.angle += angle

    def perdre_vie(self, points):
        self.vie -= points
        self.vie = max(0, self.vie)

    def obtenir_image_rotated(self):
        # Faire une rotation de l'image originale en fonction de l'angle
        rotated_image = pygame.transform.rotate(self.image_original, -self.angle)
        return rotated_image

# Classe pour représenter un ennemi
class Ennemi:
    def __init__(self, vitesse_tir_ennemi=2.0, life=100):
        self.x = random.randint(0, nombre_colonnes - 1)
        self.y = random.randint(0, nombre_lignes - 1)
        self.tirs = []
        self.temps_dernier_tir = pygame.time.get_ticks()
        self.image = pygame.image.load("song/monster.png")
        self.image = pygame.transform.scale(self.image, (taille_case, taille_case))
        self.vitesse_tir_ennemi = vitesse_tir_ennemi
        self.vie = life

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

    def tirer(self, joueur, tir_ennemi=1000):
        now = pygame.time.get_ticks()
        temps_ecoule = now - self.temps_dernier_tir
        delai_tir = tir_ennemi ## tir ennemie

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

    fenetre.blit(joueur.image, (joueur.x * taille_case, joueur.y * taille_case))

    for tir in joueur.tirs:
        pygame.draw.circle(fenetre, noir, (int(tir.x), int(tir.y)), 5)

    for ennemi in ennemis:
        fenetre.blit(ennemi.image, (ennemi.x * taille_case, ennemi.y * taille_case))

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
                    enemy_died.play()

    for ennemi in ennemis:
        for tir in ennemi.tirs:
            distance = math.sqrt((joueur.x - tir.x)**2 + (joueur.y - tir.y)**2)
            if distance < 1:
                print("Balle ennemie touche le joueur!")
                joueur.perdre_vie(5)
                tirs_ennemis_a_retirer.append(tir)
                player_degat.play()

    joueur.tirs = [tir for tir in joueur.tirs if tir not in tirs_joueur_a_retirer]
    for ennemi in ennemis:
        ennemi.tirs = [tir for tir in ennemi.tirs if tir not in tirs_ennemis_a_retirer]
    for ennemi in ennemis_a_retirer:
        ennemis.remove(ennemi)

def mapOne():
    pygame.mixer.init()
    pygame.mixer.music.load("song/game_one.mp3")
    pygame.mixer.music.set_volume(0.5)
    pygame.mixer.music.play(-1)

    joueur = Joueur(vitesse_tir_joueur=10.0)
    nombre_ennemis = 5
    ennemis = [Ennemi(vitesse_tir_ennemi=0.1, life=100) for _ in range(nombre_ennemis)]
    viseur = Viseur()  
    continuer = True
    clock = pygame.time.Clock()

    while continuer:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.mixer.music.stop()  # Stop the music before quitting
                jouer()
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
                        shoot_sound.play()

        for tir in joueur.tirs:
            tir.deplacer()

        joueur.tourner(2)

        for ennemi in ennemis:
            ennemi.suivre_joueur(joueur)
            ennemi.gestion_collision_ennemis(ennemis)
            ennemi.tirer(joueur)
            ennemi.deplacer_tirs()

        if (len(ennemis) == 0):
            new_level.play()
            mapTwo()

        joueur.deplacer()
        gestion_collisions(joueur, ennemis)

        joueur.image = joueur.obtenir_image_rotated()

        dessiner_entites(joueur, ennemis)

        fenetre.blit(viseur.image, (viseur.x - viseur.rect.width // 2, viseur.y - viseur.rect.height // 2))

        pygame.draw.circle(fenetre, noir, (int(viseur.x), int(viseur.y)), 5)

        if (joueur.vie <= 0):
            player_dead.play()
            continuer = False

        texte_vie = police.render(f"Vie : {joueur.vie}", True, noir)
        fenetre.blit(texte_vie, (10, 10))

        pygame.display.flip()
        clock.tick(60)

def mapTwo():
    pygame.mixer.init()
    pygame.mixer.music.load("song/song_two.mp3")
    pygame.mixer.music.set_volume(0.5)
    pygame.mixer.music.play(-1)

    joueur = Joueur(vitesse_tir_joueur=10.0)
    nombre_ennemis = 10
    ennemis = [Ennemi(vitesse_tir_ennemi=0.1, life=100) for _ in range(nombre_ennemis)]
    viseur = Viseur()  
    continuer = True
    clock = pygame.time.Clock()

    while continuer:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                jouer()
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
                        shoot_sound.play()

        for tir in joueur.tirs:
            tir.deplacer()

        joueur.tourner(2)

        for ennemi in ennemis:
            ennemi.suivre_joueur(joueur)
            ennemi.gestion_collision_ennemis(ennemis)
            ennemi.tirer(joueur)
            ennemi.deplacer_tirs()

        joueur.deplacer()
        gestion_collisions(joueur, ennemis)
        joueur.image = joueur.obtenir_image_rotated()

        dessiner_entites(joueur, ennemis)

        pygame.draw.circle(fenetre, noir, (int(viseur.x), int(viseur.y)), 5)

        if (len(ennemis) == 0):
            new_level.play()
            mapThree()

        fenetre.blit(viseur.image, (viseur.x - viseur.rect.width // 2, viseur.y - viseur.rect.height // 2))

        if (joueur.vie <= 0):
            player_dead.play()
            jouer()

        texte_vie = police.render(f"Vie : {joueur.vie}", True, noir)
        fenetre.blit(texte_vie, (10, 10))

        pygame.display.flip()
        clock.tick(60)


def mapThree():
    pygame.mixer.init()
    pygame.mixer.music.load("song/game_three.mp3")
    pygame.mixer.music.set_volume(0.5)
    pygame.mixer.music.play(-1)

    joueur = Joueur(vitesse_tir_joueur=10.0)
    nombre_ennemis = 2
    ennemis = [Ennemi(vitesse_tir_ennemi=0.1, life=10) for _ in range(nombre_ennemis)]
    viseur = Viseur()  
    continuer = True
    clock = pygame.time.Clock()

    while continuer:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                continuer = False
                jouer()
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
                        shoot_sound.play()

        for tir in joueur.tirs:
            tir.deplacer()

        joueur.tourner(2)
        


        for ennemi in ennemis:
            ennemi.suivre_joueur(joueur)
            ennemi.gestion_collision_ennemis(ennemis)
            ennemi.tirer(joueur, 100)
            ennemi.deplacer_tirs()

        if (len(ennemis) == 0):
            win.play() 
            jouer()

        joueur.deplacer()
        gestion_collisions(joueur, ennemis)

        dessiner_entites(joueur, ennemis)

        pygame.draw.circle(fenetre, noir, (int(viseur.x), int(viseur.y)), 5)

        fenetre.blit(viseur.image, (viseur.x - viseur.rect.width // 2, viseur.y - viseur.rect.height // 2))


        if (joueur.vie <= 0):
            player_dead.play()
            jouer()

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
