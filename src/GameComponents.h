#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <initializer_list>

#include "Common.h"

#define ALPHABET { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' }

namespace Hangman
{

	class Player
	{
	public:
		Player(const std::string& name)
			: m_UUID(s_UUID++), m_Name(name) {}
		~Player() = default;

		char RequestLetter() const;

		bool operator == (const Player& other) const { return m_UUID == other.m_UUID; }
	private:
		static int s_UUID; // Universally unique identifier
	private:
		int m_UUID;
		std::string m_Name;
	};

	class Word
	{
	public:
		Word() = default;
		Word(const std::string& str) { SetWord(str); }

		size_t Size() const { return m_Word.size(); }
		bool IsEmpty() const { return m_Word.empty() || m_View.empty(); }

		void SetWord(const std::string& word);

		void EnableView(size_t index)  { m_View[index] = true;  }
		void DisableView(size_t index) { m_View[index] = false; }

		char At(size_t index) const { return m_Word[index]; }
		bool GetView(size_t index) const { return m_View[index]; }

		std::string GetWord() const { return m_Word; }

		void Clear() { m_Word.clear(); m_View.clear(); }

	private:
		std::string m_Word;
		std::vector<bool> m_View;
	};

	class GameSession
	{
	public:
		enum class Stage { None = 0, Base, Pole1, Pole2, Rope, 
						   Head, Body, LeftArm, RightArm, LeftLeg, RightLeg };

		static size_t const s_Stages;
		static char s_DrawingSymbol;
	public:
		static void SetDictionaryPath(const char* filepath) { s_DictionaryPath = filepath; }

		static const char* GetDictionaryPath()   { return s_DictionaryPath;  }
		static size_t GetDictionaryWordCounter() { return s_DictionaryWords; }

		static std::string GetRandomWord();
	public:
		GameSession(std::initializer_list<Player*> playerlist)
		{
			Init();

			for (const auto& item : playerlist)
			{
				m_Players.push_back(item);
			}
		}

		void Init();

		void SetRandomWord();

		std::string GetWord() const { return m_Word.GetWord(); }

		bool IsInSession(const Player& player) const;
		bool IsSessionActive() const { return m_GameStarted; }
		bool IsLetterValid(char letter) const;

		void Start();

		void NextPlayer();

		bool SmartGuess();

		bool WinCheck() const;

	public: // After game starts

		virtual void DrawHangman() const;
		virtual void DrawWord() const;	
		virtual void DrawAvailableLetters() const;

		void Stop();

	public: // Before game starts

		void AddPlayer(Player* player);
		void RemovePlayer(Player* player);

	private:
		static const char* s_DictionaryPath;
		static size_t s_DictionaryWords;
	private:
		// Parses the dictionary to valid words and returns the number of words
		size_t ParseDictionary() const;

		bool Guess(char letter);

		bool IncrementStage();
	private:
		std::vector<Player*> m_Players;
		size_t m_CurrentPlayerIndex;
		std::array<char, 26> m_AvailableLetters;
		Word m_Word;
		Stage m_HangmanStage;
		bool m_GameStarted;
	};

}
