#include "chord.h"
#include <vector>
#include <iostream>

void inserirAlunos(std::vector<ChordNode> &chordNodes, const std::vector<int> &allNodes, const std::vector<Aluno> &alunos)
{
    for (const Aluno &aluno : alunos)
    {
        int ra = aluno.getRa();
        int targetNodeID = -1;

        for (int nodeID : allNodes)
        {
            if (nodeID >= ra)
            {
                targetNodeID = nodeID;
                break;
            }
        }
        if (targetNodeID == -1)
        {
            targetNodeID = allNodes.front();
        }

        for (auto &node : chordNodes)
        {
            if (node.getNodeID() == targetNodeID)
            {
                node.insertKey(aluno);
                std::cout << "Aluno " << aluno.getNome() << " (RA: " << aluno.getRa() << ") inserido no noh " << targetNodeID << std::endl;
                break;
            }
        }
    }
}

void buscarAluno(std::vector<ChordNode> &chordNodes, const std::vector<int> &allNodes)
{
    std::cout << "\nDigite o RA do aluno que deseja buscar: ";
    int searchRA;
    std::cin >> searchRA;

    int nextNode = -1;
    for (int nodeID : allNodes)
    {
        if (nodeID >= searchRA)
        {
            nextNode = nodeID;
            break;
        }
    }
    if (nextNode == -1)
    {
        nextNode = allNodes.front();
    }

    for (auto &node : chordNodes)
    {
        if (node.getNodeID() == nextNode)
        {
            Aluno aluno;
            if (node.retrieveKey(searchRA, aluno))
            {
                std::cout << "Aluno encontrado: " << aluno.getNome() << " no nó " << nextNode << std::endl;
                return;
            }
        }
    }
    std::cout << "Aluno não encontrado!\n";
}

void removerAluno(std::vector<ChordNode> &chordNodes, const std::vector<int> &allNodes)
{
    std::cout << "\nDigite o RA do aluno que deseja remover: ";
    int removeRA;
    std::cin >> removeRA;

    int removeNodeID = -1;
    for (int nodeID : allNodes)
    {
        if (nodeID >= removeRA)
        {
            removeNodeID = nodeID;
            break;
        }
    }
    if (removeNodeID == -1)
    {
        removeNodeID = allNodes.front();
    }

    for (auto &node : chordNodes)
    {
        if (node.getNodeID() == removeNodeID)
        {
            node.deleteKey(removeRA);
            std::cout << "Aluno removido com sucesso.\n";
            return;
        }
    }
    std::cout << "Aluno não encontrado para remoção.\n";
}

void imprimirEstadoNos(const std::vector<ChordNode> &chordNodes)
{
    for (const auto &node : chordNodes)
    {
        node.printNode();
    }
}

int main()
{
    std::vector<int> allNodes = {100, 500, 2000, 4000, 7000};
    std::vector<ChordNode> chordNodes;
    for (int id : allNodes)
    {
        chordNodes.emplace_back(id);
    }
    for (auto &node : chordNodes)
    {
        node.updateFingerTable(allNodes);
    }

    std::vector<Aluno> alunos = {
        Aluno(450, "Pedro"),
        Aluno(3500, "Maria"),
        Aluno(6200, "Lucas"),
        Aluno(400, "Joao")};

    inserirAlunos(chordNodes, allNodes, alunos);
    buscarAluno(chordNodes, allNodes);
    removerAluno(chordNodes, allNodes);
    imprimirEstadoNos(chordNodes);

    return 0;
}
