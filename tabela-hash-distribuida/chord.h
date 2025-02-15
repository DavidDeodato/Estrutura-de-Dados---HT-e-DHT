#ifndef CHORD_H
#define CHORD_H

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include "aluno.h"

class ChordNode
{
private:
    int nodeID;
    std::map<int, Aluno> keyValueStore;
    std::vector<int> fingerTable;
    int successor;

public:
    ChordNode(int id);
    void insertKey(Aluno aluno);
    bool retrieveKey(int ra, Aluno &aluno);
    bool deleteKey(int ra);
    void printNode() const;
    void updateFingerTable(const std::vector<int> &allNodes);
    int findSuccessor(int key);
    int getNodeID() const { return nodeID; }
};

#endif
