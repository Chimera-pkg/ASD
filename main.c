#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define max 100000

//Fungsi input jumlah data
void input_data();

//Fungsi menu
void menu();
void sorting();
void ascdsc();

//Fungsi alokasi dan salin
void alokasi();
void salin();

//Fungsi Pengurutan
void insertionSort();
void selectionSort();
void bubbleSort();
void shellSort();
void MergeSortRekursif(int l, int r);
void Merge(int left, int median, int right);
void QuickSort(int p, int r);
int Partition(int p, int r);

//Fungsi tukar
void tukar(int index1, int index2);


int data_asli[max], data[max], n, pilih, urut;

int main(){
    printf("=====Program Sorting=====\n\n");
    input_data();
    alokasi();

    do{
        salin();
        menu();
        if(pilih > 0 && pilih < 7){
            ascdsc();
            while((urut != 1) && (urut != 2)){
                puts("Mode yang anda pilih tidak tersedia");
                ascdsc();
            }
        }
        sorting();
    }while(pilih != 7);
}

void input_data(){
    printf("Jumlah data (minimal 10000)\t\t : ");
    scanf("%d", &n);
    fflush(stdin);
}

void alokasi(){
    srand(time(0));
    for(int i = 0; i < n; i++)
        data_asli[i] = rand()/1000;
}

void salin(){
    for(int i = 0; i < n; i++)
        data[i] = data_asli[i];
}

void menu(){
    puts("");
    puts("====MENU METODE SORTING====");
    puts("1. Insertion Sort");
    puts("2. Selection Sort");
    puts("3. Bubble Sort");
    puts("4. Shell Sort");
    puts("5. Merge Sort");
    puts("6. Quick Sort");
    puts("7. Keluar");
    printf("Pilih Menu\t\t : ");
    scanf("%d", &pilih);
    fflush(stdin);
}

void sorting(){
    long int waktu;
    time_t start, end;

    switch(pilih){
        case 1:
            time(&start);
            insertion();
            time(&end);
            waktu = difftime(end, start);
            break;
        case 2:
            time(&start);
            selection();
            time(&end);
            waktu = difftime(end, start);
            break;
        case 3:
            time(&start);
            bubble();
            time(&end);
            waktu = difftime(end, start);
            break;
        case 4:
            time(&start);
            shell();
            time(&end);
            waktu = difftime(end, start);
            break;
        case 5:
            time(&start);
            MergeSortRekursif(0, n-1);
            time(&end);
            waktu = difftime(end, start);
            break;
        case 6:
            time(&start);
            QuickSort(0, n-1);
            time(&end);
            waktu = difftime(end, start);
            break;
        case 7:
            exit(0);
            break;
        default:
            puts("Menu yang anda pilih tidak tersedia\n");
            return;
    }
    printf("\nWaktu Komputasi\t\t : %d\n\n", waktu);
}

void ascdsc(){
    puts("\n=====MENU MODE SORTING======");
    puts("1. Ascending");
    puts("2. Descending");
    printf("Pilih Mode\t\t : ");
    scanf("%d", &urut);
    fflush(stdin);
}

void insertion(){
    int i, j, key, kondisi;

    for(i = 1; i < n; i++){
        key = data[i];
        for(j = i-1 ; j >= 0; j--){
            if(urut == 1)
                kondisi = data[j] > key;
            else if(urut == 2)
                kondisi = data[j] < key;

            if(kondisi)
                data[j+1] = data[j];
        }
        data[j+1] = key;
    }
}

void selection(){
    int i, j, min, kondisi = 0;

    for(i=0; i < n-1; i++){
        min = i;
        for(j = i+1; j<n; j++){
            if(urut == 1)
                kondisi = data[j] < data[min];
            else if(urut == 2)
                kondisi = data[j] > data[min];

            if(kondisi)
                min = j;
        }
        tukar(i, min);
    }
}

void bubble(){
    int i, j, kondisi, did_swap = 1;

    for(i=0; i < n; i++){
        if(did_swap == 1){
            did_swap = 0;
            for(j=0; j < n-i-1; j++){
                if(urut == 1)
                    kondisi = data[j] > data[j+1];
                else if(urut == 2)
                    kondisi = data[j] < data[j+1];

                if(kondisi){
                    tukar(j, j+1);
                    did_swap = 1;
                }
            }
        }
    }
}

void shell(){
    int i, j, jarak, kondisi, did_swap = 1;

    for(jarak = n; jarak > 1; ){
        jarak /= 2;
        did_swap = 1;
        while(did_swap == 1){
            did_swap = 0;
            i = 0;
            for(i = 0; i < (n - jarak); i++){
                if(urut == 1)
                    kondisi = data[i] > data[i+jarak];
                else if(urut == 2)
                    kondisi = data[i] < data[i+jarak];

                if(kondisi){
                    tukar(i, i+jarak);
                    did_swap = 1;
                }
            }
        }
    }
}

void MergeSortRekursif(int l, int r){
    int med;

    if(l < r){
        med = (l + r) / 2;
        MergeSortRekursif(l, med);
        MergeSortRekursif(med+1, r);
        Merge(l, med, r);
    }
}

void Merge(int left, int median, int right){
    int kiri1 = left, kanan1 = median, kiri2 = median+1, kanan2 = right;
    int i, j, hasil[n], kondisi;

    for(i = left; kiri1 <= kanan1 && kiri2 <= kanan2; i++){
        if(urut == 1)
            kondisi = data[kiri1] <= data[kiri2];
        else
            kondisi = data[kiri1] >= data[kiri2];

        if(kondisi){
            hasil[i] = data[kiri1];
            kiri1++;
        }
        else{
            hasil[i] = data[kiri2];
            kiri2++;
        }
    }

    for( ; kiri1 <= kanan1; i++){
        hasil[i] = data[kiri1];
        kiri1++;
    }

    for( ; kiri2 <= kanan2; i++){
        hasil[i] = data[kiri2];
        kiri2++;
    }

    j=left;
    for( ; j <= right; j++)
        data[j] = hasil[j];
}

void QuickSort(int p, int r){
    int q;
    if(p < r){
        q = Partition(p, r);
        QuickSort(p, q);
        QuickSort(q+1, r);
    }
}

int Partition(int p, int r){
    int x = data[p], i = p, j = r, k1, k2;

    while(i<j) {
        if(urut == 1){
            while(data[j] > x)
                j--;
            while(data[i] < x)
                i++;
        }
        else if(urut == 2){
            while(data[j] < x)
                j--;
            while(data[i] > x)
                i++;
        }
    if(i < j){
        tukar(i, j);
        j--;
    }
    else
        return j;
    }
}

void tukar(int index1, int index2){
    int tampung;

    tampung = data[index1];
    data[index1] = data[index2];
    data[index2] = tampung;
}
