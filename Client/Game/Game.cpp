/*
** EPITECH PROJECT, 2023
** Sans titre(Espace de travail)
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(Engine &engine)
{
    this->_engine = &engine;
}

Game::~Game()
{
    delete this->_engine;
}

void Game::moveParallax(std::string parallaxName, float speed)
{
    IEntity &ent2 = this->_engine->scene->getEntityFromScene("room1", parallaxName);
    Visual *vis2 = (Visual *)ent2.getComponent(VISUAL);

    sf::IntRect rect = vis2->getRect();

    float parallaxSpeed = speed;

    rect.left -= parallaxSpeed;

    if (rect.left <= 0) {
        rect.left = vis2->getTexture().getSize().x - 2000;
    }

    vis2->setRect(rect);
}


void Game::moveUp()
{
    ClientSession *client = this->_engine->network->getClient().at(0);
    this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", true, false, false, false, client->getShoot());
    this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
    this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {true, false, false, false}, 5);

    this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", false, false, false, false, false);
    this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
    this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {false, false, false, false}, 5);
}

void Game::moveDown()
{
    ClientSession *client = this->_engine->network->getClient().at(0);
    this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", false, true, false, false, client->getShoot());
    this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
    this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {false, true, false, false}, 5);

    this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", false, false, false, false, false);
    this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
    this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {false, false, false, false}, 5);
}

void Game::moveLeft()
{
    ClientSession *client = this->_engine->network->getClient().at(0);
    this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", false, false, true, false, client->getShoot());
    this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
    this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {false, false, true, false}, 5);

    this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", false, false, false, false, false);
    this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
    this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {false, false, false, false}, 5);
}

void Game::moveRight()
{
    ClientSession *client = this->_engine->network->getClient().at(0);
    this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", false, false, false, true, client->getShoot());
    this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
    this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {false, false, false, true}, 5);

    this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", false, false, false, false, false);
    this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
    this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {false, false, false, false}, 5);
}
void Game::shoot()
{
    if (this->_engine->clock->getTimeElapsed("player") > 0.3) {
        this->_engine->sound->play(SOUND, "shootSong");
        ClientSession *client = this->_engine->network->getClient().at(0);
        this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", client->getUp(), client->getDown(), client->getLeft(), client->getRight(), true);
        this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
        this->_engine->system->shootSpecificSystem("player" + std::to_string(this->_engine->network->getClient().at(0)->getId()), "room" + std::to_string(this->_engine->network->getClient().at(0)->getRoom()));
        this->_engine->clock->restart("player");

        this->_engine->network->getCode().setSendPackage(client->getId(), client->getRoom(), "move entity", false, false, false, false, false);
        this->_engine->network->getUdp().sendPackage(this->_engine->network->getCode().getSendPackage());
        this->_engine->system->moveEntitySpecificSystem("player" + std::to_string(client->getId()), "room" + std::to_string(client->getRoom()), {false, false, false, false}, 5);
    }
}

void Game::preLaunchSetting()
{

    this->_engine->scene->loadSceneFromJson("./Client/scene.json", *this->_engine);
    this->_engine->scene->loadActionFromJson("./Client/action.json", *this->_engine);
    this->_engine->sound->Create(MUSIC, "test", "./Client/assets/music.ogg");
    this->_engine->sound->Create(SOUND, "shootSong", "./Client/assets/shoot.wav");

    this->_engine->scene->createEntityPreset("room1", "ennemy1", {400, 500}, "./Client/assets/ennemy1.png", "ennemy", false);
    this->_engine->scene->createEntityPreset("room1", "ennemy2", {800, 200}, "./Client/assets/ennemy1.png", "ennemy", false);
    this->_engine->scene->createEntityPreset("room1", "ennemy3", {600, 700}, "./Client/assets/ennemy1.png", "ennemy", false);
    this->_engine->scene->createEntityPreset("room1", "ennemy4", {300, 300}, "./Client/assets/ennemy1.png", "ennemy", false);

    Position *pos1 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy1").getComponent(POSITION);
    Position *pos2 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy2").getComponent(POSITION);
    Position *pos3 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy3").getComponent(POSITION);
    Position *pos4 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy4").getComponent(POSITION);

    Health *health1 = (Health *)this->_engine->scene->getEntityFromScene("room1", "ennemy1").getComponent(HEALTH);
    Health *health2 = (Health *)this->_engine->scene->getEntityFromScene("room1", "ennemy2").getComponent(HEALTH);
    Health *health3 = (Health *)this->_engine->scene->getEntityFromScene("room1", "ennemy3").getComponent(HEALTH);
    Health *health4 = (Health *)this->_engine->scene->getEntityFromScene("room1", "ennemy4").getComponent(HEALTH);

    this->_engine->scene->createTextPreset("room1", "ennemy1health", {pos1->getPostion().at(0), pos1->getPostion().at(1) - 30}, "./Client/assets/font.ttf", "PV:" + std::to_string(health1->getHealth()), sf::Color::White);
    this->_engine->scene->createTextPreset("room1", "ennemy2health", {pos2->getPostion().at(0), pos2->getPostion().at(1) - 30}, "./Client/assets/font.ttf", "PV:" + std::to_string(health2->getHealth()), sf::Color::White);
    this->_engine->scene->createTextPreset("room1", "ennemy3health", {pos3->getPostion().at(0), pos3->getPostion().at(1) - 30}, "./Client/assets/font.ttf", "PV:" + std::to_string(health3->getHealth()), sf::Color::White);
    this->_engine->scene->createTextPreset("room1", "ennemy4health", {pos4->getPostion().at(0), pos4->getPostion().at(1) - 30}, "./Client/assets/font.ttf", "PV:" + std::to_string(health4->getHealth()), sf::Color::White);
}

void Game::networkProtocol()
{
    this->_engine->sound->play(MUSIC, "test");
    this->_engine->network->connectionTcp();
    this->_engine->network->connectionUdp();
    this->_engine->network->gameProtocol();
    this->_engine->system->moveEntitySystem("rocket_player", "room1", {false, false, false, true}, 10, true);
    this->_engine->system->moveEntitySystem("rocket_ennemy", "room1", {false, false, true, false}, 10, true);
    this->_engine->system->collisionSystem("ennemy", "rocket_player", "room1", true, 20, false, true);

    this->_engine->system->collisionSystem("player", "rocket_ennemy", "room1", true, 10, false, true);
    Text *text = (Text*)this->_engine->scene->getEntityFromScene("room1", "player" + std::to_string(this->_engine->network->getClient().at(0)->getId()) + "health").getComponent(TEXT);
    Health *health = (Health*)this->_engine->scene->getEntityFromScene("room1", "player" + std::to_string(this->_engine->network->getClient().at(0)->getId())).getComponent(HEALTH);
    text->setText("PV: " + std::to_string(health->getHealth()), false);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    bool randomBool1 = std::rand() % 2 == 0;
    bool randomBool2 = std::rand() % 2 == 0;
    bool randomBool3 = std::rand() % 2 == 0;
    bool randomBool4 = std::rand() % 2 == 0;
    this->_engine->system->moveEntitySystem("ennemy", "room1", {randomBool1, randomBool2, randomBool3, randomBool4}, 1, false);
    this->_engine->system->shootSystem("ennemy", "room1", 4);
}

void Game::updateEnnemyHealth()
{
    if (this->_engine->entity->searchEntity("room1", "ennemy1")) {
        Position *pos1 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy1").getComponent(POSITION);
        Health *health1 = (Health *)this->_engine->scene->getEntityFromScene("room1", "ennemy1").getComponent(HEALTH);
        Text *txt1 = (Text *)this->_engine->scene->getEntityFromScene("room1", "ennemy1health").getComponent(TEXT);
        Position *txtpos1 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy1health").getComponent(POSITION);
        txt1->setText("PV: " + std::to_string(health1->getHealth()), false);
        txtpos1->setPosition(pos1->getPostion().at(0), pos1->getPostion().at(1) - 30);
        txt1->getText().setPosition({(float)pos1->getPostion().at(0), (float)pos1->getPostion().at(1) - 30});

        if (health1->getHealth() == 0) {
            this->_engine->scene->removeEntitytoScene("room1", "ennemy1");
            this->_engine->scene->removeEntitytoScene("room1", "ennemy1health");
        }
    }

    if (this->_engine->entity->searchEntity("room1", "ennemy2")) {
        Position *pos2 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy2").getComponent(POSITION);
        Health *health2 = (Health *)this->_engine->scene->getEntityFromScene("room1", "ennemy2").getComponent(HEALTH);
        Text *txt2 = (Text *)this->_engine->scene->getEntityFromScene("room1", "ennemy2health").getComponent(TEXT);
        Position *txtpos2 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy2health").getComponent(POSITION);
        txt2->setText("PV: " + std::to_string(health2->getHealth()), false);
        txtpos2->setPosition(pos2->getPostion().at(0), pos2->getPostion().at(1) - 30);
        txt2->getText().setPosition({(float)pos2->getPostion().at(0), (float)pos2->getPostion().at(1) - 30});

        if (health2->getHealth() == 0) {
            this->_engine->scene->removeEntitytoScene("room1", "ennemy2");
            this->_engine->scene->removeEntitytoScene("room1", "ennemy2health");
        }
    }

    if (this->_engine->entity->searchEntity("room1", "ennemy3")) {
        Position *pos3 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy3").getComponent(POSITION);
        Health *health3 = (Health *)this->_engine->scene->getEntityFromScene("room1", "ennemy3").getComponent(HEALTH);
        Text *txt3 = (Text *)this->_engine->scene->getEntityFromScene("room1", "ennemy3health").getComponent(TEXT);
        Position *txtpos3 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy3health").getComponent(POSITION);
        txt3->setText("PV: " + std::to_string(health3->getHealth()), false);
        txtpos3->setPosition(pos3->getPostion().at(0), pos3->getPostion().at(1) - 30);
        txt3->getText().setPosition({(float)pos3->getPostion().at(0),(float)pos3->getPostion().at(1) - 30});

        if (health3->getHealth() == 0) {
            this->_engine->scene->removeEntitytoScene("room1", "ennemy3");
            this->_engine->scene->removeEntitytoScene("room1", "ennemy3health");
        }
    }

    if (this->_engine->entity->searchEntity("room1", "ennemy4")) {
        Position *pos4 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy4").getComponent(POSITION);
        Health *health4 = (Health *)this->_engine->scene->getEntityFromScene("room1", "ennemy4").getComponent(HEALTH);
        Text *txt4 = (Text *)this->_engine->scene->getEntityFromScene("room1", "ennemy4health").getComponent(TEXT);
        Position *txtpos4 = (Position *)this->_engine->scene->getEntityFromScene("room1", "ennemy4health").getComponent(POSITION);
        txt4->setText("PV: " + std::to_string(health4->getHealth()), false);
        txtpos4->setPosition(pos4->getPostion().at(0), pos4->getPostion().at(1) - 30);
        txt4->getText().setPosition({(float)pos4->getPostion().at(0), (float)pos4->getPostion().at(1) - 30});

        if (health4->getHealth() == 0) {
            this->_engine->scene->removeEntitytoScene("room1", "ennemy4");
            this->_engine->scene->removeEntitytoScene("room1", "ennemy4health");
        }
    }
}