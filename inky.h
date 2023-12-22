#ifndef INKY_H
#define INKY_H
#include "ghosts.h"

class Inky:public Ghosts
{
private:
    const int InitialRow=14;
     const int InitialColumn=13;
public:
    Inky(int** temp);
    void ReturnHome() override; //returns inky to its home
    void ReturnOriginalState() override;//returns its image without returning to its home
    virtual void UpdateShortestPath(QPair <int, int> PacmanCoordiante, int pacManDir) override;


};

#endif // INKY_H
