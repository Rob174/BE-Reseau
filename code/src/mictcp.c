#include <mictcp.h>
#include <api/mictcp_core.h>
#include <time.h>
#include <stdlib.h>
#define TIMEOUT 10

/*
 * Permet de créer un socket entre l’application et MIC-TCP
 * Retourne le descripteur du socket ou bien -1 en cas d'erreur
 */
mic_tcp_sock sock;
int PA = 0;
int PE = 0;
int mic_tcp_socket(start_mode sm)
{
    int result = -1;
    //printf("[MIC-TCP] Appel de la fonction: ");  printf(__FUNCTION__); printf("\n");
    result = initialize_components(sm); /* Appel obligatoire */
    set_loss_rate(0);
    sock.fd = 1;
    sock.state = ESTABLISHED;
    return result;
}

/*
 * Permet d’attribuer une adresse à un socket.
 * Retourne 0 si succès, et -1 en cas d’échec
 */
int mic_tcp_bind(int socket, mic_tcp_sock_addr addr)
{
    printf("[MIC-TCP] Appel de la fonction: ");  printf(__FUNCTION__); printf("\n");
    srand(time(NULL));
    return 0;
}

/*
 * Met le socket en état d'acceptation de connexions
 * Retourne 0 si succès, -1 si erreur
 */
int mic_tcp_accept(int socket, mic_tcp_sock_addr* addr)
{
    printf("[MIC-TCP] Appel de la fonction: ");  printf(__FUNCTION__); printf("\n");
    //port source choisi aléatoirement
    int port_source = 1000+(double)(rand())/RAND_MAX*100;
    printf("\t\t\t\t x --> %d\n",port_source);
    sock.port_source = port_source;
    return 0;
}

/*
 * Permet de réclamer l’établissement d’une connexion
 * Retourne 0 si la connexion est établie, et -1 en cas d’échec
 */
int mic_tcp_connect(int socket, mic_tcp_sock_addr addr)
{
    printf("[MIC-TCP] Appel de la fonction: ");  printf(__FUNCTION__); printf("\n");
    int result = -1;
    if(socket == 1) {
        sock.addr = addr;
        result = 0;
    }
    set_loss_rate(50);
    return result;
}

/*
 * Permet de réclamer l’envoi d’une donnée applicative
 * Retourne la taille des données envoyées, et -1 en cas d'erreur
 */
int mic_tcp_send (int mic_sock, char* mesg, int mesg_size)
{
    //printf("[MIC-TCP] Appel de la fonction: "); printf(__FUNCTION__); printf("\n");
    mic_tcp_pdu pdu;
    pdu.header.source_port = sock.port_source;
    pdu.header.dest_port = sock.addr.port;
    //Tout le reste des champs à 0
    pdu.payload.data = mesg;
    pdu.payload.size = mesg_size;
    pdu.header.ack = 0;
    pdu.header.seq_num = PE;
    printf("\t\t\t\t%d  -(%d)->  %d...\n",sock.port_source,pdu.header.seq_num,sock.addr.port);
    int nb_env = IP_send(pdu,sock.addr);
    mic_tcp_pdu ack;
    
    int nb_recu = IP_recv(&ack, &(sock.addr),TIMEOUT);
    while(nb_recu == -1 || ack.header.seq_num != PE){
        // printf("ACK : Nb recu : %d\n",nb_recu);    
        // printf("ACK pas bon avec %d contre %d normalement\n", ack.header.seq_num,PE);
        printf("\t\t\t\tX %d!=%d\n",ack.header.seq_num,PE);
        printf("\t\t\t\t%d  -(%d)->  %d...\n",sock.port_source,pdu.header.seq_num,sock.addr.port);
        nb_env = IP_send(pdu,sock.addr);
        nb_recu = IP_recv(&ack, &(sock.addr),TIMEOUT);
    }
    printf("\t\t\t\tV\n");
    PE=PE%2+1;
    return nb_env;
}

/*
 * Permet à l’application réceptrice de réclamer la récupération d’une donnée
 * stockée dans les buffers de réception du socket
 * Retourne le nombre d’octets lu ou bien -1 en cas d’erreur
 * NB : cette fonction fait appel à la fonction app_buffer_get()
 */
int mic_tcp_recv (int socket, char* mesg, int max_mesg_size)
{
    //printf("[MIC-TCP] Appel de la fonction: "); printf(__FUNCTION__); printf("\n");
    mic_tcp_payload p;
    p.data = mesg;
    p.size = max_mesg_size;
    int taille = app_buffer_get(p);
    return taille;
}

/*
 * Permet de réclamer la destruction d’un socket.
 * Engendre la fermeture de la connexion suivant le modèle de TCP.
 * Retourne 0 si tout se passe bien et -1 en cas d'erreur
 */
int mic_tcp_close (int socket)
{
    //printf("[MIC-TCP] Appel de la fonction :  "); printf(__FUNCTION__); printf("\n");
    return -1;
}

/*
 * Traitement d’un PDU MIC-TCP reçu (mise à jour des numéros de séquence
 * et d'acquittement, etc.) puis insère les données utiles du PDU dans
 * le buffer de réception du socket. Cette fonction utilise la fonction
 * app_buffer_put().
 */
void process_received_PDU(mic_tcp_pdu pdu, mic_tcp_sock_addr addr)
{
    //printf("[MIC-TCP] Appel de la fonction: "); printf(__FUNCTION__); 
    printf("\t\t\t\t%d  <-(%d)-  %d...\n",sock.addr.port,pdu.header.seq_num,sock.port_source);
    if(pdu.header.seq_num != PA) {
        printf("\t\t\t\tX %d!=%d\n",pdu.header.seq_num);
        return;
    }
    app_buffer_put(pdu.payload);
    PA = PA%2+1;

    mic_tcp_pdu ack;
    ack.header.dest_port = pdu.header.source_port;
    ack.header.source_port = pdu.header.dest_port;
    ack.header.ack = 1;
    ack.header.ack_num = PA;
    ack.payload.data = NULL;
    ack.payload.size = 0;
    printf("\t\t\t\t%d  -(%d)->  %d...\n",ack.header.source_port,ack.header.ack_num,ack.header.dest_port);
    IP_send(ack,addr);
}
