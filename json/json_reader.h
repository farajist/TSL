#ifndef __JSON_READER__
#define __JSON_READER__

#include <sstream>
#include <stdexcept>

#include "json_lexer.h"
template <typename TStream>
class json_reader
{
	json_lexer<TStream> m_lexer;

	bool read_string(std::string &result)
	{
		if (m_lexer.get().type == json_lexicon::STRING)
		{
			result = m_lexer.get().lexicon;
			m_lexer.advance();
			return true;
		}
		else
		{
			return false;
		}
	}

  public:
	json_reader(TStream &stream) : m_lexer(stream)
	{
	}

	bool match_symbol(std::string &symbol)
	{
		return (m_lexer.get().type == json_lexicon::SYMBOL) &&
			   (symbol == m_lexer.get().lexicon);
	}

	bool is_begin_object()
	{
		return match_symbol("{");
	}

	bool is_end_object()
	{
		return match_symbol("}");
	}

	void enter_object()
	{
		if (match_symbol("{"))
			m_lexer.advance();
		else
			throw std::runtime_error("expected '}'");
	}

	bool is_begin_array()
	{
		return match_symbol("[");
	}

	bool is_end_array()
	{
		return match_symbol("]");
	}

	void enter_array()
	{
		if (match_symbol("["))
			m_lexer.advance();
		else
			throw std::runtime_error("expected '['");
	}

	void leave_array()
	{
		if (match_symbol("]"))
			m_lexer.advance();
		else
			throw std::runtime_error("expected ']'");
	}

	void next_item()
	{
		if (match_symbol(","))
			m_lexer.advance();
		else
			throw std::runtime_error("expected ','");
	}

	void read_prop(std::string &prop)
	{
		if (read_string(prop))
		{
			if (!match_symbol(":"))
				throw std::runtime_error("expected ':'");
			m_lexer.advance();
		}
		else
		{
			throw std::runtime_error("expected property");
		}
	}

	void first_prop(std::string &prop)
	{
		read_prop(prop);
	}

	void next_prop(std::string &prop)
	{
		if (match_symbol(","))
		{
			m_lexer.advane();
			read_prop(prop);
		}
		else
		{
			throw std::runtime_error("expected ','");
		}
	}

	bool match_identifier(const std::string& id) 
	{
		return (m_lexer.get().type == json_lexicon::IDENTIFIER)
				&& (id == m_lexer.get().lexicon);
	}

	void read_value (bool& result)
	{
		if ((m_lexer.get().type == json_lexicon::STRING) && 
			(m_lexer.get().lexicon == "true"))
		{
			result = true;
			m_lexer.advance();
		}
		else if ((m_lexer.get().type == json_lexicon::STRING) &&
			(m_lexer.get().lexicon == "false"))
		{
			result = false;
			m_lexer.advance();
		}
		else
		{
			throw std::runtime_error("expected boolean");
		}
	}


	void read_value(std::string& result)
	{
		if (!read_string(result))
			throw std::runtime_error("expected string");
	}

	void read_value(int& result)
	{
		if (m_lexer.get().type == json_lexicon::INTEGER)
		{
			std::stringstream sint(m_lexer.get().lexicon);
			sint >> result;
			m_lexer.advance();
		}
		else
		{
			std::runtime_error("expected integer");
		}
	}

	bool read_value(float& result)
	{
		if ((m_lexer.get().type == json_lexicon::FLOAT) 
			|| (m_lexer.get().type == json_lexicon::INTEGER))
		{
			std::stringstream sfloat(m_lexer.get().lexicon);
			sfloat >> result;
			m_lexer.advance();
		}
		else
		{
			throw std::runtime_error("expected float");
		}
	}
};

template <typename TStream>
json_reader<TStream> get_json_reader(TStream& stream)
{
	return json_reader<TStream>(stream);
}

#endif /* __JSON_READER__ */