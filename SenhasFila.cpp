#include <iostream>
#include <locale.h>
#include <string>

/*Desenvolvido por Beatriz Bastos Borges e Miguel Luizatto Alves.*/

using namespace std;

struct No
{
    int dado;
    No *prox;
};

struct Fila
{
    No *ini;
    No *fim;
};

Fila* init()
{
    Fila *f = new Fila;
    f->ini = NULL;
    f->fim = NULL;

    return f;
}

int isEmpty(Fila *f)
{
    return (f->ini == NULL);
}

void enqueue(Fila* f, int v)
{
    No *no = new No;
    no->dado = v;
    no->prox = NULL;
    if (isEmpty(f))
    {
        f->ini = no;
    }
    else
    {
        f->fim->prox = no;
    }

    f->fim = no;
}

float dequeue(Fila* f)
{
    float ret;
    if (isEmpty(f))
    {
        ret = -1;
    }
    else
    {
        No *no = f->ini;
        ret = no->dado;
        f->ini = no->prox;

        if (f->ini == NULL)
        {
            f->fim = NULL;
        }
        free(no);
    }
    return ret;
}

int count(Fila* f)
{
    int qtde = 0;
    No *no;
    no = f->ini;
    while (no != NULL)
    {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void print(Fila* f)
{
    No *no;
    no = f->ini;
    cout << "-- Qtde de elementos: " << count(f) << endl;

    while (no != NULL)
    {
        cout << no->dado << endl;
        no = no->prox;
    }
}

void freeFila(Fila* f) 
{
    No* no = f->ini;
    
    while (no != NULL) {
        No* temp = no->prox;
        free(no);
        no = temp;
    }
    free(f);
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");

    Fila* senhasGeradas;
    Fila* senhasAtendidas;

    senhasGeradas = init();
    senhasAtendidas = init();

    int opcao;

    int senha = 0;

    do
    {

        if (senha > 0)
            cout << "Há um total de " << count(senhasGeradas) << " senhas para serem atendidas\n" << endl;

        cout << "Escolha uma opcao: \n0. Sair\n1. Gerar senha\n2. Realizar atendimento\n" << endl;
        cin >> opcao;
        cout << "\n";

        if (opcao == 0 && !isEmpty(senhasGeradas))
        {
            cout << "Ainda há senhas para serem atendidas. Aguarde o fim dos atendimentos" << endl;
            opcao = -1;
        }

        switch (opcao)
        {        
            case 0:
                break;

            case 1:
                senha++;
                enqueue(senhasGeradas, senha);

                cout << "Sua senha: " << senha << "\n" << endl;

                break;

            case 2:
                int senhaAtendida;
                senhaAtendida = dequeue(senhasGeradas);

                if (senhaAtendida <= 0)
                    cout << "Não há senhas para atender. Gere uma nova ou finalize o programa.\n" << endl;
                else
                {
                    enqueue(senhasAtendidas, senhaAtendida);
                    cout << "Senha atendida: " << senhaAtendida << "\n" << endl;
                }
                break;

            default:
                cout << "Opcao inválida. Tente novamente." << endl;
                break;
        }

    } while (opcao != 0);

    freeFila(senhasGeradas);
    freeFila(senhasAtendidas);

    return 0;
}