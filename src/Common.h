#pragma once

namespace Hangman { namespace Exception
{
	class Base
	{
	public:
		Base() = default;
		explicit Base(const char* message, int errcode = 0)
			: m_Message(message), m_ErrorCode(errcode) {}

		virtual const char* Message() const { return (m_Message ? m_Message : "Unknown exeption"); }
		virtual int ErrorCode() const { return m_ErrorCode; }

	private:
		const char* m_Message;
		int m_ErrorCode;
	};

	class PlayerSessionReaddition : Base
	{
	public:
		PlayerSessionReaddition()
			: Base("Player can only be added to the same game session once.") {}
	};

	class OnlyBeforeGameStarts : Base
	{
	public:
		OnlyBeforeGameStarts()
			: Base("Can only use the specified method before game session starts.") {}
	};

	class OnlyAfterGameStarts : Base
	{
	public:
		OnlyAfterGameStarts()
			: Base("Can only use the specified method after game session starts.") {}
	};	
	
	class InvalidLetter : Base
	{
	public:
		InvalidLetter()
			: Base("Specified letter is invalid.") {}
	};

	class WordIsUndefined : Base
	{
	public:
		WordIsUndefined()
			: Base("Word must be defined.") {}
	};
}}