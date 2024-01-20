import pygame
import sys

def menu(fenetre):
    blanc = (255, 255, 255)
    noir = (0, 0, 0)
    rouge = (255, 0, 0)

    fond = pygame.image.load("IMG_6141.jpg").convert()
    font_menu = pygame.font.SysFont(None, 50)
    titre = font_menu.render("Rogue-like en Python", True, noir)
    play_button = pygame.Rect(300, 250, 200, 50)
    quit_button = pygame.Rect(300, 350, 200, 50)
    play_color = rouge
    quit_color = rouge

    while True:
        fenetre.blit(fond, (0, 0))
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
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if play_button.collidepoint(event.pos):
                    return "play"
                elif quit_button.collidepoint(event.pos):
                    pygame.quit()
                    sys.exit()
            elif event.type == pygame.MOUSEMOTION:
                if play_button.collidepoint(event.pos):
                    play_color = (255, 0, 0)  # Rouge
                else:
                    play_color = (0, 255, 0)  # Vert

                if quit_button.collidepoint(event.pos):
                    quit_color = (255, 0, 0)  # Rouge
                else:
                    quit_color = (0, 255, 0)  # Vert
