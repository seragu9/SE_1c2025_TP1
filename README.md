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

Ademas el sistema cuenta con una alarma programada cada 6 horas. Este tiempo es fijo y queda configurado en el firmware del programa mediante un #define. Cada ese tiempo sonara un buzzer para recordarle al usuario que es necesario un control.


### Plataforma de desarrollo: NUCLEO-F429ZI

### Periféricos a utilizar:

- USER BUTTON: Al presionar se comienza o se detiene una medicion
- ANALOG IN 1: Se utiliza para leer pulso cardiaco
- UART: Se utiliza para enviar información de lectura y estado del sistema a la PC
- LED1: Se utiliza para indicar que esta tomando una medicion


### Diagrama en bloques
  <img src="https://i.ibb.co/ynmFtjZ6/TP1-sag.png" width="50%">

