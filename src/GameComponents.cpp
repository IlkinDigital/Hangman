#include "GameComponents.h"

namespace Hangman
{
    int Player::s_UUID = 0;

    const char* GameSession::s_DictionaryPath = "res/Dict.txt";
    size_t const GameSession::s_Stages = 10;
    char GameSession::s_DrawingSymbol = '*';

    void GameSession::Init()
    {
        m_AvailableLetters = ALPHABET;
        m_HangmanStage = Stage::None;
        m_GameStartFlag = false;

        m_Players.clear();

        ParseDictionary();
    }
    void GameSession::AddPlayer(Player* player)
    {
        if (m_GameStartFlag)
            throw Exception::OnlyBeforeGameStarts();

        if (!IsInSession(*player))
            throw Exception::PlayerSessionReaddition();

        m_Players.push_back(player);
    }
    std::string GameSession::GetRandomWord()
    {
        return "testing";
    }
    size_t GameSession::ParseDictionary() const
    {
        size_t counter = 0;

        std::ifstream ifile;
        
        // TODO: Handle unable to open file error
        ifile.open(s_DictionaryPath, std::ios::in);

        std::stringstream ss;
        std::string line;
        while (std::getline(ifile, line))
        {
            if (line.size() > 4)
            {
                line[0] = std::tolower(line[0]);
                ss << line << '\n';
                counter++;
            }
        }

        std::ofstream ofile;

        // TODO: Handle unable to open file error
        ofile.open(s_DictionaryPath, std::ios::out);

        ofile << ss.rdbuf();

        ifile.close();
        ofile.close();

        return counter;
    }
    bool GameSession::Guess(char letter)
    {
        if (!IsLetterValid(letter))
            throw Exception::InvalidLetter();

        bool guessCheck = false;
                
        for (size_t i = 0; i < m_Word.size(); i++)
        {
            if (m_Word[i] == letter)
            {
                m_View[i] = true;
                m_AvailableLetters[letter - 'a'] = 0;
                guessCheck = true;
            }
        }

        return guessCheck ? true : IncrementStage();
    }
    bool GameSession::IncrementStage()
    {
        if (m_HangmanStage == Stage::RightLeg)
        {
            Stop();
            return false;
        }

        m_HangmanStage = (Stage)((int)m_HangmanStage + 1);
    }
    void GameSession::SetRandomWord()
    {
        m_Word = GetRandomWord();
        m_View.resize(m_Word.size());
    }
    bool GameSession::IsInSession(const Player& player) const
    {
        for (const auto& item : m_Players)
            if (*item == player)
                return true;

        return false;
    }

    bool GameSession::IsLetterValid(char letter) const
    {
        if (letter < 'a' || letter > 'z')
            return false;

        bool check = false;
        for (const auto& item : m_AvailableLetters)
            if (item == letter)
                check = true;

        return check;
    }

    void GameSession::Start()
    {
        if (m_Word.empty())
            throw Exception::WordIsUndefined();
        // TODO: Add an m_View check

        m_GameStartFlag = true;
    }

    bool GameSession::WinCheck() const
    {
        for (const auto& item : m_View)
            if (item)
                return false;
        return true;
    }

    void GameSession::DrawHangman() const
    {
        if (!m_GameStartFlag)
            throw Exception::OnlyAfterGameStarts();

        char s[(size_t)s_Stages]{}; // Stage symbols

        for (size_t i = 0; i < s_Stages; i++)
        {
            if (i + 1 <= (size_t)m_HangmanStage)
                s[i] = s_DrawingSymbol;
            else
                s[i] = ' ';
        }

        std::cout <<
            
            s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << '\n' <<
            s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2] << ' ' << s[2]<< ' ' << s[2] << '\n' <<
            s[1] << ' ' << s[1] << "                           " << s[3] << ' ' << s[3] << '\n' <<
            s[1] << ' ' << s[1] << "                           " << s[3] << ' ' << s[3] << '\n' <<
            s[1] << ' ' << s[1] << "                         " << s[4] << ' ' << s[4] << ' ' << s[4] << ' ' << s[4] << '\n' <<
            s[1] << ' ' << s[1] << "                       " << s[4] << "         " << s[4] << '\n' <<
            s[1] << ' ' << s[1] << "                     " << s[4] << "             " << s[4] << '\n' <<
            s[1] << ' ' << s[1] << "                     " << s[4] << "             " << s[4] << '\n' <<
            s[1] << ' ' << s[1] << "                     " << s[4] << "             " << s[4] << '\n' <<
            s[1] << ' ' << s[1] << "                       " << s[4] << "         " << s[4] << '\n' <<
            s[1] << ' ' << s[1] << "                         " << s[4] << ' ' << s[4] << ' ' << s[4] << ' ' << s[4] << '\n' <<
            s[1] << ' ' << s[1] << "                         " << s[6] << ' ' << s[5] << ' ' << s[5] << ' ' << s[7] << '\n' <<
            s[1] << ' ' << s[1] << "                       " << s[6] << ' ' << s[6] << ' ' << s[5] << ' ' << s[5] << ' ' << s[7] << ' ' << s[7] << '\n' <<
            s[1] << ' ' << s[1] << "                     " << s[6] << ' ' << s[6] << "   " << s[5] << ' ' << s[5] << "   " << s[7] << ' ' << s[7] << '\n' <<
            s[1] << ' ' << s[1] << "                   " << s[6] << ' ' << s[6] << "     " << s[5] << ' ' << s[5] << "     " << s[7] << ' ' << s[7] << '\n' <<
            s[1] << ' ' << s[1] << "                 " << s[6] << ' ' << s[6] << "       " << s[5] << ' ' << s[5] << "       " << s[7] << ' ' << s[7] << '\n' <<
            s[1] << ' ' << s[1] << "                           " << s[5] << ' ' << s[5] << '\n' <<
            s[1] << ' ' << s[1] << "                           " << s[5] << ' ' << s[5] << '\n' <<
            s[1] << ' ' << s[1] << "                           " << s[5] << ' ' << s[5] << '\n' <<
            s[1] << ' ' << s[1] << "                           " << s[5] << ' ' << s[5] << '\n' <<
            s[1] << ' ' << s[1] << "                           " << s[5] << ' ' << s[5] << '\n' <<
            s[1] << ' ' << s[1] << "                         " << s[8] << ' ' << s[8] << ' ' << s[9] << ' ' << s[9] << '\n' <<
            s[1] << ' ' << s[1] << "                       " << s[8] << ' ' << s[8] << "     " << s[9] << ' ' << s[9] << '\n' <<
            s[1] << ' ' << s[1] << "                     " << s[8] << ' ' << s[8] << "         " << s[9] << ' ' << s[9] << '\n' <<
            s[1] << ' ' << s[1] << "                   " << s[8] << ' ' << s[8] << "             " << s[9] << ' ' << s[9] << '\n' <<
            s[1] << ' ' << s[1] << '\n' <<
            s[1] << ' ' << s[1] << '\n' <<
            s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << '\n' <<
            s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << ' ' << s[0] << std::endl;
    }

    void GameSession::DrawWord() const
    {
        for (size_t i = 0; i < m_View.size(); i++)
        {
            if (m_View[i])
        }
    }

    void GameSession::DrawAvailableLetters() const
    {
        if (!m_GameStartFlag)
            throw Exception::OnlyAfterGameStarts();
    }

    void GameSession::Stop()
    {
        if (!m_GameStartFlag)
            throw Exception::OnlyAfterGameStarts();

        m_GameStartFlag = false;
        m_AvailableLetters = ALPHABET;
        m_Word.clear();
        m_View.clear();
        m_HangmanStage = Stage::None;
    }

    char Player::RequestLetter() const
    {
        char letter;
        std::cout << "Enter the letter you want to guess: ";
        std::cin >> letter;

        // TODO: Add std::cin crash check

        return letter;
    }

}