/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** main
*/

#include "./ImportEngine.hpp"
#include "./Game/Game.hpp"
#include <ctime>

int main(int ac, char **av)
{
    try {
        if (ac != 3) {
            std::cerr << "Missing arguments" << std::endl;
            exit(84);
        }

        Engine *engine = new Engine(av[1], av[2]);
        Game *game = new Game(*engine);
        game->preLaunchSetting();

        engine->window->run([&engine, &game]() {
            game->updateEnnemyHealth();
            game->networkProtocol();
            if (engine->scene->getActualScene() == "room1") {
                engine->system->playerKeysInterpretation(KEY_UP, [&engine, &game]() {
                    (void)engine;
                    game->moveUp();
                });
                engine->system->playerKeysInterpretation(KEY_DOWN, [&engine, &game]() {
                    (void)engine;
                    game->moveDown();
                });
                engine->system->playerKeysInterpretation(KEY_LEFT, [&engine, &game]() {
                    (void)engine;
                    game->moveLeft();
                });
                engine->system->playerKeysInterpretation(KEY_RIGHT, [&engine, &game]() {
                    (void)engine;
                    game->moveRight();
                });

            }

            engine->catchWindowEvent([&engine, &game]() {
                engine->system->changeSceneSystem();
                engine->system->changeSpriteRectSystem();
                engine->system->playerKeysInterpretation(KEY_SPACE, [&engine, &game]() {
                    (void)engine;
                    game->shoot();
                });
            });

            // float speed = 0.2;
            // for (int i = 1; i != 8; i++, speed += 0.5) {
            //     game->moveParallax("parallax" + std::to_string(i), speed);
            // }

        }, *engine);

    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
