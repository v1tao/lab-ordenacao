#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>

typedef struct Algoinfo{
    unsigned long long int comp;
    unsigned long long int attr;
}Algoinfo;
Algoinfo data;


void merge(int* main_arr, int low, int mid_point, int high)
{
    data.attr += 2;
    int size_of_arr1 = mid_point - low + 1;
    int size_of_arr2 = high - mid_point; 
    // 0 1 2 3 4 5 
    int* arr1 = malloc(sizeof(int) * (size_of_arr1 + 1));
    int* arr2 = malloc(sizeof(int) * (size_of_arr2 + 1));

    //copy both arrays
    for(int i = 0; i < size_of_arr1; i++){
        arr1[i] = main_arr[low + i];
        data.attr++;
    } 
    for(int i = 0; i < size_of_arr2; i++){
        arr2[i] = main_arr[mid_point + 1 + i];
        data.attr++;
    }
    // return sorted values to the main array by interlacation 
    arr1[size_of_arr1] = INT_MAX; 
    arr2[size_of_arr2] = INT_MAX; 
    data.attr += 2;
    int i = 0, j = 0;
    int k;

    for(i = j = 0, k = low; k <= high; k++){
      data.comp++;
      data.attr++;
      main_arr[k] = (arr1[i] <= arr2[j]) ? arr1[i++] : arr2[j++];
   }
    free(arr1);
    free(arr2);
}

void merge_sort(int* arr, int low, int high)
{
    data.comp++;
    if(low < high){
        // first array include mid_point 
        int mid_point = (high + low) / 2;
        data.attr++;
        merge_sort(arr, low, mid_point);
        merge_sort(arr, mid_point + 1, high);
        merge(arr, low, mid_point, high);
    }
}

int main(int argc, char** argv)
{
    int  option  = atoi(argv[1]); 
    int  sizes[] = {2000, 4000, 8000, 16000, 32000, 64000, 128000};
    char* test_type; 
     
    FILE* resultf; 
    resultf = fopen("../result/result-merge-sort.txt", "a"); 
    for(int i = 0; i < 7; i++){
        int* arr = malloc(sizeof(int) * sizes[i]); 
        data.attr = 0; 
        data.comp = 0; 
         
        FILE* fp; 
        switch(option){
            case 1:
                fp = fopen("../test/cres128.txt","r");  
                test_type = "crescente"; 
                break;
            case 2:
                fp = fopen("../test/decres128.txt","r");  
                test_type = "decrescente"; 
                break;
            case 3:
                fp = fopen("../test/random128.txt","r");  
                test_type = "random";
                break; 
            default:
                break;
        } 
        for(int k = 0; k < sizes[i]; k++){
            fscanf(fp, "%d\n", &arr[k]);
        } 
        
        clock_t t;
        t = clock();
        merge_sort(arr, 0, sizes[i] - 1);  
        t = clock() - t;   
        
        free(arr);
        arr = NULL; 
        double time_taken = ((double)t) / CLOCKS_PER_SEC;
        fprintf(resultf, "Teste %s %d\n\
            Tempo: %f\n\
            Num. de Comparacoes: %llu\n\
            Num. de atribuicoes: %llu\n", test_type, sizes[i],
                                            time_taken, data.comp, data.attr); 

        fclose(fp);
        
    } 
    fclose(resultf);    
    
    return 0;
}

