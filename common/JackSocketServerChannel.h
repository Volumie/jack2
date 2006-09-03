/*
Copyright (C) 2004-2006 Grame  
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software 
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/

#ifndef __JackSocketServerChannel__
#define __JackSocketServerChannel__

#include "JackChannel.h"
#include "JackSocket.h"
#include "JackThread.h"
#include <poll.h>
#include <map>

namespace Jack
{

/*!
\brief JackServerChannel using sockets.
*/

class JackSocketServerChannel : public JackServerChannelInterface, public JackRunnableInterface
{

    private:

        JackServerSocket fRequestListenSocket;	// Socket to create request socket for the client
        JackThread*	fThread;					// Thread to execute the event loop
        JackServer*	fServer;
        pollfd*	fPollTable;
        bool fRebuild;
        std::map<int, std::pair<int, JackClientSocket*> > fSocketTable;

        int HandleRequest(int fd);
        void CreateClient();
        void AddClient(int fd, char* name, int* shared_engine, int* shared_client, int* shared_ports, int* result);
        void RemoveClient(int fd, int refnum);
        void KillClient(int fd);
        void BuildPoolTable();

    public:

        JackSocketServerChannel();
        virtual ~JackSocketServerChannel();

        int Open(JackServer* server);	// Open the Server/Client connection
        void Close();					// Close the Server/Client connection

        // JackRunnableInterface interface
        bool Execute();
};

} // end of namespace

#endif

