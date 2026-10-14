#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define FEE_STANDARD 200000
#define FEE_BHYT 40000
#define MAX_DOCTOR_LOAD 5

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int stt_arr[MAX_SIZE];
    char name_arr[MAX_SIZE][30];
    int age_arr[MAX_SIZE];
    int priority_arr[MAX_SIZE];
    int bhyt_arr[MAX_SIZE];
    int fee_arr[MAX_SIZE];
    int total_patients = 0;
    int next_stt = 1;

    int choice;
    do {
        printf("\n--- KIOSK DANG KY KFAM BENH MEDCARE ---\n");
        printf("1. Tiep nhan benh nhan moi\n");
        printf("2. Hien thi danh sach cho\n");
        printf("3. Cap nhat thong tin benh nhan\n");
        printf("4. Huy so thu tu (Xoa benh nhan)\n");
        printf("5. Tim kiem benh nhan\n");
        printf("0. Thoat chuong trinh\n");
        printf("Lua chon cua ban: ");
        if (scanf("%d", &choice) != 1) {
            printf("Loi nhap lieu! Vui long nhap so.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 1) {
            if (total_patients >= MAX_SIZE) {
                printf("Hang doi da day (Toi đa 100 benh nhan)! Khong the tiep nhan them.\n");
                continue;
            }

            char name[30];
            int age, is_pregnant, has_bhyt;

            printf("Nhập ho ten benh nhan: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            printf("Nhap tuoi: ");
            scanf("%d", &age);

            printf("La phu nu mang thai? (1: Co, 0: Khong): ");
            scanf("%d", &is_pregnant);

            printf("Co BHYT? (1: Co, 0: Khong): ");
            scanf("%d", &has_bhyt);
            clearInputBuffer();

            int is_priority = (age > 70 || is_pregnant == 1) ? 1 : 0;
            int fee = (has_bhyt == 1) ? FEE_BHYT : FEE_STANDARD;

            int insert_index = total_patients;
            if (is_priority == 1) {
                int last_priority_pos = -1;
                for (int i = 0; i < total_patients; i++) {
                    if (priority_arr[i] == 1) {
                        last_priority_pos = i;
                    }
                }
                insert_index = last_priority_pos + 1;

                for (int i = total_patients; i > insert_index; i--) {
                    stt_arr[i] = stt_arr[i - 1];
                    strcpy(name_arr[i], name_arr[i - 1]);
                    age_arr[i] = age_arr[i - 1];
                    priority_arr[i] = priority_arr[i - 1];
                    bhyt_arr[i] = bhyt_arr[i - 1];
                    fee_arr[i] = fee_arr[i - 1];
                }
            }

            stt_arr[insert_index] = next_stt++;
            strcpy(name_arr[insert_index], name);
            age_arr[insert_index] = age;
            priority_arr[insert_index] = is_priority;
            bhyt_arr[insert_index] = has_bhyt;
            fee_arr[insert_index] = fee;

            total_patients++;
            printf("Dang ky thanh cong! STT cua ban la: %d\n", stt_arr[insert_index]);

        } else if (choice == 2) {
            if (total_patients == 0) {
                printf("Hien tai khong co benh nhan nao trong hang doi.\n");
            } else {
                printf("\n--- DANH SACH CHO KHAM BENH ---\n");
                printf("%-5s | %-20s | %-5s | %-10s | %-8s | %-10s\n", "STT", "Ho Ten", "Tuoi", "Uu Tien", "BHYT", "Phi Kham");
                for (int i = 0; i < total_patients; i++) {
                    printf("%-5d | %-20s | %-5d | %-10s | %-8s | %-10d\n",
                           stt_arr[i],
                           name_arr[i],
                           age_arr[i],
                           priority_arr[i] == 1 ? 'Co' : 'Khong',
                           bhyt_arr[i] == 1 ? 'Co' : 'Khong',
                           fee_arr[i]);
                }
            }
        } else if (choice == 3) {
            int target_stt, found_idx = -1;
            printf("Nhap STT benh nhan can cap nhat: ");
            scanf("%d", &target_stt);
            clearInputBuffer();

            for (int i = 0; i < total_patients; i++) {
                if (stt_arr[i] == target_stt) {
                    found_idx = i;
                    break;
                }
            }

            if (found_idx == -1) {
                printf("Khong tim thay benh nhan co STT %d\n", target_stt);
            } else {
                printf("Nhap ten moi: ");
                fgets(name_arr[found_idx], sizeof(name_arr[found_idx]), stdin);
                name_arr[found_idx][strcspn(name_arr[found_idx], "\n")] = 0;

                printf("Nhap tuoi moi: ");
                scanf("%d", &age_arr[found_idx]);

                printf("Co BHYT moi? (1: Co, 0: Khong): ");
                scanf("%d", &bhyt_arr[found_idx]);
                clearInputBuffer();

                priority_arr[found_idx] = (age_arr[found_idx] > 70) ? 1 : priority_arr[found_idx];
                fee_arr[found_idx] = (bhyt_arr[found_idx] == 1) ? FEE_BHYT : FEE_STANDARD;

                printf("Cap nhat thong tin thanh cong!\n");
            }
        } else if (choice == 4) {
            int target_stt, found_idx = -1;
            printf("Nhap STT benh nhan can huy: ");
            scanf("%d", &target_stt);
            clearInputBuffer();

            for (int i = 0; i < total_patients; i++) {
                if (stt_arr[i] == target_stt) {
                    found_idx = i;
                    break;
                }
            }

            if (found_idx == -1) {
                printf("Khong tim thay benh nhan co STT %d\n", target_stt);
            } else {
                for (int i = found_idx; i < total_patients - 1; i++) {
                    stt_arr[i] = stt_arr[i + 1];
                    strcpy(name_arr[i], name_arr[i + 1]);
                    age_arr[i] = age_arr[i + 1];
                    priority_arr[i] = priority_arr[i + 1];
                    bhyt_arr[i] = bhyt_arr[i + 1];
                    fee_arr[i] = fee_arr[i + 1];
                }
                total_patients--;
                printf("Da xoa thanh cong benh nhan khoi hang doi.\n");
            }
        } else if (choice == 5) {
            char search_name[30];
            printf("Nhap ten benh nhan can tim: ");
            fgets(search_name, sizeof(search_name), stdin);
            search_name[strcspn(search_name, "\n")] = 0;

            int found = 0;
            printf("\n--- KET QUA TIM KIEM ---\n");
            for (int i = 0; i < total_patients; i++) {
                if (strcmp(name_arr[i], search_name) == 0) {
                    printf("STT: %d | Ten: %s | Tuoi: %d | Uu tien: %s | BHYT: %s | Phi: %d\n",
                           stt_arr[i], name_arr[i], age_arr[i],
                           priority_arr[i] == 1 ? 'Co' : 'Khong',
                           bhyt_arr[i] == 1 ? 'Co' : 'Khong',
                           fee_arr[i]);
                    found = 1;
                }
            }
            if (!found) {
                printf("Khong tim thay benh nhan nao co ten '%s'\n", search_name);
            }
        }
    } while (choice != 0);

    return 0;
}
