#ifndef STRUCTURE_H
#define STRUCTURE_H
/* États du protocole ( noms des états donnés à titre indicatif => peuvent être modifiés) */
typedef enum protocol_state {
IDLE, CONNECTED
} protocol_state;
/* Mode de démarrage du protocole. NB : nécessaire à l’usage de la fonction initialize_components() */
typedef enum start_mode { CLIENT, SERVER } start_mode;
/* Structure d’une adresse de socket */
typedef struct mic_tcp_sock_addr {
    char *ip_addr; // @ IP : à fournir sous forme décimale pointée : ex = “192.168.1.2”
    int ip_addr_size; // taille de l’adresse
    unsigned short port; // numéro de port
} mic_tcp_sock_addr;
/*
 * Structure d'un socket
 */
typedef struct mic_tcp_sock {
  int fd;  /* descripteur du socket */
  protocol_state state; /* état du protocole */
  mic_tcp_sock_addr addr; /* adresse du socket */
} mic_tcp_sock;
/*
 * Structure d'un PDU MIC-TCP
 */
typedef struct mic_tcp_pdu {
  mic_tcp_header header ; /* entête du PDU */
  mic_tcp_payload payload; /* charge utile du PDU */
} mic_tcp_pdu;
/*
 * Structure de l'entête d'un PDU MIC-TCP
 */
typedef struct mic_tcp_header
{
  unsigned short source_port; /* numéro de port source */
  unsigned short dest_port; /* numéro de port de destination */
  unsigned int seq_num; /* numéro de séquence */
  unsigned int ack_num; /* numéro d'acquittement */
  unsigned char syn; /* flag SYN (valeur 1 si activé et 0 si non) */
  unsigned char ack; /* flag ACK (valeur 1 si activé et 0 si non) */
  unsigned char fin; /* flag FIN (valeur 1 si activé et 0 si non) */
} mic_tcp_header;
/*
 * Structure des données utiles d’un PDU MIC-TCP
 */
typedef struct mic_tcp_payload {
  char* data; /* données applicatives */
  int size; /* taille des données */
int app_buffer_get(mic_tcp_payload); /*<---- What ????????*/
} mic_tcp_payload;
#endif