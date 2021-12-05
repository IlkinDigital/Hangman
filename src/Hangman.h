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

        GameSession gs({ &p1 });

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
        }
    }
}
