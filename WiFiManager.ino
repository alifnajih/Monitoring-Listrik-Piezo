void startAP()
{
    WiFi.mode(WIFI_AP);

    WiFi.softAP(AP_SSID, AP_PASS);

    apMode = true;
    wifiConnected = false;

    ipAddress = WiFi.softAPIP().toString();

    Serial.println("================================");
    Serial.println("AP MODE");
    Serial.print("SSID : ");
    Serial.println(AP_SSID);

    Serial.print("IP   : ");
    Serial.println(ipAddress);
}

void connectWiFi(String ssid, String pass)
{
    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid.c_str(), pass.c_str());

    Serial.print("Connecting");

    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED &&
           millis() - start < 15000)
    {
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        wifiConnected = true;
        apMode = false;

        ipAddress = WiFi.localIP().toString();

        Serial.println();
        Serial.println("CONNECTED");

        Serial.print("IP : ");
        Serial.println(ipAddress);
    }
    else
    {
        Serial.println();
        Serial.println("FAILED");

        startAP();
    }
}

void initWiFi()
{
    prefs.begin("wifi", true);

    String ssid = prefs.getString("ssid", "");
    String pass = prefs.getString("pass", "");

    prefs.end();

    if (ssid == "")
    {
        Serial.println("No WiFi Saved");

        startAP();

        return;
    }

    connectWiFi(ssid, pass);
}