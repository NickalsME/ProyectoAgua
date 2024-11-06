# ProyectoAgua
Primer proyecto de Mantenimiento Electrónico. Sistema regulador industrial para depuradora de agua.

Enunciado:
La EDAR (Estación depuradora de aguas residuales) de Bilbao se ha puesto en contacto con nosotros conocedores de las tecnologías con las que se investigan en nuestro centro. Durante la decantación secundaria (en uno de los procesos del tratamiento de aguas residuales), el depósito tiene una gran variación del nivel de agua por circunstancias de la instalación lo que implica que no se realiza con éxito el tratamiento. Nos han encomendado la tarea de diseñar un sistema de bombeo para mantener constante el nivel de agua de este depósito.
Se digitalizará todo el proceso implementando un sistema IoT básico utilizando un microcontrolador integrándose en una red local. Se monitorizan datos del sistema transmitiendo esta información a una aplicación en un dispositivo local (por ejemplo, una computadora o un smartphone) para su monitorización en tiempo real.
El motor de la bomba debe ser trifásico, de una potencia aprox. 0.18 kW, 230/400V.
El control del sistema se realizará tanto de manera automática como manual que se seleccionará mediante un selector. Es importante que la regulación sea PID de lazo cerrado en función de la demanda de agua. Debe tener una parada de emergencia y los distintos estados de funcionamiento identificados con pilotos de colores, verde (automático), naranja (manual) y rojo (parada de emergencia). El punto de llenado del depósito (consigna) debe realizarse mediante un potenciómetro. El nivel del depósito se medirá mediante un transductor ultrasónico analógico. Cada equipo diseñará su propio sensor ultrasonido.

Para poder realizar este sistema de regulación debemos tener un esquema electrico (CADeSIMU), un GRAFCET y un programa para poder 
