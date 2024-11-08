# ProyectoAgua
Primer proyecto de Mantenimiento Electrónico. Sistema regulador industrial para depuradora de agua.

Enunciado:<br/>
La EDAR (Estación depuradora de aguas residuales) de Bilbao se ha puesto en contacto con nosotros conocedores de las tecnologías con las que se investigan en nuestro centro. Durante la decantación secundaria (en uno de los procesos del tratamiento de aguas residuales), el depósito tiene una gran variación del nivel de agua por circunstancias de la instalación lo que implica que no se realiza con éxito el tratamiento. Nos han encomendado la tarea de diseñar un sistema de bombeo para mantener constante el nivel de agua de este depósito.
Se digitalizará todo el proceso implementando un sistema IoT básico utilizando un microcontrolador integrándose en una red local. Se monitorizan datos del sistema transmitiendo esta información a una aplicación en un dispositivo local (por ejemplo, una computadora o un smartphone) para su monitorización en tiempo real.
El motor de la bomba debe ser trifásico, de una potencia aprox. 0.18 kW, 230/400V.
El control del sistema se realizará tanto de manera automática como manual que se seleccionará mediante un selector. Es importante que la regulación sea PID de lazo cerrado en función de la demanda de agua. Debe tener una parada de emergencia y los distintos estados de funcionamiento identificados con pilotos de colores, verde (automático), naranja (manual) y rojo (parada de emergencia). El punto de llenado del depósito (consigna) debe realizarse mediante un potenciómetro. El nivel del depósito se medirá mediante un transductor ultrasónico analógico. Cada equipo diseñará su propio sensor ultrasonido.

Para poder realizar este sistema de regulación necesitaremos:<br/>
-Esquema electrico (CADeSIMU) para el montaje del proyecto.<br/>
-El programa para los automatas en LOGOSoft! Comfort.<br/>
-Programa en C++ con las librerias de arduino para la ESP32.<br/>
-Una raspberry pi 4 con NodeRed y Mosquitto (microprocesador).<br/>
-Un ESP32 (microcontrolador) en el cual a travez de codigo le implementaremos las funcionalidades que necesitamos como la interpretación de datos del ultrasonido.<br/>
-PLC para poder hacer la automatización del proceso, en nuestro caso 3 modulos LOGO, 1 de alterna, 1 de directa y 1 acople de salidas analogicas.<br/>
-Ultrasonido (Para medir el nivel del agua).<br/>
-Detectores Capacitivo (Para evitar el desbordamiento), Inductivo (para el rearme del sistema) y de Barrera (para evitar que gente entre al perimetro peligroso).<br/>
-Variador de frecuencia (Para controlar la bomba de agua).<br/>
-Botonera (Inicio y pare).<br/>
-Selector (Manual/Automatico).<br/>
-Potenciometro (para la variacion de frecuencia en manual o el setpoint del regulador PI en automatico).<br/>
-Seta de emergencia.<br/>

Explicación del funcionamiento:<br/>
El sistema funciona mediante una botonera que está conectada a un autómata, la botonera se compone de un botón de arranque, uno de parada y un selector el cual nos permite seleccionar el modo automático o el modo manual.
En modo automático el autómata con el sistema de regulación PI incorporado en el programa se encarga de autorregular el nivel del agua, el cual decidimos con el potenciómetro.
En el modo manual, la función del potenciómetro cambia a controlar la frecuencia del motor.
El nivel del agua lo monitoreamos gracias a los datos que le proporciona el sensor ultrasonido a la ESP32 que lo envía a la Raspberry Pi 4 mediante el protocolo MQTT y NodeRED nos lo muestra en el monitor a tiempo real.
Al sistema le hemos integrado 2 maneras de parar el sitema en caso de fallo y una manera de aviso por peligro, la primera manera sería con una seta de emergencia que debe poder ser activada en cualquier momento, mientras que la segunda manera sería con el detector capacitivo que esta posicionado en el borde superior del tanque para que en caso de que se fuera a desbordar parase. El rearme una vez que todo esta normal y queremos volver a iniciar el programa se activa con el sensor inductivo.
La ultima medida de protección es un sensor de barrera fotoeléctrica que en caso de ser activada se enciende una luz de manera interrumpida dando aviso que alguien a entrado al perimetro de peligro.
En todas la etapas tenemos algun mensaje mostrandose en el automata y según la etapa el mensaje es balnco, ambar o rojo.
![image](https://github.com/user-attachments/assets/f909d059-d713-4f57-9f2c-ef849695838c)

Para el variador de frecuencia
esta para el potenciometro
![image](https://github.com/user-attachments/assets/6bf49472-d886-487f-9af2-7d99e06bb652)

conexion botonera.

![image](https://github.com/user-attachments/assets/905727c4-7e76-469f-bf4c-608b479f37f2)
Imágenes del resultado
![image](https://github.com/NickalsME/ProyectoAgua/blob/e5cb1fc39b095bc7fadbc87764331268e1275580/20241030_165718.jpg)
![image](https://github.com/NickalsME/ProyectoAgua/blob/e5cb1fc39b095bc7fadbc87764331268e1275580/20241030_165648.jpg)
![image](https://github.com/NickalsME/ProyectoAgua/blob/e5cb1fc39b095bc7fadbc87764331268e1275580/20241030_165744.jpg)
