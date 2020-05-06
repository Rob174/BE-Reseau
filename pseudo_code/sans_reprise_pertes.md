# Puit rcv()
Lancement en mode SERVER
Etat IDLE
Création du socket local
Initialize_components
Connexion
Etat CONNECTED
Tant que 1
    Tant que rien reçu
        IP_rcv() // si non bloquant
    app_buffer_put()

# Puit MIC_TCP
Lancement en mode SERVER
Etat IDLE
Tant que 1
    app_buffer_get
    Met à disposition le résultat 

# Source
Lancement en mode CLIENT
Etat IDLE
Création du socket local
Initialize_components
Connexion
Etat CONNECTED
Tant que 1
    mic_tcp_send