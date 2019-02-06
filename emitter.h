#ifndef EMITTER_H
#define EMITTER_H

#include <string>
#include "console.h"

class Emitter
{
public:
	virtual void emit(std::string& str)
	{
		str += m_emit_text + "\n";
	}

	void setText(std::string str) { m_emit_text = str; }
private:
	std::string m_emit_text = "POW!";
};

#endif