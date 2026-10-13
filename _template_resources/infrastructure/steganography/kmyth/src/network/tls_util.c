/* Stubbed for macOS build - network/tls module not needed for seal/unseal */
#include "tls_util.h"
#include <stddef.h>

int create_tls_connection(char **server_ip,
                          unsigned char *client_private_key,
                          size_t client_private_key_len,
                          char *client_cert_path,
                          char *ca_cert_path,
                          BIO **tls_bio,
                          SSL_CTX **tls_ctx) {
  (void)server_ip; (void)client_private_key; (void)client_private_key_len;
  (void)client_cert_path; (void)ca_cert_path; (void)tls_bio; (void)tls_ctx;
  return 1;
}

int tls_set_context(unsigned char *client_private_key,
                    size_t client_private_key_len,
                    char *client_cert_path,
                    char *ca_cert_path,
                    SSL_CTX **ctx) {
  (void)client_private_key; (void)client_private_key_len;
  (void)client_cert_path; (void)ca_cert_path; (void)ctx;
  return 1;
}

int tls_cleanup(void) { return 0; }

int get_resp_from_tls_server(BIO *bio,
                             char *req,
                             size_t req_size,
                             unsigned char **resp,
                             size_t *resp_size) {
  (void)bio; (void)req; (void)req_size; (void)resp; (void)resp_size;
  return 1;
}

int get_key_from_kmip_server(BIO *bio,
                             char *message,
                             size_t message_length,
                             unsigned char **key,
                             size_t *key_size) {
  (void)bio; (void)message; (void)message_length; (void)key; (void)key_size;
  return 1;
}
