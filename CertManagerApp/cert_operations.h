#ifndef CERT_OPERATIONS_H
#define CERT_OPERATIONS_H

void generateCSR(const char* certName);
void signCertificate(const char* certName);

#endif // CERT_OPERATIONS_H
