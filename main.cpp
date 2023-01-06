/*
** EPITECH PROJECT, 2021
** B-MAT-500-STG-5-1-304pacman-clement.muth
** File description:
** main
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

char wall;
char space;
char width;
int pos = 0;

enum valueType
{
    Pacman,
    Ghost,
    Wall,
    Space,
    Invalid,
    Value
};

enum direction
{
    Up,
    Down,
    Left,
    Right
};

class value
{
public:
    value();
    ~value();

    int id;
    int abscisse;
    int ordinary;
    enum valueType type;
    int values = 0;
};

value::value()
{
}

value::~value()
{
}

std::vector<std::string> data;
std::vector<value *> entries;
std::vector<value *> smallestpath;

value *searchIdinEntry(int id)
{
    for (int i = 0; i < entries.size(); i++)
        if (entries[i]->id = id)
            return (entries[i]);
    return (NULL);
}

value *parsingCoordinates(int abscisse, int ordinary)
{
    for (int i = 0; i < entries.size(); i++)
        if (entries[i]->abscisse == abscisse && entries[i]->ordinary == ordinary)
            return (entries[i]);
    return (NULL);
}

value *parsingType(int type)
{
    for (int i = 0; i < entries.size(); i++)
        if ((int)entries[i]->type == type)
            return (entries[i]);
    return (NULL);
}

value *drawingCardFormat(int dir, value *curr)
{
    switch (dir)
    {
    case Up:
        return (parsingCoordinates(curr->abscisse, curr->ordinary - 1));
    case Down:
        return (parsingCoordinates(curr->abscisse, curr->ordinary + 1));
    case Left:
        return (parsingCoordinates(curr->abscisse + 1, curr->ordinary));
    case Right:
        return (parsingCoordinates(curr->abscisse - 1, curr->ordinary));
    default:
        return (NULL);
    }
}

enum valueType checkPlayer(char c)
{
    switch (c)
    {
    case '1':
        return (Wall);
    case '0':
        return (Space);
    case 'F':
        return (Ghost);
    case 'P':
        return (Pacman);
    default:
        return (Invalid);
    };
}

char drawmapbycaractere(enum valueType type)
{
    switch (type)
    {
    case Wall:
        return (wall);
    case Space:
        return (space);
    case Ghost:
        return ('F');
    case Pacman:
        return ('P');
    };
    return (' ');
}

bool parsinghandling(std::string line)
{
    if (pos != 0 && width != line.size())
    {
        std::cout << "Invalid file size." << std::endl;
        return (false);
    }
    enum valueType type;
    width = line.size();
    for (int i = 0; i < line.size(); i++)
    {
        value *entryValue = new value();
        entryValue->abscisse = i;
        entryValue->ordinary = pos;
        entryValue->id = pos * width + i;
        entryValue->type = checkPlayer(line[i]);
        entries.push_back(entryValue);
        if (checkPlayer(line[i]) == Invalid)
            return (false);
    }
    return (true);
}

bool drawMap()
{
    char characters;

    for (int i = 0; i < entries.size(); i++)
    {
        if (i != 0 && entries[i - 1]->ordinary != entries[i]->ordinary)
            std::cout << std::endl;
        if (entries[i]->type == Value)
        {
            if (entries[i]->values >= 0 && entries[i]->values <= 9)
                characters = entries[i]->values + '0';
            else
                characters = '9';
        }
        else
            characters = drawmapbycaractere(entries[i]->type);
        std::cout << characters;
    }
    std::cout << std::endl;
    return (true);
}

bool checkIfPacmanMove(int Movement)
{
    std::vector<value *> next;
    if (!smallestpath.size())
        return (false);
    for (int i = 0; i < smallestpath.size(); i++)
    {
        for (int index = 0; index < 4; index++)
        {
            value *tmp = drawingCardFormat(index, smallestpath[i]);
            if (tmp->type == Pacman)
                return (true);
            if (tmp->type != Space)
                continue;
            tmp->type = Value;
            tmp->values = Movement;
            next.push_back(tmp);
        }
    }
    smallestpath = next;
    if (Movement + 1 > 9)
        Movement = -1;
    return (checkIfPacmanMove(Movement + 1));
}

bool process_path()
{
    value *end = parsingType(Pacman);
    value *current = parsingType(Ghost);
    ;
    int i = 0;

    if (current == NULL || end == NULL)
        return (false);
    smallestpath.clear();
    smallestpath.push_back(current);
    return (checkIfPacmanMove(1));
}

int main(int ac, char **av)
{
    std::string line;
    std::ifstream streamfile;

    if (ac != 4 || strlen(av[2]) != 1 || strlen(av[3]) != 1 || av[2][0] == av[3][0])
        return (84);
    wall = av[2][0];
    space = av[3][0];

    streamfile.open(av[1]);
    if (streamfile.fail())
        return (84);
    for (pos = 0; std::getline(streamfile, line); pos++)
    {
        std::string d(line.c_str());
        data.push_back(d);
        if (!parsinghandling(line))
            return (84);
    }
    if (!process_path())
        return (84);
    if (!drawMap())
        return (84);
    return (0);
}