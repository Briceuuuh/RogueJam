import pygame
import random
import math
from menu import menu
import pytmx

# Initialisation de Pygame
pygame.init()

# Paramètres du jeu
largeur_fenetre = 960
hauteur_fenetre = 640
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
rouge = (255, 128, 0)

# Création de la fenêtre du jeu
fenetre = pygame.display.set_mode((largeur_fenetre, hauteur_fenetre))
pygame.display.set_caption("Rogue-like ~ Monster's legacy")

# Police pour le texte
police = pygame.font.SysFont(None, 36)

class Viseur:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.image = pygame.image.load("original.png")  # Remplacez "path/to/your/crosshair.png" par le chemin de votre image
        self.image = pygame.transform.scale(self.image, (50, 50))  # Ajustez la taille de l'image selon vos besoins
        self.rect = self.image.get_rect()

class Carre:
    def __init__(self, image="song/kalash.png"):
        self.x = random.randint(0, nombre_colonnes - 1)
        self.y = random.randint(0, nombre_lignes - 1)
        self.size = taille_case
        self.active = True
        self.image = pygame.image.load(image)
        self.image = pygame.transform.scale(self.image, (self.size, self.size))

    def draw(self, surface):
        if self.active:
            surface.blit(self.image, (self.x * taille_case, self.y * taille_case))

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
    def __init__(self, vitesse_tir_joueur=100.0, delai_tir_joueur=1000):
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
        # self.x = random.randint(0, nombre_colonnes - 1)
        # self.y = random.randint(0, nombre_lignes - 1)
        self.x, self.y = self.random_position()
        self.tirs = []
        self.temps_dernier_tir = pygame.time.get_ticks()
        self.image = pygame.image.load("song/monster.png")
        self.image = pygame.transform.scale(self.image, (taille_case, taille_case))
        self.vitesse_tir_ennemi = vitesse_tir_ennemi
        self.vie = life
    
    def random_position(self):
        # Determine a random side of the map for enemy spawn
        side = random.choice(['left', 'right', 'top', 'bottom'])
        
        if side == 'left':
            x = -1
            y = random.randint(0, nombre_lignes - 1)
        elif side == 'right':
            x = nombre_colonnes
            y = random.randint(0, nombre_lignes - 1)
        elif side == 'top':
            x = random.randint(0, nombre_colonnes - 1)
            y = -1
        elif side == 'bottom':
            x = random.randint(0, nombre_colonnes - 1)
            y = nombre_lignes

        return x, y

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
        delai_tir = tir_ennemi  # tir ennemie

        if temps_ecoule > delai_tir:
            angles = [0, math.pi / 2, math.pi, 3 * math.pi / 2]  # Haut, Gauche, Bas, Droite
            for angle in angles:
                tir = Tir(self.x, self.y, angle, vitesse=self.vitesse_tir_ennemi)
                self.tirs.append(tir)
            
            self.temps_dernier_tir = now

    def deplacer_tirs(self):
        for tir in self.tirs:
            tir.deplacer()

def check_collision_carre(joueur, carre, delai_tir=0):
    joueur_rect = pygame.Rect(joueur.x * taille_case, joueur.y * taille_case, taille_case, taille_case)
    carre_rect = pygame.Rect(carre.x * taille_case, carre.y * taille_case, carre.size, carre.size)

    if joueur_rect.colliderect(carre_rect) and carre.active:
        joueur.delai_tir_joueur = delai_tir # Increase the player's shooting delay
        carre.active = False

# Fonction pour dessiner les entités (joueur, ennemis, tirs, carrés)
def dessiner_entites(joueur, ennemis, tmx_data):
    fenetre.fill(blanc)

    for layer in tmx_data.layers:
        if isinstance(layer, pytmx.TiledTileLayer):
            for x, y, gid in layer:
                tile_image = tmx_data.get_tile_image_by_gid(gid)
                if tile_image:
                    fenetre.blit(tile_image, (x * tmx_data.tilewidth, y * tmx_data.tileheight))

    fenetre.blit(joueur.image, (joueur.x * taille_case, joueur.y * taille_case))

    for tir in joueur.tirs:
        pygame.draw.circle(fenetre, noir, (int(tir.x), int(tir.y)), 5)

    for ennemi in ennemis:
        fenetre.blit(ennemi.image, (ennemi.x * taille_case, ennemi.y * taille_case))

        # Dessiner le point de vie au-dessus de l'ennemi
        texte_vie_ennemi = police.render(str(ennemi.vie), True, rouge)
        fenetre.blit(texte_vie_ennemi, (ennemi.x * taille_case, ennemi.y * taille_case - 20))

        for tir in ennemi.tirs:
            pygame.draw.circle(fenetre, rouge, (int(tir.x * taille_case), int(tir.y * taille_case)), 5)

# Fonction pour gérer les collisions entre les tirs et le joueur
def gestion_collisions(joueur, ennemis, degat_monster=5, degat_player=10):
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
                ennemi.perdre_vie(degat_player)
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
                joueur.perdre_vie(degat_monster)
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
    # carre = Carre()
    nombre_ennemis = 1
    ennemis = [Ennemi(vitesse_tir_ennemi=0.1, life=100) for _ in range(nombre_ennemis)]
    viseur = Viseur()  
    continuer = True
    clock = pygame.time.Clock()

    tmx_data = pytmx.util_pygame.load_pygame("./mapOne/idk.tmx")

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
        # check_collision_carre(joueur, carre)

        gestion_collisions(joueur, ennemis)

        joueur.image = joueur.obtenir_image_rotated()

        for layer in tmx_data.layers:
            if isinstance(layer, pytmx.TiledTileLayer):
                for x, y, gid in layer:
                    tile_image = tmx_data.get_tile_image_by_gid(gid)
                    if tile_image:
                        fenetre.blit(tile_image, (x * tmx_data.tilewidth, y * tmx_data.tileheight))

        dessiner_entites(joueur, ennemis, tmx_data)

        # carre.draw(fenetre)

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
    pygame.mixer.music.load("song/game_one.mp3")
    pygame.mixer.music.set_volume(0.5)
    pygame.mixer.music.play(-1)

    joueur = Joueur(vitesse_tir_joueur=10.0)
    carre = Carre('song/kalash.png')
    nombre_ennemis = 5
    ennemis = [Ennemi(vitesse_tir_ennemi=0.1, life=100) for _ in range(nombre_ennemis)]
    viseur = Viseur()
    continuer = True
    clock = pygame.time.Clock()

    tmx_data = pytmx.util_pygame.load_pygame("./mapOne/idk.tmx")

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

        if (len(ennemis) == 0):
            new_level.play()
            mapThree()

        joueur.deplacer()
        check_collision_carre(joueur, carre)

        gestion_collisions(joueur, ennemis)

        # Dessiner les entités (joueur, ennemis, tirs, carrés)
        dessiner_entites(joueur, ennemis, tmx_data)

        carre.draw(fenetre)

        fenetre.blit(viseur.image, (viseur.x - viseur.rect.width // 2, viseur.y - viseur.rect.height // 2))
        pygame.draw.circle(fenetre, noir, (int(viseur.x), int(viseur.y)), 5)

        if joueur.vie <= 0:
            player_dead.play()
            continuer = False

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
    carre = Carre('song/bazooka.png')
    viseur = Viseur()  
    continuer = True
    clock = pygame.time.Clock()

    tmx_data = pytmx.util_pygame.load_pygame("./mapThree/untitled.tmx")

    initial_timer = 120000
    current_timer = initial_timer

    enemies_spawned = 0
    max_enemies = 2
    ennemis = []

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

        elapsed_time = pygame.time.get_ticks()
        remaining_time = max(0, initial_timer - elapsed_time)
        minutes = remaining_time // 60000
        seconds = (remaining_time // 1000) % 60

        for tir in joueur.tirs:
            tir.deplacer()

        joueur.tourner(2)

        for ennemi in ennemis:
            ennemi.suivre_joueur(joueur)
            ennemi.gestion_collision_ennemis(ennemis)
            ennemi.tirer(joueur, 500)
            ennemi.deplacer_tirs()

        if len(ennemis) == 0:
            enemies_spawned += 1
            if enemies_spawned > max_enemies:
                max_enemies += 1
                enemies_spawned = 0
                for _ in range(max_enemies):
                    ennemis.append(Ennemi(vitesse_tir_ennemi=0.01, life=750))

        check_collision_carre(joueur, carre, 750)

        joueur.deplacer()
        gestion_collisions(joueur, ennemis, 5, check_val(carre.active))

        for layer in tmx_data.layers:
            if isinstance(layer, pytmx.TiledTileLayer):
                for x, y, gid in layer:
                    tile_image = tmx_data.get_tile_image_by_gid(gid)
                    if tile_image:
                        fenetre.blit(tile_image, (x * tmx_data.tilewidth, y * tmx_data.tileheight))

        dessiner_entites(joueur, ennemis, tmx_data)

        carre.draw(fenetre)

        pygame.draw.circle(fenetre, noir, (int(viseur.x), int(viseur.y)), 5)

        fenetre.blit(viseur.image, (viseur.x - viseur.rect.width // 2, viseur.y - viseur.rect.height // 2))

        if joueur.vie <= 0:
            player_dead.play()
            jouer()

        # Display the timer on the screen
        texte_vie = police.render(f"Vie : {joueur.vie}", True, (255,255,255))
        fenetre.blit(texte_vie, (10, 10))
        timer_text = police.render(f"{minutes:02d}:{seconds:02d}", True, rouge)
        fenetre.blit(timer_text, (largeur_fenetre - 200, 10))

        # Check if the timer has reached zero
        if remaining_time <= 0:
            win.play()
            jouer()

        pygame.display.flip()
        clock.tick(60)

def check_val(val):
    if val == True:
        return 10
    return 250

def jouer():
    etat_jeu = "menu"

    while True:
        if etat_jeu == "menu":
            etat_jeu = menu(fenetre)
        elif etat_jeu == "play":
            # etat_jeu = mapThree()
            etat_jeu = mapOne()
            etat_jeu = "menu"

jouer()
