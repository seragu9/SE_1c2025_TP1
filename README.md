# Definición de Requisitos y Casos de Uso del Trabajo Final


**Título**: Sistema de Monitoreo de Frecuencia Cardiaca

**Alumno**: Aguirre Godoy Sergio

--

### **1\. Selección del proyecto a implementar**


En el presente estudio, se llevó a cabo un análisis de los diversos proyectos considerados susceptibles de ser ejecutados. Estos fueron evaluados como se detalla en la Tabla 1.1. Entre los criterios de evaluación considerados se encuentran: la disponibilidad de hardware requerido, la utilidad que aportaría el proyecto, el tiempo estimado para su implementación, el potencial impacto social que este pudiera generar, su escalabilidad, la complejidad mecánica involucrada en su desarrollo y finalmente, el nivel de diversión o interés que podría generar.


1. Sistema de navegación para interiores

2. Sistema de monitoreo de frecuencia cardiaca

3. Sistema de monitoreo de tanque de agua

El sistema de navegación para interiores posibilita al usuario recibir y transferir información en diversos puntos de trabajo en recintos tales como museos, exposiciones e industrias, entre otros. Para llevar a cabo esta tarea, se requiere de la implementación de múltiples dispositivos BLE y aplicaciones destinadas a distintos tipos de dispositivos móviles como teléfonos celulares, tabletas y computadoras portátiles. Por consiguiente, el sistema ha sido evaluado con una puntuación de cinco sobre diez puntos en lo que concierne a la disponibilidad de hardware.
En cuanto a la relevancia del proyecto, aunque su necesidad no sea imperativa, su contribución a la organización y su impacto tecnológico son notables. Por ende, se le ha asignado una calificación de cuatro sobre diez en relación a su utilidad. Asimismo, el proyecto podría extenderse en el tiempo debido a factores como la compatibilidad de dispositivos, lo cual le otorga una puntuación de tres en este aspecto.
Dado que este proyecto se orienta más hacia el confort y la logística, su impacto social se adjudica con tres puntos. No obstante, su capacidad de escalabilidad al sumar dispositivos es destacable, a pesar de que la instalación en nuevos recintos podría requerir ajustes adicionales, lo que se traduce en una valoración de ocho en cuanto a escalabilidad. Por otra parte, la complejidad mecánica del proyecto, la cual radica en el desarrollo de software y la conexión de los distintos dispositivos, ha sido evaluada con un puntaje de nueve.
Dado que el proyecto resulta de interés y brinda entretenimiento a los usuarios, se le asigna una puntuación de ocho en la categoría de diversión/interés. Por consiguiente, considerando que los aspectos mencionados son ponderados conforme a factores de diez, seis, ocho, cuatro, seis, seis y tres, respectivamente, se obtienen los puntajes ponderados y se observa que la suma total de estos es de 236, tal como se indica en la última columna de la Tabla 1.

-------

El sistema de monitoreo de frecuencia cardíaca es un sistema diseñado con la finalidad de seguir de cerca el ritmo cardíaco de un individuo. Su implementación se lleva a cabo mediante el uso de sensores de pulso equipados con fotodetectores, pantallas visuales y la utilización de conexiones inalámbricas. Desde la perspectiva del hardware, los sensores son de fácil adquisición, lo cual contribuye a que este proyecto obtenga una calificación de nueve puntos en términos de disponibilidad de hardware. Su aplicación se dirige a pacientes con condiciones de control y enfermedades leves, lo que le otorga una puntuación de seis en el aspecto de utilidad del proyecto. Por otro lado, la implementación de este proyecto requiere un esfuerzo moderado, reflejado en una calificación de siete puntos en cuanto al tiempo necesario para su ejecución. Esto se traduce en un impacto significativo tanto a nivel social como de salud, ya que posiblemente permita la detección temprana de problemas cardiovasculares, obteniendo así una calificación de nueve en el aspecto de impacto social.
El sistema de monitoreo cardíaco es altamente escalable, pudiendo adaptarse tanto a usuarios individuales como a sistemas hospitalarios programables, lo cual le otorga una puntuación de ocho en escalabilidad. Además, al no requerir componentes mecánicos y al ser más electrónico y fácil de integrar, recibe una calificación de siete en cuanto a complejidad mecánica. Debido a su relevancia en el campo de la salud y las aplicaciones de internet de las cosas, este proyecto también obtiene una calificación de seis en términos de interés y diversión. De este modo, la sumatoria de los puntajes ponderados asignados a cada uno de los aspectos evaluados proporciona un total de 326 puntos.

--------------

El sistema de monitoreo de tanque de agua se fundamenta en el control del nivel de agua y en la medición de la temperatura. Cuando el nivel alcanza un umbral mínimo, el sistema activa una bomba de agua para iniciar el proceso de llenado hasta que se complete. Además, se destaca que cuenta con la posibilidad de ser implementado a través de conexión inalámbrica. 
En cuanto al hardware, se destaca su disponibilidad accesible, lo cual le otorga una calificación de nueve en este aspecto. Este proyecto presenta utilidad en escenarios donde el suministro de agua no provee la presión necesaria a los hogares o en casos donde se requiera conexión a un pozo de agua, obteniendo una calificación de siete en términos de utilidad. No obstante, se menciona que la implementación podría demandar un tiempo prolongado para probar los actuadores y sensores en el entorno próximo al agua, razón por la cual se le asigna una calificación de seis en este apartado.
Por otro lado, se indica que su impacto en la salud y calidad de vida es limitado, lo que se traduce en una calificación de cinco en impacto social. Asimismo, se destaca que su instalación se ve restringida en cierta medida, obteniendo una calificación de cinco en escalabilidad. En referencia a la complejidad mecánica, se señala que el sistema requiere la conexión de tuberías y válvulas de agua, así como el aislamiento del circuito contra el agua, lo cual representa una complejidad media, otorgándosele una calificación de cinco en este sentido. Por último, se menciona que la implementación de este sistema puede resultar en una experiencia divertida y motivadora, siendo valorada con un seis en diversión e interés.


<table>
        <thead>
            <tr>
                <th rowspan="2">Proyecto</th>
                <th colspan="2">Sistema de navegación para interiores</th>
                <th colspan="2">Sistema de monitoreo de frecuencia cardiaca</th>
                <th colspan="2">Sistema de monitoreo de tanque de agua</th>
            </tr>
            <tr>
                <th>Puntaje</th>
                <th>Puntaje Ponderado</th>
                <th>Puntaje</th>
                <th>Puntaje Ponderado</th>
                <th>Puntaje</th>
                <th>Puntaje Ponderado</th>
            </tr>
        </thead>
        <tbody>
            <tr class="header-row">
                <td align ="center">Disponibilidad de Hardware <br>(peso : 10)</td>
                <td>5</td>
                <td>50</td>
                <td>9</td>
                <td>90</td>
                <td>9</td>
                <td>90</td>
            </tr>
            <tr>
                <td align ="center">Utilidad <br>(peso : 6)</td>
                <td>4</td>
                <td>24</td>
                <td>6</td>
                <td>36</td>
                <td>7</td>
                <td>42</td>
            </tr>
            <tr class="header-row">
                <td align ="center">Tiempo de Implementación <br>(peso : 8)</td>
                <td>3</td>
                <td>24</td>
                <td>7</td>
                <td>56</td>
                <td>6</td>
                <td>48</td>
            </tr>
            <tr>
                <td align ="center">Impacto social <br>(peso : 4)</td>
                <td>3</td>
                <td>12</td>
                <td>9</td>
                <td>36</td>
                <td>5</td>
                <td>20</td>
            </tr>
            <tr class="header-row">
                <td align ="center">Escalabilidad (peso : 6)</td>
                <td>8</td>
                <td>48</td>
                <td>8</td>
                <td>48</td>
                <td>5</td>
                <td>30</td>
            </tr>
            <tr>
                <td align ="center">Complejidad Mecánica <br>(peso : 6)</td>
                <td>9</td>
                <td>54</td>
                <td>7</td>
                <td>42</td>
                <td>5</td>
                <td>30</td>
            </tr>
			<tr>
                <td align ="center">Diversion/Interés <br>(peso : 3)</td>
                <td>8</td>
                <td>24</td>
                <td>6</td>
                <td>18</td>
                <td>6</td>
                <td>18</td>
            </tr>
            <tr class="highlight-green">
                <td>Puntaje Total</td>
                <td>-</td>
                <td>236</td>
                <td>-</td>
                <td class="highlight-red">326</td>
                <td>-</td>
                <td>278</td>
            </tr>
        </tbody>
</table>
<p align="center"><em>Tabla 1.1: Comparación de proyectos</em></p>

#### Diagrama en bloques

<a href="https://imgbb.com/"><img src="https://i.ibb.co/gZB39n3f/TPF-sag.png" alt="TPF-sag" style="width:800px;" border="0"></a>
<p align="center"><em>Figura 1: Diagrama en bloques </em></p>

### **2. Elicitación de requisitos y casos de uso**

Se analizaron dos productos de monitoreo cardiaco. Se muestra la comparación de características en la Tabla 2.1.

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

#### Requisitos del proyecto

| Grupo         | ID   | Descripción                                                                                                         |
| :------------ | :----| :------------------------------------------------------------------------------------------------------------------|
| Inicio	 | 1.1  | El sistema intentará conectarse a la red inicialmente y establece conexión con la aplicación.                        |
| Interfaz de usuario | 2.1  | El sistema contará con una aplicación web.						                       |
| Visualización | 3.1  | El sistema permitirá visualizar la frecuencia cardíaca en el display local del dispositivo.                         |
|               | 3.2  | El sistema permitirá visualizar la frecuencia cardíaca en tiempo real a través de una aplicación web o móvil.       |
|               | 3.3  | El sistema permitirá visualizar datos históricos y tendencias de frecuencia cardíaca en la aplicación web.          |
| Alertas       | 4.1  | El sistema debe detectar eventos anómalos (ritmo irregular, frecuencia fuera de rango) y generar alertas visuales, sonoras y notificaciones. |
|               | 5.2  | El sistema enviará notificaciones inmediatas a los dispositivos conectados (móvil, tablet) cuando se detecten anomalías. |
| Almacenamiento| 5.1  | El sistema almacenará localmente los datos de frecuencia cardíaca en caso de pérdida de conexión WiFi.               |
| Configuración | 6.1  | El sistema permitirá configurar parámetros como umbrales de alerta y etiqueta de usuario desde la aplicación remota. |

<p align="center"><em>Tabla 2.1: Requisitos del proyecto</em></p>

#### Casos de uso

| Elemento         | Definición                                                    |
| :--------------- | :------------------------------------------------------------|
| Causa            | Se quiere leer datos de pulso en tiempo real.                |
| Precondición     | El sistema está iniciado y el sensor de pulso está activo.   |
| Flujo básico     | Se debe presionar el botón de usuario para iniciar la lectura en tiempo real. El sistema muestra el pulso en el display y puerto serie, y lo transmite vía WiFi. |
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
| Precondición     | El dispositivo está conectado a la red WiFi y sincronizado con la aplicación. |
| Flujo básico     | El usuario accede a la aplicación, modifica parámetros (umbrales,  etiqueta de usuario). El dispositivo recibe y aplica los cambios automáticamente. |
| Flujo alternativo| Si la conexión falla durante la actualización, el dispositivo mantiene la configuración anterior. |


<p align="center"><em>Tabla 2.4: Caso de uso 3: Configuración de parámetros</em></p>
