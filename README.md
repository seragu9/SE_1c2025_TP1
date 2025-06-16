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


#### Requisitos del proyecto

| Grupo         | ID   | Descripción                                                                                                         | **Estado** |
| :------------ | :----| :------------------------------------------------------------------------------------------------------------------|------------|
| Monitoreo       | 1.1   | El sistema sensará la frecuencia cardíaca en tiempo real mediante un sensor integrado al dispositivo.               | 🔴         |
|                 | 1.2   | El sistema almacenará localmente los datos de frecuencia cardíaca para asegurar la continuidad en caso de desconexión.|🔴         |
| Visualización   | 2.1   | El dispositivo mostrará en su display local la frecuencia cardíaca en tiempo real, con valores numéricos. |🔴         |
|                 | 2.2   | La aplicación web y móvil permitirá visualizar la frecuencia cardíaca en tiempo real mediante valores numéricos actualizados cada dos segundos, asegurando sincronización continua con el dispositivo. |🔴         |
|                 | 2.3   | La aplicación almacenará y mostrará datos históricos de frecuencia cardíaca, permitiendo al usuario consultar tendencias diarias, semanales y mensuales. |🔴         |
| Alertas         | 3.1   | El sistema debe detectar eventos anómalos (ritmo irregular, frecuencia fuera de rango) y generar alertas visuales, sonoras y notificaciones. |🔴         |
|                 | 3.2   | El sistema enviará notificaciones inmediatas a la aplicacion web cuando se detecten anomalías.    |🔴         |
| Configuración   | 4.1   | El sistema permitirá configurar parámetros como umbrales de alerta y etiqueta de usuario desde la aplicación remota. |🔴         |
| Comunicación    | 5.1   | El sistema intentará conectarse a la red Wi-Fi configurada en un #define hasta un máximo de 5 intentos. Si no logra conectarse, mostrará un mensaje de error en el display y continuara su uso sin conexión. |🔴         |
|                 | 5.2   | El sistema contará con una aplicación web accesible vía navegador desde dispositivos móviles y de escritorio. La aplicación permitirá monitorear datos en tiempo real y recibir notificaciones |🔴         |
| Proyecto        | 6.1   | El prototipo será acompañado de la lista de partes, el repositorio de código con su documentación, y un manual de uso. |🔴         |

<p align="center"><em>Tabla 1: Requisitos del proyecto</em></p>

