# Informe de Avance del Trabajo Final


**Título**: Sistema de Monitoreo de Frecuencia Cardiaca

**Alumno**: Aguirre Godoy Sergio

--

## Cumplimiento de los requerimientos

En base a los requerimientos planteados en la definición del proyecto requerimientos (link), se evalúa el estado actual de cada uno indicando:  
🟢 **Cumplido**  
🟡 **Pendiente, pero factible**  
🔴 **Pendiente con dudas**

El estado de los requerimientos se muestra en la tabla 1.
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

