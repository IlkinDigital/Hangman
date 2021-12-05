#pragma once

#include "GameComponents.h"

/* 											
            * * * * * * * * * * * * * * * * * * *
            * * * * * * * * * * * * * * * * * * *
            * *                               * *
            * *                               *	*
            * *                             * * * *
            * *                           *			*
            * *                         *			  *
            * *                         *             *
            * *                         *			  *
            * *                           *			*
            * *                             * * * * 
            * *                               * *
            * *                             * * * *  
            * *                           * * * * * *
            * *                         * *   * *   * *
            * *                       * *     * *     * *
            * *                     * *  	  * *       * *
            * *                               * *		  
            * *                               * *
            * *                               * *
            * *                               * * 
            * *                               * *
            * *                             * * * *
            * *                           * *     * *
            * *                         * *		    * *
            * *                       * *    		  * *
            * *
            * *
    * * * * * * * * * *
    * * * * * * * * * *

*/

namespace Hangman
{
    void StartGame()
    {
        Player p1("Ilkin");

        GameSession gs({ p1 });

        while (gs.IsSessionActive())
        {

        }
    }
}
