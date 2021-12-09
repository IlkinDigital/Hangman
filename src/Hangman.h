#pragma once

#include "GameComponents.h"

/* 											
                              
            * * * * * * * * * * * * * * * * * *
            *                                 * 
            *                                 * 
            *                              *  *  *
            *                            *		   *
            *                          *			 *
            *                          *             *
            *                          *			 *
            *                            *		   *
            *                              *  *  * 
            *                                 *
            *                                 *   
            *                              *  *  *
            *                            *    *    *
            *                          *      *      *
            *                        *        *        *
            *                                 *		  
            *                                 *
            *                               *   *
            *                             *       *
            *                           *		    *
            *                         *    		      *
            * 
            * 
    * * * * * * * * *

*/

namespace Hangman
{
    void StartGame()
    {
        Player p1("Ilkin");
        Player p2("Elvin");

        GameSession gs({ &p1, &p2 });

        gs.SetRandomWord();

        gs.Start();

        bool hmStatus = true;

        while (gs.IsSessionActive())
        {
            system("cls");

            gs.DrawHangman();

            std::cout << std::endl;
            gs.DrawWord();

            std::cout << std::endl;
            gs.DrawAvailableLetters();

            std::cout << std::endl;

            
            if (!hmStatus)
            {
                std::cout << "You lost! The word was " << gs.GetWord() <<'!' << std::endl;
                gs.Stop();
            }
            else if (gs.WinCheck())
            {
                std::cout << "You successfuly saved a man from killing himself! Congratulations!" << std::endl;
                gs.Stop();
            }
            else
            {
                hmStatus = gs.SmartGuess();
            }

            std::cout << "Press enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}
