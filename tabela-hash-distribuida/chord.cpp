#include "chord.h"

ChordNode::ChordNode(int id)
{
    nodeID = id;
    successor = id; // Inicialmente, o sucessor é ele mesmo
}

void ChordNode::insertKey(Aluno aluno)
{
    keyValueStore[aluno.getRa()] = aluno;
    std::cout << "Aluno " << aluno.getNome() << " armazenado no noh " << nodeID << std::endl;
}

bool ChordNode::retrieveKey(int ra, Aluno &aluno)
{
    if (keyValueStore.find(ra) != keyValueStore.end())
    {
        aluno = keyValueStore[ra];
        return true;
    }
    return false;
}

bool ChordNode::deleteKey(int ra)
{
    if (keyValueStore.find(ra) != keyValueStore.end())
    {
        keyValueStore.erase(ra);
        std::cout << "Aluno com RA " << ra << " removido do noh " << nodeID << std::endl;
        return true;
    }
    return false;
}

void ChordNode::printNode() const
{
    std::cout << "No " << nodeID << " armazenando: ";
    for (const auto &pair : keyValueStore)
    {
        std::cout << "[" << pair.first << " -> " << pair.second.getNome() << "] ";
    }
    std::cout << std::endl;
}

void ChordNode::updateFingerTable(const std::vector<int> &allNodes)
{
    fingerTable.clear();
    for (int i = 0; i < std::log2(allNodes.size()); i++)
    {
        int index = (nodeID + (1 << i)) % 10000;
        for (int node : allNodes)
        {
            if (node >= index)
            {
                fingerTable.push_back(node);
                break;
            }
        }
    }
}

int ChordNode::findSuccessor(int key)
{
    for (int node : fingerTable)
    {
        if (node >= key)
        {
            return node;
        }
    }
    return successor;
}
