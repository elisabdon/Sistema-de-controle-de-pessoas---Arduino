#include <stdio.h>
#include <stdint.h>
#include <windows.h>

#define u8 uint8_t

void limparTela() {
    system("cls");
}

void carregando() {
    limparTela();
    char carregando[] = "\t\t\t\t\t\t\t\t\tCARREGANDO...\n\n";
    for (u8 c = 0; carregando[c] != '\0'; c++) {
        printf("%c", carregando[c]);
        fflush(stdout);
        Sleep(30);
    }
}

int main() {
    u8 escolha = 0;
    u8 lampadas[3] = {0};
    u8 numero_Pessoas = 0;
    u8 pessoasNaCasa[255];
    u8 estadoLampadas[3] = {0};

    printf("\n");
    printf("\t\t\t\t\t\t\t  == SEJA BEM VINDO AO CONTROLE DA CASA! == \n");
    printf("\t\t\t\t\t\t\t  == APERTE |0| E |ENTER| PARA CONTINUAR == \n\n");
    printf("\t\t\t\t\t\t\t\t\t   --> ");
    scanf("%d", &escolha);
    limparTela();

    do {
        printf("\n\t\t\t\t\t\t\t    )|===================================|\n");
        printf("\t\t\t\t\t\t\t    )|              MENU                 |\n");
        printf("\t\t\t\t\t\t\t    )|===================================|\n");
        printf("\t\t\t\t\t\t\t    )| 1.  ADICIONAR PESSOA              |\n");
        printf("\t\t\t\t\t\t\t    )| 2.  LIGAR LAMPADA    |1|          |\n");
        printf("\t\t\t\t\t\t\t    )| 3.  DESLIGAR LAMPADA |1|          |\n");
        printf("\t\t\t\t\t\t\t    )| 4.  LIGAR LAMPADA    |2|          |\n");
        printf("\t\t\t\t\t\t\t    )| 5.  DESLIGAR LAMPADA |2|          |\n");
        printf("\t\t\t\t\t\t\t    )| 6.  LIGAR LAMPADA    |3|          |\n");
        printf("\t\t\t\t\t\t\t    )| 7.  DESLIGAR LAMPADA |3|          |\n");
        printf("\t\t\t\t\t\t\t    )| 8.  RETIRAR PESSOA                |\n");
        printf("\t\t\t\t\t\t\t    )| 9.  VERIFICAR NUMERO DE PESSOAS   |\n");
        printf("\t\t\t\t\t\t\t    )| 10. VERIFICAR ESTADO DAS LAMPADAS |\n");
        printf("\t\t\t\t\t\t\t    )| 11. ENCERRAR PROGRAMA             |\n");
        printf("\t\t\t\t\t\t\t    )|              ***                  |\n");
        printf("\t\t\t\t\t\t\t    )|===================================|\n");
        printf("\t\t\t\t\t\t\t    DIGITE A OPCAO--> ");
        scanf("%d", &escolha);

        limparTela();

        switch (escolha) {
            case 1:
                if (numero_Pessoas < 255) {
                    system("color 02");
                    carregando();
                    printf("\t\t\t\t\t\t\t     UMA PESSOA FOI ADICIONADA NA CASA!\n");
                    pessoasNaCasa[numero_Pessoas] = numero_Pessoas + 1;
                    if (numero_Pessoas == 0) {
                        for (u8 i = 0; i < 3; i++) {
                            lampadas[i] = estadoLampadas[i];
                        }
                    }
                    numero_Pessoas++;
                    break;
                } else {
                    system("color 07");
                    carregando();
                    printf("\t\t\t\t\t\t\t     NAO E POSSIVEL ADICIONAR MAIS PESSOAS\n");
                    break;
                }

            case 2:
                if (numero_Pessoas > 0) {
                    system("color 02");
                    carregando();
                    printf("\t\t\t\t\t\t\t     LAMPADA |1| FOI LIGADA COM SUCESSO! \n");
                    lampadas[0] = 1;
                    break;
                } else {
                    system("color 04");
                    carregando();
                    printf("\t\t\t\t\t\t   NAO FOI POSSIVEL LIGAR A LAMPADA POIS NAO EXISTEM PESSOAS \n");
                    printf("\t\t\t\t\t\t\t    INSIRA UMA PESSOA NA CASA PARA LIGAR AS LUZES \n");
                    lampadas[0] = 0;
                    break;
                }

            case 3:
                if (numero_Pessoas > 0) {
                    system("color A");
                    carregando();
                    printf("\t\t\t\t\t\t\t     LAMPADA |1| DESLIGADA COM SUCESSO!\n");
                    lampadas[0] = 0;
                    break;
                } else {
                    system("color 04");
                    carregando();
                    printf("\t\t\t\t\t\t    NAO FOI POSSIVEL INTERAGIR COM A LAMPADA POIS NAO EXISTEM PESSOAS \n");
                    printf("\t\t\t\t\t\t\t    INSIRA UMA PESSOA NA CASA PARA INTERAGIR COM AS LUZES \n");
                    break;
                }

            case 4:
                if (numero_Pessoas > 0) {
                    system("color 02");
                    carregando();
                    printf("\t\t\t\t\t\t\t       LAMPADA |2| LIGADA COM SUCESSO!\n");
                    lampadas[1] = 1;
                    break;
                } else {
                    system("color 04");
                    carregando();
                    printf("\t\t\t\t\t\t    NAO FOI POSSIVEL LIGAR A LAMPADA POIS NAO EXISTEM PESSOAS \n");
                    printf("\t\t\t\t\t\t    INSIRA UMA PESSOA NA CASA PARA LIGAR AS LUZES \n");
                    lampadas[0] = 0;
                    break;
                }

            case 5:
                if (numero_Pessoas > 0) {
                    system("color A");
                    carregando();
                    printf("\t\t\t\t\t\t\t   LAMPADA |2| DESLIGADA COM SUCESSO! \n");
                    lampadas[1] = 0;
                    break;
                } else {
                    system("color 04");
                    carregando();
                    printf("\t\t\t\t\t\tNAO FOI POSSIVEL INTERAGIR COM A LAMPADA POIS NAO EXISTEM PESSOAS \n");
                    printf("\t\t\t\t\t\t\tINSIRA UMA PESSOA NA CASA PARA INTERAGIR COM AS LUZES \n");
                    break;
                }

            case 6:
                if (numero_Pessoas > 0) {
                    system("color 02");
                    carregando();
                    printf("\t\t\t\t\t\t\t\t LAMPADA |3| LIGADA COM SUCESSO!\n");
                    lampadas[2] = 1;
                    break;
                } else {
                    system("color 04");
                    carregando();
                    printf("\t\t\t\t\t\t NAO FOI POSSIVEL LIGAR A LAMPADA POIS NAO EXISTEM PESSOAS \n");
                    printf("\t\t\t\t\t\t\t INSIRA UMA PESSOA NA CASA PARA LIGAR AS LUZES \n");
                    lampadas[0] = 0;
                    break;
                }

            case 7:
                if (numero_Pessoas > 0) {
                    system("color A");
                    carregando();
                    printf("\t\t\t\t\t\t\t\t LAMPADA |3| DESLIGADA COM SUCESSO!\n");
                    lampadas[2] = 0;
                    break;
                } else {
                    system("color 04");
                    carregando();
                    printf("\t\t\t\t\t\t NAO FOI POSSIVEL INTERAGIR COM A LAMPADA POIS NAO EXISTEM PESSOAS\n");
                    printf("\t\t\t\t\t\t\t INSIRA UMA PESSOA NA CASA PARA INTERAGIR COM AS LUZES \n");
                    break;
                }

            case 8:
                system("color 07");
                if (numero_Pessoas > 0) {
                    system("color 02");
                    carregando();
                    printf("\t\t\t\t\t\t\t UMA PESSOA FOI RETIRADA DA CASA!\n");
                    if (numero_Pessoas == 1) {
                        for (u8 i = 0; i < 3; i++) {
                            estadoLampadas[i] = lampadas[i];
                        }
                    }
                    numero_Pessoas--;

                    if (numero_Pessoas == 0) {
                        for (u8 i = 0; i < 3; i++) {
                            lampadas[i] = 0;
                        }
                    }
                } else {
                  	carregando();
                    printf("\t\t\t\t\t\t NAO EXISTEM PESSOAS PARA SEREM RETIRADAS! INSIRA NOVAS PESSOAS!\n");
                }
                break;

            case 9:
                system("color 07");
                carregando();
                printf("\t\t\t\t\t\t\t     ==== QUANTIDADE DE PESSOAS ====\n");
                printf("\t\t\t\t\t\t\t          PESSOAS NA CASA: %d \n", numero_Pessoas);
                break;

            case 10:
                system("color 07");
                carregando();
                printf("\t\t\t\t\t\t\t ESTADO DAS LAMPADAS: \n");

                for (u8 i = 0; i < 3; i++) {
                    printf("\n\t\t\t\t\t\t\t\t|LAMPADA %d| = %s (%d)\n\n", i + 1, (lampadas[i] == 1) ? "LIGADA" : "DESLIGADA", lampadas[i]);
                }
                break;

            case 11: { 
                limparTela();
                char encerramento[] = "\n\n \t\t\t\t\t\t\t\t\tENCERRANDO....";
                for (u8 e = 0; encerramento[e] != '\0'; e++) {
                    system("color 04");
                    printf("%c", encerramento[e]);
                    fflush(stdout);
                    Sleep(100);
                }
                return 0;
            }

            default:
                printf("\t\t\t\t\t\t\t\t INVALIDO! TENTE NOVAMENTE OUTRA OPCAO\n");
                break;
        }
    } while (escolha != 11);

    return 0;
}
