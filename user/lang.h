#ifndef _LANG_
#define _LANG_

#include "mqtt/mqtt_server.h"

typedef enum {SYNTAX_CHECK, CONFIG, INIT, MQTT_CLIENT_CONNECT, WIFI_CONNECT, WIFI_DISCONNECT, TOPIC_LOCAL, TOPIC_REMOTE, TIMER, SERIAL_INPUT, GPIO_INT, ALARM, HTTP_RESPONSE} Interpreter_Status;
typedef enum {STRING_T, DATA_T} Value_Type;

typedef struct _var_entry_t {
    uint8_t name[15];
    uint8_t free;
    uint32_t buffer_len;
    uint8_t *data;
    uint32_t data_len;
    Value_Type data_type;
} var_entry_t;
extern var_entry_t vars[];

extern MQTT_Client mqttClient;
extern bool mqtt_enabled, mqtt_connected;
extern bool lang_logging;

uint8_t tmp_buffer[128];
uint32_t loop_time;
uint32_t loop_count;

int text_into_tokens(char *str);
void free_tokens(void);
bool is_token(int i, char *s);
int search_token(int i, char *s);
int syntax_error(int i, char *message);

int parse_statement(int next_token);
int parse_event(int next_token, bool *happened);
int parse_action(int next_token, bool doit);
int parse_expression(int next_token, char **data, int *data_len, Value_Type * data_type, bool doit);
int parse_value(int next_token, char **data, int *data_len, Value_Type *data_type);

extern bool script_enabled;
int interpreter_syntax_check();
int interpreter_config();
int interpreter_init();
int interpreter_mqtt_connect(void);
int interpreter_wifi_connect(void);
int interpreter_wifi_disconnect(void);
int interpreter_topic_received(const char *topic, const char *data, int data_len, bool local);
int interpreter_serial_input(const char *data, int data_len);

void init_timestamps(uint8_t *curr_time);
void check_timestamps(uint8_t *curr_time);

void init_gpios();
void stop_gpios();

#endif /* _LANG_ */
