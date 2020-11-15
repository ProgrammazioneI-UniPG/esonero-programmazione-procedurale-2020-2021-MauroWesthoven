#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define MAXLENGTH 130 //128 + "\n" + "\0"

//Prototipi di funzione
void showMenu();
void insertString();
void insertEncryptKey();
void generateEncryptKey();
void printPlaintextManualKey();
void printPlaintextAutoKey();

//Inizializzazione delle variabili globali
int menu_choice;
char plaintextM[MAXLENGTH];
char manualKeyK[MAXLENGTH];
char autoKeyK[MAXLENGTH];
time_t t;

int plaintextMLenght;
int manualKeyKLenght;
int autoKeyKLenght;

char manualEncryptedText[MAXLENGTH];
char manualDecryptedText[MAXLENGTH];
char autoEncryptedText[MAXLENGTH];
char autoDecryptedText[MAXLENGTH];
char EncryptionXOROperation;
char DecryptionXOROperation;

int main() {
  srand((unsigned)time(&t));
  showMenu();
  return 0;
}

void showMenu() {
  do {
    printf("\n\n- 1: Inserisci la stringa da cifrare\n- 2: Inserisci manualmente la chiave di cifratura\n- 3: Genera automaticamente la chiave di cifratura\n- 4: Stampa stringa cifrata e chiave inserita manualmente (se presenti)\n- 5: Stampa stringa cifrata e chiave casuale (se presenti)\n- 6: Esci\n\n\nLa tua scelta: ");
    scanf("%d", &menu_choice);
    switch (menu_choice) {
      case 1:
        insertString();
        break;
      case 2:
        insertEncryptKey();
        break;
      case 3:
        generateEncryptKey();
        break;
      case 4:
        printPlaintextManualKey();
        break;
      case 5:
        printPlaintextAutoKey();
        break;
      case 6:
        puts("Grazie e Arrivederci!!!\n\n");
        break;
      default:
        printf("\033[0;31m");
        puts("\nPer favore, scegli un valore compreso tra 1 e 6.");
        printf("\033[0m");
        showMenu();
        break;
      }
  } while (menu_choice < 1 & menu_choice > 6);
}

void insertString() {
  puts("Inserisci la stringa che vuoi cifrare (max. 128 posizioni).");
  while (getchar() != '\n');
  fgets(plaintextM, MAXLENGTH, stdin);
  
  plaintextMLenght = strlen(plaintextM) - 1;
  //printf("\n%d\n", plaintextMLenght);
  /*****Test per stampare a video la stringa inserita*****/
  /*printf("%s\n", plaintextM);
  
  for (size_t i = 0; i < MAXLENGTH; i++) {
    printf("%c", plaintextM[i]);
  }*/
  showMenu();
}

void insertEncryptKey() {
  //Controllo se e' presente la stringa da cifrare, se no: rimando al menu principale, se si: prendo in input la chiave
  if (plaintextMLenght < 1) {
    do {
      printf("Prima di inserire una chiave, inserire la stringa da cifrare. (Opzione 1 dal menu principale).");
    } while (0);
  } else {
  puts("Inserisci la chiave con cui vuoi cifrare la stringa (max. 128 posizioni).");
  char n = strlen(manualKeyK);
  if (n > 0 && manualKeyK[n - 1] == '\n') { manualKeyK[n - 1] = 0; }
  while (getchar() != '\n');
  fgets(manualKeyK, MAXLENGTH, stdin);

  manualKeyKLenght = strlen(manualKeyK);
  
  if (manualKeyKLenght <= plaintextMLenght) {
    do {
      printf("\nLa lunghezza della chiave e' minore rispetto alla lunghezza della stringa.\nInserirne una nuova.\n");
      char n = strlen(manualKeyK);
      if (n > 0 && manualKeyK[n - 1] == '\n') { manualKeyK[n - 1] = 0; }
      fgets(manualKeyK, MAXLENGTH, stdin);
      
      manualKeyKLenght = strlen(manualKeyK);
    } while (manualKeyKLenght <= plaintextMLenght);
    //printf("OK!!!!\n");
  }
  printf("\nLa stringa inserita soddisfa i requisiti quindi e' stata salvata corettamente.\n\n");
  //printf("Plaintext: %s\nChiave: %s\n", plaintextM, manualKeyK);
  
  //CIFRATURA
  for (size_t i = 0; i < manualKeyKLenght - 1; i++) {
    manualEncryptedText[i] = plaintextM[i] ^ manualKeyK[i];
  }
  
  printf("\033[0;36m");
  printf("La stringa cifrata e': ");
    
  for (size_t i = 0; i < manualKeyKLenght; i++) {
    printf("%d", manualEncryptedText[i]);
  }
  puts("\n");
    
  //DECIFRATURA
  for (size_t i = 0; i < manualKeyKLenght; i++) {
    DecryptionXOROperation = manualEncryptedText[i] ^ manualKeyK[i];
    manualDecryptedText[i] = DecryptionXOROperation;
  }
  
  printf("La stringa decifrata e': %s\n", manualDecryptedText);
  printf("\033[0m");
  }
  showMenu();
}

void generateEncryptKey() {
  //Controllo se e' presente la stringa da cifrare, se no: rimando al menu principale, se si: eseguo la cifratura e decifratura con l'operatore XOR
  if (plaintextMLenght < 1) {
    do {
      printf("Prima di generare una chiave automaticamente, inserire la stringa da cifrare. (Opzione 1 dal menu principale).");
    } while (0);
  } else {
    printf("Sto generando la tua chiave. Aspetta qualche secondo...\n\n");
    sleep(2);
    
    //GENERAZIONE CHIAVE AUTOMATICA
    printf("\033[0;36m");
    printf("La chiave generata e': ");
    for (size_t i = 0; i < plaintextMLenght; i++) {
      autoKeyK[i] = (33 + rand() % 129);
      if (autoKeyK[i] < 32 || autoKeyK[i] >= 127) {
        i--;
      } else {
        printf("%c", (autoKeyK[i]));
        //printf(" %c: %d", (autoKeyK[i]), autoKeyK[i]);
      }
    }
    puts("\n\n");
    autoKeyKLenght = strlen(autoKeyK);
    //printf("\n%d", autoKeyKLenght);

    //CIFRATURA
    for (size_t i = 0; i < autoKeyKLenght; i++) {
      EncryptionXOROperation = plaintextM[i] ^ autoKeyK[i];
      autoEncryptedText[i] = EncryptionXOROperation;
    }
    //Stampo a video la stringa cifrata
    printf("La stringa cifrata e': %s\n", autoEncryptedText);
    puts("\n");
    
    //DECIFRATURA
    for (size_t i = 0; i < autoKeyKLenght; i++) {
      DecryptionXOROperation = autoEncryptedText[i] ^ autoKeyK[i];
      autoDecryptedText[i] = DecryptionXOROperation;
    }
    //Stampo a video la stringa decifrata
    printf("La stringa decifrata e': %s\n", autoDecryptedText);
    printf("\033[0m");
  }
  showMenu();
}

void printPlaintextManualKey() {
  //Controllo se la stringa da cifrare e la chiave esistono, se no: rimando al menu per farli inserire, se si: stampo a video i risultati di ogni stringa
  if (plaintextMLenght == 0) {
    do {
      puts("Impossibile stampare la stringa cifrata e la chiave inserita perche' non sono presenti.");
      puts("Segui le istruzioni del menu principale.");
    } while (plaintextMLenght != 0);
  }
  else if (manualKeyKLenght == 0) {
    do {
      puts("La chiave manuale non e' presente, scegli l'opzione 2 dal menu principale.");
    } while (manualKeyKLenght != 0);
  }
  else {
    puts("\n");
    printf("\033[0;36m");
    //Stampo la stringa originale, stringa cifrata e stringa decifrata
    printf("La stringa originale e': %s\n", plaintextM);
    printf("La stringa cifrata e': ");
    for (size_t i = 0; i < manualKeyKLenght; i++) {
      printf("%d", manualEncryptedText[i]);
    }
    puts("\n");
    printf("La chiave usata per cifrare e': %s\n", manualKeyK);
    printf("La stringa decifrata e': %s\n", manualDecryptedText);
    printf("\033[0m");
    printf("");
  }
  showMenu();
}

void printPlaintextAutoKey() {
  //Controllo se la stringa da cifrare e la chiave esistono, se no: rimando al menu per farli inserire, se si: stampo a video i risultati di ogni stringa
  if (plaintextMLenght == 0) {
    do {
      puts("Impossibile stampare la stringa cifrata e la chiave generata perche' non sono presenti.");
      puts("Segui le istruzioni del menu principale.");
    } while (plaintextMLenght != 0);
  }
  else if (autoKeyKLenght == 0) {
    do {
      puts("La chiave casuale non e' presente, scegli l'opzione 3 dal menu principale.");
    } while (autoKeyKLenght != 0);
  }
  else {
    puts("\n");
    printf("\033[0;36m");
    //Stampo la stringa originale, stringa cifrata e stringa decifrata
    printf("La stringa originale e': %s\n", plaintextM);
    printf("La stringa cifrata e': %s\n\n", autoEncryptedText);
    printf("La chiave usata per cifrare e': %s\n", autoKeyK);
    printf("La stringa decifrata e': %s\n", autoDecryptedText);
    printf("\033[0m");
  }
  showMenu();
}