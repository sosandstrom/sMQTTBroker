/*!
Main class
*/
#ifndef SMQTTBROKER_FILE
#define SMQTTBROKER_FILE

#include"sMQTTplatform.h"
#include"sMQTTClient.h"
#include"sMQTTTopic.h"
#include"sMQTTEvent.h"

class sMQTTBroker
{
public:
	//! setup broker
	bool init(unsigned short port, bool checkWifiConnection=false);
	//! call in loop function
	void update();
	//! publish message
	void publish(const std::string &topic, const std::string &payload,unsigned char qos=0,bool retain=false);
	//! restart WIFI server
	void restart();
	//! receive event from broker
	virtual bool onEvent(sMQTTEvent *event) { return true; }

	SMQTT_DEPRECATED("onConnect is deprecated, use onEvent") virtual bool onConnect(sMQTTClient *client, const std::string &username, const std::string &password) { return true; };
	SMQTT_DEPRECATED("onRemove is deprecated, use onEvent") virtual void onRemove(sMQTTClient*) {};
	SMQTT_DEPRECATED("onPublish is deprecated, use onEvent") virtual void onPublish(sMQTTClient *client, const std::string &topic, const std::string &payload) {};
	bool isClientConnected(sMQTTClient *client);
	void updateRetainedTopic(sMQTTTopic *topic);
	void publish(sMQTTClient *client, sMQTTTopic *topic, sMQTTMessage *msg);
	bool subscribe(sMQTTClient *client, const char *topic);
	void unsubscribe(sMQTTClient *client, const char *topic);
private:
	// inner function


	bool isTopicValidName(const char *filter);

private:
	void findRetainTopic(sMQTTTopic *topic, sMQTTClient *client);

	TCPServer *_server;
	sMQTTClientList clients;
	sMQTTTopicList subscribes, retains;
	bool isCheckWifiConnection;
};
#endif