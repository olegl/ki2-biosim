#include "smell_map.hpp"

smell_map::smell_map(int n, int m)
{
    smell.resize(n);
    for (int i = 0; i < smell.size(); i++)
    {
        smell[i].resize(m);
    }

    temp.resize(n);
    for (int i = 0; i < temp.size(); i++)
    {
        temp[i].resize(m);
    }
}

void smell_map::update()
{
    for (int i = 0; i < temp.size(); i++)
    {
        for (int j = 0; j < temp[i].size(); j++)
        {
            temp[i][j] = 0.0;
        }
    }

    // Geruch verbreitet sich und klingt dabei auf jedem Feld um die Hälfte ab
    for (int i = 0; i < smell.size(); i++)
    {
        for (int j = 0; j < smell[i].size(); j++)
        {
            spreadSmell(i,j);
        }
    }

    // Geruch, der durch Verbreitung entstanden ist dazuaddieren
    for (int i = 0; i < smell.size(); i++)
    {
        for (int j = 0; j < smell[i].size(); j++)
        {
            smell[i][j] += temp[i][j];
            if (smell[i][j] > 500.0)
                smell[i][j] = 500.0;
            else if (smell[i][j] < 0.01)
                smell[i][j] = 0.0;
        }
    }
}

void smell_map::addSmell(int i, int j, double intensity)
{
    smell[i][j] += intensity;
    if (smell[i][j] > 500.0)
        smell[i][j] = 500.0;
}

void smell_map::print()
{
//    for (int i = 0; i < smell.size(); i++)
//    {
//        for (int j = 0; j < smell[i].size(); j++)
//        {
//            std::cout << std::setw(4) << std::setprecision(1) << smell[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
    for (int i = 0; i < smell.size(); i++)
    {
        for (int j = 0; j < smell[i].size(); j++)
        {
            char c;
            if (smell[j][i] == 0.0)
                c = ' ';
            else if (smell[j][i] <= 5)
                c = '.';
            else if (smell[j][i] <= 10)
                c = '*';
            else if (smell[j][i] <= 50)
                c = 'o';
            else if (smell[j][i] <= 100)
                c = 'O';
            else
                c = '#';
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

bool smell_map::strongestSmell(int & x, int & y, int threshold)
{
    int x_new = x, y_new = y;
    double strongest = smell[x][y];

    if (x-1 >= 0 && smell[x-1][y] > threshold && smell[x-1][y] > strongest)
    {
        strongest = smell[x-1][y];
        x_new = x-1;
        y_new = y;
    }

    if (x+1 < smell.size() && smell[x+1][y] > threshold && smell[x+1][y] > strongest)
    {
        strongest = smell[x+1][y];
        x_new = x+1;
        y_new = y;
    }

    if (y-1 >= 0 && smell[x][y-1] > threshold && smell[x][y-1] > strongest)
    {
        strongest = smell[x][y-1];
        x_new = x;
        y_new = y-1;
    }

    if (y+1 < smell[x].size() && smell[x][y+1] > threshold && smell[x][y+1] > strongest)
    {
        strongest = smell[x][y+1];
        x_new = x;
        y_new = y+1;
    }

    if (x_new == x && y_new == y)
    {
        return false;
    }
    else
    {
        x = x_new;
        y = y_new;
        return true;
    }

}

void smell_map::updateSmell(int x, int y, double newSmell)
{
    if (newSmell > temp[x][y])
        temp[x][y] = newSmell;
}

/*
    Methode, die den Geruch vom Feld (x,y) auf die Nachbarfelder verbreitet
    */
void smell_map::spreadSmell(int x, int y)
{

    double local_smell = smell[x][y];
    smell[x][y] /= 2.0;

    if (local_smell > 0.01)
    {

        if (x-1 >= 0)
        {
            updateSmell(x-1,y,0.2*local_smell);

            if (y-1 >= 0)
            {
                updateSmell(x-1,y-1,0.2*local_smell);
            }

            if (y+1 < smell[x-1].size())
            {
                updateSmell(x-1,y+1,0.2*local_smell);
            }
        }

        if (x+1 < smell.size())
        {
            updateSmell(x+1,y,0.2*local_smell);

            if (y-1 >= 0)
            {
                updateSmell(x+1,y-1,0.2*local_smell);
            }

            if (y+1 < smell[x+1].size())
            {
                updateSmell(x+1,y+1,0.2*local_smell);
            }
        }

        if (y-1 >= 0)
        {
            updateSmell(x,y-1,0.2*local_smell);
        }

        if (y+1 < smell[x].size())
        {
            updateSmell(x,y+1,0.2*local_smell);
        }
    }
}
