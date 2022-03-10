# **Monitoreo de la calidad del aire utilizando como indicadores la concentración de CO, CO2 y GLP**

![](https://github.com/TaniaZarate/ProyectoCapstone-TotalLifeProtect/blob/main/assets/logos.jpg)

## Proyecto Capstone del Diplomado "Internet de las Cosas" de Samsung Innovation Campus y CodigoIoT.



> Integrantes: 
> 
> Cruz Varela Karen Guerlain, UAM Azcapotzalco, Ing. en Computación.
> 
> Zárate Chávez Tania Guadalupe, UAM Azcapotzalco, Ing. en Computación.
> 
> Delgadillo Marín Sergio, UAM Azcapotzalco, Ing. en Computación.
> 
> - Asesor: Vilchis León Paloma Alejandra. 
> 

# Introducción

Cuando se detecta cierta cantidad de humo y una cantidad de CO alto hace que esto sea nocivo para la salud, lo cual puede provocar:
- Intoxicación.
- Asfixia.
- Crisis nerviosa.
- Tos.
- Entre otros.

La **intoxicación por monóxido de carbono** sucede cuando se acumula CO en el torrente sanguíneo. Cuando hay demasiado monóxido de carbono en el aire, el cuerpo reemplaza el oxígeno en los glóbulos rojos con monóxido de carbono. Esto puede generar un **daño grave** en el tejido, o incluso desmayos y, en el peor de los casos, **muerte por asfixia**. Para evitar llegar a tal tragedia, es altamente recomendable tener el *espacio ventilado*, de esta manera, se evita la acumulación de monóxido de carbono en el lugar donde se resida o donde se labore.

Al igual que el monóxido de carbono, el **gas licuado de petróleo (GLP)**, que es una mezcla de propano y butano, al inhalarlo puede causar *euforia, somnolencia, inconsciencia, asfixia, trastornos del ritmo cardíaco, fluctuaciones en la presión sanguínea*, y puede resultar en la **muerte por _asfixia_ y fibrilación ventricular**.

Por otro lado, la pandemia mundial actualmente en curso derivada de la enfermedad ocasionada por el virus *SARS-CoV-2*, continúa afectando a la humanidad, a pesar de contar con alguna vacuna o el esquema de vacunación completo. Los contagios no sólo se han dado por la interacción entre personas, también es debido a la inhalación de partículas en el aire que contienen el virus, más en habitaciones que no cuentan con la ventilación adecuada, ya sea que no cuenten con aire acondicionado o simplemente que no tengan ventanas. Se pueden analizar los **niveles de CO2** para saber si la habitación se está llenando de *exhalaciones infecciosas*. El nivel de este componente permite estimar si entra suficiente aire fresco del exterior.

En cuanto a la relación con PNUD, el proyecto como tal se encuentra ubicado en el tercer objetivo de Desarrollo Sostenible, el cual es “Salud y Bienestar”, ya que Total Life Protect permite la **detección de humo, gas, CO y CO2** que pueden llegar a afectar al ser humano dentro del hogar debido a un mal uso de electrodomésticos o dispositivos necesarios en la vida diaria, además de evitar contagios y posibles muertes por el virus SARS-CoV-2 ya que determina la calidad del aire.


# Alcances

Se propone elaborar un **sistema de de monitoreo en casa**, la cual incluye un detector de humo, CO, CO2 y gas LP con activación de alarma; además, se le notificará a los dueños del hogar mediante un mensaje de texto a través de Telegram sobre el incidente, de tal manera que la persona tenga conocimiento de lo sucedido y así, tomar las medidas necesarias para evitar contagios y propagación del virus SARS-CoV-2 ya que, si se tiene un nivel alto de CO2, el virus podría esparcirse, así como muertes por intoxicación y asfixia debido a las altas concentraciones de los gases.

# Justificación

La manera en la que el **IoT** se relaciona con **_“Monitoreo de la calidad del aire utilizando como indicadores la concentración de CO, CO2 y GLP”_** es debido a que, por medio de Internet, se le notifica al usuario cuando ocurre algún incidente en casa o si existe alta concentración de CO, gas GLP y CO2, lo cual es una señal de que la _ventilación es deficiente_ y aumenta la probabilidad de contagio del virus SARS-CoV-2, así como muerte por asfixia o intoxicación, y de esta manera, también poder intercambiar los datos obtenidos por medio de Internet, y de esta manera, existe una comunicación entre personas y dispositivos del hogar.

# Objetivo

Diseñar un **dispositivo** que permita identificar de manera eficiente y oportuna el **alto nivel de concentración de _CO, gas GLP y CO2_** en los hogares, esto con la finalidad de garantizar la protección de la vida del ser humano.

# Material necesario

Para la elaboración del circuito, se necesita el siguiente material:

- **ESP32-CAM OV2640 Wifi Bluetooth.**                       1       $220.11
- **Convertidor USB Serial FTDI TTL FT232RL.**               1       $98.00
- **Cable USB a Mini USB Tipo B.**                           1       $64.00
- **Módulo Detector de Calidad de Aire MQ-135.**             1       $98.00 
- **Módulo Detector de Monóxido de Carbono MQ-7.**           1       $96.00 
- **Módulo Detector de Gas LP MQ-2.**                        1       $77.32
- **Módulo Ads1115.**                                        1       $161.00
- **Fuente de Alimentación 5V 2A / 9V 1A / 12V 1A.**         1       $62.00
- **Led Amarillos 5mm.**                                     5       $15.00
- **Led Rojos 5mm.**                                         5       $15.00
- **Led Verdes 5mm.**                                        5       $15.00
- **Cables Dupont Largos h-h (hembra-hembra).**              40      $93.00
- **Buzzer.**                                                1       $36.00
- **Resistencias.**          

Dentro del software necesario, se ocupará:

- **Arduino IDE.**
- **MQTT.**
- **Node-red.**
- **Telegram.**
- **MySQL.**
- **Grafana.**

# Explicación detallada del Detector de CO, CO2 GLP

El dispositivo que se propone estará en una caja estanca tipo IP67, en donde ésta contendrá los sensores necesarios para la detección de CO, gas GLP y CO2 (MQ-7, MQ-2 y MQ-135 respectivamente), la ESP32-CAM, el convertidor analógico digital, las resistencias, buzzer y sus conexiones con dichos sensores por medio de los cables dupont.
En la parte superior se encuentran los 3 LEDs (verde, amarillo y rojo), en donde su funcionamiento es el siguiente:

![image](https://user-images.githubusercontent.com/90163838/157773695-15a34b30-35ce-4d0d-9b8d-42294073bf2f.png)
![image](https://user-images.githubusercontent.com/90163838/157773791-132c5883-8991-4574-8a1f-c968363406f2.png)

# Funcionamiento esperado del Sistema de monitoreo de la calidad del aire utilizando como indicadores la concentración de CO, CO2 y GLP

Existen dos formas en las que opera el dispositivo detector, las cuales son:

1. ONLINE

Dependiendo de los datos que capture el dispositivo, son los mensajes que se enviarán al usuario a través de un teléfono celular, en donde en cualquier momento será notificado de algún incidente o peligro en casa. Los mensajes que se mostrarán son los siguientes:

- Calidad del aire buena.
- Calidad del aire baja, posible contaminación por humo.
- Calidad del aire media, posible contaminación por falta de ventilación.
- Calidad del aire mala, posible contaminación por fuga de gas GLP.
- Ventilar de inmediato y verificar fugas de gas.

De igual manera, todos los datos leídos por el detector se envían por medio de MQTT a Node-red, en donde se realiza la conexión con la base de datos la cual después está ligada a Grafana que ayudará a visualizar de manera gráfica todos los valores que se han estado registrando.

2. OFFLINE

De forma independiente a si se recibieron los mensajes por la aplicación, el dispositivo cuenta con una alerta audible y visual que alertarán al usuario. Las acciones se realizan de la siguiente manera:

- Calidad del aire buena: Enciende el LED verde.
- Calidad del aire media: Enciende el LED amarillo.
- Calidad del aire mala: Enciende el LED amarillo y suenan pitidos cortos.
- Calidad del aire mala (extremadamente peligrosa): Enciende el LED rojo y suenan pitidos largos.



# Circuito a realizar

El circuito del detector se ve de la siguiente manera: 

![image](https://user-images.githubusercontent.com/90163838/157774257-92bc00b4-77b7-49ca-a7d1-034406464733.png)


# Referencias
