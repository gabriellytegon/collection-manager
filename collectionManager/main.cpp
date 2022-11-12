#include <string.h>
#include <map>

using namespace std;

class Elemento{
    int id;
    string nome;
    float valor;

public:
    Elemento(int, float, string);

    float pegaValor(){
        return valor;
    }

    int pegaId(){
        return id;
    }

    string pegaNome(){
        return nome;
    }

    void insereValor(float v){
        if (v >= 0){
            valor = v;
        } else{
            printErro(0);
        }
    }

    void insereId(int i){
        if (i > 0 || i < 6){
            id = i;
        } else{
            printErro(1);
        }
    }

    void insereNome(string n){
        int tamanho = strlen(n.c_str());
        if (tamanho > 0 && tamanho < 20){
            nome = n;
        } else{
            printErro(2);
        }
    }

    void printErro(int tipoErro){
        string erro;
        if (tipoErro == 0){
            erro = "O valor do elemento  e invalido.\n";
        } else if (tipoErro == 1){
            erro = "O id do elemento possui quantidade de caracetre invalido.\n";
        } else{
            erro =
                "O nome do elemento possui quantidade de caractere invalida.\n";
        }
        printf("%s", erro.c_str());
    }
};

Elemento::Elemento(int i, float v, string n){
    insereId(i);
    insereValor(v);
    insereNome(n);
}

class Colecao{
    string nome;
    map<int, Elemento> elementos;

public:
    Colecao(string);

    void insereNome(string n){
        int tamanho = strlen(n.c_str());
        if (tamanho > 0 && tamanho < 40){
            nome = n;
        } else{
            printErro(2);
        }
    }

    void insereElemento(Elemento e){
        elementos.insert(make_pair(e.pegaId(), e));
    }

    void deletaElemento(int id){
        elementos.erase(id);
    }

    Elemento pegaElemento(int id){
        return elementos.find(id)->second;
    }

    map<int, Elemento> pegaTotalElementos(){
        return elementos;
    }

    string pegaNome(){
        return nome;
    }

    float pegaValorTotal(){
        float valorTotal = 0;
        for (auto e : elementos){
            valorTotal += e.second.pegaValor();
        }
        return valorTotal;
    }

    void printErro(int tipoErro){
        string erro;
        if (tipoErro == 0){
            erro = "O valor da colecao e invalido.\n";
        } else if (tipoErro == 1){
            erro = "O id da colecao possui quantidade de caracetre invalida.\n";
        } else{
            erro =
                "O nome da colecao possui quantidade de caractere invalida.\n";
        }
        printf("%s", erro.c_str());
    }
};

Colecao::Colecao(string n){
    insereNome(n);
}

enum EstadoColecao{
    PRA_INICIAR,
    EM_PROGRESSO,
    COMPLETO
};

class ColecaoLimitada : public Colecao{

    int tamanho, faltantes;
    EstadoColecao estado;

public:
    ColecaoLimitada(
        int,
        string n);

    void insereTamanho(int t){
        if (t > 0){
            tamanho = t;
        } else{
            printErro(0);
        }
    }

    int pegaTamanho(){
        return tamanho;
    }

    int pegaFaltante(){
        int tamanhoColecao = 0;
        for (auto i : pegaTotalElementos()){
            tamanhoColecao++;
        }
        return pegaTamanho() - tamanhoColecao;
    }

    string pegaNomeDaSituacao(){
        EstadoColecao estado = pegaSituacao();
        string nome;
        switch (estado){
            case PRA_INICIAR:
                nome = "Pra Iniciar";
                break;
            case EM_PROGRESSO:
                nome = "Em Progresso";
                break;
            case COMPLETO:
                nome = "Completo";
                break;
        }
        return nome;
    }

private:
    EstadoColecao pegaSituacao(){
        EstadoColecao estado;
        if (pegaFaltante() == 0){
            estado = COMPLETO;
        } else if (pegaFaltante() == pegaTamanho()){
            estado = PRA_INICIAR;
        } else{
            estado = EM_PROGRESSO;
        }

        return estado;
    }
};

ColecaoLimitada::ColecaoLimitada(
    int t,
    string n) : Colecao(n){
    insereTamanho(t);
};

void verOpcoesColecao(){
    printf("\nDigite o numero da opcao desejada:\n");
    printf("1. Remover elemento.\n2. Consultar elemento especifico.\n");
    printf("3. Consultar todas as informacoes da colecao.\n4. Consultar o valor da colecao.\n8. Sair do menu\n");
}

void verOpcoesColecaoLimitada(){
    printf("\nDigite o numero da opcao desejada:\n");
    printf("1. Remover elemento.\n2. Consultar elemento especifico.\n");
    printf("3. Consultar todas as informacoes da colecao.\n4. Consultar o valor da colecao.\n");
    printf("5. Consultar o número de elmentos faltantes.\n6. Consultar tamanho da colecao.\n");
    printf("7. Consultar o estado da colecao.\n8. Sair do menu\n");
}

Colecao criaColecao(){
    Elemento e(1, 1.0, "Moeda 1");
    Elemento e2(2, 3.0, "Moeda 2");
    Elemento e3(3, 5.0, "Moeda 3");
    Elemento e4(4, 2.0, "Moeda 4");

    Colecao c("Colecao de Moedas");
    c.insereElemento(e);
    c.insereElemento(e2);
    c.insereElemento(e3);
    c.insereElemento(e4);

    return c;
}

ColecaoLimitada criaColecaoLimitada(){
    Elemento e(1, 1.0, "Figurinha 1");
    Elemento e2(2, 3.0, "Figurinha 2");
    Elemento e3(3, 5.0, "Figurinha 3");
    Elemento e4(4, 2.0, "Figurinha 4");

    ColecaoLimitada cl(10, "Colecao Limitada de Figurinhas");
    cl.insereElemento(e);
    cl.insereElemento(e2);
    cl.insereElemento(e3);
    cl.insereElemento(e4);

    return cl;
}

Colecao trataOperacao(int operacaoDesejada, Colecao c){
    switch (operacaoDesejada){
        case 1:{
            printf("\nDigite o id do elemento a ser removido.\n");
            int id = 0;
            scanf("%d", &id);
            c.deletaElemento(id);
            printf("Elemento removido com sucesso!\n");
            break;
        }
        case 2:{
            printf("\n\nDigite o id do elemento a ser consultado.\n");
            int id = 0;
            scanf("%d", &id);
            Elemento e = c.pegaElemento(id);
            printf("Id: %d\nNome: %s\nValor: R$%.2f\n", e.pegaId(), e.pegaNome().c_str(), e.pegaValor());
            break;
        }
        case 3:{
            printf("\nNome da colecao: %s\nValor total da colecao: R$%.2f\n", c.pegaNome().c_str(), c.pegaValorTotal());
            map<int, Elemento> elementos = c.pegaTotalElementos();
            for (auto x : elementos){
                printf("Id: %d | Nome: %s | Valor: R$%.2f\n", x.second.pegaId(), x.second.pegaNome().c_str(), x.second.pegaValor());
            }
            break;
        }
        case 4:{
            printf("\nValor total da colecao: R$%.2f\n", c.pegaValorTotal());
            break;
        }
    }
    return c;
}

ColecaoLimitada trataOperacaoColecaoLimitada(int operacaoDesejada, ColecaoLimitada cl){
    switch (operacaoDesejada)
    {
        case 1:{
            printf("\nDigite o id do elemento a ser removido.\n");
            int id = 0;
            scanf("%d", &id);
            cl.deletaElemento(id);
            printf("Elemento removido com sucesso!\n");
            break;
        }
        case 2:{
            printf("\n\nDigite o id do elemento a ser consultado.\n");
            int id = 0;
            scanf("%d", &id);
            Elemento e = cl.pegaElemento(id);
            printf("Id: %d\nNome: %s\nValor: R$%.2f\n", e.pegaId(), e.pegaNome().c_str(), e.pegaValor());
            break;
        }
        case 3:{
            printf("\nNome da colecao: %s\nValor total da colecao: R$%.2f", cl.pegaNome().c_str(), cl.pegaValorTotal());
            printf("\nEstado da colecao: %s\nNumero de elementos faltantes: %d\n", cl.pegaNomeDaSituacao().c_str(), cl.pegaFaltante());
            map<int, Elemento> elementos = cl.pegaTotalElementos();
            for (auto x : elementos){
                printf("Id: %d | Nome: %s | Valor: R$%.2f\n", x.second.pegaId(), x.second.pegaNome().c_str(), x.second.pegaValor());
            }
            break;
        }
        case 4:{
            printf("\nValor total da colecao: R$%.2f\n", cl.pegaValorTotal());
            break;
        }
        case 5:{
            printf("\nNúmero de elementos faltantes: %d", cl.pegaFaltante());
            break;
        }
        case 6:{
            printf("\nTamanho da colecao: %d", cl.pegaTamanho());
        }
        case 7:{
            printf("\nSituacao da colecao: %s", cl.pegaNomeDaSituacao().c_str());
        }
    }
    return cl;
}

void trataColecao(){
    Colecao c = criaColecao();
    int operacaoDesejada = 0;
    while (operacaoDesejada != 8){
        verOpcoesColecao();
        scanf("%d", &operacaoDesejada);
        c = trataOperacao(operacaoDesejada, c);
    }
}

void trataColecaoLimitada(){
    ColecaoLimitada cl = criaColecaoLimitada();
    int operacaoDesejada = 0;
    while (operacaoDesejada != 8){
        verOpcoesColecaoLimitada();
        scanf("%d", &operacaoDesejada);
        cl = trataOperacaoColecaoLimitada(operacaoDesejada, cl);
    };
}

int main(){
    printf("Gerenciador de Colecoes.\n\n");
    printf("Digite o numero da colecao desejada\n0 - Colecao Normal\n1 - Colecao Limitada\n");

    int colecaoDesejada = 0;
    scanf("%d", &colecaoDesejada);

    switch (colecaoDesejada){
        case 0:
            trataColecao();
            break;
        case 1:
            trataColecaoLimitada();
            break;
    }

    return 0;
}