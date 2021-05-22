#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct item{
    long int debet, kredet;
    int ref;
    char tanggal[20], keterangan[40];
    struct item *next;
    struct item *prev;
}NODE;

//////////////// Fungsi General

void header(){
    printf("\n\n");
    printf("\t---------------------------------------- PROGRAM AKUNTANSI PERUSAHAAN ----------------------------------------\n\n"
           "\t./$$$$../$$$$$$./$$$$$../$$./$$./$$$$$$../$$$$......../$$...../$$$$$$../$$$$../$$$$$$../$$$$../$$$$$../$$$$$$.\n"
           "\t/$$.././.$$.../|.$$..$$|.$$/.$$.\\..$$.../$$../.......|.$$....|.$$...../$$.././_..$$/../$$..$$|.$$..$$.\\..$$/..\n"
           "\t. /$$$$|.$$$$$.|.$$$$$.|.$$..$$..|.$$...\\.$$$$.......|.$$....|.$$$$..../$$$$...|.$$..|.$$$$$$|.$$$$$...|.$$...\n"
           "\t..../$$|.$$./..|.$$./$$|..$$$$...|.$$....|...$$......|.$$....|.$$......../$$...| $$..|.$$./$$|.$$./$$..|.$$...\n"
           "\t./$$$$/|.$$$$$$|.$$_.$$.\\..$$.../$$$$$$./.$$$$/......|.$$$$$$|.$$$$$$../$$$$/..|.$$..|.$$/.$$|.$$/.$$..$$$$$$.\n"
         "\t.\\___/.|/_____/|/_/./_/..\\./...|______/.|..../.......|______/|______/..\\___/...|__/..|__/.__/|__/./_/./_____/.\n");
}

char *sBulan(int intBulan){
    char *nama_bulan[12] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus",
                            "Septemer", "Oktober", "November", "Desember"};
    return nama_bulan[intBulan];
}

void getDirName(char dir_loc[]){
    time_t current_time;
    char year[6];

    time(&current_time);

    struct tm *my_time = localtime(&current_time);

    strcpy(dir_loc, sBulan(my_time -> tm_mon));

    sprintf(year, " %d", my_time -> tm_year + 1900);
    strcat(dir_loc, year);
}

int menu(){
    int pilih;
    printf("\n\n\t++=======================++\n"
           "\t:: Daftar Menu Utama :   ::\n"
           "\t:: 1. Neraca Awal        ::\n"
           "\t:: 2. Jurnal Umum        ::\n"
           "\t:: 3. Buku Besar         ::\n"
           "\t:: 4. Neraca Saldo       ::\n"
           "\t:: 5. Keluar             ::\n"
           "\t++=======================++\n");
    printf("\t:: Ketik pilihan :");
    scanf("%d", &pilih);
    return pilih;
}

int getNamaAkun(){
    int ref_akun;
    printf("\t++=======================================++\n"
           "\t:: REF     NAMA AKUN                     ::\n"
           "\t++=======================================++\n"
           "\t:: 111     Kas                           ::\n"
           "\t:: 112     Piutang Usaha                 ::\n"
           "\t:: 113     Perlengkapan Usaha            ::\n"
           "\t:: 114     Asuransi Dibayar Dimuka       ::\n"
           "\t:: 115     Sewa Dibayar Dimuka           ::\n"
           "\t:: 121     Peralatan Kantor              ::\n"
           "\t:: 122     Peralatan Service             ::\n"
           "\t:: 123     Kendaraan                     ::\n"
           "\t:: 211     Utang Usaha                   ::\n"
           "\t:: 212     Utang Bank                    ::\n"
           "\t:: 311     Modal Haddy                   ::\n"
           "\t:: 312     Prive Haddy                   ::\n"
           "\t:: 411     Pendapatan Jasa Service       ::\n"
           "\t:: 511     Beban Gaji                    ::\n"
           "\t:: 512     Beban Listrik Air dan Telepon ::\n"
           "\t:: 513     Beban Asuransi                ::\n"
           "\t:: 514     Beban Sewa                    ::\n"
           "\t:: 515     Beban Lain-Lain               ::\n"
           "\t++=======================================++\n");
    printf("\t:: Ketik nomor ref akun :");
    scanf("%d", &ref_akun);
    return ref_akun;
}

char *keterangan(int ref){
    char *array_keterangan[18] = {"Kas", "Piutang Usaha", "Perlengkapan Usaha", "Asuransi Dibayar Dimuka",
                                  "Sewa Dibayar Dimuka", "Peralatan Kantor", "Peralatan Service", "Kendaraan",
                                  "Utang Usaha", "Utang Bank", "Modal Haddy", "Prive Haddy", "Pendapatan Jasa Service", "Beban Gaji", "Beban Listrik Air dan Telepon", "Beban Asuransi",
                                  "Beban Sewa", "Beban Lain-Lain"};
    switch(ref){
        case 111: return array_keterangan[0]; break;
        case 112: return array_keterangan[1]; break;
        case 113: return array_keterangan[2]; break;
        case 114: return array_keterangan[3]; break;
        case 115: return array_keterangan[4]; break;
        case 121: return array_keterangan[5]; break;
        case 122: return array_keterangan[6]; break;
        case 123: return array_keterangan[7]; break;
        case 211: return array_keterangan[8]; break;
        case 212: return array_keterangan[9]; break;
        case 311: return array_keterangan[10];break;
        case 312: return array_keterangan[11];break;
        case 411: return array_keterangan[12];break;
        case 511: return array_keterangan[13];break;
        case 512: return array_keterangan[14];break;
        case 513: return array_keterangan[15];break;
        case 514: return array_keterangan[16];break;
        case 515: return array_keterangan[17];break;
        default: return "Error : ref tidak ditemukan"; break;
    } 
}

NODE *inputItem(){
    int pilih_akun;

    pilih_akun = getNamaAkun();
    NODE *new_data = malloc(sizeof(struct item));
    new_data -> ref = pilih_akun;
    new_data -> prev = new_data -> next = NULL;
    printf("\t:: Ketik tanggal (dd/mm/yyyy) :");
    scanf("%s", &new_data -> tanggal);
    printf("\t:: Ketik nominal debet :");
    scanf("%ld", &new_data -> debet);
    printf("\t:: Ketik nominal kredet :");
    scanf("%ld", &new_data -> kredet);
    strcpy(new_data -> keterangan, keterangan(pilih_akun));
    return new_data;
}

void addAtEnd(NODE **head, NODE *new_data){
    if(*head == NULL){
        *head = new_data;
    }else{
        NODE *temp = *head;
        while(temp -> next != NULL)
            temp = temp -> next;
        temp -> next = new_data;
        new_data -> prev = temp;
    }
}

void linkedListToFile(NODE *head, FILE *fptr){
    NODE *temp = head;
    while(temp != NULL){
        fprintf(fptr, "%s,%d,%s,%ld,%ld\n", temp -> tanggal, temp -> ref, temp -> keterangan, temp -> debet, temp -> kredet);
        temp = temp -> next;
    }
}

NODE *searchLinkedList(NODE *temp, int ref, char tanggal[]){
    while(temp != NULL){
        int banding = strcmp(temp -> tanggal, tanggal);
        if(temp -> ref == ref && banding == 0){
            break;
        }
        temp = temp -> next;
    }
    return temp;
}

NODE *deleteLinkedList(NODE *head, int ref, char tanggal[]){
    if(head == NULL)
        return head;
    
    int banding = strcmp(head -> tanggal, tanggal);

    if(head -> ref == ref && banding == 0){
        head = head -> next;
        free(head);
    }else{
        NODE *temp = head -> next;
        while(temp != NULL){
            banding = strcmp(temp -> tanggal, tanggal);
            if(temp -> ref == ref && strcmp(temp -> tanggal, tanggal) == 0){

                temp -> prev -> next = temp -> next;

                if(temp -> next != NULL)
                    temp -> next -> prev = temp -> prev;

                free(temp);
                break;
            }
            temp = temp -> next;
        }
    }
    return head;
}

NODE findTotalDebetKredet(char file_dir_name[]){
    FILE *fptr = fopen(file_dir_name, "a+");

    NODE akun, total;

    total.debet = total.kredet = 0;

    //skip baris pertama file csv
    char buffer[100];
    fgets(buffer, sizeof(buffer), fptr);

    while((fscanf(fptr,"%[^,], %d, %[^,], %ld, %ld", &akun.tanggal, &akun.ref, &akun.keterangan, &akun.debet, &akun.kredet)) != 1){
        total.debet += akun.debet;
        total.kredet += akun.kredet;
    }
    fclose(fptr);
    return total;
}

void lihatFile(char file_dir_name[], int mode){
    //mode 0 = neraca dan jurnal umum, 1 = buku besar, 2 = neraca saldo
    NODE read;
    long int total_debet, total_kredet;

    total_debet = total_kredet = 0;
        
    FILE *fptr = fopen(file_dir_name, "r");

    if(fptr == NULL){
        printf("\t:: File tidak ditemukan atau belum di buat\n");
        return;
    }

    char buffer[100];
    fgets(buffer, sizeof(buffer), fptr);
    
    if(mode == 0 || mode == 1){
        printf("\t++=================++=====++==========================================++===============++===============++\n"
               "\t::    TANGGAL      :: REF ::                 KETERANGAN               ::     DEBET     ::     KREDET    ::\n"
               "\t++=================++=====++==========================================++===============++===============++\n");
    }else if(mode == 2){
        printf("\t++=====++==========================================++===============++===============++\n"
               "\t:: REF ::                 KETERANGAN               ::     DEBET     ::     KREDET    ::\n"
               "\t++=====++==========================================++===============++===============++\n");
    }
    
    while((fscanf(fptr,"%[^,], %d, %[^,], %ld, %ld", &read.tanggal, &read.ref, &read.keterangan, &read.debet, &read.kredet)) != 1){
        strcpy(read.tanggal, strtok(read.tanggal, "\n"));

        if(mode == 0 || mode == 1)
            printf("\t:: %-15s :: %-3d :: %-40s :: Rp.%-10ld :: Rp.%-10ld ::\n", read.tanggal, read.ref, read.keterangan, read.debet, read.kredet);
        else if(mode == 2)
            printf("\t:: %-3d :: %-40s :: Rp.%-10ld :: Rp.%-10ld ::\n", read.ref, read.keterangan, read.debet, read.kredet);
         
        if(mode == 0 || mode == 2){
            total_debet += read.debet;
            total_kredet += read.kredet;
        }else if(mode == 1){
            total_debet += read.debet;
            total_debet -= read.kredet;
        }
    }

    if(mode == 0 || mode == 1)
        printf("\t++=================++=====++==========================================++===============++===============++\n");
    else if(mode == 2)
        printf("\t++=====++==========================================++===============++===============++\n");

    //pengkondisian bagaimana total saldo akan ditampilkan
        
    if(mode == 1){
        if(total_debet < 0){
            total_kredet = -1 * total_debet;
            total_debet = 0;
        }
    }

    if(mode == 0){
        printf("\t::                         TOTAL                                      :: Rp.%-10ld :: Rp.%-10ld ::\n"
                "\t++====================================================================++===============++===============++\n", total_debet, total_kredet);
    }else if(mode == 1){
        printf("\t::                         TOTAL SALDO                                :: Rp.%-10ld :: Rp.%-10ld ::\n"
                "\t++====================================================================++===============++===============++\n", total_debet, total_kredet);
    }else if(mode == 2){
        printf("\t::                     TOTAL                       :: Rp.%-10ld :: Rp.%-10ld ++\n"
                "\t++=================================================++===============++===============++\n", total_debet, total_kredet);
    }
}

NODE *fileToLinkedList(NODE *head, FILE *fptr){
    NODE read;
    char buffer[100];
    fgets(buffer, sizeof(buffer), fptr);

    while((fscanf(fptr,"%[^,], %d, %[^,], %ld, %ld", &read.tanggal, &read.ref, &read.keterangan, &read.debet, &read.kredet)) != 1){
        strcpy(read.tanggal, strtok(read.tanggal, "\n"));
        NODE *new_data = malloc(sizeof(struct item));
        new_data -> next = new_data -> prev = NULL;

        strcpy(new_data -> tanggal, read.tanggal);
        new_data -> ref = read.ref;
        strcpy(new_data -> keterangan, read.keterangan);
        new_data -> debet = read.debet;
        new_data -> kredet = read.kredet;

        addAtEnd(&head, new_data);
    }
    return head;
}

void traverseTree(NODE *root, NODE *new_data){
    //Mencari leaf tempat data akan ditambahkan
    if(new_data -> ref < root -> ref){
        if(root -> prev == NULL) //Mengecek apakah leaf/tidak
            root -> prev = new_data;
        else
            traverseTree(root -> prev, new_data);
    }else{
        if(root -> next == NULL) //Mengecek apakah leaf/tidak
            root -> next = new_data;
        else
            traverseTree(root -> next, new_data);
    }
}

void insertTree(NODE **root, NODE *new_data){
    if(*root == NULL)
        *root = new_data;
    else
        traverseTree(*root, new_data); 
}

NODE *fileToTree(NODE *root, FILE *fptr){
    NODE read;
    char buffer[100];
    fgets(buffer, sizeof(buffer), fptr);

    while((fscanf(fptr,"%[^,], %d, %[^,], %ld, %ld", &read.tanggal, &read.ref, &read.keterangan, &read.debet, &read.kredet)) != 1){
        strcpy(read.tanggal, strtok(read.tanggal, "\n"));
        NODE *new_data = malloc(sizeof(struct item));
        new_data -> next = new_data -> prev = NULL;

        strcpy(new_data -> tanggal, read.tanggal);
        new_data -> ref = read.ref;
        strcpy(new_data -> keterangan, read.keterangan);
        new_data -> debet = read.debet;
        new_data -> kredet = read.kredet;

        insertTree(&root, new_data);
    }
    return root;
}

void treeToFile(NODE *root, FILE *fptr){
    if(root != NULL){
        treeToFile(root -> prev, fptr);
        fprintf(fptr, "%s,%d,%s,%ld,%ld\n", root -> tanggal, root -> ref, root -> keterangan, root -> debet, root -> kredet);
        treeToFile(root -> next, fptr);
    }
}

NODE *binarySearchTree(NODE *root, int ref){
    NODE *temp = root;
    while(temp -> ref != ref){
        if(ref < temp -> ref){
            temp = temp -> prev;
        }else{
            temp = temp -> next;
        }
    }
    return temp;
}

NODE *minValueNode(NODE *node){
    NODE *current = node;

    while(current && current -> prev != NULL)
        current = current -> prev;
    
    return current;
}

NODE *deleteTree(NODE *root, int ref){
    if(root == NULL)
        return root;

    if(ref < root -> ref)
        root -> prev = deleteTree(root -> prev, ref);
    else if(ref > root -> ref)
        root -> next = deleteTree(root -> next, ref);
    else{
        if(root -> prev == NULL){
            NODE *temp = root -> next;
            free(root);
            return temp;
        }else if(root -> next == NULL){
            NODE *temp = root->prev;
            free(root);
            return temp;
        }

        NODE *temp = minValueNode(root -> next);

        strcpy(root -> tanggal, temp -> tanggal);
        root -> ref = temp -> ref;
        strcpy(root -> keterangan, temp -> keterangan);
        root -> debet = temp -> debet;
        root -> kredet = temp -> kredet;

        root -> next = deleteTree(root -> next, temp -> ref);
    }
    return root;
}

void sortingFile(char file_dir_name[]){
    FILE *fptr = fopen(file_dir_name, "r");

    if(fptr == NULL){
        printf("File tidak ditemukan atau belum dibuat\n");
        return;
    }

    NODE *root = NULL;
    root = fileToTree(root, fptr);

    if(root == NULL){
        printf("\t:: Data kosong\n");
        return;
    }

    fclose(fptr);
    
    fptr = fopen(file_dir_name, "w");

    fprintf(fptr,"Tanggal,Ref,Keterangan,Debet,Kredet\n");
    treeToFile(root, fptr);

    fclose(fptr);
    printf("\t:: File berhasil diurut\n");
}

void printDetailakun(NODE *temp){
    printf("\t:: Tanggal     : %s\n", temp -> tanggal);
    printf("\t:: Ref         : %d\n", temp -> ref);
    printf("\t:: Keterangan  : %s\n", temp -> keterangan);
    printf("\t:: Debet       : %ld\n", temp -> debet);
    printf("\t:: Kredet      : %ld\n\n", temp -> kredet);
}

//////////////// Deklarasi Fungsi Neraca Awal
void neracaAwal(char dir_loc[]);
void inputNeracaAwal(char file_neraca_awal[]);
void editNeracaAwal(char file_neraca_awal[]);
void deleteNeracaAwal(char file_neraca_awal[]);
//////////////// Deklarasi Fungsi Jurnal Umum
void jurnalUmum(char dir_loc[]);
void inputJurnalUmum(char file_jurnal_umum[]);
void editJurnalUmum(char file_jurnal_umum[]);
void deleteJurnalUmum(char file_jurnal_umum[]);
//////////////// Deklarasi Fungsi Buku Besar
void bukuBesar(char dir_loc[]);
char *name_buku_besar(char file_buku_besar[], char dir_loc[], int iref);
NODE *searchListforBukuBesar(NODE *head_buku_besar, NODE *head_read_file, int iref);
void generateBukuBesar(char dir_loc[], char file_neraca_awal[], char file_jurnal_umum[]);
void lihatBukuBesar(char dir_loc[]);
//////////////// Deklarasi Fungsi Neraca Saldo
void neracaSaldo(char dir_loc[]);
char *name_neraca_saldo(char file_neraca_saldo[], char dir_loc[]);
void generateNeracaSaldo(char dir_loc[]);
void lihatNeracaSaldo(char dir_loc[]);

//////////////// Fungsi main

int main (){
    //variabel pengatur jalannya program
    char ulang;
    int pilih;

    //menentukan folder tempat file disimpan
    char dir_loc[40];
    getDirName(dir_loc);
    CreateDirectory(dir_loc, NULL);

    system("cls");
    system("color 17");

    header();
 
    printf("\n\t\t\t\t                    ++ Per : %s ++\n", dir_loc);

    pilih = menu();

    while(pilih != 5){
        if(pilih == 1){
            neracaAwal(dir_loc);
        }else if(pilih == 2){
            jurnalUmum(dir_loc);
        }else if(pilih == 3){
            bukuBesar(dir_loc);
        }else if(pilih == 4){
            neracaSaldo(dir_loc);
        }else{
            printf("\t:: Pilihan menu tidak tersedia\n");
        }

        label_cek_ulang :

        fflush(stdin);

        printf("\t:: Apakah anda ingin mengulang menu utama (y/n) : ");
        ulang = getchar();

        if(ulang == 'y' || ulang == 'Y'){
            system("cls");
            header();
            pilih = menu();
        }else if(ulang == 'n' || ulang == 'N'){
            break;
        }else{
            printf("\t:: Input salah!!\n");
            goto label_cek_ulang;
        }
    }
    printf("\t:: Akhir dari program\n");
    return 0;
}

//////// Fungsi neraca awal

void neracaAwal(char dir_loc[]){
    int pilih;
    char file_neraca_awal[40];
    strcpy(file_neraca_awal, dir_loc);
    strcat(file_neraca_awal,"/neraca_awal.csv");

    system("cls");
    header();
    printf("\n\t\t\t\t                         NERACA AWAL\n"
           "\n\t\t\t\t                    ++ Per 1 %s ++\n", dir_loc);

    printf("\t++=======================++\n"
           "\t:: Daftar Menu :         ::\n"
           "\t:: 1. Input neraca awal  ::\n"
           "\t:: 2. Lihat neraca awal  ::\n"
           "\t:: 3. Edit neraca awal   ::\n"
           "\t:: 4. Sorting neraca awal::\n"
           "\t:: 5. Hapus neraca awal  ::\n"
           "\t:: 6. Selesai            ::\n"
           "\t++=======================++\n");

    label_pilih_neracaAwal :

    printf("\t:: Ketik pilihan :");
    scanf("%d", &pilih);

    if(pilih == 1){
        inputNeracaAwal(file_neraca_awal);
    }else if(pilih == 2){
        lihatFile(file_neraca_awal, 0);
    }else if(pilih == 3){
        editNeracaAwal(file_neraca_awal);
    }else if(pilih == 4){
        sortingFile(file_neraca_awal);
    }else if(pilih == 5){
        deleteNeracaAwal(file_neraca_awal);
    }else if(pilih == 6){
        return;
    }else{
        printf("\t:: Input salah!!\n");
        goto label_pilih_neracaAwal;
    }
}

void inputNeracaAwal(char file_neraca_awal[]){
    //program flow variabel
    int again = 1;
    
    NODE *root_neraca_awal = NULL;
    
    while(again != 0){
        system("cls");
        printf("\n\n\tINPUT NERACA AWAL\n");
        NODE *new_data = malloc(sizeof(struct item));
        new_data = inputItem();

        insertTree(&root_neraca_awal, new_data);
        fflush(stdin);
        printf("\t:: Apakah anda ingin menambahkan data yang lain (1/0):");
        scanf("%d", &again);
    }
    
    //save neraca awal
    FILE *fptr_neraca_awal;

    if((fptr_neraca_awal = fopen(file_neraca_awal, "r")) == NULL){
        //membuat file
        fclose(fptr_neraca_awal);
        fptr_neraca_awal = fopen(file_neraca_awal, "a+");
        fprintf(fptr_neraca_awal, "Tanggal,Ref,Keterangan,Debet,Kredet\n");
    }else{
        fclose(fptr_neraca_awal);
        fptr_neraca_awal = fopen(file_neraca_awal,"a+");
    }
    // saveListToFile(head_neraca_awal, fptr_neraca_awal);
    treeToFile(root_neraca_awal, fptr_neraca_awal);
    fclose(fptr_neraca_awal);
    printf("\t:: Data berhasil ditambahkan\n");
}

void editNeracaAwal(char file_neraca_awal[]){
    int ref_to_edit;

    //read file to binary tree
    NODE *root = NULL;
    FILE *fptr = fopen(file_neraca_awal, "r");
    root = fileToTree(root, fptr);

    fclose(fptr);
    if(root == NULL){
        printf("\t:: Data kosong\n");
        return;
    }

    printf("\t:: EDIT NERACA AWAL\n");

    lihatFile(file_neraca_awal, 0);
    printf("\t:: Ketik ref akun yang ingin diedit :");
    scanf("%d",&ref_to_edit);

    //seraching tree
    
    NODE *temp = root;

    temp = binarySearchTree(temp, ref_to_edit);

    if(temp == NULL){
        printf("\t:: Ref tidak ditemukan\n");
        return;
    }

    printf("\t:: Akun yang akan di edit :\n");
    printDetailakun(temp);
    int lanjut;
    printf("\t:: Apakah anda yakin ingin melanjutkan (1/0):");
    scanf("%d", &lanjut);
    if(lanjut){
        printf("\t:: Ketik data baru :\n");

        printf("\t:: Tanggal     : ");
        scanf("%s", &temp -> tanggal);
        printf("\t:: Ref         : ");
        scanf("%d", &temp -> ref);
        strcpy(temp -> keterangan, keterangan(temp -> ref));
        printf("\t:: Debet       : ");
        scanf("%ld", &temp -> debet);
        printf("\t:: Kredet      : ");
        scanf("%ld", &temp -> kredet);

        fptr = fopen(file_neraca_awal, "w");
        fprintf(fptr,"Tanggal,Ref,Keterangan,Debet,Kredet\n");
        treeToFile(root, fptr);
        fclose(fptr);
        printf("\t:: Data berhasil diedit\n");
    }
}

void deleteNeracaAwal(char file_neraca_awal[]){
    int ref_to_delete;

    FILE *fptr = fopen(file_neraca_awal, "r");

    if(fptr == NULL){
        printf("\t:: File tidak ditemukan atau belum dibuat\n");
        return;
    }
    
    NODE *root = NULL;
    root = fileToTree(root, fptr);

    fclose(fptr);

    if(root == NULL){
        printf("\t:: Data kosong\n");
        return;
    }

    printf("\t:: HAPUS NERACA AWAL\n");

    lihatFile(file_neraca_awal, 0);

    printf("\t:: Ketik ref akun yang ingin dihapus :");
    scanf("%d", &ref_to_delete);
    int lanjut;
    printf("\t:: Apakah anda yakin ingin melanjutkan (1/0):");
    scanf("%d", &lanjut);
    if(lanjut){
        root = deleteTree(root, ref_to_delete);

        fptr = fopen(file_neraca_awal, "w");
        fprintf(fptr,"Tanggal,Ref,Keterangan,Debet,Kredet\n");
        treeToFile(root, fptr);

        if(root == NULL)
            fprintf(fptr, "\n");

        fclose(fptr);
        printf("\t:: Data berhasil dihapus\n");
    }
}

/////// Fungsi jurnal umum

void jurnalUmum(char dir_loc[]){
    int pilih;
    char file_jurnal_umum[40];
    strcpy(file_jurnal_umum, dir_loc);
    strcat(file_jurnal_umum,"/jurnal_umum.csv");

    system("cls");
    header();
    printf("\n\t\t\t\t                         JURNAL UMUM\n"
           "\n\t\t\t\t                    ++ Bulan %s ++\n", dir_loc);

    printf("\t++=======================++\n"
           "\t:: Daftar Menu :         ::\n"
           "\t:: 1. Input jurnal umum  ::\n"
           "\t:: 2. Lihat jurnal umum  ::\n"
           "\t:: 3. Edit jurnal umum   ::\n"
           "\t:: 4. Hapus jurnal umum  ::\n"
           "\t:: 5. Selesai            ::\n"
           "\t++=======================++\n");

    label_pilih_jurnal_umum :

    printf("\t:: Ketik pilihan :");
    scanf("%d", &pilih);

    if(pilih == 1){
        inputJurnalUmum(file_jurnal_umum);
    }else if(pilih == 2){
        lihatFile(file_jurnal_umum, 0);
    }else if(pilih == 3){
        editJurnalUmum(file_jurnal_umum);
    }else if(pilih == 4){
        deleteJurnalUmum(file_jurnal_umum);
    }else if(pilih == 5){
        return;
    }else{
        printf("\t:: Pilihan menu tidak tersedia\n");
        goto label_pilih_jurnal_umum;
    }
}

void inputJurnalUmum(char file_jurnal_umum[]){
    int again = 1;

    NODE *head_jurnal_umum = NULL;

    while(again != 0){
        system("cls");
        printf("\n\n\tINPUT JURNAL UMUM\n");
        NODE *new_data = malloc(sizeof(struct item));
        new_data = inputItem();

        addAtEnd(&head_jurnal_umum, new_data);

        fflush(stdin);
        printf("\t:: Apakah anda ingin menambahkan data yang lain (1/0):");
        scanf("%d", &again);
    }

    FILE *fptr_jurnal_umum;

    if((fptr_jurnal_umum = fopen(file_jurnal_umum, "r")) == NULL){
        //membuat file
        fclose(fptr_jurnal_umum);
        fptr_jurnal_umum = fopen(file_jurnal_umum, "a+");
        fprintf(fptr_jurnal_umum, "Tanggal,Ref,Keterangan,Debet,Kredet\n");
    }else{
        fclose(fptr_jurnal_umum);
        fptr_jurnal_umum = fopen(file_jurnal_umum,"a+");
    }
    
    linkedListToFile(head_jurnal_umum, fptr_jurnal_umum);
    fclose(fptr_jurnal_umum);
}

void editJurnalUmum(char file_jurnal_umum[]){
    int ref_to_edit;
    char tanggal[20];

    //read file to linked list
    NODE *head = NULL;
    FILE *fptr = fopen(file_jurnal_umum, "r");

    if(fptr == NULL){
        printf("\t:: File tidak ditemukan atau belum dibuat\n");
        return;
    }

    head = fileToLinkedList(head, fptr);

    fclose(fptr);

    if(head == NULL){
        printf("\t:: Data kosong\n");
        return;
    }

    printf("\n\n\t:: EDIT JURNAL UMUM\n");
    lihatFile(file_jurnal_umum, 0);

    printf("\t:: Ketik ref akun yang ingin diedit:");
    scanf("%d", &ref_to_edit);
    printf("\t:: Ketik tanggal (dd/mm/yyyy): ");
    scanf("%s", &tanggal);
    
    //seraching linked list
    
    NODE *temp = head;
    temp = searchLinkedList(temp, ref_to_edit, tanggal);

    if(temp == NULL){
        printf("\t:: ref tidak ditemukan\n");
        return;
    }

    printf("\t:: Akun yang akan di edit :\n");
    printf("\t:: Tanggal     : %s\n", temp -> tanggal);
    printf("\t:: Ref         : %d\n", temp -> ref);
    printf("\t:: Keterangan  : %s\n", temp -> keterangan);
    printf("\t:: Debet       : %ld\n", temp -> debet);
    printf("\t:: Kredet      : %ld\n\n", temp -> kredet);

    printf("\t:: Ketik data baru :\n");

    printf("\t:: Tanggal     : ");
    scanf("%s", &temp -> tanggal);
    printf("\t:: Ref         : ");
    scanf("%d", &temp -> ref);
    strcpy(temp -> keterangan, keterangan(temp -> ref));
    printf("\t:: Debet       : ");
    scanf("%ld", &temp -> debet);
    printf("\t:: Kredet      : ");
    scanf("%ld", &temp -> kredet);

    fptr = fopen(file_jurnal_umum, "w");
    fprintf(fptr,"Tanggal,Ref,Keterangan,Debet,Kredet\n");
    linkedListToFile(head, fptr);
    fclose(fptr);
    printf("\t:: Data berhasil diedit\n");
}

void deleteJurnalUmum(char file_jurnal_umum[]){
    int ref_to_delete;
    char tanggal[20];

    FILE *fptr = fopen(file_jurnal_umum, "r");

    if(fptr == NULL){
        printf("\t:: File tidak ditemukan atau belum dibuat\n");
        return;
    }
    
    NODE *head = NULL;
    head = fileToLinkedList(head, fptr);

    fclose(fptr);

    if(head == NULL){
        printf("\t:: Data kosong\n");
        return;
    }

    printf("\n\n\tHAPUS JURNAL UMUM\n");

    lihatFile(file_jurnal_umum, 0);
    printf("\t:: Ketik ref yang ingin dihapus :");
    scanf("%d", &ref_to_delete);
    fflush(stdin);
    printf("\t:: Ketik tanggal (dd/mm/yyy) : ");
    scanf("%s", &tanggal);

    //seraching linked list
    
    NODE *temp = head;
    temp = searchLinkedList(temp, ref_to_delete, tanggal);

    if(temp == NULL){
        printf("\t:: ref tidak ditemukan\n");
        return;
    }

    head = deleteLinkedList(head, ref_to_delete, tanggal);

    fptr = fopen(file_jurnal_umum, "w");
    fprintf(fptr,"Tanggal,Ref,Keterangan,Debet,Kredet\n");
    linkedListToFile(head, fptr);
    if(head == NULL)
        fprintf(fptr, "\n");
    fclose(fptr);
    printf("\t:: Data berhasil dihapus\n");
}   

/////// Fungsi buku besar

void bukuBesar(char dir_loc[]){
    int pilih;
    char file_neraca_awal[40], file_jurnal_umum[40];

    strcpy(file_neraca_awal, dir_loc);
    strcat(file_neraca_awal,"/neraca_awal.csv");

    strcpy(file_jurnal_umum, dir_loc);
    strcat(file_jurnal_umum,"/jurnal_umum.csv");

    system("cls");
    header();
    printf("\n\t\t\t\t                         BUKU BESAR\n"
           "\n\t\t\t\t                    ++ Per 31 %s ++\n", dir_loc);

    printf("\t++=======================++\n"
           "\t:: Buku Besar :          ::\n"
           "\t:: 1. Generate buku besar::\n"
           "\t:: 2. Lihat buku besar   ::\n"
           "\t:: 3. Selesai            ::\n"
           "\t++=======================++\n");

    label_pilih_buku_besar :

    printf("\t:: Ketik pilihan :");
    scanf("%d", &pilih);

    if(pilih == 1){
        generateBukuBesar(dir_loc, file_neraca_awal, file_jurnal_umum);
    }else if(pilih == 2){
        lihatBukuBesar(dir_loc);
    }else if(pilih == 3){
        return;
    }else{
        printf("\t:: Pilihan menu tidak tersedia\n");
        goto label_pilih_buku_besar;
    }
}

char *name_buku_besar(char file_buku_besar[], char dir_loc[], int iref){
    char ref[4];

    itoa(iref, ref, 10);
    strcpy(file_buku_besar, dir_loc);
    strcat(file_buku_besar, "/");
    strcat(file_buku_besar, ref);
    strcat(file_buku_besar, ".csv");
    return file_buku_besar;
}

NODE *searchListforBukuBesar(NODE *head_buku_besar, NODE *head_read_file, int iref){
    NODE *temp = head_read_file;
    
    while(temp != NULL){
        if(temp -> ref == iref){
            NODE *new_data = malloc(sizeof(struct item));
            new_data -> prev = NULL;
            new_data -> next = NULL;

            strcpy(new_data -> tanggal, temp -> tanggal);
            new_data -> ref = temp -> ref;
            strcpy(new_data -> keterangan, temp -> keterangan);
            new_data -> debet = temp -> debet;
            new_data -> kredet = temp -> kredet;

            addAtEnd(&head_buku_besar, new_data);
        }
        temp = temp -> next;
    }
    return head_buku_besar;
}

void generateBukuBesar(char dir_loc[], char file_neraca_awal[], char file_jurnal_umum[]){
    NODE *head_neraca_awal = NULL;
    NODE *head_jurnal_umum = NULL;

    FILE *fptr_neraca_awal = fopen(file_neraca_awal, "r");
    FILE *fptr_jurnal_umum = fopen(file_jurnal_umum, "r");

    if(fptr_neraca_awal != NULL)
        head_neraca_awal = fileToLinkedList(head_neraca_awal, fptr_neraca_awal);

    if(fptr_jurnal_umum != NULL)
        head_jurnal_umum = fileToLinkedList(head_jurnal_umum, fptr_jurnal_umum);

    fclose(fptr_neraca_awal);
    fclose(fptr_jurnal_umum);

    NODE *head_buku_besar;
    char file_buku_besar[40];

    for(int i = 111; i<=515; i++){
        if(i == 116) i = 121;
        if(i == 124) i = 211;
        if(i == 213) i = 311;
        if(i == 313) i = 411;
        if(i == 412) i = 511;
        
        head_buku_besar = NULL;

        name_buku_besar(file_buku_besar, dir_loc, i);
        
        FILE *fptr_buku_besar = fopen(file_buku_besar, "w");
        
        //neraca awal -> buku besar
        if(head_neraca_awal != NULL)
            head_buku_besar = searchListforBukuBesar(head_buku_besar, head_neraca_awal, i);

        //jurnal umum -> buku besar
        if(head_jurnal_umum != NULL)
            head_buku_besar = searchListforBukuBesar(head_buku_besar, head_jurnal_umum, i);

        if(head_buku_besar != NULL){
            fprintf(fptr_buku_besar, "Tanggal,Ref,Keterangan,Debet,Kredet\n");
            linkedListToFile(head_buku_besar, fptr_buku_besar);
        }
        fclose(fptr_buku_besar);
    }
   printf("\t:: Data buku besar berhasil di generate\n");
}

void lihatBukuBesar(char dir_loc[]){
    FILE *fptr_buku_besar;
    int pilih;
    char file_buku_besar[40];

    printf("\t++================================================++\n"
           "\t:: Pilih menu bagaimana buku besar ditampilkan :  ::\n"
           "\t++================================================++\n"
           "\t:: 1. Tampilkan untuk akun spesifik               ::\n"
           "\t:: 2. Tampilkan keseluruhan buku besar            ::\n"
           "\t++================================================++\n"
           "\t:: Pilihan : ");
    
    scanf("%d", &pilih);

    if(pilih == 1){
        int iref = getNamaAkun();
        name_buku_besar(file_buku_besar, dir_loc, iref);
        char buffer[100];

        fptr_buku_besar = fopen(file_buku_besar, "r");

        if(fgets(buffer, sizeof(buffer), fptr_buku_besar) == NULL){
            printf("\t:: Data buku besar untuk akun ini kosong\n");
            return;
        }

        fseek(fptr_buku_besar, 0, SEEK_SET );
        fclose(fptr_buku_besar);

        printf("%s :\tNo.%d\n", keterangan(iref), iref);
      
        lihatFile(file_buku_besar, 1);

    }else if(pilih == 2){
        for(int i = 111; i<=515; i++){
            if(i == 116) i = 121;
            if(i == 124) i = 211;
            if(i == 213) i = 311;
            if(i == 313) i = 411;
            if(i == 412) i = 511;
            
            name_buku_besar(file_buku_besar, dir_loc, i);

            char buffer[100];
            fptr_buku_besar = fopen(file_buku_besar, "r");

            if(fgets(buffer, sizeof(buffer), fptr_buku_besar) == NULL)
                continue;

            fseek(fptr_buku_besar, 0, SEEK_SET );
            fclose(fptr_buku_besar);

            printf("\t%s :\tNo.%d\n", keterangan(i), i);

            lihatFile(file_buku_besar, 1);
            printf("\n\n"); 
        }
    }else{
        printf("\t:: Pilihan menu tidak tersedia\n");
        return;
    }
}

/////// Fungsi neraca saldo

void neracaSaldo(char dir_loc[]){
    int pilih;

    system("cls");
    header();
    printf("\n\t\t\t\t                         NERACA SALDO\n"
           "\n\t\t\t\t                    ++ Per 31 %s ++\n", dir_loc);

    printf("\t++==========================++\n"
           "\t:: Neraca Saldo :           ::\n"
           "\t:: 1. Generate neraca saldo ::\n"
           "\t:: 2. Lihat neraca saldo    ::\n"
           "\t:: 3. Selesai               ::\n"
           "\t++==========================++\n");

    label_pilih_neraca_saldo :

    printf("\t:: Ketik pilihan :");
    scanf("%d", &pilih);

    if(pilih == 1){
        generateNeracaSaldo(dir_loc);
    }else if(pilih == 2){
        lihatNeracaSaldo(dir_loc);
    }else if(pilih == 3){
        return;
    }else{
        printf("\t:: Pilihan menu tidak tersedia\n");
        goto label_pilih_neraca_saldo;
    }
}

char *name_neraca_saldo(char file_neraca_saldo[], char dir_loc[]){
    strcpy(file_neraca_saldo, dir_loc);
    strcat(file_neraca_saldo, "/neraca_saldo.csv");
}

void generateNeracaSaldo(char dir_loc[]){
    char file_neraca_saldo[40], file_buku_besar[40], buffer[100];

    name_neraca_saldo(file_neraca_saldo, dir_loc);

    FILE *fptr_buku_besar;
    FILE *fptr_neraca_saldo = fopen(file_neraca_saldo, "w");
    fprintf(fptr_neraca_saldo, "Tanggal,Ref,Keterangan,Debet,Kredet\n");
    
    NODE *head_neraca_saldo = NULL;
    long int total_debet, total_kredet;
    total_debet =  total_kredet = 0;

    for(int i = 111; i <= 515; i++){
        if(i == 116) i = 121;
        if(i == 124) i = 211;
        if(i == 213) i = 311;
        if(i == 313) i = 411;
        if(i == 412) i = 511;

        name_buku_besar(file_buku_besar, dir_loc, i);
        
        fptr_buku_besar = fopen(file_buku_besar, "r");

        if(fgets(buffer, sizeof(buffer), fptr_buku_besar) == NULL) continue;

        NODE read;
        
        while((fscanf(fptr_buku_besar,"%[^,], %d, %[^,], %ld, %ld", &read.tanggal, &read.ref, &read.keterangan, &read.debet, &read.kredet)) != 1){
            strcpy(read.tanggal, strtok(read.tanggal, "\n"));
            total_debet += read.debet;
            total_debet -= read.kredet;
        }
        
        fclose(fptr_buku_besar);

        if(total_debet < 0){
            total_kredet = -1 * total_debet;
            total_debet = 0;
        }

        if(total_debet != 0 ^ total_kredet != 0){
            printf("haha");
            NODE *new_data = malloc(sizeof(struct item));
            new_data -> next = new_data -> prev = NULL;

            strcpy(new_data -> tanggal, "00/00/0000");
            new_data -> ref = i;
            
            strcpy(new_data -> keterangan, keterangan(i));
           
            new_data -> debet = total_debet;
            new_data -> kredet = total_kredet;
          
            addAtEnd(&head_neraca_saldo, new_data);
        }
        total_debet = total_kredet = 0;
    }
    
    linkedListToFile(head_neraca_saldo, fptr_neraca_saldo);
    if(head_neraca_saldo == NULL)
        fprintf(fptr_neraca_saldo, "\n");
    fclose(fptr_neraca_saldo);
    printf("\t:: Data neraca saldo berhasil di generate\n");
}

void lihatNeracaSaldo(char dir_loc[]){
    char file_neraca_saldo[40];
    name_neraca_saldo(file_neraca_saldo, dir_loc);
    lihatFile(file_neraca_saldo, 2);   
}