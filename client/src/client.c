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



	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Soy un log");
	
	
	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();


	if (config == NULL) {
        fprintf(stderr, "Error: No se pudo cargar el archivo de configuración.\n");
        return 1;
    }

    // Verificar si la clave "CLAVE" está presente en la configuración
    if (!config_has_property(config, "CLAVE")) {
        fprintf(stderr, "Error: La clave 'CLAVE' no está presente en la configuración.\n");
        config_destroy(config); // Liberar la memoria de la configuración
        return 1;
    }

    // Obtener el valor asociado a la clave "CLAVE" como cadena (string)
    valor = config_get_string_value(config, "CLAVE");
    if (valor == NULL) {
        fprintf(stderr, "Error: No se pudo obtener el valor de la clave 'CLAVE'.\n");
        config_destroy(config); // Liberar la memoria de la configuración
        return 1;
    }

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");

	// Loggeamos el valor de config
	log_info(logger, valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él
	iniciar_servidor();
	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);


	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "MiPrograma", true, LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	while(1){
		leido = readline("> ");

		if(!leido){
			break;
		}
		log_info(logger, leido);
		printf("%s\n", leido);
		free(leido);
	}
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete
	agregar_a_paquete(paquete, leido, strlen(leido));

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
