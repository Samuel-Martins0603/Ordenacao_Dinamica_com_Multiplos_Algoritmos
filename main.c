#include <stdio.h>
#include <stdlib.h> 

// Variaveis globais
int comparacoes = 0, trocas = 0;

// Função para imprimir vetor
void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//Funções de ordenação 

void bubbleSort(int arr[], int n) {
    comparacoes = trocas = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            comparacoes++;
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                trocas++;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    comparacoes = trocas = 0;
    for(int i = 0; i < n-1; i++) {
        int min = i;
        for(int j = i+1; j < n; j++) {
            comparacoes++;
            if(arr[j] < arr[min])
                min = j;
        }
        if(min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
            trocas++;
        }
    }
}

void insertionSort(int arr[], int n) {
    comparacoes = trocas = 0;
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0) {
            comparacoes++;
            if(arr[j] > key) {
                arr[j + 1] = arr[j];
                trocas++;
                j--;
            } else break;
        }
        arr[j + 1] = key;
    }
}

int partition(int arr[], int low, int high) {
    int pivo = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++) {
        comparacoes++;
        if(arr[j] < pivo) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            trocas++;
        }
    }
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    trocas++;
    return i+1;
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Alocação dinâmica 
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for(i = 0; i < n1; i++) L[i] = arr[l + i];
    for(j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = j = 0;
    k = l;
    while(i < n1 && j < n2) {
        comparacoes++;
        if(L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
        trocas++;
    }
    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void shellSort(int arr[], int n) {
    comparacoes = trocas = 0;
    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for(j = i; j >= gap; j -= gap) {
                comparacoes++;
                if(arr[j-gap] > temp) {
                    arr[j] = arr[j-gap];
                    trocas++;
                } else break;
            }
            arr[j] = temp;
        }
    }
}

void heapify(int arr[], int n, int i) {
    int maior = i;
    int esq = 2*i + 1;
    int dir = 2*i + 2;
    if(esq < n) {
        comparacoes++;
        if(arr[esq] > arr[maior]) maior = esq;
    }
    if(dir < n) {
        comparacoes++;
        if(arr[dir] > arr[maior]) maior = dir;
    }
    if(maior != i) {
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        trocas++;
        heapify(arr, n, maior);
    }
}

void heapSort(int arr[], int n) {
    comparacoes = trocas = 0;
    for(int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    for(int i = n-1; i > 0; i--) {
        int temp = arr[0];
	arr[0] = arr[i];
	arr[i] = temp;
        trocas++;
        heapify(arr, i, 0);
    }
}

// Main

int main() {
    int *arr = NULL;
    int n = 0;
    int escolha;
    int total;

    printf("Escolha o algoritmo:\n");
    printf("1) Bubble Sort\n");
    printf("2) Selection Sort\n");
    printf("3) Insertion Sort\n");
    printf("4) Quick Sort\n");
    printf("5) Merge Sort\n");
    printf("6) Shell Sort\n");
    printf("7) Heap Sort\n");
    scanf("%d", &escolha);

    printf("Quantos valores deseja inserir? ");
    scanf("%d", &total);

    for(int i = 0; i < total; i++) {

        int valor;
        printf("Digite o valor: ");
        scanf("%d", &valor);

        int *temp = realloc(arr, (n + 1) * sizeof(int));
        if(temp == NULL) {
            printf("Erro ao alocar memoria!\n");
            free(arr);
            return 1;
        }

        arr = temp;
        arr[n] = valor;
        n++;

        switch(escolha) {
            case 1: bubbleSort(arr, n); 
			break;
            case 2: selectionSort(arr, n); 
			break;
            case 3: insertionSort(arr, n); 
			break;
            case 4: comparacoes = trocas = 0; quickSort(arr, 0, n-1); 
			break;
            case 5: comparacoes = trocas = 0; mergeSort(arr, 0, n-1); 
			break;
            case 6: shellSort(arr, n); 
			break;
            case 7: heapSort(arr, n); 
			break;
            default:
                printf("Opcao invalida!\n");
                free(arr);
                return 1;
        }

        printf("Estrutura atual: ");
        printArray(arr, n);
        printf("Comparacoes: %d | Trocas: %d\n\n", comparacoes, trocas);
    }

    free(arr);
    return 0;
}
