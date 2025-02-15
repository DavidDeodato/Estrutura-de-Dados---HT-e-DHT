#include <iostream>
#include <vector>
#include "chord.h"
#include "aluno.h"

using namespace std;

// Função para criar a rede com os IDs dos nós especificados
vector<ChordNode> criarRede(const vector<int>& ids) {
    vector<ChordNode> rede;
    for (size_t i = 0; i < ids.size(); i++) {
        rede.push_back(ChordNode(ids[i]));
    }
    // Atualiza a finger table de cada nó
    for (size_t i = 0; i < rede.size(); i++) {
        rede[i].updateFingerTable(ids);
    }
    return rede;
}

// Teste A: Inserção de um aluno
// Adiciona "Pedro" (RA 450) no nó de ID 500 (primeiro nó com ID >= 450)
void testInsertion() {
    cout << "Teste A: Insercao de 'Pedro' (RA 450) no no 500\n";
    vector<int> nosIds = {100, 500, 2000, 4000, 7000};
    vector<ChordNode> rede = criarRede(nosIds);

    Aluno alunoPedro(450, "Pedro");

    // Procura o nó cujo ID seja 500 e insere o aluno
    for (size_t i = 0; i < rede.size(); i++) {
        if (rede[i].getNodeID() == 500) {
            rede[i].insertKey(alunoPedro);
            break;
        }
    }
    // Exibe o conteúdo de cada nó
    for (size_t i = 0; i < rede.size(); i++) {
        rede[i].printNode();
    }
    cout << "\n";
}

// Teste B: Busca de um aluno
// Insere "Maria" (RA 3500) no nó 4000 e tenta localizá-la
void testSearch() {
    cout << "Teste B: Busca de 'Maria' (RA 3500) no no 4000\n";
    vector<int> nosIds = {100, 500, 2000, 4000, 7000};
    vector<ChordNode> rede = criarRede(nosIds);

    Aluno alunoMaria(3500, "Maria");

    // Insere no nó com ID 4000
    for (size_t i = 0; i < rede.size(); i++) {
        if (rede[i].getNodeID() == 4000) {
            rede[i].insertKey(alunoMaria);
            break;
        }
    }
    // Tenta recuperar o aluno do nó 4000
    Aluno resultado;
    bool sucesso = false;
    for (size_t i = 0; i < rede.size(); i++) {
        if (rede[i].getNodeID() == 4000 && rede[i].retrieveKey(3500, resultado)) {
            sucesso = true;
            break;
        }
    }
    if (sucesso)
        cout << "Sucesso: Encontrou 'Maria' -> " << resultado.getNome() << "\n";
    else
        cout << "Erro: 'Maria' nao foi encontrada no no 4000.\n";
    cout << "\n";
}

// Teste C: Remoção de um aluno
// Insere "Lucas" (RA 6200) no nó 7000 e, em seguida, o remove
void testRemoval() {
    cout << "Teste C: Remocao de 'Lucas' (RA 6200) no no 7000\n";
    vector<int> nosIds = {100, 500, 2000, 4000, 7000};
    vector<ChordNode> rede = criarRede(nosIds);

    Aluno alunoLucas(6200, "Lucas");

    // Insere no nó 7000
    for (size_t i = 0; i < rede.size(); i++) {
        if (rede[i].getNodeID() == 7000) {
            rede[i].insertKey(alunoLucas);
            break;
        }
    }
    // Remove o aluno do nó 7000
    bool removido = false;
    for (size_t i = 0; i < rede.size(); i++) {
        if (rede[i].getNodeID() == 7000 && rede[i].deleteKey(6200)) {
            removido = true;
            break;
        }
    }
    if (removido)
        cout << "'Lucas' removido com sucesso.\n";
    else
        cout << "Erro: Nao foi possivel remover 'Lucas'.\n";

    // Verifica se a remoção foi efetiva
    Aluno temp;
    bool encontrado = false;
    for (size_t i = 0; i < rede.size(); i++) {
        if (rede[i].getNodeID() == 7000 && rede[i].retrieveKey(6200, temp)) {
            encontrado = true;
            break;
        }
    }
    if (!encontrado)
        cout << "Confirmado: 'Lucas' nao esta na rede.\n";
    else
        cout << "Erro: 'Lucas' ainda persiste na rede.\n";
    cout << "\n";
}

// Teste D: Insercoes multiplas
// Insere vários alunos em seus nós de destino e mostra o estado final
void testBulkInsertion() {
    cout << "Teste D: Insercao multipla de alunos\n";
    vector<int> nosIds = {100, 500, 2000, 4000, 7000};
    vector<ChordNode> rede = criarRede(nosIds);

    // Criando alunos
    Aluno alunoPedro(450, "Pedro");
    Aluno alunoJoao(400, "Joao");
    Aluno alunoMaria(3500, "Maria");
    Aluno alunoLucas(6200, "Lucas");

    // Inserindo de acordo com a regra (primeiro nó com ID >= RA)
    for (size_t i = 0; i < rede.size(); i++) {
        int id = rede[i].getNodeID();
        if (id == 500) {
            rede[i].insertKey(alunoPedro);
            rede[i].insertKey(alunoJoao);
        }
        if (id == 4000)
            rede[i].insertKey(alunoMaria);
        if (id == 7000)
            rede[i].insertKey(alunoLucas);
    }
    // Exibe os nós com os alunos inseridos
    for (size_t i = 0; i < rede.size(); i++) {
        rede[i].printNode();
    }
    cout << "\n";
}

// Teste E: Busca por aluno inexistente
// Insere "Pedro" (RA 450) e tenta buscar um aluno com RA 9999 (que nao existe)
void testSearchMissing() {
    cout << "Teste E: Busca de aluno inexistente (RA 9999)\n";
    vector<int> nosIds = {100, 500, 2000, 4000, 7000};
    vector<ChordNode> rede = criarRede(nosIds);

    Aluno alunoPedro(450, "Pedro");
    // Insere no nó 500
    for (size_t i = 0; i < rede.size(); i++) {
        if (rede[i].getNodeID() == 500) {
            rede[i].insertKey(alunoPedro);
            break;
        }
    }
    // Tenta recuperar RA 9999
    Aluno vazio;
    bool existe = false;
    for (size_t i = 0; i < rede.size(); i++) {
        if (rede[i].retrieveKey(9999, vazio)) {
            existe = true;
            break;
        }
    }
    if (!existe)
        cout << "Correto: Nenhum aluno com RA 9999 encontrado.\n";
    else
        cout << "Erro: Encontrou aluno com RA 9999.\n";
    cout << "\n";
}

int main() {
    cout << "Executando testes da DHT:\n\n";
    testInsertion();
    testSearch();
    testRemoval();
    testBulkInsertion();
    testSearchMissing();
    cout << "Finalizado: Todos os testes foram realizados.\n";
    return 0;
}