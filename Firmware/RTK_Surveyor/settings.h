//System can enter a variety of states starting at Rover_No_Fix at power on
typedef enum
{
  STATE_ROVER_NOT_STARTED = 0,
  STATE_ROVER_NO_FIX,
  STATE_ROVER_FIX,
  STATE_ROVER_RTK_FLOAT,
  STATE_ROVER_RTK_FIX,
  STATE_BASE_NOT_STARTED,
  STATE_BASE_TEMP_SETTLE, //User has indicated base, but current pos accuracy is too low
  STATE_BASE_TEMP_SURVEY_STARTED,
  STATE_BASE_TEMP_TRANSMITTING,
  STATE_BASE_TEMP_WIFI_STARTED,
  STATE_BASE_TEMP_WIFI_CONNECTED,
  STATE_BASE_TEMP_CASTER_STARTED,
  STATE_BASE_TEMP_CASTER_CONNECTED,
  STATE_BASE_FIXED_NOT_STARTED,
  STATE_BASE_FIXED_TRANSMITTING,
  STATE_BASE_FIXED_WIFI_STARTED,
  STATE_BASE_FIXED_WIFI_CONNECTED,
  STATE_BASE_FIXED_CASTER_STARTED,
  STATE_BASE_FIXED_CASTER_CONNECTED,
} SystemState;
volatile SystemState systemState = STATE_ROVER_NOT_STARTED;

typedef enum
{
  RTK_SURVEYOR = 0,
  RTK_EXPRESS,
} ProductVariant;
ProductVariant productVariant = RTK_SURVEYOR;

typedef enum
{
  BUTTON_ROVER = 0,
  BUTTON_BASE,
  BUTTON_PRESSED,
  BUTTON_RELEASED,
} ButtonState;
ButtonState buttonPreviousState = BUTTON_ROVER;
ButtonState setupButtonState = BUTTON_RELEASED; //RTK Express Setup Button

//Data port mux (RTK Express) can enter one of four different connections
typedef enum muxConnectionType_e
{
  MUX_UBLOX_NMEA = 0,
  MUX_PPS_EVENTTRIGGER,
  MUX_I2C,
  MUX_ADC_DAC,
} muxConnectionType_e;

//User can enter fixed base coordinates in ECEF or degrees
typedef enum
{
  COORD_TYPE_ECEF = 0,
  COORD_TYPE_GEOGRAPHIC,
} coordinateType_e;

//Freeze and blink LEDs if we hit a bad error
typedef enum
{
  ERROR_NO_I2C = 2, //Avoid 0 and 1 as these are bad blink codes
  ERROR_GPS_CONFIG_FAIL,
} t_errorNumber;

//Radio status LED goes from off (LED off), no connection (blinking), to connected (solid)
enum RadioState
{
  RADIO_OFF = 0,
  BT_ON_NOCONNECTION, //WiFi is off
  BT_CONNECTED,
  WIFI_ON_NOCONNECTION, //BT is off
  WIFI_CONNECTED,
};
volatile byte radioState = RADIO_OFF;

//Return values for getByteChoice()
enum returnStatus {
  STATUS_GETBYTE_TIMEOUT = 255,
  STATUS_GETNUMBER_TIMEOUT = -123455555,
  STATUS_PRESSED_X = 254,
};

//These are the allowable messages to either broadcast over SPP or log to UBX file
struct gnssMessages
{
  bool gga = true;
  bool gsa = true;
  bool gsv = true;
  bool rmc = true;
  bool gst = true;
  bool rawx = false;
  bool sfrbx = false;
};

//This is all the settings that can be set on RTK Surveyor. It's recorded to NVM and the config file.
struct struct_settings {
  int sizeOfSettings = 0; //sizeOfSettings **must** be the first entry and must be int
  int rtkIdentifier = RTK_IDENTIFIER; // rtkIdentifier **must** be the second entry
  bool printDebugMessages = false;
  bool enableSD = true;
  bool enableDisplay = true;
  bool frequentFileAccessTimestamps = false;
  int maxLogTime_minutes = 60*10; //Default to 10 hours
  int observationSeconds = 60; //Default survey in time of 60 seconds
  float observationPositionAccuracy = 5.0; //Default survey in pos accy of 5m
  bool fixedBase = false; //Use survey-in by default
  bool fixedBaseCoordinateType = COORD_TYPE_ECEF;
  double fixedEcefX = 0.0;
  double fixedEcefY = 0.0;
  double fixedEcefZ = 0.0;
  double fixedLat = 0.0;
  double fixedLong = 0.0;
  double fixedAltitude = 0.0;
  uint32_t dataPortBaud = 115200; //Default to 115200bps
  uint32_t radioPortBaud = 57600; //Default to 57600bps to support connection to SiK1000 radios
  bool enableSBAS = false; //Bug in ZED-F9P v1.13 firmware causes RTK LED to not light when RTK Floating with SBAS on.
  bool enableNtripServer = false;
  char casterHost[50] = "rtk2go.com"; //It's free...
  uint16_t casterPort = 2101;
  char mountPoint[50] = "bldr_dwntwn2";
  char mountPointPW[50] = "WR5wRo4H";
  char wifiSSID[50] = "TRex";
  char wifiPW[50] = "parachutes";
  float surveyInStartingAccuracy = 1.0; //Wait for 1m horizontal positional accuracy before starting survey in
  uint16_t measurementRate = 250; //Elapsed ms between GNSS measurements. 25ms to 65535ms. Default 4Hz.
  uint16_t navigationRate = 1; //Ratio between number of measurements and navigation solutions. Default 1 for 4Hz (with measurementRate).
  gnssMessages broadcast;
  gnssMessages log;
  bool enableI2Cdebug = false; //Turn on to display GNSS library debug messages
  bool enableHeapReport = false; //Turn on to display free heap
  muxConnectionType_e dataPortChannel = MUX_UBLOX_NMEA; //Mux default to ublox UART1
} settings;

//These are the devices on board RTK Surveyor that may be on or offline.
struct struct_online {
  bool microSD = false;
  bool display = false;
  bool gnss = false;
  bool logging = false;
  bool serialOutput = false;
  bool eeprom = false;
  bool rtc = false;
  bool battery = false;
  bool accelerometer = false;
} online;
