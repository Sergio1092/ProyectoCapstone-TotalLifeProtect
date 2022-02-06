# **Total Life Protect**

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

Se propone elaborar un **sistema de automatización en casa**, la cual incluye un detector de humo, CO y gas con activación de alarma; además, se le notificará a los dueños del hogar, mediante un mensaje de texto, sobre el incidente, de tal manera que la persona tenga conocimiento de lo sucedido. 

Por otra parte, se medirá el nivel de CO2 que se encuentra en el hogar, esto con el fin de evitar contagios y propagación del virus SARS-CoV-2 ya que, si se tiene un nivel alto de CO2 (>1000 ppm), el virus podría esparcirse.

# Justificación

La manera en la que el **IoT** se relaciona con **_“Total Life Protect”_** es debido a que, por medio de Internet, se le notifica al usuario cuando ocurre algún incidente en casa o si existe alta concentración de CO, gas GLP y CO2, lo cual es una señal de que la _ventilación es deficiente_ y aumenta la probabilidad de contagio del virus SARS-CoV-2, así como muerte por asfixia o intoxicación, y de esta manera, también poder intercambiar los datos obtenidos por medio de Internet, de esta manera, existe una comunicación entre personas y dispositivos del hogar.

# Objetivo

Diseñar un **dispositivo** que permita identificar de manera eficiente y oportuna el **alto nivel de _CO, gas GLP y CO2_** en los hogares, esto con la finalidad de garantizar la protección de la vida del ser humano.

# Material necesario

Para la elaboración del circuito, se necesita el siguiente material:

- Cables Dupont Largos h-h (hembra-hembra)		  40	  $93.00
- Display Pantalla Oled					                 1    $114.00
- ESP32-CAM OV2640 Wifi Bluetooth			           1	  $220.11
- Fuente de Alimentación 5V 2A / 9V 1A / 12V 1A	 1	  $62.00
- Led Amarillos 5mm						                   5	  $15.00
- Led Rojos 5mm						                       5	  $15.00
- Led Verdes 5mm						                     5	  $15.00
- Módulo Detector de Calidad de Aire MQ-135 		 1	  $98.00 
- Módulo Detector de Monóxido de Carbono MQ-7	   1	  $96.00 
- Módulo Detector de Gas GLP MQ-6			           1	  $75.00
- Módulo Ads1115 						                     1	  $161.00
- Buzzer							                           1	  $36.00
- Resistencias

# Explicación detallada de Total Life Protect

El dispositivo que se propone estará en una caja estanca tipo IP67, en donde ésta contendrá los sensores necesarios para la detección de CO, gas GLP y CO2 (MQ-7, MQ-6 y MQ-135 respectivamente), la ESP32-CAM y sus conexiones con dichos sensores por medio de los cables dupont.
Lo que se plantea es que en la parte frontal se encuentre la pantalla OLED y en la parte superior 3 LEDs (verde, amarillo y rojo) y su funcionamiento sería el siguiente:
1. Con respecto al CO, la manera con la que se podrá detectar los niveles de concentración es por medio de los 3 LED’s, ya que:
    - Cuando se encuentre en un nivel bajo, generalmente 35 ppm o menos, el LED verde estará encendido. A pesar de ser un nivel bajo, está situación debe ser monitoreada, ya que       si es por un tiempo prolongado (más de 8 horas) suele ser una situación peligrosa.
    - Cuando se encuentre en un nivel medio, entre 36 y 100 ppm, el LED amarillo será ahora quien este encendido y debe atenderse de inmediato ya que esos niveles de                   concentración pueden causar serios problemas de salud, por lo que, en ese momento, se recomendará ventilar el hogar abriendo puertas y ventanas. 
    - Finalmente, cuando se encuentre en un nivel alto, mayores a 100 ppm, el LED rojo se encenderá, alertando al usuario de inmediato de esta situación, ya que, si se detectan       mayores a 100 ppm y las personas al interior muestran síntomas, es considerada una situación de extremo peligro. También es una situación de riesgo sí hay esos niveles de       concentración y las personas no tienen ningún síntoma, por lo que, para ambos casos, se recomendará ventilar el hogar abriendo puertas y ventanas y esperar afuera hasta         que el CO haya bajado a niveles fuera de peligro.
 
2. En relación al CO2, la forma por la cual se podrán visualizar los niveles de concentración es a través de la pantalla OLED, ya que:
    - Cuando se encuentre entre 400 - 600 ppm, se podrá ver en la pantalla que la calidad del aire es EXCELENTE, y por lo tanto, no hay ningún riesgo.
    - Cuando se encuentre entre 700 - 800 ppm, la pantalla mostrará el mensaje de BUENO, indicando así la buena calidad de aire en ese momento.
    - Cuando se encuentre entre 900 - 1000 ppm, se podrá ver en la pantalla que la calidad del aire es NORMAL, y por lo tanto, es un nivel aceptable.
 
*En estos primeros tres casos no hay ningún factor de riesgo*
    - Cuando se encuentre entre 1100 - 1500 ppm, la pantalla mostrará el mensaje de MEDIOCRE, indicando así que el aire está contaminado, y por lo tanto, se recomienda                 ventilación en el hogar.
    - Finalmente, cuando se encuentre entre 1600 - 2100 ppm (o más), se podrá ver en la pantalla que la calidad del aire es MALA, indicando así que el ambiente está altamente         contaminado, por lo que se necesita urgentemente ventilar la zona afectada.

3. En cuanto al gas GLP, al igual que con el sensor de CO, la forma de detectar los niveles de gas será mediante los 3 LED’s y será de la siguiente manera:
    - <!-- 2100 ppm peligro, dice, >1000 ppm esta feo xd https://nj.gov/health/eoh/rtkweb/documents/fs/1594sp.pdf -->

En última instancia, los datos que capture el dispositivo también podrán ser monitoreados por el usuario a través de un teléfono celular, esto por medio de Internet, en donde en cualquier momento será notificado de algún incidente o peligro en casa.


# Circuito



# Referencias
