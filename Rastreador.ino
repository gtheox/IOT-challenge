#include "display/DisplayLoRa.h"
#include <HardwareSerial.h>
#include <TinyGPS++.h>

// Comunicação serial com o módulo A9G (GPS e GSM)
HardwareSerial A9G(1);

// Objeto para decodificar informações de GPS
TinyGPSPlus gps;
// Objeto do Display LoRa para exibição
DisplayLoRa Display;

// Pinos para comunicação serial
const int RX_PIN = 23;
const int TX_PIN = 22;

// Pino do botão de configuração
const int btnConf = 37;

// --- CONFIGURAÇÕES DA REDE E SERVIDOR ---
String APN = "claro.com.br"; // APN da operadora do seu chip. Ex: claro.com.br,

String SERVER_IP =
    "192.168.15.108";        // SUBSTITUA PELO IP DO SEU MAC NA REDE WI-FI
String SERVER_PORT = "5012"; // A porta HTTP da sua API .NET
String MOTO_ID_PARA_TESTE =
    "1"; // ID da moto que vamos atualizar para este teste

// URL final montada
String SERVER_URL = "http://" + SERVER_IP + ":" + SERVER_PORT + "/api/motos/" +
                    MOTO_ID_PARA_TESTE + "/localizacao";

// Variáveis para controle do tempo
long prevMillis;
bool updateMillis = true;
long prevSendMillis = 0;
const int intervalSend = 30000; // Intervalo entre envios (30 segundos)

// Exibe mensagens no Serial e no Display
void printMsg(String msg, bool clear) {
  Serial.println(msg);
  Display.println(msg, clear);
}

// Função de timeout sem utilizar delay()
bool timeout(const int DELAY, long *millisAnterior, bool *flag) {
  if (*flag) {
    *millisAnterior = millis();
    *flag = false;
  }
  return ((*millisAnterior + DELAY) < millis()) ? (*flag = true) : false;
}

// Envia comandos AT para o módulo A9G e espera resposta
bool sendToA9G(String cmd, String *response, int timeoutWait = 3000) {
  *response = "";
  A9G.println(cmd);
  updateMillis = true;
  while (!timeout(timeoutWait, &prevMillis, &updateMillis)) {
    if (A9G.available()) {
      *response = A9G.readString();
      return true;
    }
  }
  return false;
}

// Configura o módulo A9G para uso do GPS
void A9config() {
  String response;
  while (response.indexOf("OK") < 0) {
    printMsg("Enviando AT", true);
    if (!sendToA9G("AT", &response))
      printMsg("Sem resposta...", true);
    else
      printMsg("Resposta: " + response, true);
  }
  sendToA9G("AT+GPS=1", &response);
  sendToA9G("AT+GPSRD=1", &response);
}

// Inicializa conexão GPRS para envio HTTP
bool setupGPRS() {
  String response;
  sendToA9G("AT+CGATT=1", &response);
  sendToA9G("AT+CGDCONT=1,\"IP\",\"" + APN + "\"", &response);
  sendToA9G("AT+CGACT=1,1", &response);
  return response.indexOf("OK") >= 0;
}

// Envia as coordenadas GPS para o servidor via HTTP POST
bool sendHTTPPost(float lat, float lng) {
  String response;
  // Monta o JSON exatamente como o nosso DTO na API espera
  String data = "{\"latitude\":" + String(lat, 6) +
                ",\"longitude\":" + String(lng, 6) + "}";

  sendToA9G("AT+HTTPINIT", &response);
  sendToA9G("AT+HTTPPARA=\"URL\",\"" + SERVER_URL + "\"", &response);
  sendToA9G("AT+HTTPPARA=\"CONTENT\",\"application/json\"", &response);
  sendToA9G("AT+HTTPDATA=" + String(data.length()) + ",10000", &response);
  delay(100);
  A9G.print(data);
  delay(500);

  sendToA9G("AT+HTTPACTION=1", &response, 6000); // 1 = POST

  // Verifica se a resposta da API foi "204 No Content", que é o nosso código de
  // sucesso
  bool success = response.indexOf("204") >= 0;

  sendToA9G("AT+HTTPTERM", &response);
  return success;
}

// Configuração inicial do dispositivo
void setup() {
  A9G.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  Serial.begin(115200);
  Display.begin();
  pinMode(btnConf, INPUT);
  printMsg("Inicializando...", true);

  updateMillis = true;
  while (!timeout(5000, &prevMillis, &updateMillis)) {
    if (digitalRead(btnConf)) {
      A9config();
      break;
    }
  }

  while (A9G.available() > 0)
    A9G.read();

  printMsg("Setup GPRS...", true);
  if (setupGPRS()) {
    printMsg("GPRS OK!", false);
  } else {
    printMsg("GPRS Falhou!", false);
  }
}

// Loop principal: recebe dados do GPS e envia localização periodicamente
void loop() {
  while (A9G.available() > 0)
    if (gps.encode(A9G.read()))
      displayInfo();

  if (millis() - prevSendMillis > intervalSend && gps.location.isValid()) {
    prevSendMillis = millis();

    printMsg("Enviando Local...", true);
    if (sendHTTPPost(gps.location.lat(), gps.location.lng())) {
      printMsg("Localizacao enviada!", false);
    } else {
      printMsg("Erro ao enviar!", false);
    }
  }
}

// Exibe as informações recebidas do GPS
void displayInfo() {
  char location[30], date[30], time[30];
  if (gps.location.isValid())
    sprintf(location, "%.6f,%.6f", gps.location.lat(), gps.location.lng());
  else
    strcpy(location, "INVALID");

  if (gps.date.isValid() && gps.time.isValid()) {
    uint8_t day, month, hours;
    uint16_t year;
    day = gps.date.day();
    month = gps.date.month();
    year = gps.date.year();
    hours = gps.time.hour();
    applyTimeZone(-3, &day, &month, &year, &hours);
    sprintf(date, "%02d/%02d/%02d", day, month, year);
    sprintf(time, "%02d:%02d:%02d", hours, gps.time.minute(),
            gps.time.second());
  } else {
    strcpy(date, "INVALID");
    strcpy(time, "INVALID");
  }
  printMsg("Location: " + String(location), true);
  printMsg("Date: " + String(date), false);
  printMsg("Time: " + String(time), false);
}

// Ajusta horário UTC para fuso local
void applyTimeZone(int8_t delta, uint8_t *day, uint8_t *month, uint16_t *year,
                   uint8_t *hours) {
  if (delta < 0) {
    if (int8_t(*hours) < -delta) {
      *hours += 24 + delta;
      if (--*day == 0) {
        if (--*month == 0) {
          *month = 12;
          *year--;
        }
        *day = getMonthLength(*month, *year);
      }
    } else
      *hours += delta;
  } else {
    *hours += delta;
    if (*hours > 23) {
      *hours -= 24;
      if (++*day > getMonthLength(*month, *year)) {
        *day = 1;
        if (++*month > 12) {
          *month = 1;
          *year++;
        }
      }
    }
  }
}

// Retorna a quantidade de dias do mês
uint8_t getMonthLength(uint8_t month, uint16_t year) {
  if (month == 2)
    return (year % 4 == 0) ? 29 : 28;
  if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
    return 30;
  return 31;
}