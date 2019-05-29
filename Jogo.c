#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define numberOfGames 5000

int main ()
{
    int lastGame[60], frequency[60], frequencyTop[60][2],frequencyTemp[2]; 
    int game[numberOfGames][6], played[numberOfGames][6], i, j, k, aux;
    char isExists;
    for (i=0; i<60; i++){
		frequency[i] = 0;
	}
        
    
    srand (time(NULL));
    
    //Sorteia os numeros
    for (i=0; i<numberOfGames; i++){ 
        for (j=0; j<6; j++){
            do{
                game[i][j] = rand() % 60 + 1; 
                isExists = 'N';
                for (k=0; k<j; k++) 
                    if (game[i][j] == game[i][k])
                        isExists = 'S';
            }while (isExists == 'S'); 
            played[i][j] = game[i][j]; 
            frequency[game[i][j]-1]++;                  
        }
    }
	
	//Ordena os jogos
    for(i=0;i<numberOfGames;i++){   
        for(j=0;j<6;j++){
            for(k=j; k<6; k++){
                if(played[i][k]<played[i][j]){
                    aux = played[i][j];
                    played[i][j] = played[i][k];
                    played[i][k] = aux;
                }
            }
        }
	}
	
	
    printf("Jogos sorteados\n");
    for(i=0;i<numberOfGames;i++){ 
        printf("Jogo %d:    ", i+1);
        for(j=0;j<6;j++)
            printf("%d ", game[i][j]);
        printf("(");
        for(j=0;j<6;j++)
            printf("%d ", played[i][j]);
        printf(")\n");
    }
    
    ////////////////////////////////////////////////////////////////
	//						Trata a frequencia
	////////////////////////////////////////////////////////////////
    
    //Exibe e copia a frequencia
    printf("\n\n\nQuantedade de vezes que os numeros foram sortiados!\n");
	for(i=0;i<60;i++){
		printf("%d: %d\n", i+1, frequency[i]);
		frequencyTop[i][0] = i;
		frequencyTop[i][1] = frequency[i];
	}
	
	//Ordena a frequencia
	for(i=0;i<60;i++){   
        for(j=i;j<60;j++){   
            if(frequencyTop[i][1]<frequencyTop[j][1]){
                frequencyTemp[0] =  frequencyTop[i][0];
                frequencyTemp[1] =  frequencyTop[i][1];
				frequencyTop[i][0] = frequencyTop[j][0];
				frequencyTop[i][1] = frequencyTop[j][1];
                frequencyTop[j][0] = frequencyTemp[0];
                frequencyTop[j][1] = frequencyTemp[1];
            }
        }
	}
	
	j = 0;
	//Exibe as quinze duplas
	printf("\n\n\nAs 15 duplas que mais sairam!\n\n\n");
	for(i=0; i<30;i++){
		printf("%d = %d: %d e %d: %d\n", j+1, frequencyTop[i][0], frequencyTop[i][1], frequencyTop[i+1][0], frequencyTop[i+1][1]);
		i++;
		j++;
	}
	
	printf("\n\n\nOs 15 numeos que mais sairam!\n\n\n");
	for(i=0; i<15;i++){
		printf("%d = %d: %d\n", i+1, frequencyTop[i][0], frequencyTop[i][1]);
		i++;
	}
	
	//Define o ultimo jogo de cada numero
	isExists = 'N';
	for(i=1;i<=60;i++){   
        for(j=numberOfGames-1;j>=0;j--){
            for(k=0; k<6; k++){
                if(i == played[j][k]){
                    lastGame[i-1] = numberOfGames - j;
                    isExists = 'S';
                    break;
                }
            }
            if(isExists == 'S') break;
        }
    	isExists = 'N';
	}
	
	printf("\n\n\nQuantidade de jogadas desde a última vez que o número foi sorteado.!\n\n\n");
	for(i=0; i<60;i++){
		if(lastGame[i] == 0){
			printf("N %2d = saiu no ultimo sorteio.\n", i+1);
		}else{
			printf("N %2d =  nao sai a %d sorteios seguidos...\n", i+1, lastGame[i]);
		}
	}
	
	//////////////////////////////////////////////////////////////////////////////////////
	//					Sorteia o jogo para 3 usuarios
	//////////////////////////////////////////////////////////////////////////////////////
	
	char CPF[11];
	char Name[100];
	int playedValue[6];
	   
	for(i = 0; i < 3; i++){
			
		printf("\n\n\nDigite o Nome do jogador Numero %d\n", i+1);
		scanf("%s", &Name);
		
		printf("Digite o CPF do jogador Numero %d\n", i+1);
		scanf("%s", &CPF);
		
		printf("Digite o Jogo do jogador Numero %d\n", i+1);
		scanf("%d", &playedValue);
		
		int drawNumber = rand() % numberOfGames + 1;
		int hits = 0;
		
		for(j = 0; j < 6; j++){
			for(k = 0; k < 6; k++){
		        if(played[drawNumber][j] == playedValue[k]){
					hits++;
	  	  	    }	
			}
		}
		
		printf("Parabéns %s, você acertou %d números! Sorteio [ %d ]\n", Name, hits, drawNumber);
		
	}
		
    return 0;
}