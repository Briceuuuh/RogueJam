# 💡 Game Engine - Get Started


Here you have a simple main for create easily some entity or scene with the game engine

```C++
// How to do a simple start
int main(int ac, char **av)
{
    /*----------Create the engine main class----------*/
    Engine *engine = new Engine(av[1], av[2]);
    //or
    char *port;
    char *ipAdress;
    Engine *engine = new Engine(ipAdress, port);

    engine->_DEBUGMOD_ = true; // set the debug variable for have a look at all the entity of a scene


    /*------------------------------------------------*/

    /*-----------------Create a scene-----------------*/
    engine->scene->createScene("My First Scene"); //Create a simple scene with a name
    engine->scene->createScene("My Second Scene"); //Create a second scene

    /*------------------------------------------------*/

    /*-----------------Create a entity-----------------*/
    engine->scene->addEntitytoScene("My First Scene", "My Entity Name"); // Create a entity in a specified scene
    engine->scene->addEntitytoScene("My Third Scene", "My Entity Name"); // Don't work because the scene doesn't exist

    /*------------------------------------------------*/

    engine->entity->addComponent("My First scene", "My Entity Name", POSITION, VISUAL, ...); // Add component to a entity
    engine->entity->removeComponent("My First scene", "My Entity Name", POSITION, VISUAL, ...); // Remove component to a entity

    engine->entity->addPosition("My First scene", "My Entity Name", {10, 40}); // Add Position to a entity (if the entity have POSITION component)
    engine->entity->addTexture("My First scene", "My Entity Name", "/img/sprite.png"); // Add Texture to a entity (if the entity have VISUAL component)
    /*
        And many more method if you search with:
        engine->entity->...
    */


    /*-----------------Remove a entity-----------------*/
    engine->scene->removeEntitytoScene("My First Scene", "My Entity Name");

    /*------------------------------------------------*/

    /*-----------------Event management-----------------*/
    engine->event->addEventToCatch(KEY_INPUT, MOUSE_EVENT, CLOSE_EVENT); // Add event to catch. by default all is active.
    engine->event->removeEventToCatch(KEY_INPUT, CLOSE_EVENT); // Remove event to catch.
    if (engine->event->getKeyPressed() == KEY_A /*or any other*/) // Get if a key is pressed, or mouse
    if (engine->event->WindowCloseEvent()) // Catch if the window is closed

    /*------------------------------------------------*/


    /*-----------------Event management-----------------*/
    engine->system->changeSceneOnClick("My Entity name", "My Entity Name", "My Next scene name", MOUSE_LEFT); // Configuration of a scene change by clicking on the left mouse
    engine->system->changeSpriteRectOnHover("My First Scene", "My entity to hover name", {400, 200}); // Change the sprite rec by the new passed as parameter

    /*------------------------------------------------*/

    /*-----------------Window management-----------------*/

    engine->window->create(500, 400, "Title"); // Create a custom window with width and height and a title
    engine->window->display(); // Display the window if created
    /*
        engine->window->....   and many more if you search in the documentation
    */
    /*------------------------------------------------*/

    return(0);
}
```

If you want to explore more, you can read the documentation.

## 🚨 Don't forget to compile your project with the engine, because the engine is a static library.