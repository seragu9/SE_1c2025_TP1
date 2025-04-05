# Trabajo Prático N1 - Idea Proyecto


**Título**: Sistema de Monitoreo de Frecuencia Cardiaca

**Alumno**: Aguirre Godoy Sergio

**Objetivo**: Desarrollar un sistema que permita controlar pulso cardiaco de una persona

## Descripción: 


El sistema cuenta con un boton para realizar la lectura de pulso cardiaco. Al pulsar una vez se encendera un led que indica que se esta tomando datos de pulso. 
La lectura de pulso cardiaco se realiza mediante un sensor como por ejemplo:
- https://www.mercadolibre.com.ar/modulo-sensor-pulso-cardiaco-detector-ritmo-ky-039-arduino/p/MLA46752256#polycard_client=search-nordic&searchVariation=MLA46752256&wid=MLA2026286570&sid=search

Para realizar una lectura es recomendable que el usuario primero ingrese un dedo al sensor en posicion correcta manteniendolo mientras presiona el pulsador para comenzar con la lectura. Luego de unos 5 segundos debe oprimir nuevamente el pulsador para finalizar la lectura y continuamente podria retirar el dedo del sensor.



En cada paso se indicará mediante el puerto serie el estado del proceso:
- Comenzando lectura...
- Pulso cardiaco 76 Latidos por minuto
- Lectura finalizada


### Plataforma de desarrollo: NUCLEO-F429ZI

### Periféricos a utilizar:

- USER BUTTON: Al presionar se comienza o se detiene una medicion
- ANALOG IN 1: Se utiliza para leer pulso cardiaco
- UART: Se utiliza para enviar información de lectura y estado del sistema a la PC
- LED1: Se utiliza para indicar que esta tomando una medicion

### Flujo del Programa
1. Inicialización:

  - Configura las entradas (botón) y salidas (LED).

  - Establece comunicación UART para enviar mensajes.

2. Bucle Main:

  - Monitorea el estado del botón.

  - Activa o desactiva el modo de lectura según el estado del botón.

  - En el modo de lectura activa:

      - Lee valores del sensor KY-039.

      - Calcula los BPM utilizando un promedio móvil de las lecturas y un promedio ponderado de los intervalos entre picos detectados.

  - Genera mensajes que indican los BPM calculados y los envía a través de UART.

  <a href="https://ibb.co/1tqWy5GY"><img src="https://i.ibb.co/Zp8D4PzR/main.png" alt="main" border="0"></a>
  
3. Cálculo de BPM:

  - Promedio Móvil: Ayuda a suavizar las señales del sensor, reduciendo el ruido.

  - Detección de Picos: Identifica incrementos consecutivos en la señal para determinar cuándo ocurre un latido.

  - Promedio Ponderado: Usa los últimos tres intervalos entre latidos para calcular los BPM con mayor precisión.

  <a href="https://ibb.co/4nXq2wLh"><img src="https://i.ibb.co/sdNfCp48/bpm.png" alt="bpm" border="0"></a>
  
4. Mensajes UART:

  - Informan el inicio y fin de lectura.

  - Muestran los BPM calculados en tiempo real.


### Diagrama en bloques
  <a href="https://ibb.co/0pyKSYXb"><img src="https://i.ibb.co/CpK6ZVtG/dbloques2.png" alt="dbloques2" border="0"></a>


