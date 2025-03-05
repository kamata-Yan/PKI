#include "cert_operations.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <sys/stat.h>
#include <direct.h>

using namespace std;

// Проверка существования папки
bool directoryExists(const std::string& path) {
    struct stat info;
    return (stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR));
}

// Создание папки, если её нет
void createDirectoryIfNotExists(const std::string& path) {
    if (!directoryExists(path)) {
        if (_mkdir(path.c_str()) != 0) {
            MessageBoxA(NULL, "Ошибка при создании папки C:/certs!", "Ошибка", MB_OK | MB_ICONERROR);
        }
    }
}

// Функция генерации CSR
void generateCSR(const char* certName) {
    std::string certsDir = "C:/certs";
    createDirectoryIfNotExists(certsDir);

    std::string keyPath = certsDir + "/" + certName + ".key";
    std::string csrPath = certsDir + "/" + certName + ".csr";
    std::string subj = "/C=BY/ST=Minsk/L=Minsk/O=MyCompany/CN=" + std::string(certName);

    std::string csrCommand = "openssl req -new -newkey rsa:4096 -nodes -keyout " + keyPath +
        " -out " + csrPath + " -subj \"" + subj + "\"";

    int result = system(csrCommand.c_str());
    if (result != 0) {
        MessageBoxA(NULL, "Ошибка при создании CSR! Проверьте OpenSSL.", "Ошибка", MB_OK | MB_ICONERROR);
        return;
    }

    MessageBoxA(NULL, "CSR успешно создан! Файл сохранён в C:/certs/", "Успех", MB_OK | MB_ICONINFORMATION);
}

// Функция подписания сертификата
void signCertificate(const char* certName) {
    std::string certsDir = "C:/certs";
    createDirectoryIfNotExists(certsDir);

    std::string keyPath = certsDir + "/" + certName + ".key";
    std::string csrPath = certsDir + "/" + certName + ".csr";
    std::string crtPath = certsDir + "/" + certName + ".crt";

    std::string signCommand = "openssl ca -config C:/OpenSSL/openssl-openssl-3.4.0/apps/openssl.cnf -in " +
        csrPath + " -out " + crtPath + " -batch";

    int result = system(signCommand.c_str());
    if (result != 0) {
        MessageBoxA(NULL, "Ошибка при подписании сертификата! Проверьте OpenSSL.", "Ошибка", MB_OK | MB_ICONERROR);
        return;
    }

    MessageBoxA(NULL, "Сертификат успешно подписан! Файл сохранён в C:/certs/", "Успех", MB_OK | MB_ICONINFORMATION);
}
