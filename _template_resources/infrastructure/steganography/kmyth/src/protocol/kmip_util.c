/* Stubbed for macOS build - KMIP protocol not needed for seal/unseal */
#include <stddef.h>
typedef struct KMIP KMIP;
#include "kmip_util.h"

int build_kmip_get_request(KMIP *ctx, unsigned char *id, size_t id_len,
                           unsigned char **request, size_t *request_len) {
  (void)ctx; (void)id; (void)id_len; (void)request; (void)request_len; return 1;
}
int parse_kmip_get_request(KMIP *ctx, unsigned char *request, size_t request_len,
                           unsigned char **id, size_t *id_len) {
  (void)ctx; (void)request; (void)request_len; (void)id; (void)id_len; return 1;
}
int build_kmip_get_response(KMIP *ctx, unsigned char *id, size_t id_len,
                            unsigned char *key, size_t key_len,
                            unsigned char **response, size_t *response_len) {
  (void)ctx; (void)id; (void)id_len; (void)key; (void)key_len;
  (void)response; (void)response_len; return 1;
}
int parse_kmip_get_response(KMIP *ctx, unsigned char *response, size_t response_len,
                            unsigned char **id, size_t *id_len,
                            unsigned char **key, size_t *key_len) {
  (void)ctx; (void)response; (void)response_len; (void)id; (void)id_len;
  (void)key; (void)key_len; return 1;
}
