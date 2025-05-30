# Trabajo Prático N3


**Título**: Sistema de Monitoreo de Frecuencia Cardiaca

**Alumno**: Aguirre Godoy Sergio

**Objetivo**: Desarrollar un sistema que permita controlar pulso cardiaco de una persona

## Descripción: 


El sistema cuenta con un boton para realizar la lectura de pulso cardiaco. Al pulsar una vez se encendera un led que indica que se esta tomando datos de pulso. 
La lectura de pulso cardiaco se realiza mediante un sensor como por ejemplo:
- https://es.aliexpress.com/i/1005003939587424.html

En cada paso se indicará, mediante el puerto serie y el display, el estado del proceso:
- Comenzando lectura...
- Latidos por minuto: 76
- Lectura finalizada

Al iniciar el sistema se reproduce un mensaje por el parlante:

- "Pulse el botón para comenzar la lectura"

### Plataforma de desarrollo: NUCLEO-F429ZI

### Periféricos a utilizar:

- USER BUTTON: Al presionar se comienza o se detiene una medicion
- ANALOG IN 1: Se utiliza para leer pulso cardiaco
- UART: Se utiliza para enviar información de lectura y estado del sistema a la PC
- LED1: Se utiliza para indicar que esta tomando una medicion
- I2C: Se utiliza para visualizar informacion de lectura y estado del sistema
- PWM: Se utiliza para enviar señal de audio al parlante.
  
## Flujo del Programa
1. Inicialización:

  - Configura las entradas (botón) y salidas (LED).

  - Se configura la inicializacion del Display OLED SSD1306.
  
  - El boton contiene una maquina de estados finita para evitar rebotes.
  
  - Establece comunicación UART para enviar mensajes.

2. Bucle Main:

  - Monitorea el estado del botón.

  - Activa o desactiva el modo de lectura según el estado del botón.

  - En el modo de lectura activa:

      - Lee valores del sensor HW-827.

      - Calcula los BPM utilizando un umbral de deteccion y un promedio ponderado de los intervalos entre picos detectados.

  - Genera mensajes que indican los BPM calculados y los envía a través de UART.

  <a href="https://ibb.co/mCYXf4PF"><img src="https://i.ibb.co/JRbyDHSF/dftp3-system.png" alt="dftp3_system" style="width:500px;" border="0"></a>
  
3. Cálculo de BPM:

  - Umbral de Detección: Utiliza un umbral (`threshold`) para detectar el inicio de un pulso. El umbral se calcula como un valor base (1,65 V) más una variación de 12 mV.
  - Detección de Ascenso: Comprueba si el valor actual del sensor cruza el umbral desde abajo. Si la lectura anterior (`prev_value`) está por debajo del umbral y la lectura actual (`reader`) está por encima, se detecta un pulso.
  - Filtrado de Latidos Rápidos: Calcula la diferencia entre el contador de pulsos actual (`pulse_counter`) y el último conteo de latidos (`last_beat_count`). Si esta diferencia es menor o igual a 45 (equivalente a 450ms), se descarta el latido como inválido (demasiado rápido).

  <a href="https://ibb.co/fzs84wWY"><img src="https://i.ibb.co/VcsH24GW/dftp3-bpm.png" alt="dftp3_bpm" style="width:500px;" border="0"></a>

  
4. Mensajes UART y de Display:

  - Informan el inicio y fin de lectura.

  - Muestran los BPM calculados en tiempo real.


## Diagrama en bloques
  <a href="https://ibb.co/QF4Nj5Nd"><img src="https://i.ibb.co/jvSMZpMR/TP2-sag.png" alt="TP2-sag" style="width:800px;" border="0" /></a>


## Video demostrativo

[![Video del sistema de monitoreo cardiaco](https://img.youtube.com/vi/C37dG0QMjgk/0.jpg)](https://www.youtube.com/watch?v=C37dG0QMjgk)
