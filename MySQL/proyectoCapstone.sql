/*
	Base de datos para el almacenamiento de niveles de los sensores MQ2, MQ7 y MQ135
  Por: Karen Cruz, Sergio Delgadillo, Tania Zárate
	Fecha: 25 de febrero de 2022
	Proyecto Capstone:
	Monitoreo de la calidad del aire utilizando como indicadores la concentración de CO, CO2 y GLP
*/

/*Se crea la base de datos*/
CREATE DATABASE proyectoCapstone;

/*Sentencia para usar la base de datos "proyectoCapstone."*/
USE proyectoCapstone;

/*
Se crea la tabla "datos" la cual contendrá:
	- id: identificador numérico y autoincrementable
    - fecha: fecha y hora en tiempo real con formato "aaaa-mm-dd hh:mm:ss"
    - idd: identificador del usuario el cual envía la información
    - mq2, mq7 y mq135: datos obtenidos de estos sensores
*/
CREATE TABLE datos (id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY, fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP, 
idd CHAR (248), mq2 FLOAT(5,3) UNSIGNED NOT NULL, mq7 FLOAT(5,3) UNSIGNED NOT NULL, 
mq135 FLOAT(5,3) UNSIGNED NOT NULL);

/*Se verifican los métodos de autenticación para verificar que el usuario root se
identifique de forma correcta*/
SELECT user, authentication_string, plugin, host FROM mysql.user;

/*Se muestran todos los datos de la tabla "datos"*/
SELECT * FROM datos;
