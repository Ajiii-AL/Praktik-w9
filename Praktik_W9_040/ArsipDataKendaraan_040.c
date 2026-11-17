/* PROGRAM ArsipDataKendaraan_XXX
   Program untuk mengelola data kendaraan */

#include <stdio.h>
#include <stdlib.h>

// Declaration
typedef struct {
    int idKendaraan;
    char nomorPlat[15];
    char jenisKendaraan[25];
    int tahunProduksi;
} Kendaraan;

// Procedure to add vehicle data
void TambahDataKendaraan() {
    Kendaraan kendaraan;
    FILE *fileKendaraan;

    fileKendaraan = fopen("Kendaraan.dat", "ab");

    if (fileKendaraan == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\n=== TAMBAH DATA KENDARAAN ===\n");

    printf("ID Kendaraan    : ");
    scanf("%d", &kendaraan.idKendaraan);

    printf("Nomor Plat      : ");
    scanf("%14s", kendaraan.nomorPlat);

    printf("Jenis Kendaraan : ");
    scanf("%24s", kendaraan.jenisKendaraan);

    printf("Tahun Produksi  : ");
    scanf("%d", &kendaraan.tahunProduksi);

    fwrite(&kendaraan, sizeof(kendaraan), 1, fileKendaraan);

    fclose(fileKendaraan);

    printf("\nData kendaraan berhasil ditambahkan!\n");
}

// Procedure to display vehicle data
void LihatDataKendaraan() {
    Kendaraan kendaraan;
    FILE *fileKendaraan;

    fileKendaraan = fopen("Kendaraan.dat", "rb");

    if (fileKendaraan == NULL) {
        printf("\nData kendaraan belum tersedia!\n");
        return;
    }

    printf("\n=== DATA KENDARAAN ===\n");

    while (fread(&kendaraan, sizeof(kendaraan), 1, fileKendaraan) == 1) {
        printf("\nID Kendaraan    : %d", kendaraan.idKendaraan);
        printf("\nNomor Plat      : %s", kendaraan.nomorPlat);
        printf("\nJenis Kendaraan : %s", kendaraan.jenisKendaraan);
        printf("\nTahun Produksi  : %d\n", kendaraan.tahunProduksi);
    }

    fclose(fileKendaraan);
}

// Procedure to update vehicle plate number
void UbahNomorPlat() {
    Kendaraan kendaraan;
    FILE *fileKendaraan, *fileTemp;
    int id, ditemukan = 0;
    char platBaru[15];

    fileKendaraan = fopen("Kendaraan.dat", "rb");

    if (fileKendaraan == NULL) {
        printf("\nData kendaraan belum tersedia!\n");
        return;
    }

    fileTemp = fopen("Temp.dat", "wb");

    if (fileTemp == NULL) {
        printf("File temporary cannot be opened!\n");
        fclose(fileKendaraan);
        return;
    }

    printf("\n=== UBAH NOMOR PLAT ===\n");
    printf("Masukkan ID Kendaraan : ");
    scanf("%d", &id);

    while (fread(&kendaraan, sizeof(kendaraan), 1, fileKendaraan) == 1) {

        if (kendaraan.idKendaraan == id) {
            ditemukan = 1;

            printf("Nomor Plat Lama : %s\n", kendaraan.nomorPlat);
            printf("Nomor Plat Baru : ");
            scanf("%14s", platBaru);

            sprintf(kendaraan.nomorPlat, "%s", platBaru);
        }

        fwrite(&kendaraan, sizeof(kendaraan), 1, fileTemp);
    }

    fclose(fileKendaraan);
    fclose(fileTemp);

    if (ditemukan == 1) {
        remove("Kendaraan.dat");
        rename("Temp.dat", "Kendaraan.dat");

        printf("\nNomor plat berhasil diubah!\n");
    } else {
        remove("Temp.dat");
        printf("\nID Kendaraan tidak ditemukan!\n");
    }
}

// Procedure to delete vehicle data
void HapusDataKendaraan() {
    Kendaraan kendaraan;
    FILE *fileKendaraan, *fileTemp;
    int id, ditemukan = 0;

    fileKendaraan = fopen("Kendaraan.dat", "rb");

    if (fileKendaraan == NULL) {
        printf("\nData kendaraan belum tersedia!\n");
        return;
    }

    fileTemp = fopen("Temp.dat", "wb");

    if (fileTemp == NULL) {
        printf("File temporary cannot be opened!\n");
        fclose(fileKendaraan);
        return;
    }

    printf("\n=== HAPUS DATA KENDARAAN ===\n");
    printf("Masukkan ID Kendaraan : ");
    scanf("%d", &id);

    while (fread(&kendaraan, sizeof(kendaraan), 1,
                 fileKendaraan) == 1) {

        if (kendaraan.idKendaraan == id) {
            ditemukan = 1;
        } else {
            fwrite(&kendaraan, sizeof(kendaraan), 1, fileTemp);
        }
    }

    fclose(fileKendaraan);
    fclose(fileTemp);

    if (ditemukan == 1) {
        remove("Kendaraan.dat");
        rename("Temp.dat", "Kendaraan.dat");

        printf("\nData kendaraan berhasil dihapus!\n");
    } else {
        remove("Temp.dat");
        printf("\nID Kendaraan tidak ditemukan!\n");
    }
}

// Main Program
int main() {
    int pilihan;

    do {
        printf("\n================================\n");
        printf("     ARSIP DATA KENDARAAN\n");
        printf("================================\n");
        printf("1. Tambah Data Kendaraan\n");
        printf("2. Lihat Data Kendaraan\n");
        printf("3. Ubah Nomor Plat\n");
        printf("4. Hapus Data Kendaraan\n");
        printf("5. Keluar\n");
        printf("================================\n");
        printf("Pilih Menu : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                TambahDataKendaraan();
                break;

            case 2:
                LihatDataKendaraan();
                break;

            case 3:
                UbahNomorPlat();
                break;

            case 4:
                HapusDataKendaraan();
                break;

            case 5:
                printf("\nProgram selesai.\n");
                break;

            default:
                printf("\nPilihan tidak valid!\n");
        }

    } while (pilihan != 5);

    return 0;
}
