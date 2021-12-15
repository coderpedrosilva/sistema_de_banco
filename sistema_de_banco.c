#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <locale.h>

typedef struct{
	int codigo;
	char nome[50];
	char email[50];
	char cpf[20];
	char dataNascimento[20];
	char dataCadastro[20];
} Cliente;

typedef struct {
	int numero;
	Cliente cliente;
	float saldo;
	float limite;
	float saldoTotal;
} Conta;

void menu();
void infoCliente(Cliente cliente);
void infoConta(Conta conta);
void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void listarContas();
float atualizaSaldoTotal(Conta conta);
Conta buscarContaPorNumero(int numero);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta conta_origem, Conta conta_destino, float valor);

static Conta contas[50];
static int contador_contas = 0;
static int contador_clientes = 0;

int main(){

    setlocale(LC_ALL, "Portuguese_Brazil");

	menu();

	return 0;
}


void menu(){
	int opcao = 0;
	printf("\n\n=============================\n");
	printf("============ BDV ============\n");
	printf("====== BANCO DE VALORES =====\n");
	printf("=============================\n\n");

	printf("Selecione uma opção no menu: \n\n");
	printf("1 - Criar conta\n");
	printf("2 - Efetuar depósito\n");
	printf("3 - Efetuar saque\n");
	printf("4 - Efetuar transferência\n");
	printf("5 - Listar contas\n");
	printf("6 - Sair do sistema\n\n");

	scanf("%d", &opcao);
	getchar();

	switch(opcao){
	case 1:
	    system("@cls||clear");
		criarConta();
		break;
    case 2:
	    system("@cls||clear");
		efetuarDeposito();
		break;
	case 3:
	    system("@cls||clear");
		efetuarSaque();
		break;
	case 4:
	    system("@cls||clear");
		efetuarTransferencia();
		break;
	case 5:
	    system("@cls||clear");
		listarContas();
		break;
	case 6:
	    system("@cls||clear");
		printf("\n\nAtendimento encerrado\n");
		Sleep(2000);
		exit(0);
	default:
	    system("@cls||clear");
		printf("\n\nOpção inválida!\n");
		Sleep(2000);
		system("@cls||clear");
		menu();
		break;
	}
}

void infoCliente(Cliente cliente){
	printf("Código: %d \nNome: %s \nData de nascimento: %s \nCadastro: %s \n",
			cliente.codigo, strtok(cliente.nome, "\n"), strtok(cliente.dataNascimento, "\n"),
			strtok(cliente.dataCadastro, "\n"));
}

void infoConta(Conta conta){
	printf("Número da conta: %d \nCliente: %s \nData de Nascimento: %s \nData de Cadastro: %s \nSaldo Total: %.2f\n",
			conta.numero, strtok(conta.cliente.nome, "\n"), strtok(conta.cliente.dataNascimento, "\n"),
			strtok(conta.cliente.dataCadastro, "\n"), conta.saldoTotal);
}

void criarConta(){
	Cliente cliente;

	//Data de cadastro
	char dia[3];
	char mes[3];
	char ano[5];
	char data_cadastro[20];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	//dia
	if(tm.tm_mday < 10){
		sprintf(dia, "0%d", tm.tm_mday);
	}else{
		sprintf(dia, "%d", tm.tm_mday);
	}

	//mês
	if((tm.tm_mon + 1) < 10){
		sprintf(mes, "0%d", tm.tm_mon + 1);
	}else{
		sprintf(mes, "%d", tm.tm_mon + 1);
	}

	//ano
	sprintf(ano, "%d", tm.tm_year + 1900);

	strcpy(data_cadastro, "");
	strcat(data_cadastro, dia);
	strcat(data_cadastro, "/");
	strcat(data_cadastro, mes);
	strcat(data_cadastro, "/");
	strcat(data_cadastro, ano);
	strcat(data_cadastro, "\0");
	strcpy(cliente.dataCadastro, data_cadastro);

	//Criar cliente
	printf("\n\n=============================\n");
	printf("====== CADASTRAR CONTA ======\n");
	printf("=============================\n\n");
	cliente.codigo = contador_clientes + 1;

	printf("Nome do cliente: \n");
	fflush(stdout);
	fgets(cliente.nome, 50, stdin);

	printf("\nE-mail do cliente: \n");
	fflush(stdout);
	fgets(cliente.email, 50, stdin);

	printf("\nCPF do cliente: \n");
	fflush(stdout);
	fgets(cliente.cpf, 20, stdin);

	printf("\nData de nascimento do cliente (dd/mm/aaaa): \n");
	fflush(stdout);
	fgets(cliente.dataNascimento, 20, stdin);

	contador_clientes++;

	contas[contador_contas].numero = contador_contas + 1;
	contas[contador_contas].cliente = cliente;
	contas[contador_contas].saldo = 0.0;
	contas[contador_contas].limite = 0.0;
	contas[contador_contas].saldoTotal = atualizaSaldoTotal(contas[contador_contas]);

	system("@cls||clear");

	printf("\n\n=============================\n");
	printf("= CONTA CRIADA COM SUCESSO! =\n");
	printf("=============================\n\n");
	printf("=== Dados da conta criada ===\n\n");
	infoConta(contas[contador_contas]);
	contador_contas++;
	printf("\n=============================\n\n");

	system("pause");
	system("@cls||clear");
	menu();
}

float atualizaSaldoTotal(Conta conta){
	return conta.saldo + conta.limite;
}

Conta buscarContaPorNumero(int numero){
	Conta c;
	if(contador_contas > 0){
		for(int i = 0; i < contador_contas; i++){
			if(contas[i].numero == numero){
				c = contas[i];
			}
		}
	}
	return c;
}

void sacar(Conta conta, float valor){
	if(valor > 0 && conta.saldoTotal >= valor){
		for(int i = 0; i < contador_contas; i++){
			if(contas[i].numero == conta.numero){
				if(contas[i].saldo == valor){
					contas[i].saldo = contas[i].saldo - valor;
					contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
					system("@cls||clear");
					printf("\n\n=============================\n");
                    printf("======= TELA DE SAQUE =======\n");
                    printf("=============================\n");
					printf("\nSaque efetivado com sucesso!\n");
				}else{
					float restante = contas[i].saldo = valor;
					contas[i].limite = contas[i].limite + restante;
					contas[i].saldo = 0.0;
					contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
					system("@cls||clear");
					printf("\n\n=============================\n");
                    printf("======= TELA DE SAQUE =======\n");
                    printf("=============================\n");
					printf("\nSaque efetuado com sucesso!\n");
				}
			}
		}
	}else{
	    system("@cls||clear");
	    printf("\n\n=============================\n");
        printf("======= TELA DE SAQUE =======\n");
        printf("=============================\n");
		printf("\nSaque não realizado. Tente novamente.\n");
	}
}

void depositar(Conta conta, float valor){
	if(valor > 0){
		for(int i = 0; i < contador_contas; i++){
			if(contas[i].numero == conta.numero){
				contas[i].saldo = contas[i].saldo + valor;
				contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
				system("@cls||clear");
                printf("\n\n=============================\n");
                printf("====== TELA DE DEPÓSITO =====\n");
                printf("=============================\n");
				printf("\nDepósito efetuado com sucesso!\n");
			}
		}
	}else{
	    system("@cls||clear");
        printf("\n\n=============================\n");
        printf("====== TELA DE DEPÓSITO =====\n");
        printf("=============================\n");
		printf("\nErro ao efetuar depósito. Tente novamente.\n ");
	}
}

void transferir(Conta conta_origem, Conta conta_destino, float valor){
	if(valor > 0 && conta_origem.saldoTotal >= valor){
		for(int co = 0; co < contador_contas; co++){
			if(contas[co].numero == conta_origem.numero){
				for(int cd = 0; cd < contador_contas; cd++){
					if(contas[cd].numero == conta_destino.numero){
						if(contas[co].saldo >= valor){
							contas[co].saldo = contas[co].saldo - valor;
							contas[cd].saldo = contas[cd].saldo + valor;
							contas[co].saldoTotal = atualizaSaldoTotal(contas[co]);
							contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]);
							system("@cls||clear");
                            printf("\n\n=============================\n");
                            printf("=== TELA DE TRANSFERÊNCIA ===\n");
                            printf("=============================\n");
							printf("\nTransferência realizada com sucesso!\n");
						}else{
							float restante = contas[co].saldo - valor;
							contas[co].limite = contas[co].limite + restante;
							contas[co].saldo = 0.0;
							contas[cd].saldo = contas[cd].saldo + valor;
							contas[co].saldoTotal = atualizaSaldoTotal(contas[co]);
							contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]);
							system("@cls||clear");
                            printf("\n\n=============================\n");
                            printf("=== TELA DE TRANSFERÊNCIA ===\n");
                            printf("=============================\n");
							printf("\nTransferência realizada com sucesso!\n");
						}
					}
				}
			}
		}
	}else{
	    system("@cls||clear");
        printf("\n\n=============================\n");
        printf("=== TELA DE TRANSFERÊNCIA ===\n");
        printf("=============================\n");
		printf("\nTransferência não realizada. Tente novamente.\n");
	}
}


void efetuarSaque(){
    	printf("\n\n=============================\n");
        printf("======= TELA DE SAQUE =======\n");
        printf("=============================\n");
	if(contador_contas > 0){
		int numero;
        printf("\nInforme o número da conta: \n");
		scanf("%d", &numero);

		Conta conta = buscarContaPorNumero(numero);

		if(conta.numero == numero){
			float valor;
			printf("\nInforme o valor do saque: \n");
			scanf("%f", &valor);

			sacar(conta, valor);
		}else{
        system("@cls||clear");
        printf("\n\n=============================\n");
        printf("======= TELA DE SAQUE =======\n");
        printf("=============================\n");
			printf("\nNão foi encontrada uma conta com o número %d\n", numero);
		}

	}else{
	    system("@cls||clear");
	    printf("\n\n=============================\n");
        printf("======= TELA DE SAQUE =======\n");
        printf("=============================\n");
		printf("\nAinda não existem contas para saque.\n");
	}
	Sleep(2000);
	system("@cls||clear");
	menu();
}

void efetuarDeposito(){
	if(contador_contas > 0){
			int numero;
            printf("\n\n=============================\n");
            printf("===== TELA DE DEPÓSITO ======\n");
            printf("=============================\n");
			printf("\nInforme o número da conta: \n");
			fflush(stdout);
			scanf("%d", &numero);

			Conta conta = buscarContaPorNumero(numero);

			if(conta.numero == numero){
				float valor;
				printf("\nInforme o valor do depósito: \n");
				fflush(stdout);
				scanf("%f", &valor);

				depositar(conta, valor);
			}else{
			    system("@cls||clear");
                printf("\n\n=============================\n");
                printf("===== TELA DE DEPÓSITO ======\n");
                printf("=============================\n");
				printf("\nNão foi encontrada uma conta com o número %d\n", numero);
			}

		}else{
		    system("@cls||clear");
            printf("\n\n=============================\n");
            printf("===== TELA DE DEPÓSITO ======\n");
            printf("=============================\n");
			printf("\nAinda não existem contas para depósito.\n");
		}
		Sleep(2000);
		system("@cls||clear");
		menu();
}

void efetuarTransferencia(){
	if(contador_contas > 0){
		int numero_o, numero_d;
		system("@cls||clear");
        printf("\n\n=============================\n");
        printf("=== TELA DE TRANSFERÊNCIA ===\n");
        printf("=============================\n");
		printf("\nInforme o número da sua conta:\n");
		fflush(stdout);
		scanf("%d", &numero_o);

		Conta conta_o = buscarContaPorNumero(numero_o);

		if(conta_o.numero == numero_o){
			printf("\nInforme o número da conta destino: \n");
			fflush(stdout);
			scanf("%d", &numero_d);

		Conta conta_d = buscarContaPorNumero(numero_d);

		if(conta_d.numero == numero_d){
			float valor;
			printf("\nInforme o valor da transferência: \n");
			fflush(stdout);
			scanf("%f", &valor);

			transferir(conta_o, conta_d, valor);
			}else{
			    system("@cls||clear");
                printf("\n\n=============================\n");
                printf("=== TELA DE TRANSFERÊNCIA ===\n");
                printf("=============================\n");
				printf("\nA conta destino com número %d não foi encontrada.\n", numero_d);
			}
		}else{
		    system("@cls||clear");
            printf("\n\n=============================\n");
            printf("=== TELA DE TRANSFERÊNCIA ===\n");
            printf("=============================\n");
			printf("\nA conta com número %d não foi encontrada.\n", numero_o);
		}
	}else{
	    system("@cls||clear");
        printf("\n\n=============================\n");
        printf("=== TELA DE TRANSFERÊNCIA ===\n");
        printf("=============================\n");
		printf("\nAinda não existem contas para transferência.\n");
	}
	Sleep(2000);
	system("@cls||clear");
	menu();
}

void listarContas(){
	if(contador_contas > 0){
        printf("\n\n=============================\n");
        printf("====== LISTA DE CONTAS ======\n");
        printf("=============================\n\n");
		for(int i = 0; i < contador_contas; i++){
			infoConta(contas[i]);
			printf("\n");
			Sleep(1000);
		}
	}else{
        printf("\n\n=============================\n");
        printf("====== LISTA DE CONTAS ======\n");
        printf("=============================\n");
		printf("\nNão existem contas cadastradas ainda.\n\n");
	}
	system("pause");
	system("@cls||clear");
	menu();
}













