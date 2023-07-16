#pragma once
#ifndef _MESSAGER_H_
#define _MESSAGER_H_

class Messager
{
public:
	static enum MESSAGE
	{
		REDWIN,
		GREENWIN,
		RESTART,
		EXPLODE,
		HITYOU,
	};
	virtual void Receive(MESSAGE message) = 0;

	template<typename... Args>
	void Send(MESSAGE message, Messager* receiver, Args... args);
	void Send(MESSAGE message) {}
};

template<typename... Args>
void Messager::Send(MESSAGE message, Messager* receiver, Args... args)
{
	receiver->Receive(message);
	Send(message, args...);
}

#endif