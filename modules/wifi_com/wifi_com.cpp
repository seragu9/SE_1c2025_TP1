//=====[Libraries]=============================================================
// detec +IPD,0,396:GET /set?valor=28 HTTP/1.1

#include "arm_book_lib.h"

#include "wifi_com.h"

#include "non_blocking_delay.h"
#include "serial_com.h"
#include "pulse_sensor.h"
#include "data_history.h"
#include "string.h"
#include "heart_monitor_system.h"

//=====[Declaration of private defines]========================================

#define DELAY_10_SECONDS        10000
#define DELAY_5_SECONDS         5000

#define BEGIN_USER_LINE   "<div style='font-size:48px;'>"
#define END_USER_LINE     "</div>"
#define WARNING_THRESHOLD_LINE  "<div style='font-size:32px;color:red;'> Alerta activa</div>"
#define LABEL_HIGH_THRESHOLD "<label for=\"umbralAlto\">Umbral Alto:</label><input type=\"number\" id=\"umbralAlto\" name=\"umbralAlto\" value=\""
#define LABEL_LOW_THRESHOLD "<label for=\"umbralBajo\">Umbral Bajo:</label><input type=\"number\" id=\"umbralBajo\" name=\"umbralBajo\" value=\""
#define LABEL_TAG   "<label for=\"etiqueta\">Etiqueta:</label><input type=\"text\" id=\"etiqueta\" name=\"etiqueta\" value=\""
    


#define WEB_TIME_REFRESH  "10"

#define IP_MAX_LENGTH (15 + 1)

//=====[Declaration of private data types]=====================================

Register_t registers[MAX_REG];
int historialIndex;

typedef enum {
   WIFI_STATE_INIT,
   WIFI_STATE_SEND_AT,
   WIFI_STATE_WAIT_AT,
   WIFI_STATE_SEND_CWMODE,
   WIFI_STATE_WAIT_CWMODE,
   WIFI_STATE_SEND_CWJAP_IS_SET,
   WIFI_STATE_WAIT_CWJAP_IS_SET,
   WIFI_STATE_SEND_CWJAP_SET,
   WIFI_STATE_WAIT_CWJAP_SET_1,
   WIFI_STATE_WAIT_CWJAP_SET_2,
   WIFI_STATE_SEND_CIFSR,
   WIFI_STATE_WAIT_CIFSR,
   WIFI_STATE_LOAD_IP,
   WIFI_STATE_SEND_CIPMUX,
   WIFI_STATE_WAIT_CIPMUX,
   WIFI_STATE_SEND_CIPSERVER,
   WIFI_STATE_WAIT_CIPSERVER,
   WIFI_STATE_SEND_CIPSEND,
   WIFI_STATE_WAIT_CIPSEND,
   WIFI_STATE_SEND_HTML,
   WIFI_STATE_WAIT_HTML,
   WIFI_STATE_SEND_CIPCLOSE,
   WIFI_STATE_WAIT_CIPCLOSE,
   WIFI_STATE_SEND_CIPSEND_HISTORY,
   WIFI_STATE_WAIT_CIPSEND_HISTORY,
   WIFI_STATE_SEND_HTML_HISTORY,
   WIFI_STATE_WAIT_HTML_HISTORY,
   WIFI_STATE_IDLE,
   WIFI_STATE_READ_GET,
   //WIFI_STATE_WAIT_BEFORE_SEND,
   WIFI_STATE_ERROR
} wifiComState_t;



//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartWifi( PE_8, PE_7, 115200 );

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static const char responseOk[] = "OK";
static const char responseCwjapOk[] = "+CWJAP:";
static const char responseCwjap1[] = "WIFI CONNECTED";
static const char responseCwjap2[] = "WIFI GOT IP";
static const char responseCifsr[] = "+CIFSR:STAIP,\"";
static const char responseStatus3[] = "STATUS:3";
static const char responseCipstatus[] = "+CIPSTATUS:";
static const char responseSendOk[] = "SEND OK";
static const char responseCipclose[] = "CLOSED";

static int currentConnectionId;
static int lastConnectionId;
static char wifiComApSsid[AP_SSID_MAX_LENGTH] = "";
static char wifiComApPassword[AP_PASSWORD_MAX_LENGTH] = "";
static char wifiComIpAddress[IP_MAX_LENGTH];
bool wifiComFlagRespuesta = false;
bool wifiComFlagNuevaConexion = false;
char ipdContentBuffer[512];
int ipdContentIndex = 0;
int ipdExpectedLength = 0;
bool flagSolicitudHome = false;
bool flagHistRequest = false;


static const char* wifiComExpectedResponse;
static wifiComState_t wifiComState;

static nonBlockingDelay_t wifiComDelay;

static const char htmlCodeHeader [] =
   "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
   "<title>Heart Monitor System</title>"
   "<meta http-equiv=\"refresh\" content=\"10\"> </head>"
   "<body style='font-family:sans-serif;text-align:center;'>"
    "<h1>Monitor de Parámetros</h1>"
    ;

static const char htmlCodePreConfig [] = 
    "<h2>Configuración del Sistema</h2>"
    "<form id=\"configForm\">"
    ;

static const char htmlCodePostConfig [] = 
    "<button type=\"submit\">Enviar</button>"
    "</form>"
    "<script>"
    "document.getElementById('configForm').addEventListener('submit', function(e) {"
      "e.preventDefault();"
      "const alto = document.getElementById('umbralAlto').value;"
      "const bajo = document.getElementById('umbralBajo').value;"
      "const etiqueta = encodeURIComponent(document.getElementById('etiqueta').value);"

      "fetch(`/set?alto=${alto}&bajo=${bajo}&tag=${etiqueta}`)"
        ".then(res => res.text())"
        ".then(data => alert(\"Configuración enviada correctamente\"))"
        ".catch(err => alert(\"Error al enviar configuración\"));"
    "});"
  "</script>"
    "<div style=\"position: absolute; top: 10px; right: 10px;\">"
  "<form method=\"GET\" action=\"/historial\">"
    "<input type=\"submit\" value=\"📊 Historial\"></form></div>"
   ;

static char htmlCodeParam [500] = "";

static const char htmlCodeFooter [] =
    "<h2>Configuración del Sistema</h2>"
    "<form id=\"configForm\">"
    "<label for=\"umbralAlto\">Umbral Alto:</label>"
    "<input type=\"number\" id=\"umbralAlto\" name=\"umbralAlto\" value=\"120\"><br>"
    "<label for=\"umbralBajo\">Umbral Bajo:</label>"
    "<input type=\"number\" id=\"umbralBajo\" name=\"umbralBajo\" value=\"60\"><br>"
    "<label for=\"etiqueta\">Etiqueta:</label>"
    "<input type=\"text\" id=\"etiqueta\" name=\"etiqueta\" value=\"Default\"><br>"
    "<button type=\"submit\">Enviar</button>"
  "</form>"
  "<script>"
    "document.getElementById('configForm').addEventListener('submit', function(e) {"
      "e.preventDefault();"
      "const alto = document.getElementById('umbralAlto').value;"
      "const bajo = document.getElementById('umbralBajo').value;"
      "const etiqueta = encodeURIComponent(document.getElementById('etiqueta').value);"

      "fetch(`/set?alto=${alto}&bajo=${bajo}&tag=${etiqueta}`)"
        ".then(res => res.text())"
        ".then(data => alert(\"Configuración enviada correctamente\"))"
        ".catch(err => alert(\"Error al enviar configuración\"));"
    "});"
  "</script>"
    "<div style=\"position: absolute; top: 10px; right: 10px;\">"
  "<form method=\"GET\" action=\"/historial\">"
    "<input type=\"submit\" value=\"📊 Historial\"></form></div>"
   ;

static char htmlCodeBody [350] = "";

static char htmlCodeHistoryHeader [] = 
    "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
   "<title>Heart Monitor System</title> </head>"
   "<body style='font-family:sans-serif;text-align:center;'>"
    "<h2>Historial de Lecturas</h2>"
  "<table><thead><tr>"
        "<th>Fecha y Hora</th> <th>BPM</th><th>Etiqueta</th> </tr> </thead>"
    "<tbody>"
    ;

static char htmlCodeHistoryBody [2048] = "";

static char htmlCodeHistoryFooter [] = 
    "</tbody></table>"
  "<a class=\"volver-btn\" href=\"/\">⬅️ Volver</a></body></html>"
    ;


//=====[Declarations (prototypes) of private functions]========================

static bool isExpectedResponse();
void checkForThresholdRequest();
bool wifiComCharRead( char* receivedChar );
void wifiComStringWrite( const char* str );
void detectAndPrintIpdLine();
void procesarEntradaIPD(char c);
void wifiComCharDispatcher();
void wifiComWebPageDataUpdate();
void wifiComWebPageHistDataUpdate();

//=====[Implementations of public functions]===================================

void wifiComSetWiFiComApSsid( char * ApSsid )
{
    strncpy(wifiComApSsid, ApSsid, AP_SSID_MAX_LENGTH);
}

void wifiComSetWiFiComApPassword( char * ApPassword )
{
    strncpy(wifiComApPassword, ApPassword, AP_PASSWORD_MAX_LENGTH );
}

char * wifiComGetIpAddress()
{
   return wifiComIpAddress;
}

void wifiComRestart()
{
    wifiComState = WIFI_STATE_INIT;
}

void wifiComInit()
{
    wifiComState = WIFI_STATE_INIT;
}

void wifiComUpdate()
{
   int lengthOfHtmlCode;
   static char receivedCharWifiCom;
   static int IpStringPositionIndex;
   char strToSend[50] = "";
   
   switch (wifiComState) {

      case WIFI_STATE_INIT:
         nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
         wifiComState = WIFI_STATE_SEND_AT;
      break;

      case WIFI_STATE_SEND_AT:
         if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT\r\n" );
            wifiComExpectedResponse = responseOk;
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_AT;
         }
      break;

      case WIFI_STATE_WAIT_AT:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CWMODE;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            sendUartMessage("AT command not responded ");
            sendUartMessage("correctly\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CWMODE:
         if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CWMODE=1\r\n" );
            wifiComExpectedResponse = responseOk;
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CWMODE;
         }
      break;

      case WIFI_STATE_WAIT_CWMODE:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CWJAP_IS_SET;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            sendUartMessage("AT+CWMODE=1 command not ");
            sendUartMessage("responded correctly\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CWJAP_IS_SET:
         if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CWJAP?\r\n" );
            wifiComExpectedResponse = responseCwjapOk;
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CWJAP_IS_SET;
         }
      break;

      case WIFI_STATE_WAIT_CWJAP_IS_SET:
         if (isExpectedResponse()) {
            wifiComExpectedResponse = responseOk;
            wifiComState = WIFI_STATE_SEND_CIFSR;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CWJAP_SET;
         }
      break;

      case WIFI_STATE_SEND_CWJAP_SET:
         if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CWJAP=\"" );
            wifiComStringWrite( wifiComApSsid );
            wifiComStringWrite( "\",\"" );
            wifiComStringWrite( wifiComApPassword );
            wifiComStringWrite( "\"" );
            wifiComStringWrite( "\r\n" );
            wifiComExpectedResponse = responseCwjap1;
            nonBlockingDelayWrite(&wifiComDelay, DELAY_10_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CWJAP_SET_1;
         }
      break;

      case WIFI_STATE_WAIT_CWJAP_SET_1:
         if (isExpectedResponse()) {
            wifiComExpectedResponse = responseCwjap2;
            wifiComState = WIFI_STATE_WAIT_CWJAP_SET_2;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            sendUartMessage("Error in state: ");
            sendUartMessage("WIFI_STATE_WAIT_CWJAP_SET_1\r\n");
            sendUartMessage("Check Wi-Fi AP credentials ");
            sendUartMessage("and restart\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
         break;

      case WIFI_STATE_WAIT_CWJAP_SET_2:
         if (isExpectedResponse()) {
            wifiComState = WIFI_STATE_SEND_CIFSR;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            sendUartMessage("Error in state: ");
            sendUartMessage("WIFI_STATE_WAIT_CWJAP_SET_2\r\n");
            sendUartMessage("Check Wi-Fi AP credentials ");
            sendUartMessage("and restart\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CIFSR:
         if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CIFSR\r\n" );
            wifiComExpectedResponse = responseCifsr;
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIFSR;
         }
      break;

      case WIFI_STATE_WAIT_CIFSR:
         if (isExpectedResponse()) {
            wifiComState = WIFI_STATE_LOAD_IP;
            IpStringPositionIndex = 0;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            sendUartMessage("AT+CIFSR command not responded ");
            sendUartMessage("correctly\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_LOAD_IP:
         if (wifiComCharRead(&receivedCharWifiCom)) {
            if ( (receivedCharWifiCom != '"') && 
               (IpStringPositionIndex < IP_MAX_LENGTH) ) {
               wifiComIpAddress[IpStringPositionIndex] = receivedCharWifiCom;
               IpStringPositionIndex++;
            } else {
               wifiComIpAddress[IpStringPositionIndex] = '\0';
               sendUartMessage("IP address assigned correctly\r\n\r\n");
               wifiComState = WIFI_STATE_SEND_CIPMUX;
            }
         }
      break;

      case WIFI_STATE_SEND_CIPMUX:
         if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CIPMUX=1\r\n" );
            wifiComExpectedResponse = responseOk;
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIPMUX;
         }
      break;

      case WIFI_STATE_WAIT_CIPMUX:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPSERVER;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            sendUartMessage("AT+CIPMUX=1 command not ");
            sendUartMessage("responded correctly\r\n");
            wifiComState = WIFI_STATE_ERROR;
         }
      break;

      case WIFI_STATE_SEND_CIPSERVER:
         if (nonBlockingDelayRead(&wifiComDelay)) {
            wifiComStringWrite( "AT+CIPSERVER=1,80\r\n" );
            wifiComExpectedResponse = responseOk;
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIPSERVER;
         }
      break;

      case WIFI_STATE_WAIT_CIPSERVER:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_READ_GET;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
         sendUartMessage("AT+CIPSERVER=1,80 command not ");
         sendUartMessage("responded correctly\r\n");
         wifiComState = WIFI_STATE_ERROR;
         }
      break;

        // lectura de peticiones
      case WIFI_STATE_READ_GET:
        wifiComCharDispatcher();  // Detectar petición completa
        
        if (flagSolicitudHome) {
            flagSolicitudHome = false;
            currentConnectionId = lastConnectionId;
            wifiComWebPageDataUpdate();
            //printf("es home\n");
            wifiComState = WIFI_STATE_SEND_CIPSEND;
        } else if (flagHistRequest) {
            flagHistRequest = false;
            currentConnectionId = lastConnectionId;
            // pagina de datos historicos
            wifiComWebPageHistDataUpdate();
            wifiComState = WIFI_STATE_SEND_CIPSEND_HISTORY;
        }
        if (nonBlockingDelayRead(&wifiComDelay)) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            
         }
        break;

      case WIFI_STATE_SEND_CIPSEND:
         lengthOfHtmlCode = ( strlen(htmlCodeHeader) 
                               + strlen(htmlCodeBody) 
                               + strlen(htmlCodePreConfig) 
                               + strlen(htmlCodeParam) 
                               + strlen(htmlCodePostConfig) );
         sprintf( strToSend, "AT+CIPSEND=%c,%d\r\n", 
                  currentConnectionId, lengthOfHtmlCode );
         wifiComStringWrite( strToSend );
         wifiComState = WIFI_STATE_WAIT_CIPSEND;
         wifiComExpectedResponse = responseOk;
      break;

      case WIFI_STATE_SEND_CIPSEND_HISTORY:
         lengthOfHtmlCode = ( strlen(htmlCodeHistoryHeader) 
                               + strlen(htmlCodeHistoryBody) 
                               + strlen(htmlCodeHistoryFooter) );
         sprintf( strToSend, "AT+CIPSEND=%c,%d\r\n", 
                  currentConnectionId, lengthOfHtmlCode );
         wifiComStringWrite( strToSend );
         wifiComState = WIFI_STATE_WAIT_CIPSEND_HISTORY;
         wifiComExpectedResponse = responseOk;
      break;

      case WIFI_STATE_WAIT_CIPSEND:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_HTML;
            
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_READ_GET;
            //printf("cipsend a read\n");
         }
         //printf("cipsend\n");
      break;

      case WIFI_STATE_WAIT_CIPSEND_HISTORY:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_HTML_HISTORY;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_READ_GET;
         }
      break;

      case WIFI_STATE_SEND_HTML:
        wifiComStringWrite( htmlCodeHeader );
        wifiComStringWrite( htmlCodeBody );
        wifiComStringWrite( htmlCodePreConfig );
        wifiComStringWrite( htmlCodeParam );
        wifiComStringWrite( htmlCodePostConfig );
        wifiComState = WIFI_STATE_WAIT_HTML;
        wifiComExpectedResponse = responseSendOk;
      break;

      case WIFI_STATE_SEND_HTML_HISTORY:
        wifiComStringWrite( htmlCodeHistoryHeader );
        wifiComStringWrite( htmlCodeHistoryBody );
        wifiComStringWrite( htmlCodeHistoryFooter );
        wifiComState = WIFI_STATE_WAIT_HTML_HISTORY;
        wifiComExpectedResponse = responseSendOk;
      break;

      case WIFI_STATE_WAIT_HTML:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, 500);
            wifiComState = WIFI_STATE_SEND_CIPCLOSE;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPCLOSE;
         }
      break;

      case WIFI_STATE_WAIT_HTML_HISTORY:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, 500);
            wifiComState = WIFI_STATE_SEND_CIPCLOSE;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_SEND_CIPCLOSE;
         }
      break;

      case WIFI_STATE_SEND_CIPCLOSE:
         if (nonBlockingDelayRead(&wifiComDelay)) {
            sprintf( strToSend, "AT+CIPCLOSE=%c\r\n", currentConnectionId );
            wifiComStringWrite( strToSend );
            wifiComExpectedResponse  = responseCipclose;
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_WAIT_CIPCLOSE;
         }
      break;

      case WIFI_STATE_WAIT_CIPCLOSE:
         if (isExpectedResponse()) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_READ_GET;
         }
         if (nonBlockingDelayRead(&wifiComDelay)) {
            nonBlockingDelayWrite(&wifiComDelay, DELAY_5_SECONDS);
            wifiComState = WIFI_STATE_READ_GET;
         }
         //printf("%d\n",currentConnectionId);
      break;

      case WIFI_STATE_IDLE:
      case WIFI_STATE_ERROR:
      break;
   }
}

//=====[Implementations of private functions]==================================

bool wifiComCharRead( char* receivedChar )
{
    char receivedCharLocal = '\0';
    if( uartWifi.readable() ) {
        uartWifi.read(&receivedCharLocal,1);
        *receivedChar = receivedCharLocal;
        return true;
    }
    return false;
}

void wifiComStringWrite( const char* str )
{
    uartWifi.write( str, strlen(str) );
}

static bool isExpectedResponse()
{
   static int responseStringPositionIndex = 0;
   char charReceived;
   bool moduleResponse = false;

   if( wifiComCharRead(&charReceived) ){
      if (charReceived == wifiComExpectedResponse[responseStringPositionIndex]) {
         responseStringPositionIndex++;
         if (wifiComExpectedResponse[responseStringPositionIndex] == '\0') {
            responseStringPositionIndex = 0;
            moduleResponse = true;
         }
      } else {
         responseStringPositionIndex = 0;
      }
   }
   return moduleResponse;
}

void procesarCharParaRespuesta(char c) {
    static int pos = 0;

    if (c == wifiComExpectedResponse[pos]) {
        pos++;
        if (wifiComExpectedResponse[pos] == '\0') {
            pos = 0;
            wifiComFlagRespuesta = true;
        }
    } else {
        pos = 0;
    }
}


void wifiComCharDispatcher()
{
    char c;
    //printf("fd\n");
    if (wifiComCharRead(&c)) {
        //procesarCharParaRespuesta(c);  // como isExpectedResponse() pero sin leer
        procesarEntradaIPD(c);        // acumula +IPD si aparece
        //printf("%c",c);
    }
}

void procesarEntradaIPD(char c) {
    static enum { BUSCANDO_IPD, ACUMULANDO_LINEA } estado = BUSCANDO_IPD;
    static char ipdBuffer[512];
    static int index = 0;
    static char ventana[6] = {0};

    // Ventana deslizante para detectar "+IPD,"
    for (int i = 0; i < 4; ++i) {
        ventana[i] = ventana[i + 1];
    }
    ventana[4] = c;
    ventana[5] = '\0';

    switch (estado) {
        case BUSCANDO_IPD:
            if (strncmp(ventana, "+IPD,", 5) == 0) {
                estado = ACUMULANDO_LINEA;
                index = 0;
                strcpy(ipdBuffer, "+IPD,");
                index = strlen(ipdBuffer);
            }
            break;

        case ACUMULANDO_LINEA:
            if (index < sizeof(ipdBuffer) - 1) {
                ipdBuffer[index++] = c;

                if (c == '\n') {
                    ipdBuffer[index] = '\0';  // cerrar string

                    //printf("\r\n📨 Línea IPD detectada:\r\n%s", ipdBuffer);

                    // Extraer ID de conexión (por ejemplo de +IPD,0,...)
                    char* coma1 = strchr(ipdBuffer, ',');
                    if (coma1) {
                        lastConnectionId = *(coma1 + 1);
                    }

                    // Buscar tipo de solicitud
                    if (strstr(ipdBuffer, "GET / ") != NULL) {
                        flagSolicitudHome = true;
                        //printf("✅ Solicitud GET / detectada\r\n");
                    }

                    // 
                    if (strstr(ipdBuffer, "GET /historial") != NULL) {
                        flagHistRequest = true;
                        //printf("✅ Solicitud histo detectada\r\n");                        
                    }
                    // /set?alto=125&bajo=22&tag=huo
                    char* lineaGET = strstr(ipdBuffer, "GET /set?alto=");
                    if (lineaGET != NULL) {
                        flagSolicitudHome = true;
                        int alto = 0, bajo = 0;
                        char tag[100];
                        sscanf(lineaGET, "GET /set?alto=%d&bajo=%d&tag=%s", &alto, &bajo, tag);
                        low_limit = bajo;
                        high_limit = alto;
                        sprintf( tag_name, "%s", tag);
                        printf("Nuevos datos recibidos: Alto=%d, Bajo=%d, tag=%s\n", alto, bajo, tag); 
                    }

                    // Reiniciar
                    estado = BUSCANDO_IPD;
                    index = 0;
                }
            } else {
                // reiniciar
                estado = BUSCANDO_IPD;
                index = 0;
            }
            break;
    }
}


void wifiComWebPageDataUpdate()
{
    htmlCodeBody[0] = '\0';
    htmlCodeParam[0] = '\0';

    if(readingState){
        sprintf( htmlCodeBody, "%s BPM: %d %s", BEGIN_USER_LINE, (int)getBPM(), END_USER_LINE );
    
        if(alertaActiva){
            sprintf( htmlCodeBody + strlen(htmlCodeBody), "%s ", WARNING_THRESHOLD_LINE);
        }
    }
    else{
        sprintf( htmlCodeBody, "%s Sin lectura disponible %s", BEGIN_USER_LINE, END_USER_LINE );
    }

    sprintf( htmlCodeParam, "%s%d\"><br>", LABEL_HIGH_THRESHOLD, high_limit);
    sprintf( htmlCodeParam + strlen(htmlCodeParam), "%s%d\"><br>", LABEL_LOW_THRESHOLD, low_limit);
    sprintf( htmlCodeParam + strlen(htmlCodeParam), "%s%s\"><br>", LABEL_TAG, tag_name);
    
}

void wifiComWebPageHistDataUpdate()
{
    //"<tr><td>2025-06-17 22:30</td><td>65</td><td>Alberto</td></tr>"
    htmlCodeHistoryBody[0] = '\0';
    for (int i = 0; i < MAX_REG; i++) {
        int pos = (historialIndex + i) % MAX_REG;
        if (registers[pos].bpm != 0) {
            char row[350];
            snprintf(row, sizeof(row), "<tr><td>%s</td><td>%d</td><td>%s</td></tr>",
                    registers[pos].datetime, (int)registers[pos].bpm, registers[pos].tag);
            
            strcat(htmlCodeHistoryBody, row);
        }
    }
    //printf("%s\n", htmlCodeHistoryBody);
}
