# 🛸 (GT)R TYPE
![MENU](docs/menu.png)

## 🌍 Prologue

In galaxy X1X, in 2163.

The new space government seeks to destroy enemy planets. It's a tough fight, but luckily you're here to help, Captain.

## 🔑 prerequisites

if you have a *Windows machine*, you'll need to install Visual Studio, CMake and CPack.

*More about Visual Studio => https://visualstudio.microsoft.com/*

*More about CMake => https://cmake.org/download/*

*More about NSIS (Cpack) => https://nsis.sourceforge.io/Download*

## 💻 Usage

* __Linux__ ~
Simply run the bash script *build.sh*:
```bash
./build.sh
```

* __Windows__ ~ (on powershell):
```powershell
.\build.bat
```

This will generate 2 binaries:

On linux:
* `./rtype_server` 
* `./rtype_client`

On Windows:
* `.\rtype_server.exe` 
* `.\rtype_client.exe`

### Server

```bash
./rtype_server [PORT]
```

the arguments is:
* __[ PORT ]__ for the port to be connected to

### Client

```bash
./rtype_client [PORT] [HOST]
```

the arguments are:
* __[ PORT ]__ for the port to be connected to
* __[ HOST ]__ for the machine's domain name

## 📝 Architecture

Our project is composed by 3 parts:
* Game Engine
* Client
* Server

### Game Engine
![Diagram](docs/RType-Engine.png)

* For the Game Engine, we decided to develop a *ECS (Entity Component System)* like. Hope you'll like it !
* Read the get started for an easy start (
[READ THE DOC](Engine/README.md))


### Server

![Server](docs/RType-Server.png)

* Here's a documentation if you need to learn more about our binary protocol : [READ THE DOC](Server/docs/README.md)

## 👥 Autors

* Maël POMPILIUS
* Florian ETHEVE
* Ethan GUILLOUX
* Brice HUET
* Noémie MAILLOT
