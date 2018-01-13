#ifndef __JSON_LEXER__
#define __JSON_LEXER__

#include <string>
#include <stdexcept>

class json_lexicon
{
  public:
	enum lexicon_type
	{
		SYMBOL,
		INTEGER,
		FLOAT,
		STRING,
		IDENTIFIER,
		END
	} type;
	std::string lexicon;
};
template <typename TStream>
class json_lexer
{
	TStream &m_stream;
	json_lexicon next_lex;
	int n_line;

	char next()
	{
		if (m_stream.eof())
		{
			throw std::runtime_error("end of file");
		}
		m_stream.get();
		return m_stream.peek();
	}

	void read()
	{
		next_lex.lexicon = "";
		if (m_stream.eof())
		{
			next_lex.type = json_lexicon::END;
		}
		char c = m_stream.peek();
		while (isspace(c))
		{
			if (c == '\n')
				n_line++;
			c = next();
		}

		if (c == EOF)
		{
			next_lex.type = json_lexicon::END;
			return;
		}
		else if ((c == '{') || (c == ':') ||
				 (c == '}') || (c == ',') || (c == '[') || (c == ']'))
		{
			next_lex.lexicon.push_back(c);
			next_lex.type = json_lexicon::SYMBOL;

			c = next();
			return;
		}
		else if (isalpha(c))
		{
			next_lex.type = json_lexicon::IDENTIFIER;
			do
			{
				next_lex.lexicon.push_back(c);
				c = next();
			} while (isalnum(c));
			return;
		}
		else if (isdigit(c))
		{
			do
			{
				next_lex.lexicon.push_back(c);
				c = next();
			} while (isdigit(c));
			 if (c != '.')
			{
				next_lex.type = json_lexicon::INTEGER;
				return;
			}

			do
			{
				next_lex.lexicon.push_back(c);
				c = next();
			} while (isdigit(c));
			next_lex.type = json_lexicon::FLOAT;
			return;
		}
		else if (c == '"')
		{
			next_lex.type == json_lexicon::STRING;
			for (;;)
			{
				c = next();
				if (c == '"')
					break;
				if (c == '\\')
				{
					c = next();
					switch (c)
					{
					case '"':
						break;
					case '\\':
						next_lex.lexicon.push_back('\\');
						break;
					case '/':
						next_lex.lexicon.push_back('/');
						break;
					case 'b':
						next_lex.lexicon.push_back('b');
						break;
					case 'f':
						next_lex.lexicon.push_back('f');
						break;
					case 'r':
						next_lex.lexicon.push_back('r');
						break;
					case 't':
						next_lex.lexicon.push_back('t');
						break;
					case 'u':
						throw std::runtime_error("unicode strings not supported");
					default :
						throw std::runtime_error("unexpected escape sequence");
					}
				}
				else 
				{
					next_lex.lexicon.push_back(c);
				}
			}
			c = next();
			return;
		}
		else
		{
			c = next();
			throw std::runtime_error("unexpected character");
		}
	}
	public:
	json_lexer(TStream& stream) : m_stream(stream)
	{
		n_line = 1;
		read();
	}

	const json_lexicon& get() { return next_lex; }
	void advance() { read(); }
};

template <typename TStream>
json_lexer<TStream> get_json_lexer(TStream& stream)
{
	return json_lexer<TStream>(stream);
}
#endif /* __JSON_LEXER__ */