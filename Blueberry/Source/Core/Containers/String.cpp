#include "String.h"

namespace Blueberry { namespace StringCalls_TCHAR {

	size_t Length(const CharT* string)
	{
		const CharT* first = string;
		while (*(string++));
		return string - first - 1;
	}

	bool Equals(const CharT* string_a, const CharT* string_b)
	{
		while (*(string_a++) && *(string_b++))
		{
			if (*string_a != *string_b)
				return false;
		}
		return (*string_a == *string_b);
	}

} }

namespace Blueberry {

	StringView::StringView(const StringView& other)
		: m_Data(other.m_Data)
		, m_Length(other.m_Length)
	{}

	StringView::StringView(const String& string)
		: m_Data(string.Data())
		, m_Length(string.Length())
	{}

	StringView::StringView(const CharT* string)
		: m_Data(string)
		, m_Length(StringCalls_TCHAR::Length(string))
	{}

	StringView::StringView(const CharT* string, SizeT string_length)
		: m_Data(string)
		, m_Length(string_length)
	{}

	StringView& StringView::operator=(const StringView& other)
	{
		m_Data = other.m_Data;
		m_Length = other.m_Length;
		return *this;
	}

	StringView& StringView::operator=(const String& string)
	{
		m_Data = string.Data();
		m_Length = string.Length();
		return *this;
	}

	StringView& StringView::operator=(const CharT* string)
	{

		m_Data = string;
		m_Length = StringCalls_TCHAR::Length(string);
		return *this;
	}

	String::String()
	{
		m_Data.SetSizeUninitialized(1);
		m_Data[0] = 0;
	}

	String::String(const String& other)
		: m_Data(other.m_Data)
	{
	}

	String::String(String&& other) noexcept
		: m_Data(Blueberry::Move(other.m_Data))
	{
	}

	String::String(StringView string_view)
	{
		m_Data.SetSizeUninitialized(string_view.Length() + 1);
		Memory::Copy(m_Data.Data(), string_view.Data(), m_Data.Size() * sizeof(CharT));
		m_Data.Back() = 0;
	}

	String::String(const CharT* string)
	{
		m_Data.SetSizeUninitialized(StringCalls_TCHAR::Length(string) + 1);
		Memory::Copy(m_Data.Data(), string, m_Data.Size() * sizeof(CharT));
	}

	String::String(const CharT* string, SizeT string_length)
	{
		m_Data.SetSizeUninitialized(string_length + 1);
		Memory::Copy(m_Data.Data(), string, m_Data.Size() * sizeof(CharT));
		m_Data.Back() = 0;
	}

	String::~String()
	{
		m_Data.SetSizeInternal(0);
	}

	Blueberry::String& String::operator=(const String& other)
	{
		m_Data = other.m_Data;
		return *this;
	}

	Blueberry::String& String::operator=(String&& other) noexcept
	{
		m_Data = Blueberry::Move(other.m_Data);
		return *this;
	}

	Blueberry::String& String::operator=(StringView string_view)
	{
		m_Data.SetSizeInternal(0);
		m_Data.SetSizeUninitialized(string_view.Length() + 1);
		Memory::Copy(m_Data.Data(), string_view.Data(), m_Data.Size() * sizeof(CharT));
		m_Data.Back() = 0;

		return *this;
	}

	Blueberry::String& String::operator=(const CharT* string)
	{
		m_Data.SetSizeInternal(0);
		m_Data.SetSizeUninitialized(StringCalls_TCHAR::Length(string) + 1);
		Memory::Copy(m_Data.Data(), string, m_Data.Size() * sizeof(CharT));

		return *this;
	}

}