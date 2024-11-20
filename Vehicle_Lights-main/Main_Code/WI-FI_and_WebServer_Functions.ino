



void WI_FI_Init() {
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void Server_Init() {

  server.on("/", []() { //defines a route handler for the web server at the root URL ("/").
    server.send(200, "text/html", html);
    init_WebPage();
  });
  //#####################################################
  server.begin();     // staring server
  webSocket.begin();  // starting websocket
  webSocket.onEvent(webSocketEvent);
}


// the callback for handling incoming data
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload,
                    size_t length) {
  // if a new websocket connection is established
  if (type == WStype_CONNECTED) {
    IPAddress ip = webSocket.remoteIP(num);

    webSocket.sendTXT(num, "Websocket established!");  // send status message
    Serial.println("New client connected! Num: " + String(num));
    init_WebPage();
  }
  // if new text data is received
  if (type == WStype_TEXT) {
    Serial.printf("Client[%u] Received: %s\n", num, payload);
    messageHandler(num, payload, length);
  }
}

void init_WebPage() {
  String sendData;
  sendData = "M_" + String(NUM_LEDS_L);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "N_" + String(NUM_LEDS_R);
  webSocket.broadcastTXT(sendData);
  delay(10);
  if (freq_L == NEO_KHZ800) {
    sendData = "T_1";
    webSocket.broadcastTXT(sendData);
  } else {
    sendData = "T_0";
    webSocket.broadcastTXT(sendData);
  }
  delay(10);
  if (freq_R == NEO_KHZ800) {
    sendData = "U_1";
    webSocket.broadcastTXT(sendData);
  } else {
    sendData = "U_0";
    webSocket.broadcastTXT(sendData);
  }
  delay(10);
  switch (scheme_L) {
    case NEO_GRBW:
      sendData = "V_1";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_RGBW:
      sendData = "V_2";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_BRGW:
      sendData = "V_3";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_GRB:
      sendData = "V_4";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_RGB:
      sendData = "V_5";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_BRG:
      sendData = "V_6";
      webSocket.broadcastTXT(sendData);
      break;
  }
  delay(10);
  switch (scheme_R) {
    case NEO_GRBW:
      sendData = "W_1";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_RGBW:
      sendData = "W_2";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_BRGW:
      sendData = "W_3";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_GRB:
      sendData = "W_4";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_RGB:
      sendData = "W_5";
      webSocket.broadcastTXT(sendData);
      break;
    case NEO_BRG:
      sendData = "W_6";
      webSocket.broadcastTXT(sendData);
      break;
  }
  delay(10);
  sendData = "X_" + String(Strobe);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "B_" + String(map(brightness, 0, 255, 0, 100));
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "D_" + String(duration / 1000);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "J_" + String(BlinkerLEDs);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "K_" + String(BlinkerSpeed);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "Y_" + String(strip_select);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "F_" + ColorString(leftColor);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "G_" + ColorString(RightColor);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "H_" + ColorString(DRLColor);
  webSocket.broadcastTXT(sendData);
  delay(10);
  sendData = "I_" + ColorString(BrakeColor);
  webSocket.broadcastTXT(sendData);
  delay(20);
}


void messageHandler(uint8_t num, uint8_t *payload, size_t length) {
  String getData;
  String sendData;
  String getColor;

  for (int i = 0; i < length; i++) {
    if (!isdigit(payload[i])) continue;
    getData += (char)payload[i];
  }
  if (payload[0] == 'F' || payload[0] == 'G' || payload[0] == 'H' || payload[0] == 'I' || payload[0] == 'Z') {
    for (int i = 2; i < length; i++) {
      getColor += (char)payload[i];
    }
  }
  switch (payload[0]) {
      // LeftblinkerEffects
    case 'a':
      BlinkerAnimation = getData.toInt();
      Serial.print("Received Blinker Animation type: ");
      Serial.println(getData);

      // Add this line for debugging
      sendData = "a_" + getData;
      webSocket.broadcastTXT(sendData);

      // Display a message in the serial monitor
      Serial.print("Blinker Animation type changed to: ");

      if (BlinkerAnimation == 1) {
        Serial.println("Heartbeat");
      } else if (BlinkerAnimation == 2) {
        Serial.println("Sequential");
      } else if (BlinkerAnimation == 3) {
        Serial.println("Blinker");
      } else if (BlinkerAnimation == 4) {
        Serial.println("Solid Sequential");
      } else {
        Serial.println("Unknown Animation Type");
      }

      break;

      // no of LEDS Left
    case 'M':
      NUM_LEDS_L = getData.toInt();
      Serial.println(getData);
      sendData = "M_" + getData;
      webSocket.broadcastTXT(sendData);
      updateConfig_L();
      break;
    // no of LEDS Right
    case 'N':
      NUM_LEDS_R = getData.toInt();
      Serial.println(getData);
      sendData = "N_" + getData;
      webSocket.broadcastTXT(sendData);
      updateConfig_R();
      break;
    // frequncy Left Strip
    case 'T':
      freq_select = getData.toInt();
      Serial.println(getData);
      sendData = "T_" + getData;
      webSocket.broadcastTXT(sendData);
      if (freq_select)
        freq_L = NEO_KHZ800;  // 800KHz
      else
        freq_L = NEO_KHZ400;  // 400KHz
      updateConfig_L();
      break;
    // frequency Right Strip
    case 'U':
      freq_select = getData.toInt();
      Serial.println(getData);
      sendData = "U_" + getData;
      webSocket.broadcastTXT(sendData);
      if (freq_select)
        freq_R = NEO_KHZ800;  // 800KHz
      else
        freq_R = NEO_KHZ400;  // 400KHz
      updateConfig_R();
      break;
    // Color Scheme Select for left Strip
    case 'V':
      scheme_select = getData.toInt();
      Serial.println(getData);
      switch (scheme_select) {
        case 1:
          scheme_L = NEO_GRBW;
          break;
        case 2:
          scheme_L = NEO_RGBW;
          break;
        case 3:
          scheme_L = NEO_BRGW;
          break;
        case 4:
          scheme_L = NEO_RGB;
          break;
        case 5:
          scheme_L = NEO_GRB;
          break;
        case 6:
          scheme_L = NEO_BRG;
          break;
      }
      updateConfig_L();
      sendData = "V_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    case 'W':
      scheme_select = getData.toInt();
      Serial.println(getData);
      switch (scheme_select) {
        case 1:
          scheme_R = NEO_GRBW;
          break;
        case 2:
          scheme_R = NEO_RGBW;
          break;
        case 3:
          scheme_R = NEO_BRGW;
          break;
        case 4:
          scheme_R = NEO_RGB;
          break;
        case 5:
          scheme_R = NEO_GRB;
          break;
        case 6:
          scheme_R = NEO_BRG;
          break;
      }
      updateConfig_R();
      sendData = "W_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    case 'X':
      Strobe = getData.toInt();
      Serial.println(getData);
      sendData = "X_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    case 'Y':
      strip_select = getData.toInt();
      Serial.println(getData);
      sendData = "Y_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    // left strip color
    case 'F':
      rgbColor = (int)strtol(&getColor[0], NULL, 16);
      Red = rgbColor >> 16;
      Green = rgbColor >> 8 & 0xFF;
      Blue = rgbColor & 0xFF;
      hexColor = ((Red << 16) & 0xFF0000) | ((Green << 8) & 0x00FF00) | (Blue & 0x0000FF);
      hexColorStr[8];
      col = converter.RGBToRGBW(Red, Green, Blue);
      leftColor = leds_L->Color(col.r, col.g, col.b, col.w);
      Serial.println(getData);
      //sendData = "F_" + ColorString(leftColor);
      
      sprintf(hexColorStr, "#%06X", hexColor);  // Format hex color
      sendData = "F_" + String(hexColorStr); 
      webSocket.broadcastTXT(sendData);
      break;
      // extra strip color
    case 'Z':
      rgbColor = (int)strtol(&getColor[0], NULL, 16);
      Red = rgbColor >> 16;
      Green = rgbColor >> 8 & 0xFF;
      Blue = rgbColor & 0xFF;
      hexColor = ((Red << 16) & 0xFF0000) | ((Green << 8) & 0x00FF00) | (Blue & 0x0000FF);
      hexColorStr[8];
      col = converter.RGBToRGBW(Red, Green, Blue);
      thrdColor = leds_L->Color(col.r, col.g, col.b, col.w);
      Serial.println(getData);
      sprintf(hexColorStr, "#%06X", hexColor);  // Format hex color
      sendData = "Z_" + String(hexColorStr);
      webSocket.broadcastTXT(sendData);
      break;
    // right strip color
    case 'G':
      rgbColor = (int)strtol(&getColor[0], NULL, 16);
      Red = rgbColor >> 16;
      Green = rgbColor >> 8 & 0xFF;
      Blue = rgbColor & 0xFF;
      hexColor = ((Red << 16) & 0xFF0000) | ((Green << 8) & 0x00FF00) | (Blue & 0x0000FF);
      hexColorStr[8];
      col = converter.RGBToRGBW(Red, Green, Blue);
      RightColor = leds_L->Color(col.r, col.g, col.b, col.w);
      Serial.println(getData);
      sprintf(hexColorStr, "#%06X", hexColor);  // Format hex color
      sendData = "G_" + String(hexColorStr);
      // sendData = "G_" + ColorString(RightColor);
      webSocket.broadcastTXT(sendData);
      break;
    // DRL Color
    case 'H':
      rgbColor = (int)strtol(&getColor[0], NULL, 16);
      Red = rgbColor >> 16;
      Green = rgbColor >> 8 & 0xFF;
      Blue = rgbColor & 0xFF;
      hexColor = ((Red << 16) & 0xFF0000) | ((Green << 8) & 0x00FF00) | (Blue & 0x0000FF);
      hexColorStr[8];
      col = converter.RGBToRGBW(Red, Green, Blue);
      DRLColor = leds_L->Color(col.r, col.g, col.b, col.w);
      Serial.println(getData);
      sprintf(hexColorStr, "#%06X", hexColor);  // Format hex color
      sendData = "H_" + String(hexColorStr);
      //sendData = "H_" + ColorString(DRLColor);
      webSocket.broadcastTXT(sendData);
      break;
    case 'I':
      rgbColor = (int)strtol(&getColor[0], NULL, 16);
      Red = rgbColor >> 16;
      Green = rgbColor >> 8 & 0xFF;
      Blue = rgbColor & 0xFF;
      hexColor = ((Red << 16) & 0xFF0000) | ((Green << 8) & 0x00FF00) | (Blue & 0x0000FF);
      hexColorStr[8];
      col = converter.RGBToRGBW(Red, Green, Blue);
      BrakeColor = leds_L->Color(col.r, col.g, col.b, col.w);
      Serial.println(getData);
      sprintf(hexColorStr, "#%06X", hexColor);  // Format hex color
      sendData = "I_" + String(hexColorStr);
      //sendData = "I_" + ColorString(BrakeColor);
      webSocket.broadcastTXT(sendData);
      break;
    case 'J':
      BlinkerLEDs = getData.toInt();
      Serial.println(getData);
      sendData = "J_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    case 'K':
      BlinkerSpeed = getData.toInt();
      Serial.println(getData);
      sendData = "K_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    case 'S':
      SaveConfig();
      webSocket.broadcastTXT("S_1");
      break;
    // effect
    case 'E':
      isPlay = true;
      effect = getData.toInt();
      Serial.println(getData);

      currentEffect =
        getData.toInt() - 1;  // so that the loop starts from the current one

      sendData = "E_" + getData;
      webSocket.broadcastTXT(sendData);

      setEffect(effect);
      break;
    // brightness
    case 'B':
      Serial.println(getData);
      brightness = map(getData.toInt(), 0, 100, 0, 255);

      sendData = "B_" + getData;
      webSocket.broadcastTXT(sendData);

      leds_L->setBrightness(brightness);
      leds_R->setBrightness(brightness);
      leds_3->setBrightness(brightness);
      break;
    // duration
    case 'D':
      Serial.println(getData);
      duration = (getData.toInt() * 100);

      sendData = "D_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    // play
    case 'P':
      if (getData == "1") {
        isPlay = true;
        if (effect == 0) {
          effect = 1;
        }
        sendData = "E_" + String(effect, DEC);
        webSocket.broadcastTXT(sendData);
        setEffect(effect);
      } else {
        isPlay = false;
      }
      sendData = "P_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    // loop
    case 'L':
      if (getData == "1") {
        isPlay = true;
        isLoopEffect = true;
        isRandom = false;
      } else {
        isLoopEffect = false;
      }
      sendData = "L_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
    // random
    case 'R':
      if (getData == "1") {
        isPlay = true;
        isLoopEffect = false;
        isRandom = true;
      } else {
        isRandom = false;
      }
      sendData = "R_" + getData;
      webSocket.broadcastTXT(sendData);
      break;
  }
  Serial.println("Sent: " + sendData);
}


void playEffects() {
  // effects handling
  if (isPlay == true) {
    String sendData;
    if (isLoopEffect) {
      if ((millis() - lastChange) > duration) {
        setFavEffects(favEffects, numFavEffects);

        sendData = "E_" + String(currentEffect, DEC);
        webSocket.broadcastTXT(sendData);
        Serial.println("Sent: " + sendData);
      }
    }
    if (isRandom) {
      if ((millis() - lastChange) > duration) {
        lastChange = millis();
        effect = favEffects[random(0, numFavEffects - 1)];
        currentEffect = effect - 1;

        sendData = "E_" + String(effect, DEC);
        webSocket.broadcastTXT(
          sendData);  // send the number of the current effect
        Serial.println("Sent: " + sendData);
      }
    }
    setEffect(effect);
  } else
    fadeall();
}