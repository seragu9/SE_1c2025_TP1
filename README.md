# Memoria del Trabajo Final: Sistema de Monitoreo de Frecuencia Cardiaca


**Universidad de Buenas Aires**
**Facultad de Ingeniería**
**86.65 Sistemas Embebidos**

**Autor:** Aguirre Godoy Sergio

**Padrón:** 96953

*Este trabajo fue realizado en la Ciudad de Buenos Aires entre Mayo y Agosto de 2025.*

## Resumen
Este proyecto presenta el desarrollo de un sistema embebido para el monitoreo continuo de la frecuencia cardíaca, implementado con la placa de desarrollo STM32 Nucleo-F429ZI. 
El sistema emplea un sensor fotodetector para la medición del pulso, permitiendo una adquisición en tiempo real de los datos fisiológicos del usuario. 
Incorpora una visualizacion basada en un display. La conectividad Wi-Fi facilita la transmisión de datos hacia plataformas externas para visualización remota, y permite configurar umbrales de alerta personalizables, mejorando así su adaptabilidad a distintos perfiles clínicos o deportivos. La capacidad de almacenamiento local permite el registro histórico de mediciones para análisis posterior. El diseño del sistema prioriza la modularidad del software y la integración de componentes, con el objetivo de ofrecer una solución compacta de bajo costo para aplicaciones en telemedicina y monitoreo personal de la salud.


 *** *** mide entre 30 y 200 bpm

300 ( 3 lect de 100hz ) 2000 ( 20 lecturas)

## Tabla de Contenidos

- [1. Introducción](#1-introducción)
- [2. Objetivos](#2-objetivos)
- [3. Metodología](#3-metodología)
- [4. Descripción del Sistema](#4-descripción-del-sistema)
- [5. Resultados](#5-resultados)
- [6. Conclusiones](#6-conclusiones)
- [7. Trabajo Futuro](#7-trabajo-futuro)
- [8. Referencias](#8-referencias)

## Registro de versiones

| **Revisión** | **Cambios realizados** |  **Fecha** |
|:------------:|:----------------------:|:----------:|
|       1      | Creación del documento | 12/06/2025 |
|       2      |                        |            |
|       3      |                        |            |

## 1. Introducción general

### 1.1. Objetivo
  Desarrollar un sistema embebido portátil para el monitoreo de la frecuencia cardíaca en el hogar, que permita al usuario controlar su pulso en tiempo real y almacenar registros históricos accesibles de forma remota por profesionales de la salud.

### 1.2. Intro
El monitoreo de la frecuencia cardíaca es una herramienta fundamental para el cuidado de la salud, ya que permite detectar a tiempo alteraciones en el ritmo del corazón que podrían ser indicio de enfermedades cardiovasculares. Si bien existen dispositivos comerciales para esta tarea, muchos de ellos presentan limitaciones en cuanto a accesibilidad, personalización o posibilidad de seguimiento remoto por parte de profesionales médicos.

El presente proyecto aborda esta problemática mediante el desarrollo de un sistema embebido que permite a cualquier persona controlar su pulso desde su hogar de forma sencilla, confiable y económica. El sistema utiliza sensores ópticos (fotodetectores) para medir el ritmo cardíaco en tiempo real y cuenta con una pantalla para visualizar la información y configurar umbrales de alerta según las necesidades del usuario. Además, se integra con una red Wi-Fi, lo que posibilita el envío de los datos registrados a plataformas externas, donde pueden ser consultados por médicos u otros profesionales de la salud para realizar un seguimiento histórico del paciente.

Este proyecto se destaca especialmente por combinar monitoreo local e inalámbrico en un solo dispositivo portátil, accesible y personalizable. Esto lo diferencia de otros sistemas similares, que suelen estar pensados para un entorno clínico cerrado o requieren dispositivos adicionales para transmitir los datos. 
También se valoró la facilidad de acceso a los componentes electrónicos utilizados, la escalabilidad del diseño para adaptarlo a diferentes contextos (hogar, clínica, institución), y su potencial impacto social, al contribuir a la prevención y detección temprana de problemas cardíacos.

Con esta propuesta, se busca acercar la tecnología al cuidado cotidiano de la salud, potenciando el rol del monitoreo domiciliario dentro del ecosistema de soluciones de telemedicina e Internet de las Cosas (IoT).


### 1.2. Análisis de sistemas similares en el mercado

Se analizaron cuatro productos de monitoreo cardiaco. Se muestra la comparación de características en la Tabla 2.1.

<table border="1" cellspacing="0" cellpadding="5">
    <thead>
        <tr>
            <th>Característica</th>
            <th> [MAGENE H303](https://www.magene.com/en/sensors/52-h303-heart-rate-monitor.html)</th>
            <th>[POLAR Verity Sense](https://www.polar.com/us-en/products/accessories/polar-verity-sense)</th>
            <th>[WELLUE O2Ring](https://getwellue.com/pages/o2ring-oxygen-monitor)</th>
            <th>[Wellue Oxiband](https://www.mercadolibre.com.ar/oximetro-de-pulso-wellue-oxiband-con-app-y-recordatorio/p/MLA50740493)</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Tipo de sensor</td>
            <td>Banda torácica con sensor ECG</td>
            <td>Banda óptica para brazo (PPG)</td>
            <td>Anillo con sensor óptico (PPG)</td>
            <td>Sensor óptico PPG para SpO2 y pulso</td>
        </tr>
        <tr>
            <td>Rango frecuencia cardíaca</td>
            <td>30 - 240 bpm</td>
            <td>30 - 220 bpm</td>
            <td>No especificado (pulso y SpO2)</td>
            <td>30 - 250 bpm</td>
        </tr>
        <tr>
            <td>Duración batería</td>
            <td>Hasta 1000 horas</td>
            <td>Hasta 20 horas</td>
            <td>Hasta 14 horas</td>
            <td>Aproximadamente 8 horas</td>
        </tr>
        <tr>
            <td>Tipo de batería</td>
            <td>Pila botón CR2032</td>
            <td>Batería recargable integrada</td>
            <td>Batería recargable integrada</td>
            <td>Batería recargable integrada</td>
        </tr>
        <tr>
            <td>Conectividad inalámbrica</td>
            <td>Bluetooth 4.2 y ANT+</td>
            <td>Bluetooth 5.0</td>
            <td>Bluetooth 4.0</td>
            <td>Bluetooth 4.0</td>
        </tr>
        <tr>
            <td>Impermeabilidad</td>
            <td>IP67 (resistente al agua y polvo)</td>
            <td>Resistente al agua (IPX7)</td>
            <td>IP24 (resistente a salpicaduras)</td>
            <td>No especificado</td>
        </tr>
        <tr>
            <td>Display</td>
            <td>No incluye display (se conecta a apps o dispositivos externos)</td>
            <td>No incluye display (se conecta a apps)</td>
            <td>No incluye display (datos en app)</td>
            <td>Sí, display OLED integrado</td>
        </tr>
        <tr>
            <td>Audio / alertas</td>
            <td>No incluye</td>
            <td>No incluye</td>
            <td>Vibración para alertas</td>
            <td>Alarmas sonoras y visuales</td>
        </tr>
        <tr>
            <td>Precio aproximado</td>
            <td>$30 - $40 USD</td>
            <td>$90 - $120 USD</td>
            <td>$150 - $200 USD</td>
            <td>$600 - $800 USD</td>
        </tr>
        <tr>
            <td>Uso principal</td>
            <td>Monitoreo deportivo y fitness</td>
            <td>Monitoreo deportivo y salud continua</td>
            <td>Monitoreo médico de SpO2 y pulso</td>
            <td>Monitoreo médico de SpO2 y frecuencia cardíaca</td>
        </tr>
    </tbody>
</table>
<p align="center"><em>Tabla 2.1: Comparación de productos de mercado</em></p>

## Capítulo 2. Introducción específica

### 2.1. Requisitos

En la tabla 2.1 se muestran los requisitos del sistema desarrollado.

| Grupo         | ID   | Descripción                                                                                                         |
| :------------ | :----| :------------------------------------------------------------------------------------------------------------------|
| Monitoreo       | 1.1   | El sistema sensará la frecuencia cardíaca en tiempo real mediante un sensor integrado al dispositivo.               |
|                 | 1.2   | El sistema almacenará localmente los datos de frecuencia cardíaca para asegurar la continuidad en caso de desconexión.|
| Visualización   | 2.1   | El dispositivo mostrará en su display local la frecuencia cardíaca en tiempo real, con valores numéricos. |
|                 | 2.2   | La aplicación web y móvil permitirá visualizar la frecuencia cardíaca en tiempo real mediante valores numéricos actualizados cada dos segundos, asegurando sincronización continua con el dispositivo. |
|                 | 2.3   | La aplicación almacenará y mostrará datos históricos de frecuencia cardíaca, permitiendo al usuario consultar tendencias diarias, semanales y mensuales. |
| Alertas         | 3.1   | El sistema debe detectar eventos anómalos (ritmo irregular, frecuencia fuera de rango) y generar alertas visuales, sonoras y notificaciones. |
|                 | 3.2   | El sistema enviará notificaciones inmediatas a la aplicacion web cuando se detecten anomalías.    |
| Configuración   | 4.1   | El sistema permitirá configurar parámetros como umbrales de alerta y etiqueta de usuario desde la aplicación remota. |
| Comunicación    | 5.1   | El sistema intentará conectarse a la red Wi-Fi configurada en un #define hasta un máximo de 5 intentos. Si no logra conectarse, mostrará un mensaje de error en el display y continuara su uso sin conexión. |
|                 | 5.2   | El sistema contará con una aplicación web accesible vía navegador desde dispositivos móviles y de escritorio. La aplicación permitirá monitorear datos en tiempo real y recibir notificaciones |
| Proyecto        | 6.1   | El prototipo será acompañado de la lista de partes, el repositorio de código con su documentación, y un manual de uso. |

<p align="center"><em>Tabla 2.1: Requisitos del proyecto</em></p>

**Tabla 2.1: Requisitos del sistema automático.**

### 2.2. Casos de uso
En las tablas 2.2, 2.3 y 2.4 se presentan tres casos de uso del sistema representativos de su funcionalidad.

| Elemento         | Definición                                                    |
| :--------------- | :------------------------------------------------------------|
| Causa            | Se quiere leer datos de pulso en tiempo real.                |
| Precondición     | El sistema está iniciado y el sensor de pulso está activo.   |
| Flujo básico     | Se debe presionar el botón de usuario para iniciar la lectura en tiempo real. El sistema muestra el pulso en el display y puerto serie, y lo transmite vía Wi-Fi. |
| Flujo alternativo| Si no se presiona el botón, el sistema permanece en modo espera.  |

<p align="center"><em>Tabla 2.2: Caso de uso 1: Lectura de datos de pulso en tiempo real</em></p>

---


| Elemento         | Definición                                                    |
| :--------------- | :------------------------------------------------------------|
| Causa            | El usuario desea revisar el historial y tendencias de la frecuencia cardíaca. |
| Precondición     | El dispositivo ha estado registrando y sincronizando datos con la aplicación web. |
| Flujo básico     | El usuario accede a la aplicación web, selecciona `Datos Historicos` y visualiza los reportes de datos históricos. |
| Flujo alternativo| Si no hay datos almacenados, se muestra un mensaje indicando que no hay registros disponibles. |


<p align="center"><em>Tabla 2.3: Caso de uso 2: Visualización y análisis de datos históricos</em></p>

---


| Elemento         | Definición                                                    |
| :--------------- | :------------------------------------------------------------|
| Causa            | El usuario quiere modificar parámetros  de forma remota. |
| Precondición     | El dispositivo está conectado a la red Wi-Fi y sincronizado con la aplicación. |
| Flujo básico     | El usuario accede a la aplicación, modifica parámetros (umbrales,  etiqueta de usuario). El dispositivo recibe y aplica los cambios automáticamente. |
| Flujo alternativo| Si la conexión falla durante la actualización, el dispositivo mantiene la configuración anterior. |


<p align="center"><em>Tabla 2.4: Caso de uso 3: Configuración de parámetros</em></p>


### 2.3. Descripción de módulos utilizado

En base a la arquitectura de control y los requisitos establecidos se decidió por utilizar los módulos que se
describen a continuación.

#### 2.3.1. Módulo del microcontrolador
Se utilizó como módulo microcontrolador la placa NUCLEO-F429ZI [5], equipada con un microcontrolador STM32F429ZI, figura 2.1.

Los principales puntos tenidos en cuenta para la adopción de esta placa son:

* Rendimiento y recursos: El STM32F429ZI incluye un núcleo ARM Cortex-M4 de alto rendimiento con
capacidad de punto flotante, ideal para realizar cálculos en tiempo real y ejecutar múltiples tareas si-
multáneamente.
* Periféricos integrados: La placa cuenta con una amplia gama de periféricos como UART, SPI, ADC y GPIO,
que permiten una integración eficiente con los sensores y actuadores del sistema.
* Compatibilidad con herramientas de desarrollo: La placa es compatible con Mbed OS y herramientas como
STM32CubeIDE, lo que facilita el desarrollo del software.
* Documentación y soporte: La disponibilidad de documentación detallada simplifica el proceso de implementación y resolución de problemas.

<picture>
    <img alt="" src="img/nucleo.png">
</picture>

**Figura 2.1: NUCLEO-F429ZI.**

#### 2.3.2. Módulo del display grafico
Para la implementación del HMI se utilizó el módulo display SSD1306 [4] con pantalla OLED de 0.96’ que se muestra en la figura 2.2.
El comando gráfico del OLED se realiza a través de una comunicación I2C.

<picture>
    <img alt="" src="img/ssd1306.PNG">
</picture>

**Figura 2.2: Modulo display.**

#### 2.3.3. Módulo Wi-Fi
Para la implementación de la comunicación con la computadora de supervisión a través de un navegador web
se utiliza el módulo Wi-Fi ESP12F incluido en la placa NODEMCU ESP8266 [2] de la figura 2.3.
Este módulo se comunica con el microcontrolador a través de una interfaz UART y la configuración del mismo
se realiza a través de comandos AT.

<picture>
    <img alt="" src="img/NODEMCU8266.png">
</picture>

**Figura 2.3: NODEMCU8266.**

#### 2.3.4.  Sensor de pulso cardiaco.
El modulo HW-827 . Este sensor tiene led y utiliza fotodetector para tomar los pulsos al apoyar el dedo.

<picture>
    <img alt="" src="img/hw827.png">
</picture>

**Figura 2.4: Sensor de pulso cardiaco.**


## Capítulo 3. Diseño e implementación

### 3.1.Hardware

#### 3.1.1. Diagrama en bloques

En la Figura 3.1 se muestra un diagrama del hardware del sistema desarrollado.

<picture>
    <img alt="" src="img/dbloquesf.png">
</picture>

**Figura 3.1: Diagrama en bloque del sistema.**

#### 3.1.2. Lista de señales
En la tabla 3.1 se listan las señales del sistema, indicando la conexión de los puertos de la placa NUCLEO-
F429ZI a los módulos de hardware.

**Tabla 3.1: Lista de señales del sistema.**

### 3.2. Firmware

#### 3.2.1. Repositorio
Todo el código del proyecto se encuentra en el repositorio git en [3].

#### 3.2.2. Tecnologı́a
El sistema se encuentra implementado en C++ utilizando Mbed. El firmware presenta un archivo main.cpp el cual lo único que realiza es llamar a las funciones inicio de sistema, y en el lazo principal, la funcion de actualizacion del sistema.

#### 3.2.3. Estructura del repositorio


| Directorio/Archivo        | Contenido principal                                          |
|-------------------|--------------------------------------------------------------|
| `SE_1c2025_TP1/`            | Archivos fuente del proyecto                                 |
| `SE_1c2025_TP1/modules/button/`       | Control de botón de usuario con maquina de estados      |
| `SE_1c2025_TP11/modules/display/`    | Funciones gráficas para el display SSD1306                   |
| `SE_1c2025_TP1/modules/heart_monitor_system/` | Lógica principal y configuración del sistema     |
| `SE_1c2025_TP1/modules/pulse_sensor/`    | Funciones de control de sensor de pulso cardiaco         |
| `SE_1c2025_TP1/modules/serial_com/`    | Funciones de escritura por puerto serie                 |
| `SE_1c2025_TP1/files/`    | Archivos utilizados (mensaje de audio)          |
| `SE_1c2025_TP1/main.cpp`    | Archivo principal de ejecución          |
| `SE_1c2025_TP1/mbed_app.json`    | Archivo de configuracion para el compilador     |

**Figura 3.2: Estructura de directorios y modulos.**


| Nombre de elemento        | Tipo                          |      Descripción   |
|-------------------|-----------------------|---------------------------------------|
| hw827         | Objeto AnalogIn      | Se usa para leer la etrada analogica A0 de la placa Nucleo donde se conecta el HW-827.      |

**Figura 3.3: Objetos y Variables del modulo pulse sensor.**

#### 3.2.6. Arquitectura
En la figura 3.3 se muestra el diagrama de flujo del firmware.

<picture>
    <img alt="" src="img/uml.png">
</picture> 

**Figura 3.3: Diagrama de flujo principal del firmware.**


## Capítulo 4. Ensayos y resultados

### 4.1. Pruebas funcionales del hardware
Las pruebas funcionales del hardware se realizaron por módulos.

### 4.1.1. Módulo Wi-Fi NODEMCU8266
Se cargo el firmware AT en el modulo. Luego se por conexion USB y comunicacion por el puerto serie se constato el correcto envio de comandos y sus respuestas.

### 4.1.2. Módulo Sesor de pulso HW-827

### 4.1.3. Modulo Display OLED SSD1306

### 4.1.8. Pruebas de integracion
Las pruebas de integración realizadas se encuentran en formato de video en el siguiente enlace:

Se verificó:
* Disposición del hardware.
* Lógica del funcionamiento del sistema.
* Comandos por puerto serie.
* Monitoreo mediante el servidor web.
* Alertas de umbrales.

### 4.1.9. Cumplimiento de requisitos
En la tabla 4.1 se presenta la evaluación del cumplimiento de los requisitos iniciales de la tabla 2.1. Se evaluó
a el estado actual de cada uno indicando en verde aquellos que ya fueron cumplidos y en rojo los requerimientos
no cumplidos.

### 4.1.10. Comparación con otros sistemas similares

En la Tabla 4.2 se puede observar la continuación del análisis de la Sección 1.2, donde se puede ver ahora sumado 
a la comparación al sistema de monitoreo realizado.

### 4.2. Documentación del desarrollo realizado

<table><thead>
  <tr>
    <th>Elemento</th>
    <th>Referencia</th>
  </tr></thead>
<tbody>
  <tr>
    <td>Presentación del proyecto</td>
    <td>Capı́tulo 1</td>
  </tr>
  <tr>
    <td>Listado de requisitos</td>
    <td>Tabla 2.1</td>
  </tr>
  <tr>
    <td>Casos de uso del proyecto</td>
    <td>Tablas 2.2 a 2.3</td>
  </tr>
  <tr>
    <td>Diagrama en bloques del sistema</td>
    <td>Figura 3.1</td>
  </tr>
  <tr>
    <td>Lista de señales</td>
    <td>Tabla 3.1</td>
  </tr>
  <tr>
    <td>Implementación del hardware</td>
    <td>Sección 3.1</td>
  </tr>
  <tr>
    <td>Módulos de software</td>
    <td>Sección 3.2</td>
  </tr>
  <tr>
    <td>Repositorio</td>
    <td>[7]</td>
  </tr>
  <tr>
    <td>Cumplimiento de requisitos</td>
    <td>Tabla 4.1</td>
  </tr>
  <tr>
    <td>Conclusiones finales</td>
    <td>Capı́tulo 5</td>
  </tr>
</tbody>
</table>

**Tabla 4.2: Elementos del sumario del sistema automático para el sistema de monitoreo de frecuencia cardiaca.**

## Capı́tulo 5 Conclusiones

### 5.1. Resultados obtenidos


### 5.1. Proximos pasos

## Bibliografı́a

