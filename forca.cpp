#include <iostream>
#include <stdlib.h>
#include <cstring> //Para usar o memset. Estou usando isso para limpar um vetor estático

using namespace std;


char word[30], secretWord[30], lettersBank[30], letter; //O vetor "secretWord" serve para o usuário ter um feedback visual. Ele será o símbolo "_"
int wordSize=0, chances=6, hits=0, letterBankIndex = -1;
bool hitLetter = false;

// Define a palavra secreta da rodada
void SetWord()
{
    int i = 0;
    cin >> word;// O moderador do jogo define a palavra e logo após o programa é limpo para que o jogador não veja a palavra

    while (word[i] != '\0')// O '\0' representa o 'Enter' do teclado
    {
        i++;
        wordSize++;
    }

    system("cls");
}

// Mostra o feedback visual para que o jogador saiba quantas letras tem na palavra, quantas faltam e quais já acertou
void SetVisualFeedback()
{
    for (int i = 0; i < wordSize; i++)
    {
        secretWord[i] = '-';
    }
    
}

// Verifica se a letra digitada está na lista de letras que já foram digitadas
bool IsLetterInBank(char currentLetterInLoop) 
{
    bool check = false;

    if(currentLetterInLoop != letter)
    {
        for(int i=0; i < wordSize; i++)
        {
            if(letter == lettersBank[i])
            {
                check = true;
            }
        }
    }
    return check;
}

// Verifica na palavra do jogo se ela contém a letra digitada
void CheckHasLetterInWord() 
{
    letterBankIndex++;
    char tempLetter = ' ';

    for(int i = 0; i < wordSize; i++)
    {
        if(word[i] == letter && !IsLetterInBank(tempLetter))
        {
            hitLetter = true;
            secretWord[i] = word[i];
            hits++;
            lettersBank[letterBankIndex] = letter;
            tempLetter = letter;
        }
    }

    if(!hitLetter && !IsLetterInBank(tempLetter))
    {
        chances--;
        lettersBank[letterBankIndex] = letter;
    }

    hitLetter = false;
    system("cls");
}

void GameRoutine()
{
    while ((chances > 0) && (hits < wordSize))
    {
        cout << "Letras digitadas: \n";
        for (int i = 0; i < 30; i++)
        {
            cout << lettersBank[i];
        }
        
        cout << "\n\nChances restantes: " << chances << endl << endl;
        cout << "Palavra secreta: ";

        // Desenhar o feedback visual de quantas letras faltam para completar a palavra
        for (int i = 0; i < wordSize; i++)
        {
            cout << secretWord[i];
        }

        cout << "\n\nDigite uma letra: ";
        cin >> letter;

        CheckHasLetterInWord();
    }
}

// Reinicia as variáveis globais do jogo
void ResetGame()
{
    wordSize = 0;
    chances = 6;
    hits = 0;
    letterBankIndex = -1;
    hitLetter = false;

    //Esta função pode limpar o vetor
    memset(word, ' ', sizeof(word));
    memset(secretWord, '\0', sizeof(secretWord));
    memset(lettersBank, '\0', sizeof(lettersBank));
}

// Inicia o jogo
void StartGame()
{
    ResetGame();
    system("cls");
    cout << "Escreva a palavra desta rodada\n";

    SetWord();
    SetVisualFeedback();
    GameRoutine();
}

// Executa após o fim do jogo, mesmo que o jogador perca ou ganhe
void PostGame()
{
    if(hits == wordSize)
    {
        cout << "You Win!!!\n\n";
    }else
    {
        cout << "You Lose...  \nT-T \n:(\n\n";
    }

    cout << "A palavra secreta era: ";

    // Impressão da palavra secreta para o player não ficar na curiosidade
    for(int i=0; i<wordSize; i++)
    {
        cout << word[i];
    }
    cout << "\n\n";
}

int main()
{
    int playAgainNumber=0;
    StartGame();
    PostGame();

    cout << "Gostaria de jogar novamente?\nYes (1)\nNo (0)\n\n";
    cin >> playAgainNumber;
    if(playAgainNumber == 1){main();}
    
    return 0;
}