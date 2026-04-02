#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, "Soy un Log");

	

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	ip = config_get_string_value (config, "IP");
	puerto = config_get_string_value (config, "PUERTO");
	valor = config_get_string_value (config, "CLAVE");

	log_info(logger, "%s",valor);

	

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */
    log_info(logger, "Leemos la consola");
	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	log_info(logger, "Creamos la conexion hacia el servidor");
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	log_info(logger, "Intentamos enviar mensaje con su valor");
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	log_info(logger, "Ahora enviaremos un paquete, escribe mensajes y cuando quieras terminar, envia la CADENA VACIA");
	paquete(conexion);

    log_info(logger, "Terminando programa");
	terminar_programa(conexion, logger, config);

	

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "logger_tp0", true ,LOG_LEVEL_INFO);
	if(nuevo_logger == NULL){
		perror("Error al crear el archivo LOGGER");
        exit(EXIT_FAILURE);
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");
	if (nuevo_config == NULL) {
    // ¡No se pudo crear el config!
    // Terminemos el programa
	    perror("Error al crear el config");
        exit(EXIT_FAILURE);
}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
    while (1) {

		leido = readline("> ");

        //Verifico que puntero no haya recibido error
        if (leido==NULL) {
            break;
        }

        //Verifico si contenido que ingrese es cadena vacia. En casoque si detienete el programa
		if (strcmp(leido, "")==0){
			free(leido);
			break;
		}
        else{
			log_info(logger, "Mensaje de consola: %s", leido);
            free(leido);

		}
     // 4. Logueamos la línea como pide el TP 
        

    }


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	

	// Leemos y esta vez agregamos las lineas al paquete
    while (1) {

		leido = readline("> ");

        if (leido==NULL) {
            break;
        }

		if (strcmp(leido, "")==0){
			free(leido);
			break;
		}
		else{
			agregar_a_paquete(paquete ,leido, strlen(leido)+1 );

		}

        
	}

	enviar_paquete(paquete,conexion);

	eliminar_paquete(paquete);
     
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  log_destroy(logger);
	  config_destroy(config);
	  liberar_conexion(conexion);
}
