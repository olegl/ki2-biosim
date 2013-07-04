#ifndef SMELL_MAP_H
#define SMELL_MAP_H

#include <vector>
#include <iostream>
#include <iomanip>


class smell_map
{
    public:
        // Konstruktor erstellt eine leere Map der Dimension n x m
        smell_map(int n, int m);

        // Update-Methode, die die Smell-Map nach den gegebenen Regeln aktualisiert
        void update();

        // Methode, die einen Geruch der übergebenen Intensität auf dem Feld (i,j) hinzufügt
        // Wird keine Intensität übergeben, wird der Defaultwert 100 genommen
        void addSmell(int i, int j, double intensity = 100);

        // Ausgabe (für Debugging)
        void print();

        // Gibt den Nachbarn mit dem stärksten Geruch oberhalb der Schwelle threshhold zurück
        // Wenn das übergebene Feld den stärksten Geruch hat, wird false zurückgegeben
        bool strongestSmell(int & x, int & y, int threshold = 0);

    private:
        // Speicher der eigentlichen Karte
        std::vector<std::vector<double>> smell;

        // Temporäre Karte zum Updaten
        std::vector<std::vector<double>> temp;

        // Methode, die den Geruch verteilt
        void spreadSmell(int i, int j);

        // Updatemethode für das Feld (x,y)
        void updateSmell(int x, int y, double newSmell);

};

#endif // SMELL_MAP_H
