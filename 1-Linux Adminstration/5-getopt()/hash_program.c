#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <stdlib.h>
#include <unistd.h>


void calculate_sha1(const char *input) ;
void calculate_sha256(const char *input) ;


int main(int argc, char *argv[]) {
    int opt;
    char *input = NULL;

    if (argc < 3) {
        printf("Usage: %s -a <text> or -b <text>\n", argv[0]);
        return 1;
    }

    while ((opt = getopt(argc, argv, "a:b:")) != -1) {
        switch (opt) {
            case 'a':
                input = argv[optind - 1]; 
                if (input != NULL) {
                    calculate_sha256(input);
                }
                break;
            case 'b':
                input = argv[optind - 1]; 
                if (input != NULL) {
                    calculate_sha1(input);
                }
                break;
            case '?':
                printf("Unknown option\n");
                break;
        }
    }

    return 0;
}




// تعريف دالة حساب SHA-256
void calculate_sha256(const char *input) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length;

    // إنشاء سياق (context) خاص بـ EVP
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        printf("Error initializing EVP_MD_CTX\n");
        return;
    }

    // تهيئة الـ SHA256
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1) {
        printf("Error initializing SHA256 digest\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // تحديث الهاش بالنص المدخل
    if (EVP_DigestUpdate(ctx, input, strlen(input)) != 1) {
        printf("Error updating digest\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // الحصول على النتيجة النهائية للهاش
    if (EVP_DigestFinal_ex(ctx, hash, &length) != 1) {
        printf("Error finalizing digest\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // طباعة الهاش (SHA-256)
    printf("SHA-256: ");
    for (unsigned int i = 0; i < length; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // تحرير السياق بعد الاستخدام
    EVP_MD_CTX_free(ctx);
}

// تعريف دالة حساب SHA-1
void calculate_sha1(const char *input) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length;

    // إنشاء سياق (context) خاص بـ EVP
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (ctx == NULL) {
        printf("Error initializing EVP_MD_CTX\n");
        return;
    }

    // تهيئة الـ SHA1
    if (EVP_DigestInit_ex(ctx, EVP_sha1(), NULL) != 1) {
        printf("Error initializing SHA1 digest\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // تحديث الهاش بالنص المدخل
    if (EVP_DigestUpdate(ctx, input, strlen(input)) != 1) {
        printf("Error updating digest\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // الحصول على النتيجة النهائية للهاش
    if (EVP_DigestFinal_ex(ctx, hash, &length) != 1) {
        printf("Error finalizing digest\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // طباعة الهاش (SHA-1)
    printf("SHA-1: ");
    for (unsigned int i = 0; i < length; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // تحرير السياق بعد الاستخدام
    EVP_MD_CTX_free(ctx);
}
