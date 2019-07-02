const char* wifiSsid              = "xxx";
const char* wifiPassword          = "xxx";
const char* wifiHostname          = "pipeline-monitor";
const uint32_t deviceId           = ESP.getChipId();

const int   pinLedStatus          = BUILTIN_LED;
const int   pinLedExtern          = 2;

const char* otaHostName           = "pipeline-monitor";
const char* otaPassword           = "passwrd";
const int   otaPort               = 8266;

const char* mqttServer            = "mqtt.xxx.de";
const int   mqttPort              = 1883;
const char* mqttUsername          = "xxx";
const char* mqttPassword          = "xxx";
      char* mqttFeed              = "/pipelines/%s"; // %s will be replaced by the device id
const char* mqttWillTopic         = "offline";
const int   mqttQos               = 1;
const int   mqttRetain            = 0;

#define     ENABLE_DEEPSLEEP      false
