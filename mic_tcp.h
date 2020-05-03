#ifdef MICTCP_H
#define MICTCP_H
/*******A CODER*******/
/*
 * Permet de créer un socket entre l’application et MIC-TCP
 * Retourne le descripteur du socket ou bien -1 en cas d'erreur
 */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int mic_tcp_socket(start_mode sm);//ATTENTION : mettre obligatoirement : result = initialize_components(sm); au début
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*
 * Permet d’attribuer une adresse à un socket.
 * Retourne 0 si succès, et -1 en cas d’échec
 */
int mic_tcp_bind(int socket, mic_tcp_sock_addr addr);
/*
 * Permet de réclamer l’envoi d’une donnée applicative
 * Retourne la taille des données envoyées, et -1 en cas d'erreur
 */
int mic_tcp_send (int mic_sock, char* mesg, int mesg_size);
/*
 * Permet à l’application réceptrice de réclamer la récupération d’une donnée
 * stockée dans les buffers de réception du socket
 * Retourne le nombre d’octets lu ou bien -1 en cas d’erreur
 * NB : cette fonction fait appel à la fonction app_buffer_get()
 */
int mic_tcp_recv (int socket, char* mesg, int max_mesg_size);
/*
 * Permet de traiter un PDU MIC-TCP reçu (mise à jour des numéros de séquence
 * et d'acquittement, etc.) puis d'insérer les données utiles du PDU dans
 * le buffer de réception du socket. Cette fonction utilise la fonction
 * app_buffer_put(). Elle est appelée par initialize_components()
 */
void process_received_PDU(mic_tcp_pdu pdu, mic_tcp_sock_addr addr);
#endif